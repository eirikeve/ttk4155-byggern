#include "sdk_common.h"
#include "ble_srv_common.h"
#include "ble_spi.h"
#include <string.h>
#include "nrf_gpio.h"
#include "boards.h"

#include "sdk_config.h"

#include "app_error.h"
#include "nrf_drv_spis.h"

#define SPIS_INSTANCE 0 /**< SPIS instance index. */
static const nrf_drv_spis_t spis = NRF_DRV_SPIS_INSTANCE(SPIS_INSTANCE);/**< SPIS instance. */

static uint8_t       m_tx_buf[2] = {0, 0};                         /**< TX buffer. */
static uint8_t       m_rx_buf[2];                        /**< RX buffer. */
static const uint8_t m_tx_length = sizeof(m_tx_buf);        /**< Transfer length. */
static const uint8_t m_rx_length = sizeof(m_rx_buf);        /**< Receive length. */

static volatile bool spis_xfer_done; /**< Flag used to indicate that SPIS instance completed the transfer. */

void spis_event_handler(nrf_drv_spis_event_t event)
{
    if (event.evt_type == NRF_DRV_SPIS_XFER_DONE)
    {
        spis_xfer_done = true;
    }
}

uint32_t ble_spi_init(ble_spi_t * p_spi, const ble_spi_init_t * p_spi_init)
{
    if (p_spi == NULL || p_spi_init == NULL)
    {
        return NRF_ERROR_NULL;
    }

    uint32_t   err_code;
    ble_uuid_t ble_uuid;

    // Initialize service structure
    p_spi->evt_handler               = p_spi_init->evt_handler;
    p_spi->conn_handle               = BLE_CONN_HANDLE_INVALID;

    // Add Custom Service UUID
    ble_uuid128_t base_uuid = {CUSTOM_SERVICE_UUID_BASE};
    err_code =  sd_ble_uuid_vs_add(&base_uuid, &p_spi->uuid_type);
    VERIFY_SUCCESS(err_code);
    
    ble_uuid.type = p_spi->uuid_type;
    ble_uuid.uuid = CUSTOM_SERVICE_UUID;

    // Add the Custom Service
    err_code = sd_ble_gatts_service_add(BLE_GATTS_SRVC_TYPE_PRIMARY, &ble_uuid, &p_spi->service_handle);
    if (err_code != NRF_SUCCESS)
    {
        return err_code;
    }

    // Initialize the spi
    nrf_drv_spis_config_t spis_config = NRF_DRV_SPIS_DEFAULT_CONFIG;
    spis_config.csn_pin               = APP_SPIS_CS_PIN;
    spis_config.miso_pin              = APP_SPIS_MISO_PIN;
    spis_config.mosi_pin              = APP_SPIS_MOSI_PIN;
    spis_config.sck_pin               = APP_SPIS_SCK_PIN;

    // Initialize the tx buffer
    m_tx_buf[0] = 0;
    spis_xfer_done = true;
    err_code = nrf_drv_spis_init(&spis, &spis_config, spis_event_handler);
    err_code = nrf_drv_spis_buffers_set(&spis, m_tx_buf, m_tx_length, m_rx_buf, m_rx_length);
    if (err_code != NRF_SUCCESS)
    {
        return err_code;
    }

    // Add Custom Value characteristic
    return custom_value_char_add(p_spi, p_spi_init);
}

    /**@brief Function for adding the Custom Value characteristic.
 *
 * @param[in]   p_spi        Custom Service structure.
 * @param[in]   p_spi_init   Information needed to initialize the service.
 *
 * @return      NRF_SUCCESS on success, otherwise an error code.
 */
static uint32_t custom_value_char_add(ble_spi_t * p_spi, const ble_spi_init_t * p_spi_init)
{
    uint32_t            err_code;
    ble_gatts_char_md_t char_md;
    ble_gatts_attr_md_t cccd_md;
    ble_gatts_attr_t    attr_char_value;
    ble_uuid_t          ble_uuid;
    ble_gatts_attr_md_t attr_md;

    memset(&cccd_md, 0, sizeof(cccd_md));

    //  Read  operation on Cccd should be possible without authentication.
    BLE_GAP_CONN_SEC_MODE_SET_OPEN(&cccd_md.read_perm);
    BLE_GAP_CONN_SEC_MODE_SET_OPEN(&cccd_md.write_perm);
    
    cccd_md.vloc       = BLE_GATTS_VLOC_STACK;

    memset(&char_md, 0, sizeof(char_md));

    char_md.char_props.read   = 1;
    char_md.char_props.write  = 1;
    char_md.char_props.notify = 1; 
    char_md.p_char_user_desc  = NULL;
    char_md.p_char_pf         = NULL;
    char_md.p_user_desc_md    = NULL;
    char_md.p_cccd_md         = &cccd_md; 
    char_md.p_sccd_md         = NULL;
		
    memset(&attr_md, 0, sizeof(attr_md));

    attr_md.read_perm  = p_spi_init->custom_value_char_attr_md.read_perm;
    attr_md.write_perm = p_spi_init->custom_value_char_attr_md.write_perm;
    attr_md.vloc       = BLE_GATTS_VLOC_STACK;
    attr_md.rd_auth    = 0;
    attr_md.wr_auth    = 0;
    attr_md.vlen       = 0;

    ble_uuid.type = p_spi->uuid_type;
    ble_uuid.uuid = CUSTOM_VALUE_CHAR_UUID;

    memset(&attr_char_value, 0, sizeof(attr_char_value));

    attr_char_value.p_uuid    = &ble_uuid;
    attr_char_value.p_attr_md = &attr_md;
    attr_char_value.init_len  = sizeof(uint8_t);
    attr_char_value.init_offs = 0;
    attr_char_value.max_len   = sizeof(uint8_t);

    err_code = sd_ble_gatts_characteristic_add(p_spi->service_handle, &char_md,
                                               &attr_char_value,
                                               &p_spi->custom_value_handles);
    if (err_code != NRF_SUCCESS)
    {
        return err_code;
    }

    return NRF_SUCCESS;
}


/**@brief Function for handling the Connect event.
 *
 * @param[in]   p_spi       Custom Service structure.
 * @param[in]   p_ble_evt   Event received from the BLE stack.
 */
static void on_connect(ble_spi_t * p_spi, ble_evt_t const * p_ble_evt)
{
    p_spi->conn_handle = p_ble_evt->evt.gap_evt.conn_handle;
    ble_spi_evt_t evt;

    evt.evt_type = BLE_CUS_EVT_CONNECTED;

    p_spi->evt_handler(p_spi, &evt);

}

/**@brief Function for handling the Disconnect event.
 *
 * @param[in]   p_spi       Custom Service structure.
 * @param[in]   p_ble_evt   Event received from the BLE stack.
 */
static void on_disconnect(ble_spi_t * p_spi, ble_evt_t const * p_ble_evt)
{
    UNUSED_PARAMETER(p_ble_evt);
    p_spi->conn_handle = BLE_CONN_HANDLE_INVALID;
}

static void on_write(ble_spi_t * p_spi, ble_evt_t const * p_ble_evt)
{
ret_code_t err_code;

    ble_gatts_evt_write_t * p_evt_write = &p_ble_evt->evt.gatts_evt.params.write;
    

    // Check if the handle passed with the event matches the Custom Value Characteristic handle.
    if (p_evt_write->handle == p_spi->custom_value_handles.value_handle && spis_xfer_done)
    {
        spis_xfer_done = false;
        m_tx_buf[0] = p_evt_write->data[0];
        err_code = nrf_drv_spis_buffers_set(&spis, m_tx_buf, m_tx_length, m_rx_buf, m_rx_length);
        APP_ERROR_CHECK(err_code);
        // Put specific task here. 
        nrf_gpio_pin_toggle(LED_4);
    }
}


void ble_spi_on_ble_evt( ble_evt_t const * p_ble_evt, void * p_context)
{
    ble_spi_t * p_spi = (ble_spi_t *) p_context;
    
    if (p_spi == NULL || p_ble_evt == NULL)
    {
        return;
    }
    
    switch (p_ble_evt->header.evt_id)
    {
        case BLE_GAP_EVT_CONNECTED:
            on_connect(p_spi, p_ble_evt);
            break;

        case BLE_GAP_EVT_DISCONNECTED:
            on_disconnect(p_spi, p_ble_evt);
            break;
        
        case BLE_GATTS_EVT_WRITE:
            on_write(p_spi, p_ble_evt);

        default:
            // No implementation needed.
            break;
    }
}

uint32_t ble_spi_custom_value_update(ble_spi_t * p_spi, uint8_t custom_value){
    if (p_spi == NULL)
    {
        return NRF_ERROR_NULL;
    }

    uint32_t err_code = NRF_SUCCESS;
    ble_gatts_value_t gatts_value;

    // Initialize value struct.
    memset(&gatts_value, 0, sizeof(gatts_value));

    gatts_value.len     = sizeof(uint8_t);
    gatts_value.offset  = 0;
    gatts_value.p_value = &custom_value;

    // Update database.
    err_code = sd_ble_gatts_value_set(p_spi->conn_handle,
                                        p_spi->custom_value_handles.value_handle,
                                        &gatts_value);
    if (err_code != NRF_SUCCESS)
    {
        return err_code;
    }

    // Send value if connected and notifying.
    if ((p_spi->conn_handle != BLE_CONN_HANDLE_INVALID)) 
    {
        ble_gatts_hvx_params_t hvx_params;

        memset(&hvx_params, 0, sizeof(hvx_params));

        hvx_params.handle = p_spi->custom_value_handles.value_handle;
        hvx_params.type   = BLE_GATT_HVX_NOTIFICATION;
        hvx_params.offset = gatts_value.offset;
        hvx_params.p_len  = &gatts_value.len;
        hvx_params.p_data = gatts_value.p_value;

        err_code = sd_ble_gatts_hvx(p_spi->conn_handle, &hvx_params);
    }
    else
    {
        err_code = NRF_ERROR_INVALID_STATE;
    }

    return err_code;
}

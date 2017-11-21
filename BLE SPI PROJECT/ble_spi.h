#ifndef BLE_CUS_H
#define BLE_CUS_H

//Custom UUID
//0b0d8fa6-4bd3-4efd-95a2-54b3696d7026

/**@brief   Macro for defining a ble_spi instance.
 *
 * @param   _name   Name of the instance.
 * @hideinitializer
 */
/**@brief   Macro for defining a ble_hrs instance.
 *
 * @param   _name   Name of the instance.
 * @hideinitializer
 */
#define BLE_CUS_DEF(_name)                                                                          \
static ble_spi_t _name;                                                                             \
NRF_SDH_BLE_OBSERVER(_name ## _obs,                                                                 \
                     BLE_HRS_BLE_OBSERVER_PRIO,                                                     \
                     ble_spi_on_ble_evt, &_name)


#define CUSTOM_SERVICE_UUID_BASE { 0x26, 0x70, 0x6d, 0x69, 0xb3, 0x54, 0xa2, 0x95, \
                                     0xfd, 0x4e, 0xd3, 0x4b, 0xa6, 0x8f, 0x0d, 0x0b }

#define CUSTOM_SERVICE_UUID 0x1400
#define CUSTOM_VALUE_CHAR_UUID 0x1401


/**@brief Custom Service event type. */
typedef enum
{
    BLE_CUS_EVT_NOTIFICATION_ENABLED,                             /**< Custom value notification enabled event. */
    BLE_CUS_EVT_NOTIFICATION_DISABLED,                            /**< Custom value notification disabled event. */
    BLE_CUS_EVT_DISCONNECTED,
    BLE_CUS_EVT_CONNECTED
} ble_spi_evt_type_t;

/**@brief Custom Service event. */
typedef struct
{
    ble_spi_evt_type_t evt_type;                                  /**< Type of event. */
} ble_spi_evt_t;

// Forward declaration of the ble_spi_t type.
typedef struct ble_spi_s ble_spi_t;

/**@brief Custom Service event handler type. */
typedef void (*ble_spi_evt_handler_t) (ble_spi_t * p_spi, ble_spi_evt_t * p_evt);


/**@brief Custom Service init structure. This contains all options and data needed for
 *        initialization of the service.*/
typedef struct
{
    ble_spi_evt_handler_t         evt_handler;                    /**< Event handler to be called for handling events in the Custom Service. */
    uint8_t                       initial_custom_value;           /**< Initial custom value */
    ble_srv_cccd_security_mode_t  custom_value_char_attr_md;     /**< Initial security level for Custom characteristics attribute */
} ble_spi_init_t;

/**@brief Custom Service structure. This contains various status information for the service. */
struct ble_spi_s
{
    ble_spi_evt_handler_t         evt_handler;                    /**< Event handler to be called for handling events in the Custom Service. */
    uint16_t                      service_handle;                 /**< Handle of Custom Service (as provided by the BLE stack). */
    ble_gatts_char_handles_t      custom_value_handles;           /**< Handles related to the Custom Value characteristic. */
    uint16_t                      conn_handle;                    /**< Handle of the current connection (as provided by the BLE stack, is BLE_CONN_HANDLE_INVALID if not in a connection). */
    uint8_t                       uuid_type; 
};








/**@brief Function for initializing the Custom Service.
 *
 * @param[out]  p_spi       Custom Service structure. This structure will have to be supplied by
 *                          the application. It will be initialized by this function, and will later
 *                          be used to identify this particular service instance.
 * @param[in]   p_spi_init  Information needed to initialize the service.
 *
 * @return      NRF_SUCCESS on successful initialization of service, otherwise an error code.
 */
uint32_t ble_spi_init(ble_spi_t * p_spi, const ble_spi_init_t * p_spi_init);

/**@brief Function for adding the Custom Value characteristic.
 *
 * @param[in]   p_spi        Custom Service structure.
 * @param[in]   p_spi_init   Information needed to initialize the service.
 *
 * @return      NRF_SUCCESS on success, otherwise an error code.
 */
static uint32_t custom_value_char_add(ble_spi_t * p_spi, const ble_spi_init_t * p_spi_init);

/**@brief Function for handling the Application's BLE Stack events.
 *
 * @details Handles all events from the BLE stack of interest to the Battery Service.
 *
 * @note 
 *
 * @param[in]   p_ble_evt  Event received from the BLE stack.
 * @param[in]   p_context  Custom Service structure.
 */
void ble_spi_on_ble_evt( ble_evt_t const * p_ble_evt, void * p_context);

/**@brief Function for updating the custom value.
 *
 * @details The application calls this function when the cutom value should be updated. If
 *          notification has been enabled, the custom value characteristic is sent to the client.
 *
 * @note 
 *       
 * @param[in]   p_spi          Custom Service structure.
 * @param[in]   Custom value 
 *
 * @return      NRF_SUCCESS on success, otherwise an error code.
 */

uint32_t ble_spi_custom_value_update(ble_spi_t * p_spi, uint8_t custom_value);

#endif
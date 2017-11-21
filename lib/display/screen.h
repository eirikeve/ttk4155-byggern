#pragma once
#include "oled.h"
#include "../fonts/fonts.h"
#include "../utilities/utilities.h"
#include <stdlib.h>
#include <stdio.h>
#include <util/delay.h>


/**
 * Specifies subscreen positioning/orientation relative to superscreen (parent)
 * LEFT indicates that the subscreen is left of its parent/superscreen.
 **/
enum Orientation
{
  LEFT,
  RIGHT,
  UPPER,
  LOWER
};

/**
 * Screen class implements writing chars, strings, and bytes (pages) to SRAM.
 * Displays the SRAM content on the physical screen by using the OLED class to write to screen.
 * The SRAM memory areas consists of two 1024 byte sequences, each byte representing a page in the OLED.
 * Can split the physical screen into multiple logical screens ("subscreens"), which are
 * addressed. individually.
 * Supports dual buffering to SRAM using the timer/interrupt-based ScreenHandler class, 
 * but this functionality is not yet fully implemented. (Still some bugs.) 
 * Memory addresses for the start of the two SRAM vram areas is specified in utilities/utilities.h

 **/
class Screen
{

private:
  // OLED for writing from SRAM to the physical screen
  OLED oled;
  // Pointer to the start of the currently used SRAM
  volatile uint8_t *vram;
  // Flag which is used when using ScreenHandler.
  bool ready_to_render;

  // Pointer to the Screen's superscreen (parent)
  Screen *superScreen;
  // Pointer to the Screen's subscreen (child)
  Screen *subScreen;

  
  // The page we're currently writing to
  uint8_t loc_page;
  // The column we're currently writing to
  uint8_t loc_col;

  // Flag which indicates whether this screen should display borders to neighbouring screens/subscreens
  bool has_border_lines;

  // Width of the font we use (PROGMEM font5)
  const uint8_t character_size = 5;

  // The page where this screen starts (inclusive)
  uint8_t page0;
  // The page where this screen ends (non-inclusive)
  uint8_t page1;
  // The column where this screen starts (inclusive)
  uint8_t col0;
  // The column where this screen ends (non-inclusive)
  uint8_t col1;

  // page1-page0
  uint8_t pagesize;
  // col1-col0
  uint8_t colsize;


private:
  /**
   * Switches the current vram pointer to another memory area.
   * If the specified buffer is not either of the two reserved SRAM areas,
   * it sets the vram pointer to (uint8_t*)AVR_VRAM_2
   * Used by ScreenHandler for dual buffering.
   * @param buffer: pointer to start of SRAM buffer
   **/
  void changeBufferTo(uint8_t * buffer = (uint8_t*)AVR_VRAM_1);
  
  /**
   * Copies the contents of the other SRAM area to the currently used SRAM area.
   * Used by ScreenHandler for dual buffering.
   **/
  void copyVRAMtoCurrentBuffer();
  
public:

  // Default Constructor
  Screen();
  /**
   * Constructor which creates a Screen object as a subscreen of another screen.
   * @param superscreen: pointer to another screen object
   * @param sz: Size of this resulting subscreen - represents pages or columns depending on the param o.
   * @param o: Orientation indicationg where this screen will be in relation to the superscreen
   **/
  Screen(Screen *superscreen, uint8_t sz, Orientation o);
  
  /**
   * Destructor implemented due to subscreen functionality.
   * When deleted, a Screen also deletes its subscreens.
   * In addition, it sets its superscreen's page/col variables correctly, and removes 
   * references to itself.
   **/
  ~Screen();

  /**
   * Adds Screen object as a subscreen of another screen.
   * @param superscreen: pointer to another screen object
   * @param sz: Size of this resulting subscreen - represents pages or columns depending on the param o.
   * @param o: Orientation indicationg where this screen will be in relation to the superscreen
   **/
  void addSubScreen(Screen *subscreen, uint8_t sz, Orientation o);

  /**
   * Removes this screen's subscreen, and also calls removeSubScreen on the subscreen.
   * Sets this screen's page/col variables correctly, and also sets the subscreen's page/col variables to 0.
   * (Need to re-add the subscreen in order to draw to it)
   **/
  void removeSubScreen();

  /**
   * Sets the has_border_lines flag to true, and calls updateBorderLines()
   **/
  void addBorderLines();

  /**
   * Writes border lines to SRAM, or removes them, depending on has_border_lines
   * The rightmost column and bottom pixel row of each screen is used for border lines,
   * if those are not the bottom pixel row or the rightmost pixel column of the physical display
   **/
  void updateBorderLines();

    /**
   * Sets the has_border_lines flag to true, and calls updateBorderLines()
   **/
  void removeBorderLines();

  // Returns true if this screen has a subscreen
  bool hasSubScreen() {return (subScreen ? true : false);}

  // Changes loc_page to page
  void goToPage(uint8_t page);
  // Changes loc_col to col
  void goToColumn(uint8_t col);
  // Changes loc_page and loc_col to page, col, respectiviely
  void goTo(uint8_t page, uint8_t col);
  // This is where we start writing.
  inline void goToStart() {goTo(0,1);}
  
  /**
   * Writes a single char to the SRAM buffer, using write().
   * Auto-increments loc_col and loc_page. Inserts small spacing between characters.
   * Fonts used are taken from PROGMEM font5.
   * Also supports \n character.
   * @param c ASCII character
   **/
  void writeChar(unsigned char c);

  /**
   * Calls writeChar until \0 character is read, or until it has been called 255 times.
   * @param string: C-string with \0 eof character
   **/
  void writeString(char *string);

  /**
   * Writes a byte to the SRAM. Auto-increments loc_col
   * @param c: A byte, where 1 represents a pixel turned on
   **/
  void write(uint8_t c);

  /**
   * Writes v to the whole display
   * @param v: A byte, where 1 represents a pixel turned on
   **/
  void fill(uint8_t v);

  // Clears the display and sets loc_page, loc_col, to their start values
  void clear();

  /**
   * Function used to flag that a screen is ready to be rendered when using ScreenHandler.
   **/
  void flagReadyToRender();

  /**
   * Writes the whole SRAM content of buffer to the physical display.
   * @param buffer: Pointer to SRAM memory area start.
   **/
  void render(uint8_t * buffer = (uint8_t*)AVR_VRAM_1);

  // Needs access to private methods changeBufferTo and copyVRAMtoCurrentBuffer for dual buffering
  friend class ScreenHandler;


};
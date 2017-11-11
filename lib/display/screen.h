#pragma once
#include "oled.h"
#include "../fonts/fonts.h"
#include "../utilities/utilities.h"
extern "C" {
  #include <stdlib.h>
  }


enum Orientation
{
  LEFT,
  RIGHT,
  UPPER,
  LOWER
};

class Screen
{

private:
  OLED oled;
  static uint8_t *vram;
  static bool ready_to_render;

  Screen *superScreen;
  Screen *subScreen;

  

  uint8_t loc_page;
  uint8_t loc_col;

  bool has_border_lines;


  const uint8_t character_size = 5;


private:
  void changeBufferTo(uint8_t * buffer = (uint8_t*)AVR_VRAM_1);
  void copyVRAMtoCurrentBuffer();
  
public:
  uint8_t page0;
  uint8_t page1;
  uint8_t col0;
  uint8_t col1;

  uint8_t pagesize;
  uint8_t colsize;

  Screen();
  Screen(Screen *superscreen, uint8_t sz, Orientation o);
  ~Screen();
  void addSubScreen(Screen *subscreen, uint8_t sz, Orientation o);
  void removeSubScreen();
  void addBorderLines();
  void updateBorderLines();
  void removeBorderLines();
  bool hasSubScreen() {return (subScreen ? true : false);}
  void goToPage(uint8_t page);
  void goToColumn(uint8_t col);
  void goTo(uint8_t page, uint8_t col);
  void writeChar(unsigned char c);
  void writeString(char *string);
  void write(uint8_t c);
  void fill(uint8_t v);
  void clear();
  void selfTest();
  void flagReadyToRender();
  void render(uint8_t * buffer);

  friend class ScreenHandler;


};
// Joystick class for use in TTK4155
// Written by Håvard Borge, Eirik Vesterkjær
// 18/09/2017

#include "../adc/adc.h"
// #include "../utilities/bmath.h"
#include <stdint.h>

enum Direction
{
  NORTH = 0,
  SOUTH = 1,
  WEST = 2,
  EAST = 3,
  NORTH_WEST = 4,
  NORTH_EAST = 5,
  SOUTH_WEST = 6,
  SOUTH_EAST = 7,
  NEUTRAL = 8
};

class Joystick
{
public:
  // Value read from ADC at joystick max y position
  uint8_t x_max;
  // Value read from ADCadc.h at joystick max x position
  uint8_t y_max;
  // Value read from ADC at joystick min y position
  uint8_t x_min;
  // Value read from ADC at joystick min x position
  uint8_t y_min;
  // Value read from ADC at joystick centre x
  uint8_t centre_x;
  // Value read from ADC at joystick centre y
  uint8_t centre_y;
  // Value with which the joystick can be away from the centre in a dir before registering as that dir
  uint8_t threshold;
  // Scale factor for reading from ADC, multiplied by 100.

  int8_t x;
  uint8_t rawX;

  int8_t y;
  uint8_t rawY;

  ADC adc;

public:
  Joystick(const uint8_t threshold);
  Direction read(int8_t *x, int8_t *y);
  int8_t readX();
  int8_t readY();
  Direction getDir() const;

private:
  void autoCalibrate();

  void formatValue(uint8_t raw, int8_t *result, uint8_t *center, uint8_t *threshold);
  uint8_t readRawX();
  uint8_t readRawY();
};
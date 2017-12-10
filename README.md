# Byggern

Project repository for TTK 4155 - Embedded and Industrial Computer Systems Design, Autumn 2017.  

Group: Håvard Borge (__Howiezi__ @ GitHub), Åsmund Eek (__aasmune__ @ GitHub), Eirik Vesterkjær (__eirikeve__ @ GitHub)  

https://github.com/eirikeve/Byggern.git

We forgot to take a nice top-down picture of the project - so here's an image showing the corner of our breadboard while we were in the process of tearing everything apart.
![Breadboard](/images/byggern_img_readme.png)

## Project Overview

We built an embedded computer system for controlling a "ping-pong"-like game. The computer consisted of two separate MCUs communicating over CAN, along with a set of external components, and the physical game board.

### Node 1

__Node 1__ controlled the main interface, and handled user input. An ATmega162 MCU served as the centre of the node. It was connected to an OLED display (w/ memory-mapped IO), 2kB SRAM, an ADC, a CAN controller (via SPI interface), along with an UART output for printing to terminal. All of this was connected from scratch, and drivers were developed by us.

### Node 2
__Node 2__ controlled the game board using input received from __Node 1__ over the CAN bus. The MCU was of the type ATmega2560, on an Arduino Mega. The control of the game board was done via a motor controller, interfaced with over I2C.

## Design pattern choices
Implemented singleton design pattern, with lazy initialization for most of the classes, and some with multiton.
https://stackoverflow.com/questions/1008019/c-singleton-design-pattern/1008289#1008289, and Modern C++ Design by Andrei Alexandrescu with some modifications because of limitations in the gcc compiler for avr.


## Key Features

In no specific order, here are the main features implemented in this embedded computer system.

* __C/C++ toolchain__ using CMake, AVR libc and GCC (we programmed in C++).
* __Drivers__ for interfacing with various components.  
* Implementation of various __communication protocols__: SPI, UART, CAN, etc.
* Moore __FSM__ with dynamically loaded state functions.  
* Motor, servo and solenoid __PID control__.
* Support for __tuning PID parameters__ while running.
* __Communication and control over CAN__, along with node synchronization in case of a node reset.
* __Menu system__ allowing the user to choose between different features to run.  
* __OLED display__ writing with support for dual buffering, and partitioning the screen into separate window areas.  
* Lightweight version of the __Snake__ game.  
* "3D" block game with __bouncing/physics emulation__.  
* __EEPROM writing & reading__ for storage of high scores (Snake) and PID values.  
* __Custom BLE service on NRF52__ with passthrough of GATT characteristic to an SPI master (not implemented in final version due to an SPI bug we didn't have time to figure out).  
* __Dynamic menu system__ (not included in final version due to memory limitations). 
* __UML__ documentation of project.


## Compiling and flashing

__Node 1__ was flashed via a JTAG interface with Atmel ICE, while __Node 2__ was flashed directly over UART.
This is done by calling   
```Bash
cmake .
sudo make flash
```  
in the node1/node2 folders.


## Address space on Node 1
- OLED COMMAND
[0X1000, 0X11FF] 512 BYTES

- OLED DATA
[0X1200, 0X13FF] 512 BYTES

- ADC
[0x1400, 0x17FF] 1kB

- SRAM
[0x1800, 0x1FFF] 2kB
    - VRAM 1: [0x1800, 0x1BFF]
    - VRAM 2: [0x1C00, 0x1FFF]
    


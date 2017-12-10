# Byggern

Project repository for TTK 4155 - Embedded and Industrial Computer Systems Design, Autumn 2017.  
Group: Håvard Borge (Howiezi @ GitHub), Åsmund Eek (aasmune @ GitHub), Eirik Vesterkjær (eirikeve @ GitHub)  

https://github.com/eirikeve/Byggern.git

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

* C/C++ toolchain using CMake, AVR libc and GCC (we programmed in C++).
* Drivers for interfacing with various components.  
* Implementation of various communication protocols: SPI, UART, CAN, etc.
* Moore FSM with dynamically loaded state functions.  
* Motor, servo and solenoid PID control.
* Support for tuning PID parameters while running.
* Communication and control over CAN, along with node synchronization in case of a node reset.
* Menu system allowing the user to choose between different features to run.  
* OLED display writing with support for dual buffering, and partitioning the screen into separate window areas.  
* Lightweight version of the Snake game.  
* "3D" block game with bouncing/physics emulation.  
* EEPROM writing for storage of high scores (Snake) and PID values.  
* Custom BLE service on NRF52 with passthrough of GATT characteristic to an SPI master (not implemented in final version due to an SPI bug we didn't have time to figure out).  
* Dynamic menu system (not included in final version due to memory limitations). 
* UML documentation of project.



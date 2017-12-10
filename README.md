# Byggern

Project repository for TTK 4155 - Autumn 2017

Group: Håvard Borge, Åsmund Eek, Eirik Vesterkjær

https://github.com/eirikeve/Byggern.git

## Design pattern choices
Implemented singleton design pattern, with lazy initialization for most of the classes, and some with multiton.
https://stackoverflow.com/questions/1008019/c-singleton-design-pattern/1008289#1008289, and Modern C++ Design by Andrei Alexandrescu with some modifications because of limitations in the gcc compiler for avr.

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
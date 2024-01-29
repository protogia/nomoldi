# nofungi-lamp

## description/idea
The Idea is about measuring humidity and temperature in a room to calculate the dewpoint. Depending to the dewpoint the µC calculates a critical tempereature to prevent mold creation. To indicate if its better to ventilate or to heat the room. 

## used project-hardaware
- microcontroller: Atmega8-16pu
- sensor: DHT22  

## wiring for programming/flashing

| AVRISP2 Pin | ATmega8-16PU Pin | 
|-------------|-------------------|
| VTG         | VCC (Pin 7)       |
| SCK         | SCK (Pin 19)      |
| MOSI        | MOSI (Pin 17)     |
| MISO        | MISO (Pin 18)     |
| RESET       | RESET (Pin 1)     |
| GND         | GND (Pin 8)       |
| VTG         | PB0 (Pin 14) -- 1kOhm Resistor -- LED |


## compile & and upload

### using make

```bash
make
make flash
```

### or manually

```bash
# create .elf
avr-gcc -mmcu=atmega8 -Wall -Os -o main.elf main.c
# create hex
avr-objcopy -j .text -j .data -O ihex main.elf main.hex
# upload
avrdude -p m8 -c avrisp2 -e -U flash:w:main.hex 
```

## wiring in production

| ATmega8-16PU Pin | DHT22 Pin | Description         |
|-------------------|-----------|---------------------|
| Pin 2 (PC2)       | Signal    | DHT22 Signal (Data) |
| VCC (Pin 7)       | VCC       | Power Supply        |
| GND (Pin 8)       | GND       | Ground              |
| Pin 14 (PB0)      | -         | 1kOhm Resistor -- LED (optional) --VCC |



#define F_CPU 1000000   

#include <avr/io.h>
#include <util/delay.h>
#include <math.h>

#define DHT_PIN 2 


void DHT22_Start(void) {
    DDRC |= (1 << DHT_PIN);

    // init DHT22
    PORTC &= ~(1 << DHT_PIN);
    _delay_ms(1000);
    PORTC |= (1 << DHT_PIN);
    _delay_ms(30);


    DDRC &= ~(1 << DHT_PIN);
}

uint8_t DHT22_Read(void) {
    uint8_t j;
    uint8_t result = 0;

    for (j = 0; j < 8; j++) {
        while (!(PINC & (1 << DHT_PIN))); // wait for begin of bit

        _delay_us(30);

        if (PINC & (1 << DHT_PIN)) // check if bit is 1 or 0
            result |= (1 << (7 - j));

        while (PINC & (1 << DHT_PIN)); // wait for end of bit
    }

    return result;
}

int main(void) {

    DDRB |= _BV(DDB0); 

    while (1) {
        DHT22_Start(); // start communication
        uint8_t humidity_high = DHT22_Read(); // read highBit of humidity
        uint8_t humidity_low = DHT22_Read();  // read lowBit of humidity
        uint8_t temperature_high = DHT22_Read(); 
        uint8_t temperature_low = DHT22_Read();  

        float humidity = ((uint16_t)humidity_high << 8 | humidity_low) / 10.0;
        float temperature = ((uint16_t)temperature_high << 8 | temperature_low) / 10.0;

        float dewPoint = temperature - (100 - humidity) / 5.0;
        float critical_point = dewPoint - 5

        if (temperature < critical_point) {
            PORTD &= ~(1 << PB0); // LOW
        } else {
            PORTD |= (1 << PB0); // PD0 HIGH
        }

        _delay_ms(2000);
    }

    return 0;
}

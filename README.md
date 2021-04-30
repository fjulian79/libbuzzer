# libpulsedpin
A class used to create low frequency pulsed signals without busy waiting or hardware timers

**A small demo to demonstrate how to use the class:**

```C++
#include <Arduino.h>
#include <pulsedpin/pulsedpin.h>

PulsedPin buzzer;

void setup()
{
    buzzer.begin(PB8);
    
    /**
     *  Creates 3 Tones, 100ms per tone, 200ms pause
     */
    buzzer.pulse(100, 200, 3);
}

void loop()
{
    uint32_t ticks = millis();

    buzzer.task(ticks);
}
```
# libbuzzer
A class used to control a simple buzzer and generate pulsed tones without busy waiting.

**A small demo to demonstrate how to use the class:**

```C++
#include <Arduino.h>
#include <buzzer/buzzer.h>

Buzzer buzzer;

void setup()
{
    buzzer.begin(PB8);
    
    /**
     *  Creates 3 Tones, 100ms per tone, 200ms pause
     */
    buzzer.beep(100, 200, 3);
}

void loop()
{
    uint32_t ticks = millis();

    buzzer.task(ticks);
}
```
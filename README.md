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
    
    buzzer.pulse(250, 250, 10);
}

void loop()
{
    uint32_t ticks = millis();

    buzzer.task(ticks);
}
```
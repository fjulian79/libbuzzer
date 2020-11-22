/*
 * buzzer, a class used to control a simple buzzer and generate pulsed tones 
 * without bussy waiting.
 * 
 * Copyright (C) 2020 Julian Friedrich
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>. 
 *
 * You can file issues at https://github.com/fjulian79/libbuzzer/issues
 */

#include <buzzer/buzzer.hpp>
#include <Arduino.h>

Buzzer::Buzzer() : 
      Pin(0)
    , Step(0)
    , Count(0)
    , LastTick(0)
{
    Delay[0] = 0;
    Delay[1] = 0;
}

Buzzer::Buzzer(uint32_t pin)
{
    init(pin);
}

void Buzzer::init(uint32_t pin)
{
    Pin = pin;
    Delay[0] = 0;
    Delay[1] = 0;
    Step = 0;
    Count = 0;
    LastTick = 0;

    pinMode(Pin, OUTPUT);
    digitalWrite(Pin, LOW);
}

void Buzzer::enable(bool state)
{
    Count = 0;
    Step = 0;

    if (state)
    {
        digitalWrite(Pin, HIGH);
    }
    else
    {
        digitalWrite(Pin, LOW);
    }
}

void Buzzer::pulse(uint16_t on_ms, uint16_t off_ms, uint16_t cnt)
{
    Delay[0] = on_ms;
    Delay[1] = off_ms;

    if(Count == 0)
    {
        LastTick = millis() - on_ms;
    }

    Count = cnt;
}

void Buzzer::task(uint32_t millis)
{
    if ((millis - LastTick >= Delay[Step]) && (Count != 0))
    {
        if(Step == 0)
        {
            digitalWrite(Pin, HIGH);
        }
        else
        {
            digitalWrite(Pin, LOW);
        }
        
        Step++;

        if(Step == 2)
        {
            Count --;
            Step = 0;
        }

        LastTick = millis;
    }
}

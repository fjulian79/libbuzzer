/*
 * PulsedPin, a class used to create low frequency pulsed signals without busy 
 * waiting or hardware timers.
 * 
 * Copyright (C) 2021 Julian Friedrich
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
 * You can file issues at https://github.com/fjulian79/libpulsedpin/issues
 */

#include <pulsedpin/pulsedpin.hpp>
#include <Arduino.h>

PulsedPin::PulsedPin() : 
      Pin(0)
    , Delay({0,0,0})
    , Step(0)
    , Steps(0)
    , Loops(0)
    , LastTick(0)
{

}

PulsedPin::PulsedPin(uint32_t pin)
{
    begin(pin);
}

void PulsedPin::begin(uint32_t pin)
{
    Pin = pin;
    Delay = {0,0,0};
    Step = 0;
    Steps = 0;
    Loops = 0;
    LastTick = 0;

    pinMode(Pin, OUTPUT);
    digitalWrite(Pin, LOW);
}

void PulsedPin::set(bool state)
{
    Steps = 0;
    Step = 0;
    Loops = 0;

    if (state)
        digitalWrite(Pin, HIGH);
    else
        digitalWrite(Pin, LOW);
}

void PulsedPin::pulse(uint16_t on_ms)
{
    pulse(on_ms, 0, 1, 0, 1);
}

void PulsedPin::pulse(uint16_t on_ms, uint16_t pause_ms, uint8_t tones)
{
    pulse(on_ms, 0, 1, pause_ms, tones);
}

void PulsedPin::pulse(uint16_t on_ms, uint16_t off_ms, uint8_t tones, uint16_t pause_ms, uint8_t cnt)
{
    Delay.On = on_ms;
    Delay.Off = off_ms;
    Delay.Pause = pause_ms;
    Steps = tones != 0 ? tones * 2 : 1;
    Loops = cnt;
    
    Step = 0;
    digitalWrite(Pin, HIGH);
    LastTick = millis(); 
}

void PulsedPin::task(uint32_t millis)
{
    uint16_t delay = 0;

    if (Loops != 0)
    {   
        if (Step == 0)
            delay = Delay.On;
        else if (Step < Steps-1)
            delay = Step%2 == 0 ? Delay.On : Delay.Off;
        else
            delay = Delay.Pause;
            
        if (millis - LastTick >= delay)
        {
            Step++;
            if(Step == Steps)
            {
                if (Loops < PULSEDPIN_INFINTIE)
                    Loops--;
                Step = 0;
            }

            if (Loops != 0)
                digitalToggle(Pin);

            if ((Loops == 1) && (Step == Steps -1))
                Loops = Step = 0;

            LastTick = millis;
        }
    }
}

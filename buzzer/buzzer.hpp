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

#include <stdint.h>

#ifndef BUZZER_HPP_
#define BUZZER_HPP_

class Buzzer
{
    public:

        /**
         * @brief Construct a new Buzzer object
         * 
         * The class will not be ready unil init() has been called
         */
        Buzzer();

        /**
         * @brief Construct a new Buzzer object
         * 
         * Calls the init function. The class is ready to be used imediately. 
         * 
         * @param pin The pin the buzzer is connected to.
         */
        Buzzer(uint32_t pin);

        /**
         * @brief Initializes the class for usage
         * 
         * @param pin The pin the buzzer is connected to.
         */
        void init(uint32_t pin);

        /**
         * @brief Turn the buzzer statically on or off.
         * 
         * Anny ongoing sequence will be interrupted.
         * 
         * @param state The new buzer state.
         */
        void enable(bool state);

        /**
         * @brief Starts a simple on/off sequence.
         * 
         * @param on_ms   Duration of the ON period in milliseconds.
         * @param off_ms  Duration of the OFF period in milliseconds.  
         * @param cnt     Optional parameter to secifiy the number of tones to 
         *                generate. Defaults to 1.
         */
        void pulse(uint16_t on_ms, uint16_t off_ms, uint16_t cnt = 1);

        /**
         * @brief The task function to call in the main loop.
         * 
         * @param millis The current wall clock in ms.
         */
        void task(uint32_t millis);

    private:
        
        /**
         * @brief The Pin number to use.
         */
        uint32_t Pin;

        /**
         * @brief The delay array, slot 0 is the ON period, slot 1 is the off 
         * period.
         */
        uint16_t Delay[2];

        /**
         * @brief The index in the delay array.
         */
        uint8_t Step;

        /**
         * @brief The number of tones to create
         */
        uint16_t Count;

        /**
         * @brief The time stamp of the last task tick.
         * 
         */
        uint32_t LastTick;
};

#endif /* BUZZER_HPP_ */
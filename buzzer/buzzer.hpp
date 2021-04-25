/*
 * buzzer, a class used to control a simple buzzer and generate pulsed tones 
 * without busy waiting.
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
#include <stddef.h>

#ifndef BUZZER_HPP_
#define BUZZER_HPP_

/**
 * @brief Let the buzzer beep for a infinite amount of time.
 */
#define BUZZ_INFINTIE               UINT8_MAX

/**
 * @brief A class used to control a simple buzzer and generate pulsed tones 
 * without busy waiting.
 */
class Buzzer
{
    public:

        /**
         * @brief Construct a new Buzzer object
         * 
         * The class will not be ready until init() has been called
         */
        Buzzer();

        /**
         * @brief Construct a new Buzzer object
         * 
         * Calls the init function. The class is ready to be used immediately. 
         * 
         * @param pin The pin the buzzer is connected to.
         */
        Buzzer(uint32_t pin);

        /**
         * @brief Initializes the class for usage
         * 
         * @param pin The pin the buzzer is connected to.
         */
        void begin(uint32_t pin);

        /**
         * @brief Turn the buzzer statically on or off.
         * 
         * Any ongoing sequence will be interrupted.
         * 
         * @param state The new buzzer state.
         */
        void enable(bool state);

        /**
         * @brief Creates a single tone with the given duration.
         * 
         * @param on_ms Optional tone duration, defaults to 100 ms.
         */
        void beep(uint16_t on_ms = 100);

        /**
         * @brief Creates a given number of pulsed tones.
         * 
         * @param on_ms The duration of the tones.
         * @param pause_ms The pause between two tones.
         * @param tones The number of tones to create, defaults to 
         *              BUZZ_INFINTIE.
         */
        void beep(uint16_t on_ms, uint16_t pause_ms, 
                uint8_t tones = BUZZ_INFINTIE);

        /**
         * @brief Creates a a tone sequences.
         * 
         * @param on_ms The duration of the tones.
         * @param off_ms The pause within a sequence.
         * @param tones The number of tones in a sequence.
         * @param pause_ms The pause between sequences.
         * @param cnt The number of sequences, defaults to BUZZ_INFINTIE.
         */
        void beep(uint16_t on_ms, uint16_t off_ms, uint8_t tones, 
                uint16_t pause_ms, uint8_t loops = BUZZ_INFINTIE);

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
         * @brief Holds the delays configured fo on/of/pause.
         * 
         */
        struct 
        {
            uint16_t On;
            uint16_t Off;
            uint16_t Pause;

        } Delay;
        
        /**
         * @brief The current step within the sequence.
         */
        uint8_t Step;

        /**
         * @brief Number of step within a sequence.
         * 
         */
        uint8_t Steps;

        /**
         * @brief The number of sequences.
         */
        uint16_t Loops;

        /**
         * @brief The time stamp of the last task tick.
         * 
         */
        uint32_t LastTick;
};

#endif /* BUZZER_HPP_ */
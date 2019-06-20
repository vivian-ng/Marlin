/**
 * Marlin 3D Printer Firmware
 * Copyright (C) 2016 MarlinFirmware [https://github.com/MarlinFirmware/Marlin]
 *
 * Based on Sprinter and grbl.
 * Copyright (C) 2011 Camiel Gubbels / Erik van der Zalm
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
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

/**
 * MRR ESPE pin assignments
 * MRR ESPE is a 3D printer control board based on the ESP32 microcontroller.
 * Supports 4 stepper drivers (using I2S stepper stream), heated bed,
 * single hotend, and LCD controller.
 */

#ifndef BOARD_NAME
  #define BOARD_NAME "MRR ESPE"
#endif

//
// Limit Switches
//
#define X_MIN_PIN          33
#define Y_MIN_PIN          35
#define Z_MIN_PIN          15

//
// Enable I2S stepper stream
//
#ifdef I2S_STEPPER_STREAM
  #define I2S_STEPPER_STREAM
#endif

//
// Steppers
//
#define X_STEP_PIN         129
#define X_DIR_PIN          130
#define X_ENABLE_PIN       128
//#define X_CS_PIN           21

#define Y_STEP_PIN         132
#define Y_DIR_PIN          133
#define Y_ENABLE_PIN       131
//#define Y_CS_PIN           22

#define Z_STEP_PIN         135
#define Z_DIR_PIN          136
#define Z_ENABLE_PIN       134
//#define Z_CS_PIN            5 // SS_PIN

#define E0_STEP_PIN        138
#define E0_DIR_PIN         139
#define E0_ENABLE_PIN      137
//#define E0_CS_PIN          21


//
// Temperature Sensors
//
#define TEMP_0_PIN         36   // Analog Input
#define TEMP_BED_PIN       39   // Analog Input

//
// Heaters / Fans
//
#define HEATER_0_PIN        2
#define FAN_PIN            13
#define HEATER_BED_PIN      4

//
// MicroSD card
//
#define MOSI_PIN           23
#define MISO_PIN           19
#define SCK_PIN            18
#define SS_PIN              5
#define SDSS                5

//////////////////////////
// LCDs and Controllers //
//////////////////////////


//
// LCD Display output pins
//
#if ENABLED(REPRAP_DISCOUNT_FULL_GRAPHIC_SMART_CONTROLLER)
  #define LCD_PINS_RS         17
  #define LCD_PINS_ENABLE     21
  #define LCD_PINS_D4         140
  #define LCD_PINS_D5         141
  #define LCD_PINS_D6         142
  #define LCD_PINS_D7         143

#elif ENABLED(CR10_STOCKDISPLAY)
  #define LCD_PINS_RS         17
  #define LCD_PINS_ENABLE     21
  #define LCD_PINS_D4         32
  #define BEEPER_PIN          37
#endif

//
// LCD Display input pins
//
#if ENABLED(REPRAP_DISCOUNT_FULL_GRAPHIC_SMART_CONTROLLER)
  #define BEEPER_PIN          37
  #define BTN_EN1             12
  #define BTN_EN2             14
  #define BTN_ENC             22

#elif ENABLED(CR10_STOCKDISPLAY)
  #define BTN_EN1             12
  #define BTN_EN2             14
  #define BTN_ENC             22

#endif


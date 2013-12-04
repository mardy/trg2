
/**
 * That Rabbit Game 2: Stone Age Rabbit Hunt
 * Copyright (C) 2010, 2011, 2012, 2013 Thomas Perl <m@thp.io>
 * http://thp.io/2011/trg2/
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
 **/

#ifndef TRG_CONFIG_H
#define TRG_CONFIG_H

#ifdef ANDROID
#  include <GLES/gl.h>
#else
#  include "SDL_opengl.h"
#  define glOrthof glOrtho
#endif

// Number of blood stains on the screen when rabbit is hit
#define BLOOD_STAINS 7

// Number of coins in the full coin bucket
#define FULL_COIN_COUNT 10

// Duration of the game in seconds
#define DEFAULT_DURATION 90

// Damage severity offset of the "arrowed" state in the atlas
#define SEVERITY_ARROWED 4

// Damage severity offset of the "stoned" state in the atlas
#define SEVERITY_STONED 5

// Distance in world pixels to consider the head hit by a stone
#define STONE_HIT_DISTANCE 30

// Number of stones in the current level (only one level so far)
#define STONE_COUNT 2

// Default tint of the background items when the menu is active
#define DEFAULT_TINT_MENU .9

// Duration (in ms) of the "tilt the device" hint after start
#define TILT_HELP_DURATION 3000

#endif /* TRG_CONFIG_H */

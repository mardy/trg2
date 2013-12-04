
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

#ifndef TRG_EVENT_H
#define TRG_EVENT_H

enum TouchEvent {
    TOUCH_UNDEFINED = 0,
    TOUCH_DOWN,
    TOUCH_MOVE,
    TOUCH_UP,
};

enum KeyEvent {
    KEY_UNDEFINED = 0,
    KEY_DOWN,
    KEY_UP,
};

enum Key {
    K_UNDEFINED = 0,
    K_LEFT,
    K_RIGHT,
    K_UP,
    K_DOWN,
};

#endif /* TRG_EVENT_H */


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

#ifndef RABBITGAME_H
#define RABBITGAME_H

#include "event.h"
#include "gamescene.h"

class RabbitGame
{
    GameScene m_scene;

public:
    RabbitGame();

    void init();
    void resize(int width, int height);
    void render();
    void touch(enum TouchEvent event, float x, float y, int finger);
    void key(enum KeyEvent event, enum Key key);
    void accelerometer(float x, float y, float z);

    int exec();
};

#endif // RABBITGAME_H

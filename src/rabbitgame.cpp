
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

#include "config.h"

#include "rabbitgame.h"
#include "soundplayer.h"
#include "animation.h"
#include "timer.h"


RabbitGame::RabbitGame()
{
    SoundPlayer::startMusic();
}

void
RabbitGame::init()
{
}

void
RabbitGame::resize(int width, int height)
{
    m_scene.initializeGL(width, height);
}

void
RabbitGame::render()
{
    Timer::process();
    m_scene.paintGL();
}

void
RabbitGame::touch(enum TouchEvent event, float x, float y, int finger)
{
    m_scene.touchEvent(event, x, y, finger);
}

void
RabbitGame::key(enum KeyEvent event, enum Key key)
{
    m_scene.keyEvent(event, key);
}

void
RabbitGame::accelerometer(float x, float y, float z)
{
    m_scene.accelerometerEvent(x, y, z);
}

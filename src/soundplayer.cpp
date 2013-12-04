
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

#include "soundplayer.h"


SoundPlayer *
SoundPlayer::instance = NULL;

SoundPlayer::SoundPlayer()
{
}

void
SoundPlayer::play(SoundEffect sound, float position)
{
    if (!instance) {
        instance = new SoundPlayer();
    }

    /* TODO: Randomize */
    if (sound == WTF) sound = WTF0;
    if (sound == DAMN) sound = DAMN0;
    if (sound == LAUGH) sound = LAUGH0;

    /* TODO: Play sound */
}

void
SoundPlayer::startMusic()
{
    if (!instance) {
        instance = new SoundPlayer();
    }

    /* TODO: Play music */
}

void
SoundPlayer::stopMusic()
{
    if (instance) {
        /* TODO: Stop music */
    }
}

SoundPlayer*
SoundPlayer::getInstance()
{
    if (!instance) {
        instance = new SoundPlayer();
    }

    return instance;
}

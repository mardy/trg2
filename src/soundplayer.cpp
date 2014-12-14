
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

#include <stdlib.h>

#define DECLARE_RESOURCE(name) \
    extern char resource_ ## name[]; \
    extern unsigned int resource_ ## name ##_len;

DECLARE_RESOURCE(shot_wav)
DECLARE_RESOURCE(flap_wav)
DECLARE_RESOURCE(load_wav)
DECLARE_RESOURCE(beep_wav)
DECLARE_RESOURCE(end_wav)
DECLARE_RESOURCE(damn0_wav)
DECLARE_RESOURCE(damn1_wav)
DECLARE_RESOURCE(laugh0_wav)
DECLARE_RESOURCE(laugh1_wav)
DECLARE_RESOURCE(wtf0_wav)
DECLARE_RESOURCE(wtf1_wav)
DECLARE_RESOURCE(baalcrap_it)


static SoundPlayerImpl *
impl()
{
    static SoundPlayerImpl *impl = 0;
    if (!impl) {
        impl = new SoundPlayerImpl();

#define LOAD_SOUND(key, data) impl->load(key, data, data ## _len)
        LOAD_SOUND(SoundPlayer::LOAD, resource_load_wav);
        LOAD_SOUND(SoundPlayer::SHOT, resource_shot_wav);
        LOAD_SOUND(SoundPlayer::FLAP, resource_flap_wav);
        LOAD_SOUND(SoundPlayer::DROP, resource_flap_wav);
        LOAD_SOUND(SoundPlayer::BEEP, resource_beep_wav);
        LOAD_SOUND(SoundPlayer::END, resource_end_wav);
        LOAD_SOUND(SoundPlayer::DAMN0, resource_damn0_wav);
        LOAD_SOUND(SoundPlayer::DAMN1, resource_damn1_wav);
        LOAD_SOUND(SoundPlayer::LAUGH0, resource_laugh0_wav);
        LOAD_SOUND(SoundPlayer::LAUGH1, resource_laugh1_wav);
        LOAD_SOUND(SoundPlayer::WTF0, resource_wtf0_wav);
        LOAD_SOUND(SoundPlayer::WTF1, resource_wtf1_wav);
#undef LOAD_SOUND
        impl->load_music(resource_baalcrap_it, resource_baalcrap_it_len);
    }

    return impl;
}

void
SoundPlayer::play(SoundEffect sound, float position)
{
    static int pseudorandom = 0;
    pseudorandom++;

    if (sound == WTF) {
        sound = (pseudorandom % 2 == 0) ? WTF0 : WTF1;
    }

    if (sound == DAMN) {
        sound = (pseudorandom % 2 == 0) ? DAMN0 : DAMN1;
    }

    if (sound == LAUGH) {
        sound = (pseudorandom % 2 == 0) ? LAUGH0 : LAUGH1;
    }

    impl()->play(sound);
}

void
SoundPlayer::startMusic()
{
    impl()->music(true);
}

void
SoundPlayer::stopMusic()
{
    impl()->music(false);
}

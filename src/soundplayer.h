
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

#ifndef TRG_SOUNDPLAYER_H
#define TRG_SOUNDPLAYER_H

#include <stdlib.h>

class SoundPlayer {
public:
    enum SoundEffect {
        LOAD, SHOT, FLAP, DROP, BEEP, END, DAMN, LAUGH, WTF,
        DAMN0, DAMN1, LAUGH0, LAUGH1, WTF0, WTF1, EFFECT_COUNT
    };

    static void play(SoundEffect sound, float position);

    static void startMusic();
    static void stopMusic();
};

class SoundPlayerImplPriv;

class SoundPlayerImpl {
public:
    SoundPlayerImpl();
    ~SoundPlayerImpl();

    void load(enum SoundPlayer::SoundEffect effect, const char *data, size_t len);
    void load_music(const char *data, size_t len);
    void play(enum SoundPlayer::SoundEffect effect);
    void music(bool playing);

private:
    SoundPlayerImplPriv *priv;
};

#endif /* TRG_SOUNDPLAYER_H */

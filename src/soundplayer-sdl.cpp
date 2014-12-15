
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

#ifdef USE_SDL_MIXER

#include "soundplayer.h"

#include <SDL_mixer.h>


class SoundPlayerImplPriv {
public:
    SoundPlayerImplPriv();

    Mix_Chunk *sounds[SoundPlayer::EFFECT_COUNT];
    Mix_Music *music;
};

SoundPlayerImplPriv::SoundPlayerImplPriv()
    : sounds()
    , music(0)
{
    memset(sounds, 0, sizeof(sounds));
}

SoundPlayerImpl::SoundPlayerImpl()
    : priv(new SoundPlayerImplPriv())
{
    Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 4096);
}

SoundPlayerImpl::~SoundPlayerImpl()
{
    delete priv;
}

void
SoundPlayerImpl::load(enum SoundPlayer::SoundEffect effect,
                      const char *data, size_t size)
{
    priv->sounds[effect] = Mix_LoadWAV_RW(SDL_RWFromConstMem(data, size), 1);
}

void
SoundPlayerImpl::load_music(const char *data, size_t size)
{
    priv->music = Mix_LoadMUS_RW(SDL_RWFromConstMem(data, size)
#ifdef TRG_USE_SDL2
                                 , 1
#endif
                                 );
}

void
SoundPlayerImpl::play(enum SoundPlayer::SoundEffect sound)
{
    int channel = 0;

    /* Sounds which cannot be played at the same time must be played on
     * the same channel, so that if another sound from the same set is
     * playing, it gets stopped. */
    switch (sound) {
        case SoundPlayer::LOAD:
        case SoundPlayer::SHOT:
            channel = 1;
            break;
        case SoundPlayer::WTF0:
        case SoundPlayer::WTF1:
            channel = 2;
            break;
        case SoundPlayer::DAMN0:
        case SoundPlayer::DAMN1:
            channel = 3;
            break;
        case SoundPlayer::LAUGH0:
        case SoundPlayer::LAUGH1:
            channel = 4;
            break;
        default:
            channel = 0;
    }

    if (priv->sounds[sound]) {
        Mix_PlayChannel(channel, priv->sounds[sound], 0);
    }
}

void
SoundPlayerImpl::music(bool playing)
{
    if (playing) {
        Mix_PlayMusic(priv->music, -1);
    } else {
        Mix_HaltMusic();
    }
}

#endif // USE_SDL_MIXER

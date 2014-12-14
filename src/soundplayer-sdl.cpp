
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

#define DECLARE_RESOURCE(name) \
    extern unsigned char resource_ ## name; \
    extern unsigned int resource_ ## name ##_len;

DECLARE_RESOURCE(shot_wav)
DECLARE_RESOURCE(flap_wav)
DECLARE_RESOURCE(load_wav)
DECLARE_RESOURCE(baalcrap_it)

class SoundPlayerImpl {
public:
    SoundPlayerImpl();

    Mix_Chunk *sounds[SoundPlayer::EFFECT_COUNT];
    Mix_Music *music;
};

SoundPlayerImpl::SoundPlayerImpl()
{
    Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 4096);
#define LoadWAVFromMem(mem) Mix_LoadWAV_RW(SDL_RWFromMem(&mem, mem ## _len), 1)
    sounds[SoundPlayer::LOAD] = LoadWAVFromMem(resource_load_wav);
    sounds[SoundPlayer::SHOT] = LoadWAVFromMem(resource_shot_wav);
    sounds[SoundPlayer::FLAP] = LoadWAVFromMem(resource_flap_wav);
    sounds[SoundPlayer::DROP] = LoadWAVFromMem(resource_flap_wav);
    sounds[SoundPlayer::BEEP] = LoadWAVFromMem(resource_flap_wav);
    sounds[SoundPlayer::END] = LoadWAVFromMem(resource_flap_wav);
    sounds[SoundPlayer::DAMN] = 0; // not used
    sounds[SoundPlayer::LAUGH] = 0; // not used
    sounds[SoundPlayer::WTF] = 0; // not used
    sounds[SoundPlayer::DAMN0] = LoadWAVFromMem(resource_flap_wav);
    sounds[SoundPlayer::DAMN1] = LoadWAVFromMem(resource_flap_wav);
    sounds[SoundPlayer::LAUGH0] = LoadWAVFromMem(resource_flap_wav);
    sounds[SoundPlayer::LAUGH1] = LoadWAVFromMem(resource_flap_wav);
    sounds[SoundPlayer::WTF0] = LoadWAVFromMem(resource_flap_wav);
    sounds[SoundPlayer::WTF1] = Mix_LoadWAV("flap.wav");

    music = Mix_LoadMUS_RW(SDL_RWFromMem(&resource_baalcrap_it, resource_baalcrap_it_len));
}

SoundPlayer::SoundPlayer()
    : impl(new SoundPlayerImpl)
{
}

void
SoundPlayer::play(SoundEffect sound, float position)
{
    if (!instance) {
        instance = new SoundPlayer();
    }

    int channel = 0;
    /* Sounds which cannot be played at the same time must be played on
     * the same channel, so that if another sound from the same set is
     * playing, it gets stopped. */
    if (sound == LOAD ||
        sound == SHOT ||
        sound == DAMN) {
        channel = 1;
    }

    /* TODO: Randomize */
    if (sound == WTF) sound = WTF0;
    if (sound == DAMN) sound = DAMN0;
    if (sound == LAUGH) sound = LAUGH0;

    Mix_PlayChannel(channel, instance->impl->sounds[sound], 0);
}

void
SoundPlayer::startMusic()
{
    if (!instance) {
        instance = new SoundPlayer();
    }

    Mix_PlayMusic(instance->impl->music, -1);
}

void
SoundPlayer::stopMusic()
{
    if (instance) {
        Mix_HaltMusic();
    }
}

#endif // USE_SDL_MIXER

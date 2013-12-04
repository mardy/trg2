
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

#ifndef TRG_TIMEDISPLAY_H
#define TRG_TIMEDISPLAY_H

#include "sprite.h"
#include "texture.h"
#include "timemanager.h"
#include "texturepart.h"
#include "soundplayer.h"


class TimeDisplay : public Sprite
{
    static constexpr float WIDTH = 55.;
    static constexpr float HEIGHT = 55.;
    static constexpr float TEXTURE_X = 20.;
    static constexpr float TEXTURE_Y = 600.;

    static constexpr int CLOCK_PARTS = 8;
    static constexpr int COUNTDOWN_PARTS = 5;

    Texture *texture;
    TimeManager *timeManager;

    int offset;

public:
    TimeDisplay(Texture *texture, TimeManager *timeManager)
        : Sprite(new TexturePart(texture, TEXTURE_X, TEXTURE_Y,
                    TEXTURE_X+WIDTH, TEXTURE_Y+HEIGHT))
        , texture(texture)
        , timeManager(timeManager)
        , offset(0)
    {
        setCenter(0, 0);
    }

    virtual void draw() {
        int remainingSeconds = (int)(timeManager->getRemainingTimeMillis()/1000);
        int newOffset = offset;

        if (remainingSeconds <= COUNTDOWN_PARTS) {
            newOffset = CLOCK_PARTS + COUNTDOWN_PARTS - remainingSeconds;
        } else {
            newOffset = std::max(0, CLOCK_PARTS - 1 - (int)(CLOCK_PARTS * remainingSeconds * 1000 / timeManager->getDuration()));
        }

        if (newOffset != offset) {
            offset = newOffset;
            onOffsetChanged(remainingSeconds);
        }

        timeManager->getDuration();

        if (remainingSeconds) {
            Sprite::draw();
        }
    }

    void onOffsetChanged(int remainingSeconds) {
        float x = TEXTURE_X + WIDTH * offset;
        float y = TEXTURE_Y;

        TexturePart *newTexturePart = new TexturePart(texture,
                x, y, x + WIDTH, y + HEIGHT);
        updateTexturePart(newTexturePart);

        if (remainingSeconds == 0) {
            SoundPlayer::play(SoundPlayer::END, .5);
        }  else if (remainingSeconds > 0 &&
                remainingSeconds <= COUNTDOWN_PARTS) {
            SoundPlayer::play(SoundPlayer::BEEP, .5);
        }
    }
};

#endif /* TRG_TIMEDISPLAY_H */

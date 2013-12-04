
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

#include <math.h>

#include "util.h"
#include "crosshairs.h"
#include "sprite.h"
#include "textureparts.h"
#include "soundplayer.h"


Crosshairs::Crosshairs(GameScene *scene, Texture *texture, int width, int height)
    : scene(scene)
    , spriteGreen(new Sprite(TextureParts::makeCrosshairsGreen(texture)))
    , spriteRed(new Sprite(TextureParts::makeCrosshairsRed(texture)))
    , screenWidth(width)
    , screenHeight(height)
    , rabbit(NULL)
    , desiredX(0.)
    , desiredY(0.)
    , isLoaded(false)
    , timeStamp(-1)
    , timeOfLastShot(-1)
    , aimBar(new AimBar(texture))
{
    spriteRed->setCenter(24, 24);
    spriteGreen->setCenter(24, 24);
    aimBar->setPosition(screenWidth / 2,
                        screenHeight / 8 + aimBar->getHeight() /2);
}

bool
Crosshairs::isNearRabbit()
{
    float dx = rabbit->getX() - getX();
    float dy = rabbit->getY() - getY();
    return (dx * dx + dy * dy < MAX_DISTANCE_2);
}

void
Crosshairs::ai()
{
    if (rabbit->hasLanded()) {
        setDesiredPosition(screenWidth / 2, -spriteRed->getHeight());
    } else {
        if (isNearRabbit() && allowedToShoot()) {
            setDesiredPosition(rabbit->getX(), rabbit->getY());
            if (timeStamp > 0 && currentTimeMillis() - timeStamp >= MILLISECONDS_TO_SHOOT) {
                shoot();
                timeOfLastShot = currentTimeMillis();
                timeStamp = -1;
                isLoaded = false;
            }
        } else {
            setDesiredPosition((float)(screenWidth/2 + screenWidth/2.5 * sinf(currentTimeMillis() / 4000.)),
                (float)(screenHeight/2 + screenHeight/3 * sinf(currentTimeMillis() / 2000.)));
        }

    }

    float dx = desiredX - getX();
    float dy = desiredY - getY();

    move(dx / 220., dy / 220.);
}

void
Crosshairs::shoot()
{
    SoundPlayer::play(SoundPlayer::SHOT, 0.5);
    // TODO: Play SoundPlayer::LAUGH after 500 ms
    setY(getY() - RECOIL_STRENGTH);

    if (this->hits(rabbit)) {
        rabbit->looseCoin();
        /* FIXME: Vibrate after 300 msec */
    }
}

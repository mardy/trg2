
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

#include "rabbitsprite.h"

#include "textureparts.h"
#include "coinbucketsprite.h"
#include "soundplayer.h"

#include <math.h>


const float RabbitSprite::ANGLE_MAX = 45.;
const float RabbitSprite::MAX_ROTATION = 30.;

const int RabbitSprite::CENTER_X = 45;
const int RabbitSprite::CENTER_Y = 42;

RabbitSprite::RabbitSprite(Texture *texture)
    : SpriteContainer(TextureParts::makeRabbitHead(texture))
    , stars(NULL)
    , leftWing(NULL)
    , rightWing(NULL)
    , leftWingFlap(NULL)
    , rightWingFlap(NULL)
    , coinBucket(NULL)
{
    setCenter(CENTER_X, CENTER_Y);

    leftWing = new Wing(TextureParts::makeWing(texture), true);
    leftWing->setCenter(leftWing->getWidth(), leftWing->getHeight() /2);
    leftWing->setPosition(0, -5);
    leftWing->setRotation(ANGLE_MAX);
    leftWingFlap = new WingFlap(leftWing);

    rightWing = new Wing(TextureParts::makeWing(texture)->setMirror(HORIZONTAL), false);
    rightWing->setCenter(0, rightWing->getHeight() / 2);
    rightWing->setPosition(0, -5);
    rightWing->setRotation(-ANGLE_MAX);
    rightWingFlap = new WingFlap(rightWing);

    coinBucket = new CoinBucketSprite(texture);
    coinBucket->setPosition(0, 20);

    addChildBack(leftWing);
    addChildBack(rightWing);
    addChildBack(coinBucket);

    stars = new Stars(texture);
}

void
RabbitSprite::flapWing(bool left, bool right)
{
    if (left || right) {
       SoundPlayer::play(SoundPlayer::FLAP, .5);
    }

    if (left) {
        leftWingFlap->restart();
    } else {
        leftWingFlap->rewind();
    }

    if (right) {
        rightWingFlap->restart();
    } else {
        rightWingFlap->rewind();
    }
}

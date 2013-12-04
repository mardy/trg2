
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

#include "physicalrabbit.h"

#include <math.h>
#include <algorithm>
#include <iostream>

#include <stdio.h>


PhysicalRabbit::PhysicalRabbit(GameScene *scene, RabbitSprite *rabbit, Sprite *coinSprite, int screenWidth, int screenHeight)
    : sprite(rabbit)
    , velocity(0.)
    , gravitySpeed(0.)
    , coinGravity(0.)
    , screenWidth(screenWidth)
    , screenHeight(screenHeight)
    , coinDrops(false)
    , coinSprite(coinSprite)
    , boundaryCheck(true)
    , scene(scene)
{
}

void
PhysicalRabbit::move()
{
    float angle = sprite->getRotation()*M_PI/180.;

    velocity = std::max(0., velocity * .99);
    gravitySpeed += (.005 * GRAVITY);

    float sMovement = velocity;
    float sMovementY = sMovement * cosf(fabsf(angle));
    float sMovementX = angle*3.5;

    if (hasLanded()) {
        sMovementX = 0.;
    }

    float newY = sprite->getY() + gravitySpeed - sMovementY;
    float newX = sprite->getX() + sMovementX;

    if (boundaryCheck) {
        newX = std::min(screenWidth, std::max(0, (int)newX));
        newY = std::min(screenHeight - sprite->getHeight(), std::max((float)-40, newY));
    }

    setPosition(newX, newY);

    if (coinDrops) {
        moveCoin();
    } else {
        coinSprite->setPosition(newX, newY + 17);
    }
}

void
PhysicalRabbit::processGesture(InputGesture gesture)
{
    InputGesture currentGestureToPerform = GESTURE_NOTHING;
    bool finished = false;
    bool both = false;

    if (gesture != GESTURE_NOTHING) {
        if (inputQueue.size() < 2) {
            inputQueue.push(gesture);
        }
    }

    currentGestureToPerform = (inputQueue.empty()?GESTURE_NOTHING:inputQueue.front());

    if (currentGestureToPerform != GESTURE_NOTHING) {
        inputQueue.pop();

        switch (currentGestureToPerform) {
            case GESTURE_TAP_BEGIN:
                velocity = 3.;
                gravitySpeed = 0.;
                sprite->flapWing(true, true);
                break;
            case GESTURE_TAP_END:
                velocity = -gravitySpeed;
                gravitySpeed = 0.;
                sprite->flapWing(false, false);
                break;
            case GESTURE_LEFT:
                if (sprite->getRotation() > -45) {
                    sprite->setRotation(sprite->getRotation() - 10);
                }
                break;
            case GESTURE_RIGHT:
                if (sprite->getRotation() < 45) {
                    sprite->setRotation(sprite->getRotation() + 10);
                }
                break;
            default:
                break;
        }
    }
}

void
PhysicalRabbit::draw()
{
    if (sprite != NULL) {
        sprite->draw();
    }

    if (coinDrops) {
        coinSprite->draw();
    }
}

void
PhysicalRabbit::setPosition(float x, float y)
{
    if (sprite != NULL) {
        sprite->setPosition(x, y);
    }
}

void
PhysicalRabbit::jiggle()
{
    scene->jiggle();
}

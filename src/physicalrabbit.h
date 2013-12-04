
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

#ifndef TRG_PHYSICALRABBIT_H
#define TRG_PHYSICALRABBIT_H

#include <math.h>

#include "inputgesture.h"
#include "rabbitsprite.h"
#include "soundplayer.h"
#include "gamescene.h"

#include <queue>


class GameScene;

class PhysicalRabbit
{
    /**
     * Yes, people tell you gravity is 9.81, but here in that rabbit land, it's
     * 4.81f! It really is a very special land. How gee!
     **/
    static constexpr float GRAVITY = 4.81f;
    static constexpr float VELOCITY_FACTOR = 6000.f;

    RabbitSprite *sprite;
    float velocity;
    float gravitySpeed;
    float coinGravity;
    std::queue<InputGesture> inputQueue;

    int screenWidth;
    int screenHeight;
    bool coinDrops;
    Sprite *coinSprite;
    bool boundaryCheck;

    GameScene *scene;

    virtual void moveCoin() {
        if (coinSprite->getY() < screenHeight) {
            coinGravity += (.005 * GRAVITY);
            coinSprite->setY(coinSprite->getY() + coinGravity);
        } else {
            coinDrops = false;
            SoundPlayer::play(SoundPlayer::DROP, .5);
        }
    }

    void jiggle();

public:
    PhysicalRabbit(GameScene *scene, RabbitSprite *rabbit, Sprite *coinSprite, int screenWidth, int screenHeight);

    RabbitSprite *getSprite() {
        return sprite;
    }

    void setFlap(float value) {
        velocity = 1.;
        gravitySpeed = 0.;
    }

    virtual void move();
    virtual void processGesture(InputGesture gesture);

    virtual void clearInputQueue() {
        while (!inputQueue.empty()) {
            inputQueue.pop();
        }
    }

    virtual void draw();
    virtual void setPosition(float x, float y);

    virtual float getX() {
        return sprite->getX();
    }

    virtual float getY() {
        return sprite->getY();
    }

    virtual int getCoinCount() {
        return sprite->getCoinCount();
    }

    virtual void looseCoin() {
        sprite->looseCoin();

        coinDrops = true;
        coinGravity = 0.;

        jiggle();
    }

    virtual bool hasLanded() {
        return sprite->isUnder(screenHeight - 5);
    }

    virtual void resetMovement() {
        velocity = 0.;
        sprite->setRotation(0.);
        sprite->setScale(1.);
        sprite->reset();
        clearInputQueue();
        setBoundaryCheck(true);
    }

    virtual void setBoundaryCheck(bool boundaryCheck) {
        this->boundaryCheck = boundaryCheck;
    }
};

#endif /* TRG_PHYSICALRABBIT_H */

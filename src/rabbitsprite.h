
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

#ifndef TRG_RABBITSPRITE_H
#define TRG_RABBITSPRITE_H

#include "config.h"

#include "coinbucketsprite.h"
#include "spritecontainer.h"
#include "stars.h"
#include "wing.h"


class RabbitSprite : public SpriteContainer
{
    static const float ANGLE_MAX;
    static const float MAX_ROTATION;

    static const int CENTER_X;
    static const int CENTER_Y;

    Stars *stars;
    Wing *leftWing;
    Wing *rightWing;

    WingFlap *leftWingFlap;
    WingFlap *rightWingFlap;

    CoinBucketSprite *coinBucket;

public:
    RabbitSprite(Texture *texture);

    CoinBucketSprite *getCoinBucket() {
        return this->coinBucket;
    }

    bool wingFlapAnimationRunning() {
        return leftWingFlap->running() || rightWingFlap->running();
    }

    void flapWing(bool left, bool right);

    virtual void setRotation(float angle) {
        SpriteContainer::setRotation(angle);
        coinBucket->setRotation(-angle / 2.);
    }

    virtual float getWidth() {
        return 50.;
    }

    virtual float getHeight() {
        return 60.;
    }

    bool isUnder(float y) {
        return getY() + getHeight() > y;
    }

    bool looseCoin() {
        bool result = coinBucket->looseCoin();
        switch (coinBucket->getCoinCount()) {
            case 8:
                setTexturePart(TextureParts::makeDamagedRabbitHead(getTexture(), 0));
                setCenter(CENTER_X, CENTER_Y);
                break;
            case 6:
                setTexturePart(TextureParts::makeDamagedRabbitHead(getTexture(), 1));
                setCenter(CENTER_X, CENTER_Y);
                break;
            case 4:
                setTexturePart(TextureParts::makeDamagedRabbitHead(getTexture(), 2));
                setCenter(CENTER_X, CENTER_Y);
                break;
            case 2:
                setTexturePart(TextureParts::makeDamagedRabbitHead(getTexture(), 3));
                setCenter(CENTER_X, CENTER_Y);
                break;
            default:
                /* do nothing */
                break;

        }

        stars->show();

        return result;
    }

    virtual void onAfterDraw() {
        SpriteContainer::onAfterDraw();
        stars->draw();
    }

    void tick() {
        stars->tick();
    }

    void accelerometerEvent(float x, float y, float z) {
        setRotation(45.*y/9.81);
    }

    int getCoinCount() {
        return coinBucket->getCoinCount();
    }

    void makeStoned() {
        setTexturePart(TextureParts::makeDamagedRabbitHead(getTexturePart()->getTexture(), SEVERITY_STONED));
    }

    void makeArrowed() {
    }

    void reset() {
        setTexturePart(TextureParts::makeRabbitHead(getTexturePart()->getTexture()));
        setCenter(CENTER_X, CENTER_Y);
        coinBucket->reset();
    }

};

#endif /* TRG_RABBITSPRITE_H */

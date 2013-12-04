
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

#ifndef CROSSHAIRS_H
#define CROSSHAIRS_H

#include "aimbar.h"
#include "util.h"
#include "gamescene.h"
#include "physicalrabbit.h"
#include "sprite.h"

class GameScene;
class PhysicalRabbit;

class Crosshairs
{
    static const int MAX_DISTANCE_2 = 2500;
    static const int MILLISECONDS_TO_SHOOT = 3000;
    static const int WAIT_TIME_BETWEEN_SHOTS = 3000;
    static const int RECOIL_STRENGTH = 50;

    GameScene *scene;
    Sprite *spriteGreen;
    Sprite *spriteRed;
    int screenWidth;
    int screenHeight;
    PhysicalRabbit *rabbit;
    float desiredX;
    float desiredY;
    bool isLoaded;

    long timeStamp;
    long timeOfLastShot;
    AimBar *aimBar;

    bool allowedToShoot() {
        return (timeOfLastShot == -1 || (currentTimeMillis() -
                    timeOfLastShot) > WAIT_TIME_BETWEEN_SHOTS);
    }

public:
    Crosshairs(GameScene *scene, Texture *texture, int width, int height);

    void setDistance(float distance)
    {
        spriteGreen->setDistance(distance);
        spriteRed->setDistance(distance);
    }

    bool getIsLoaded() {
        return isLoaded;
    }

    void setRabbit(PhysicalRabbit *rabbit) {
        this->rabbit = rabbit;
    }

    void draw() {
        if (isNearRabbit() && allowedToShoot()) {
            spriteGreen->draw();
        } else {
            spriteRed->draw();
        }

        if (this->isLoaded) {
            aimBar->setProgress(timeStamp > 0 ? std::min((float)1., (float)(currentTimeMillis() - timeStamp) / (float) MILLISECONDS_TO_SHOOT) : (float)0.);
            aimBar->draw();
        }
    }

    void setX(float x) {
        spriteRed->setX(x);
        spriteGreen->setX(x);
    }

    void setY(float y) {
        spriteRed->setY(y);
        spriteGreen->setY(y);
    }

    float getX() { return spriteRed->getX(); }
    float getY() { return spriteGreen->getY(); }

    void setPosition(float x, float y) {
        setX(x);
        setY(y);
    }

    void move(float dx, float dy) {
        setX(spriteRed->getX() + dx);
        setY(spriteRed->getY() + dy);
    }

    bool isNearRabbit();

    void setDesiredPosition(float x, float y) {
        desiredX = x;
        desiredY = y;
    }

    void ai();

    bool changeLoadingState() {
        if (isNearRabbit() && allowedToShoot()) {
            if (!isLoaded) {
                timeStamp = currentTimeMillis();
                isLoaded = true;
                return true;
            }
        } else {
            if (isLoaded) {
                timeStamp = -1;
                isLoaded = false;
                return true;
            }
        }

        return false;
    }

    void shoot();

    bool hits(PhysicalRabbit *o) {
        // TODO: hit test
        return true;
    }

};

#endif

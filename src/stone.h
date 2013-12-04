
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

#ifndef TRG_STONE_H
#define TRG_STONE_H

#include <math.h>

#include "sprite.h"
#include "textureparts.h"
#include "animation.h"
#include "gamescene.h"


class GameScene;

class Stone : public Sprite {
public:
    Stone(Texture *texture, GameScene *scene, int id);

    void setValue(float value);
    int getId() { return id; }

private:
    GameScene *scene;
    int id;
};

class StoneAnimation : public Animation {
public:
    StoneAnimation(Stone *stone)
        : Animation(0, 360, 5000, true)
        , _stone(stone)
    {
        setDuration(stone->getId()?5000:8000);
    }

    void setValue(float value) {
        _stone->setValue(value);
    }

    Stone *getStone() { return _stone; }

private:
        Stone *_stone;
};

#endif /* TRG_STONE_H */

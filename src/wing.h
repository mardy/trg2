
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

#ifndef TRG_WING_H
#define TRG_WING_H

#include "sprite.h"
#include "texturepart.h"
#include "animation.h"


class Wing : public Sprite
{
    bool left;

public:
    Wing(TexturePart *texturePart, bool left)
        : Sprite(texturePart)
        , left(left)
    {
    }

    void setFlap(float value) {
        if (left) {
            setRotation(45-2*45*sinf(value*M_PI/2));
        } else {
            setRotation(2*45*sinf(value*M_PI/2)-45);
        }
    }
};

class WingFlap : public Animation
{
public:
    WingFlap(Wing *wing)
        : Animation(0, 1, 300)
        , _wing(wing)
    {
    }

    void setValue(float value) {
        _wing->setFlap(value);
    }

private:
    Wing *_wing;
};

#endif /* TRG_WING_H */

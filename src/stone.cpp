
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

#include "stone.h"


Stone::Stone(Texture *texture, GameScene *scene, int id)
    : Sprite(TextureParts::makeStone(texture))
    , scene(scene)
    , id(id)
{
}

void
Stone::setValue(float value)
{
    if (id == 1) {
        setRotation(-value*3.);
        setPosition(scene->width() - value/360.*scene->width()/2,
                (1.-fabs(sinf(value/360.*M_PI)))*scene->height());
    } else {
        setRotation(value*5.);
        setPosition(value/360.*scene->width()/2,
                (1.-fabs(sinf(value/360.*M_PI)))*scene->height());
    }
    setScale(value/360.);
    setDistance(4.-4*(value/360.));
    if (value < 180) {
        setOpacity(value/180.);
    } else {
        setOpacity(1.);
    }
}

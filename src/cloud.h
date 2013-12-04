
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

#ifndef TRG_CLOUD_H
#define TRG_CLOUD_H

#include <stdlib.h>
#include <vector>

#include "sprite.h"
#include "texture.h"
#include "textureparts.h"
#include "animation.h"


class Cloud : public Sprite
{
    int id;
    float screenWidth;

public:
    Cloud(Texture *texture, int id, float screenWidth, float screenHeight)
        : Sprite(TextureParts::makeCloud(texture, id))
        , id(id)
        , screenWidth(screenWidth)
    {
        setPosition(rand()%((int)screenWidth), rand()%((int)(screenHeight/2)));
    }

    void step() {
        float x = getX() + (1 + .5 * id) * .2;
        if (x > screenWidth + getWidth()) {
            x = -getWidth();
        }

        setPosition(x, getY());
    }
};

class FadeInClouds : public Animation {
public:
    FadeInClouds(std::vector<Cloud*> *clouds)
        : Animation(0, 1, 5000)
        , _clouds(clouds)
    {
    }

    void setValue(float value) {
        for (Cloud *cloud: *_clouds) {
            cloud->setOpacity(value);
        }
    }

private:
    std::vector<Cloud*> *_clouds;
};

#endif /* TRG_CLOUD_H */

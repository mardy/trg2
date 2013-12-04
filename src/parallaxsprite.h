
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

#ifndef TRG_PARALLAXSPRITE_H
#define TRG_PARALLAXSPRITE_H

#include "sprite.h"
#include "texturepart.h"


class ParallaxSprite : public Sprite
{
    float screenWidth;
    float screenHeight;
    float xOffset;
    float yOffset;

public:
    ParallaxSprite(TexturePart *texturePart,
            float screenWidth, float screenHeight);

    void update(float x, float y) {
        float xpos = (x / screenWidth);
        float ypos = (y / screenHeight);
        setPosition(xpos + xOffset,
                screenHeight + yOffset + 5 +
                screenHeight * .14 * (1 - ypos));
    }

    void setXOffset(float xOffset) {
        this->xOffset = xOffset;
    }

    void setYOffset(float yOffset) {
        this->yOffset = yOffset;
    }

};

#endif /* TRG_PARALLAXSPRITE_H */

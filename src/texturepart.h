
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

#ifndef TRG_TEXTUREPART_H
#define TRG_TEXTUREPART_H

#include "mirror.h"
#include "texture.h"

#include <math.h>


class TexturePart
{
    Texture *texture;
    float x1;
    float y1;
    float x2;
    float y2;

    float width;
    float height;

    Mirror mirror;

    float texCoords[2*4];
    bool freeTexture;

public:
    TexturePart(Texture *texture, float x1, float y1, float x2, float y2);

    // This constructor takes the full texture size and owns the texture
    // (will free the texture when no longer used)
    TexturePart(Texture *texture);

    ~TexturePart();

    float setWidth(float width) {
        this->width = width;
        if (x2 > x1) {
            x2 = x1 + width;
        } else {
            x1 = x2 + width;
        }
        recalculateTexCoords();
    }

    float setHeight(float height) {
        this->height = height;
        if (y2 > y1) {
            y2 = y1 + height;
        } else {
            y1 = y2 + height;
        }
        recalculateTexCoords();
    }

    float getWidth() {
        if (width < 0) {
            width = fabs(x2-x1);
        }

        return width;
    }

    float getHeight() {
        if (height < 0) {
            height = fabs(y2-y1);
        }

        return height;
    }

    TexturePart* setMirror(Mirror mirror) {
        this->mirror = mirror;
        recalculateTexCoords();
        return this;
    }

    int getTextureName() {
        return texture->getTextureName();
    }

    float *getTexCoords() {
        return texCoords;
    }

    void recalculateTexCoords();

    Texture *getTexture() {
        return this->texture;
    }
};

#endif /* TRG_TEXTUREPART_H */

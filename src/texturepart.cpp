
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

#include "texturepart.h"

#include <string.h>

TexturePart::TexturePart(Texture *texture, float x1, float y1, float x2, float y2)
    : texture(texture)
    , x1(x1)
    , y1(y1)
    , x2(x2)
    , y2(y2)
    , width(-1.)
    , height(-1.)
    , mirror(NONE)
    , freeTexture(false)
{
    recalculateTexCoords();
}

TexturePart::TexturePart(Texture *texture)
    : texture(texture)
    , x1(0)
    , y1(0)
    , x2(texture->getWidth())
    , y2(texture->getHeight())
    , width(-1.)
    , height(-1.)
    , mirror(NONE)
    , freeTexture(true)
{
    recalculateTexCoords();
}

TexturePart::~TexturePart()
{
    if (freeTexture) {
        delete texture;
    }
}

void
TexturePart::recalculateTexCoords()
{
    float xa, xb, ya, yb;
    float w = texture->getWidth(),
          h = texture->getHeight();

    if (mirror == HORIZONTAL || mirror == BOTH) {
        xa = x2;
        xb = x1;
    } else {
        xa = x1;
        xb = x2;
    }

    if (mirror == VERTICAL || mirror == BOTH) {
        ya = y2;
        yb = y1;
    } else {
        ya = y1;
        yb = y2;
    }

    float coords[] = {
        xa/w, ya/h,
        xa/w, yb/h,
        xb/w, ya/h,
        xb/w, yb/h,
    };

    memcpy(texCoords, coords, sizeof(texCoords));
}

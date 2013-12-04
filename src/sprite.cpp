
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

#include "sprite.h"

#include "config.h"

#include <string.h>
#include <stdlib.h>


float Sprite::tintR = 1.;
float Sprite::tintG = 1.;
float Sprite::tintB = 1.;


Sprite::Sprite(TexturePart *texturePart)
    : texturePart(texturePart)
    , x(0)
    , y(0)
    , width(texturePart?texturePart->getWidth():0)
    , height(texturePart?texturePart->getHeight():0)
    , angle(0)
    , scale(1)
    , opacity(1)
    , hidden(false)
    , distance(0)
    , red(1.)
    , green(1.)
    , blue(1.)
{
    recalculateVtxCoords();
}

Sprite::Sprite(TexturePart *texturePart, float width, float height, float x, float y)
    : texturePart(texturePart)
    , x(x)
    , y(y)
    , width(width)
    , height(height)
    , angle(0)
    , scale(1)
    , opacity(1)
    , hidden(false)
    , distance(0)
    , red(1.)
    , green(1.)
    , blue(1.)
{
    recalculateVtxCoords();
}

void
Sprite::draw()
{
    if (hidden) {
        return;
    }

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();

    glTranslatef(x + eye_offset * distance, y, 0);
    glRotatef(angle, 0, 0, 1);
    glScalef(scale, scale, 1);

    onBeforeDraw();

    if (texturePart) {
        glEnableClientState(GL_TEXTURE_COORD_ARRAY);
        glEnableClientState(GL_VERTEX_ARRAY);

        glBindTexture(GL_TEXTURE_2D, texturePart->getTextureName());
        glTexCoordPointer(2, GL_FLOAT, 0, texturePart->getTexCoords());
        glVertexPointer(2, GL_FLOAT, 0, vtxCoords);
        glColor4f(tintR*red, tintG*green, tintB*blue, opacity);

        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

        glDisableClientState(GL_VERTEX_ARRAY);
        glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    }

    onAfterDraw();

    glPopMatrix();
}

void
Sprite::recalculateVtxCoords()
{
    float cx = width/2,
          cy = height/2;
    recalculateVtxCoords(cx, cy);
}

void
Sprite::recalculateVtxCoords(float cx, float cy)
{
    float tmp[] = {
        -cx, -cy,
        -cx, height-cy,
        width-cx, -cy,
        width-cx, height-cy,
    };
    memcpy(vtxCoords, tmp, sizeof(vtxCoords));
}

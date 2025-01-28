
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

#ifndef TRG_SPRITE_H
#define TRG_SPRITE_H

#include "texturepart.h"
#include "stereo.h"


class Sprite
{
    TexturePart *texturePart;

    float x;
    float y;
    float width;
    float height;
    float angle;
    float scale;
    float opacity;
    bool hidden;
    float distance;
    float red, green, blue;

    static float tintR, tintG, tintB;

    float vtxCoords[2*4];

    void recalculateVtxCoords();
    void recalculateVtxCoords(float x, float y);

public:
    Sprite(TexturePart *texturePart=NULL);
    Sprite(TexturePart *texturePart, float width, float height, float x=0, float y=0);

    void setColor(float r, float g, float b) {
        red = r;
        green = g;
        blue = b;
    }

    void setDistance(float distance) {
        this->distance = distance;
    }

    static void tintRed(float value) {
        tintR = 1;
        tintG = 1-value;
        tintB = 1-value;
    }

    static void tintBlack(float value) {
        tintR = tintG = tintB = (1-value);
    }

    bool getHidden() { return hidden; }
    void setHidden(bool hidden) { this->hidden = hidden; }

    TexturePart *getTexturePart() {
        return texturePart;
    }

    virtual void setTexturePart(TexturePart *texturePart) {
        this->texturePart = texturePart;
        this->width = texturePart->getWidth();
        this->height = texturePart->getHeight();
        this->recalculateVtxCoords();
    }

    virtual Texture *getTexture() {
        return this->texturePart->getTexture();
    }

    virtual void setPosition(float x, float y) {
        this->x = x;
        this->y = y;
    }

    virtual void setX(float x) {
        this->x = x;
    }

    virtual void setY(float y) {
        this->y = y;
    }

    virtual void setScale(float scale) {
        this->scale = scale;
    }

    virtual float getScale() {
        return this->scale;
    }

    virtual void setCenter(float cx, float cy) {
        recalculateVtxCoords(cx, cy);
    }

    virtual void setRotation(float angle) {
        this->angle = angle;
    }

    virtual float getRotation() {
        return this->angle;
    }

    void setOpacity(float opacity) {
        this->opacity = opacity;
    }

    float getOpacity() {
        return this->opacity;
    }

    void move(float dx, float dy) {
        x += dx;
        y += dy;
    }

    virtual float getX() {
        return this->x;
    }

    virtual float getY() {
        return this->y;
    }

    void setWidth(float width) {
        this->width = width;
        recalculateVtxCoords();
    }

    void setHeight(float height) {
        this->height = height;
        recalculateVtxCoords();
    }

    virtual float getWidth() {
        return this->width;
    }

    virtual float getHeight() {
        return this->height;
    }

    virtual void draw();

protected:
    virtual void updateTexturePart(TexturePart *texturePart) {
        this->texturePart = texturePart;
    }

    virtual void onBeforeDraw() {}
    virtual void onAfterDraw() {}

};

#endif /* TRG_SPRITE_H */

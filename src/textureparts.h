
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

#ifndef TRG_TEXTUREPARTS_H
#define TRG_TEXTUREPARTS_H

#include "texturepart.h"
#include "texture.h"


// Helper macro for defining a new getter function by taking the values
// directly from Inkscape's window (these are not image-space coordinates)
#define INKSCAPE_PART(FUNCTION_NAME, X, Y, W, H) \
    static TexturePart *FUNCTION_NAME(Texture *texture) { \
        return new TexturePart(texture, X, 1024-Y-H, X + W, 1024-Y); \
    }

class TextureParts
{
private:
    TextureParts() { /* no point in calling this */ }

public:
    static TexturePart *makeRabbitHead(Texture *texture)
    {
        return new TexturePart(texture, 70, 519, 70 + 100, 519 + 72);
    }

    static TexturePart *makeDamagedRabbitHead(Texture *texture, int severity)
    {
        float x, y;

        // The damaged heads are aligned next to each other in the atlas
        x = 20 + severity * 110;
        y = 661;

        return new TexturePart(texture, x, y, x + 100, y + 72);
    }

    static TexturePart *makeWing(Texture *texture)
    {
        return new TexturePart(texture, 12, 519, 12 + 55, 519 + 60);
    }

    static TexturePart *makeBucketBack(Texture *texture)
    {
        return new TexturePart(texture, 180, 519, 180 + 61, 519 + 58);
    }

    static TexturePart *makeBucket(Texture *texture)
    {
        return new TexturePart(texture, 260, 519, 260 + 61, 519 + 54);
    }

    static TexturePart *makeCoin(Texture *texture)
    {
        return new TexturePart(texture, 340, 519, 340 + 19, 519 + 19);
    }

    static TexturePart *makeSky(Texture *texture)
    {
        return new TexturePart(texture, 5, 0, 5 + 1, 0 + 1024);
    }

    static TexturePart *makeCloud(Texture *texture, int id)
    {
        switch (id % 3) {
            case 1:
                return new TexturePart(texture, 280, 0, 280 + 133, 0 + 188);
            case 2:
                return new TexturePart(texture, 20, 218, 20 + 200, 218 + 144);
            default:
                return new TexturePart(texture, 20, 0, 20 + 250, 0 + 195);
        }
    }

    static TexturePart *makeMeadow(Texture *texture) {
        return new TexturePart(texture, 20, 382, 20 + 930, 382 + 130);
    }

    static TexturePart *makeHills(Texture *texture) {
        return new TexturePart(texture, 234, 242, 234 + 790 - 1, 242 + 120);
    }

    static TexturePart *makeMountains(Texture *texture) {
        return new TexturePart(texture, 420, 0, 420 + 600, 0 + 210);
    }

    static TexturePart *makeCrosshairsRed(Texture *texture) {
        return new TexturePart(texture, 970, 426, 970 + 48, 426 + 48);
    }

    static TexturePart *makeCrosshairsGreen(Texture *texture) {
        return new TexturePart(texture, 970, 376, 970 + 48, 376 + 48);
    }

    static TexturePart *makeAimBarBackground(Texture *texture) {
        return new TexturePart(texture, 370, 519, 370 + 185, 519 + 24);
    }

    static TexturePart *makeAimBarForeground(Texture *texture) {
        return new TexturePart(texture, 370, 549, 370 + 185, 549 + 24);
    }

    static TexturePart *makeVirtualFinger(Texture *texture) {
        return new TexturePart(texture, 565, 521, 565 + 48, 521 + 48);
    }

    static TexturePart *makeRedStar(Texture *texture) {
        return new TexturePart(texture, 630, 519, 630 + 30, 519 + 30);
    }

    static TexturePart *makeYellowStar(Texture *texture) {
        return new TexturePart(texture, 630, 554, 630 + 30, 554 + 30);
    }

    static TexturePart *makeIntroTouchArrows(Texture *texture) {
        return new TexturePart(texture, 670, 519, 670 + 162, 519 + 75);
    }

    static TexturePart *makeIntroLeftArrow(Texture *texture) {
        return new TexturePart(texture, 849, 519, 849 + 45, 519 + 43);
    }

    static TexturePart *makeIntroUpArrow(Texture *texture) {
        return new TexturePart(texture, 917, 519, 917 + 32, 519 + 42);
    }

    static TexturePart *makeIntroRightArrow(Texture *texture) {
        return new TexturePart(texture, 963, 519, 963 + 41, 519 + 45);
    }

    INKSCAPE_PART(makeBlueFlower, 790, 258, 89, 131);
    INKSCAPE_PART(makeRedFlower, 881, 175, 132, 214);

    INKSCAPE_PART(makeBloodDrop1, 358, 470, 5, 4);
    INKSCAPE_PART(makeBloodDrop2, 355, 461, 8, 8);
    INKSCAPE_PART(makeBloodDrop3, 354, 453, 9, 6);

    INKSCAPE_PART(makeBloodStain, 872, 2, 150, 150);

    INKSCAPE_PART(makeBigArrowedHead, 15, 10, 136, 100);
    INKSCAPE_PART(makeBigStonedHead, 15, 116, 136, 100);

    INKSCAPE_PART(makeStone, 690, 280, 80, 80);
    INKSCAPE_PART(makeArrow, 675, 225, 200, 28);

    INKSCAPE_PART(makeThat, 933, 439, 90, 45);
    INKSCAPE_PART(makeRabbit, 942, 489, 80, 18);
    INKSCAPE_PART(makeGame, 767, 395, 163, 61);
    INKSCAPE_PART(makeTwo, 160, 5, 60, 80);

    INKSCAPE_PART(makeURL, 390, 230, 260, 50);
    INKSCAPE_PART(makeHelpTilt, 590, 13, 266, 136);
    INKSCAPE_PART(makeHelpTap, 232, 9, 328, 108);
    INKSCAPE_PART(makeFlyButton, 424, 120, 150, 96);
};

#endif /* TRG_TEXTUREPARTS_H */


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

#include "landscape.h"

#include "textureparts.h"
#include "parallaxsprite.h"

#define PLANT_FLOWER(GENERATOR, X, Y, MIRROR) \
    { \
        Sprite *flower = NULL; \
        flower = new Sprite(TextureParts::GENERATOR(texture)); \
        flower->setCenter(-getWidth()/2 - X, Y); \
        flower->getTexturePart()->setMirror(MIRROR); \
        addChildFront(flower); \
        flowers.push_back(flower); \
    }

Landscape::Landscape(Texture *texture, float width, float height)
    : SpriteContainer(TextureParts::makeSky(texture), width, height)
    , meadow(new ParallaxSprite(TextureParts::makeMeadow(texture),
                  width, height))
    , rabbit(NULL)
{
    setCenter(0, 0);

    meadow->setDistance(3.);

    addChildFront(meadow);

    for (int i=0; i < CLOUDS; i++) {
        Cloud *c = new Cloud(texture, i, width, height);
        c->setDistance(i*.5);
        addChildFront(c);
        clouds.push_back(c);
    }
    fadeInClouds = new FadeInClouds(&clouds);
    fadeInClouds->restart();

    ParallaxSprite *ps;
    TexturePart *part;
    int yOffset;

    for (int kind=0; kind<2; kind++) {
        if (kind == 0) {
            part = TextureParts::makeMountains(texture);
            yOffset = -90;
        } else {
            part = TextureParts::makeHills(texture);
            yOffset = -70;
        }

        for (int shift=-1; shift<=1; shift++) {
            if (shift == 0) continue;
            ps = new ParallaxSprite(part, width, height);
            ps->setDistance(5.-kind*2);
            ps->setYOffset(yOffset);
            ps->setXOffset(shift*width/3);
            parallaxSprites.push_back(ps);
        }
    }

    meadow->setYOffset(-15);
    parallaxSprites.push_back(meadow);

    PLANT_FLOWER(makeBlueFlower, 200, -30, NONE);
    PLANT_FLOWER(makeRedFlower, -30, 0, NONE);
    PLANT_FLOWER(makeRedFlower, -300, -40, HORIZONTAL);

    TexturePart *bloodTexture = TextureParts::makeBloodStain(texture);
    for (int i=0; i<BLOOD_STAINS; i++) {
        Sprite *blood = new Sprite(bloodTexture);
        bloodStains.push_back(blood);
        addChildFront(blood);
        blood->setOpacity(0);
    }
}

void
Landscape::step()
{
    for (Cloud *cloud: clouds) {
        cloud->step();
    }
}

void
Landscape::reposition()
{
    float x, y;

    if (rabbit != NULL) {
        Sprite *s = rabbit->getSprite();
        x = s->getX();
        y = s->getY();
    } else {
        x = getWidth() / 2;
        y = getHeight() / 2;
    }

    for (ParallaxSprite *parallaxSprite: parallaxSprites) {
        parallaxSprite->update(x, y);
    }

    for (Sprite *flower: flowers) {
        flower->setPosition(-x/3, getHeight() - y/3);
    }
}

void
Landscape::onAfterDraw()
{
    for (ParallaxSprite *parallaxSprite: parallaxSprites) {
        if (parallaxSprite != meadow) {
            parallaxSprite->draw();
        }
    }

    if (rabbit !=NULL) {
        rabbit->draw();
    }

    SpriteContainer::onAfterDraw();
}

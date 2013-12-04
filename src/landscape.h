
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

#ifndef TRG_LANDSCAPE_H
#define TRG_LANDSCAPE_H

#include "cloud.h"
#include "texture.h"
#include "physicalrabbit.h"
#include "parallaxsprite.h"
#include "spritecontainer.h"
#include "animation.h"

#include <vector>


class Landscape : public SpriteContainer
{
    std::vector<ParallaxSprite*> parallaxSprites;
    ParallaxSprite *meadow;

    static const int CLOUDS = 10;
    std::vector<Cloud*> clouds;
    std::vector<Sprite*> flowers;
    std::vector<Sprite*> bloodStains;
    FadeInClouds *fadeInClouds;

    PhysicalRabbit *rabbit;

public:
    Landscape(Texture *texture, float width, float height);

    void doJiggle(float value) {
        if (value <= 100) {
            setX(sin(value)*(float)(100-value)/10.);
            setY(cos(value)*(float)(100-value)/10.);
            Sprite::tintRed(1.-value/100.);
        } else {
            setX(0);
            setY(0);
            Sprite::tintRed(0.);
        }

        for (Sprite *s: bloodStains) {
            /* value: 0..300 */
            if (value < 50) {
                s->setDistance(3.-3.*value/50.);
                s->setScale(1.4*(.7+.3*value/50.));
            } else {
                s->setDistance(0.);
                s->setScale(1.4);
            }
            s->setOpacity(1.-value/300.);
            s->move(0, .02);
        }
    }

    void repositionBloodStains() {
        for (Sprite *s: bloodStains) {
            s->setPosition(rand() % (int)getWidth(),
               rand() % (int)getHeight());
            s->setRotation(rand() % 360);
            s->setScale(.5 + .005 * (float)(rand() % 100));
        }
    }

    void setRabbit(PhysicalRabbit *rabbit) {
        this->rabbit = rabbit;
    }

    void step();
    void reposition();

protected:
    virtual void onAfterDraw();
};

class JiggleAnimation : public Animation
{
public:
    JiggleAnimation(Landscape *landscape)
        : Animation(0, 300, 3000)
        , _landscape(landscape)
    {
    }

    void setValue(float value) {
        _landscape->doJiggle(value);
    }

private:
    Landscape *_landscape;
};

#endif /* TRG_LANDSCAPE_H */

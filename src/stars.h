
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

#ifndef TRG_STARS_H
#define TRG_STARS_H

#include "textureparts.h"
#include "sprite.h"

#include "config.h"

class Stars {
    Sprite *redStar;
    Sprite *yellowStar;
    float angle;
    float scale;
    bool visible;
    static const int STARS;
    static const float MAXSCALE;
    float distance;

public:
    Stars(Texture *texture)
        : redStar(NULL)
        , yellowStar(NULL)
        , angle(0.)
        , scale(1.)
        , visible(false)
        , distance(0)
    {
        redStar = new Sprite(TextureParts::makeRedStar(texture));
        redStar->setPosition(100, 0);
        yellowStar = new Sprite(TextureParts::makeYellowStar(texture));
        yellowStar->setPosition(150, 0);
    }

    void draw()
    {
        if (!visible) {
            return;
        }

        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();

        glRotatef(angle, 0, 0, 1);
        glScalef(scale, scale, 1);

        for (int i=0; i<STARS; i++) {
            glRotatef(360. / (float)STARS, 0, 0, 1);
            if (i % 2 == 0) {
                redStar->draw();
            } else {
                yellowStar->draw();
            }
        }

        glPopMatrix();
    }

    void show()
    {
        angle = 0.;
        scale = .3;
        distance = 20.;
        visible = true;
    }

    void tick()
    {
        if (visible) {
            redStar->setDistance(distance);
            yellowStar->setDistance(distance);
            redStar->setRotation(redStar->getRotation() + 5);
            yellowStar->setRotation(yellowStar->getRotation() - 5);
            if (scale > MAXSCALE) {
                visible = false;
            }
            angle += 2.;
            scale *= 1.05;
            if (distance > 0) {
                distance -= 1.;
            }
        }
    }

};

#endif /* TRG_STARS_H */


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

#ifndef TRG_AIMBAR_H
#define TRG_AIMBAR_H

#include "config.h"

#include "spritecontainer.h"
#include "texture.h"


class AimBar : public SpriteContainer
{
    Sprite *foreground;
    float progress;

public:
    AimBar(Texture *texture);

    void setProgress(float progress) {
        this->progress = progress;
        float width = progress * getTexturePart()->getWidth();

        foreground->getTexturePart()->setWidth(width);
        foreground->getTexturePart()->setMirror(HORIZONTAL);

        foreground->setPosition(0, getHeight() / 2);
        foreground->setWidth(width);
        foreground->setCenter(0, getHeight());
    }

protected:
    virtual void onAfterDraw() {
        SpriteContainer::onAfterDraw();

        glPushMatrix();
        glTranslatef(-getWidth() / 2, 0, 0);
        foreground->draw();
        glPopMatrix();
    }
};

#endif /* TRG_AIMBAR_H */

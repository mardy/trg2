
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

#ifndef TRG_FONT_H
#define TRG_FONT_H

#include "config.h"
#include "texturepart.h"
#include "sprite.h"

#include <list>


class Font {
private:
    float opacity;
    int spacing;
    Sprite *bestScore;
    Sprite *seconds;
    Sprite *coins;
    Sprite *digits[10];

    std::list<Sprite*> line;

    int xOffset; /* calculated width / 2 */

    int calculateWidth();
    void prependNumber(int number);

public:
    Font(Texture *texture, int spacing=3);
    void setSeconds(int seconds);
    void setCoins(int coins);
    void draw(int centerX, int centerY);
    void setOpacity(float opacity) {
        this->opacity = opacity;
    }
};

#endif /* TRG_FONT_H */

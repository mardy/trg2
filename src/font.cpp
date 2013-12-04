
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

#include "font.h"


#define SET_CENTER(x) {x->setCenter(0, x->getHeight()/2);}

Font::Font(Texture *texture, int spacing)
    : opacity(1.)
    , spacing(spacing)
    , bestScore(NULL)
    , seconds(NULL)
    , coins(NULL)
    , line()
{
    // Coordinate and size of "Best score" text (in atlas)
    int bestY = 742, bestH = 26;

    // Coordinates and size of digits in atlas
    int digitsY = 808, digitsH = 38;
    int digits__x_and_width[] = {
        /* x0, w0, x1, w1, etc.. */
        591, 26,
        626, 18,
        649, 26,
        678, 25,
        706, 27,
        737, 24,
        765, 27,
        795, 27,
        824, 25,
        853, 25,
    };

    bestScore = new Sprite(new TexturePart(texture, 19, bestY, 19 + 164, bestY+bestH));
    seconds = new Sprite(new TexturePart(texture, 187, bestY, 187 + 116, bestY+bestH));
    coins = new Sprite(new TexturePart(texture, 306, bestY, 306 + 75, bestY+bestH));
    SET_CENTER(bestScore);
    SET_CENTER(seconds);
    SET_CENTER(coins);

    for (int i=0; i<10; i++) {
        int xValue = digits__x_and_width[i*2];
        int wValue = digits__x_and_width[i*2+1];
        digits[i] = new Sprite(new TexturePart(texture, xValue,
                    digitsY, xValue+wValue, digitsY+digitsH));
        SET_CENTER(digits[i]);
    }
}

void
Font::setSeconds(int seconds)
{
    line.clear();
    prependNumber(seconds);
    line.push_front(NULL);
    line.push_front(NULL);
    line.push_front(bestScore);
    line.push_back(NULL);
    line.push_back(NULL);
    line.push_back(this->seconds);
    xOffset = calculateWidth() / 2;
}

void
Font::setCoins(int coins)
{
    line.clear();
    prependNumber(coins);
    line.push_front(NULL);
    line.push_front(NULL);
    line.push_front(bestScore);
    line.push_back(NULL);
    line.push_back(NULL);
    line.push_back(this->coins);
    xOffset = calculateWidth() / 2;
}

void
Font::draw(int centerX, int centerY)
{
    int x = centerX - xOffset;

    for (Sprite *s: line) {
        if (s) {
            s->setOpacity(opacity);
            s->setPosition(x, centerY);
            s->draw();
            x += s->getWidth();
        }

        x += spacing;
    }
}

int
Font::calculateWidth()
{
    int width = (line.size()-1) * spacing;

    for (Sprite *s: line) {
        if (s) {
            width += s->getWidth();
        }
    }

    return width;
}

void
Font::prependNumber(int number)
{
    int digit;
    bool written = false;

    while (number > 0 || !written) {
        digit = number % 10;

        line.push_front(digits[digit]);

        number /= 10;
        written = true;
    }
}

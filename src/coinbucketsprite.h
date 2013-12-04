
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

#ifndef TRG_COINBUCKETSPRITE_H
#define TRG_COINBUCKETSPRITE_H

#include <stdlib.h>

#include "spritecontainer.h"
#include "textureparts.h"

#include <vector>


class CoinBucketSprite : public SpriteContainer
{
    Sprite *bucketFront;
    Texture *texture;

    std::vector<Sprite*> coins;

    Sprite *makeCoin() {
        Sprite *coin = new Sprite(TextureParts::makeCoin(texture));
        coin->setPosition(coin->getWidth() + (rand()%(int)(getWidth()-coin->getWidth()*2)) - getWidth() / 2, 35 + rand()%10);
        return coin;
    }

public:
    CoinBucketSprite(Texture *texture);

    void reset() {
        setCoinCount(FULL_COIN_COUNT);
    }

    virtual void setRotation(float angle) {
        SpriteContainer::setRotation(angle);
        bucketFront->setRotation(angle / 2);
    }

    virtual bool looseCoin() {
        if (!coins.empty()) {
            coins.erase(coins.begin());
        }

        return coins.empty();
    }

    virtual int getCoinCount() {
        return coins.size();
    }

    virtual void setCoinCount(int count) {
        while (coins.size() > count) {
            coins.erase(coins.begin());
        }
        while (coins.size() < count) {
            coins.push_back(makeCoin());
        }
    }

protected:
    virtual void onAfterDraw()
    {
        for (Sprite *coin: coins) {
            coin->draw();
        }

        if (bucketFront != NULL) {
            bucketFront->draw();
        }
    }
};

#endif /* TRG_COINBUCKETSPRITE_H */


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

#include "menu.h"

#include "textureparts.h"


Menu::Menu(Texture *texture, int width, int height)
    : SpriteContainer()
    , font(new Font(texture))
    , width(width)
    , height(height)
    , that(new Sprite(TextureParts::makeThat(texture)))
    , rabbit(new Sprite(TextureParts::makeRabbit(texture)))
    , game(new Sprite(TextureParts::makeGame(texture)))
    , two(new Sprite(TextureParts::makeTwo(texture)))
    , flyButton(new Sprite(TextureParts::makeFlyButton(texture)))
    , url(new Sprite(TextureParts::makeURL(texture)))
    , credits(new Credits(width, height))
{
    // TODO: Save and restore the high scores from disk
    font->setSeconds(78);
    font->setCoins(3);

    that->setPosition(width / 2 - 170, 100);
    addChildBack(that);

    rabbit->setPosition(width / 2 - 70, 100);
    addChildBack(rabbit);

    game->setPosition(width / 2 + 70, 100);
    addChildBack(game);

    two->setPosition(width / 2 + 170, 100);
    addChildBack(two);

    flyButton->setPosition(width/2, height/2+50);
    addChildBack(flyButton);

    url->setPosition(width/2, height - 30);
    url->setCenter(url->getWidth()/2, url->getHeight());
    addChildBack(url);

    addChildFront(credits);
}

void
Menu::onAfterDraw()
{
    SpriteContainer::onAfterDraw();

    // XXX: Once we have score saving/restoring in place, uncomment this
    //font->draw(width/2, height/2 - 50);
}

void
Menu::setOpacity(float opacity)
{
    that->setOpacity(opacity);
    rabbit->setOpacity(opacity);
    game->setOpacity(opacity);
    two->setOpacity(opacity);
    flyButton->setOpacity(opacity);
    url->setOpacity(opacity);
    font->setOpacity(opacity);
    credits->setOpacity(opacity);
}

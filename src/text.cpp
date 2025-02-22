
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

#include "text.h"

#include "textrenderer.h"


Text::Text(const char *text)
    : Sprite(new TexturePart(TextRenderer(text).texture()))
{
}

Text::~Text()
{
    delete getTexturePart();
}

void
Text::set(const char *text)
{
    Texture *texture = getTexturePart()->getTexture();
    texture->updateFromData(TextRenderer(text).render(), true);
    setWidth(texture->getWidth());
    // XXX: We don't need to use setHeight for now - all text has same height
    //setHeight(texture->getHeight());
}

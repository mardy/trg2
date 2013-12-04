
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

#include "gameover.h"

#include <stdio.h>


GameOverAnimation::GameOverAnimation(GameOver *gameOver)
    : Animation(0, 100, 4000)
    , gameOver(gameOver)
{
}

void
GameOverAnimation::setValue(float value)
{
    gameOver->setValue(value);
}

GameOver::GameOver(Texture *texture)
    : SpriteContainer(TextureParts::makeBigStonedHead(texture))
    , gameOverType(GameOver::FAILED_STONE)
    , animation(NULL)
    , ran(false)
    , m_text("Game over!")
{
    animation = new GameOverAnimation(this);
    m_text.setScale(2);
    m_text.setColor(1., 0., 0.);
    addChildFront(&m_text);
    m_text.setPosition(0, getHeight()/2);
}

void
GameOver::setGameOverType(enum GameOverType gameOverType)
{
    if (this->gameOverType != gameOverType) {
        this->gameOverType = gameOverType;

        if (gameOverType == FAILED_ARROW) {
            setTexturePart(TextureParts::makeBigArrowedHead(getTexturePart()->getTexture()));
        } else if (gameOverType == FAILED_STONE) {
            setTexturePart(TextureParts::makeBigStonedHead(getTexturePart()->getTexture()));
        }
    }
}

void
GameOver::setValue(float value)
{
    setRotation(sqrt(value)*360.);
    setScale(value/100. * 2.);
    setOpacity(value/100.);
    setDistance(4.-4.*value/100.);

    char tmp[100];
    sprintf(tmp, "YOU ARE DEAD! %.0f", value);
    m_text.set(tmp);
}

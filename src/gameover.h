
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

#ifndef TRG_GAMEOVER_H
#define TRG_GAMEOVER_H

#include "spritecontainer.h"
#include "textureparts.h"
#include "animation.h"
#include "text.h"


class GameOver;

class GameOverAnimation : public Animation
{
    public:
        GameOverAnimation(GameOver *gameOver);
        void setValue(float value);

    private:
        GameOver *gameOver;
};

class GameOver : public SpriteContainer
{
    public:
        enum GameOverType {
            SUCCESS,
            FAILED_STONE,
            FAILED_ARROW,
        };

        GameOver(Texture *texture);
        void setGameOverType(enum GameOverType gameOverType);

        void setValue(float value);

        void reset() { ran = false; animation->stop(); setHidden(true); }
        void start() { if (!ran) { ran = true; animation->restart(); setHidden(false); } }
        bool finished() { return ran && !animation->running(); }

    private:
        enum GameOverType gameOverType;
        GameOverAnimation *animation;
        bool ran;
        Text m_text;
};

#endif /* TRG_GAMEOVER_H */

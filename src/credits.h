
/**
 * That Rabbit Game 2: Stone Age Rabbit Hunt
 * Copyright (C) 2014 Thomas Perl <m@thp.io>
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

#ifndef TRG_CREDITS_H
#define TRG_CREDITS_H

#include "spritecontainer.h"
#include "text.h"


class Credits : public SpriteContainer
{
    public:
        Credits(int width, int height);
        virtual void onBeforeDraw();

    private:
        int m_width;
        int m_height;
        Text m_text;
        int m_current_line;
        int m_current_step;
        int m_current_frame;
};

#endif /* TRG_CREDITS_H */

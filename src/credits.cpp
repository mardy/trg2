

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

#include "credits.h"

#include <stdio.h>

static const char *
credits[] = {
    "A game by",
    "Thomas Perl",
    "Code contributions by:",
    "Alberto Mardegan",
    "Music 'Crap on the dancefloor' by:",
    "Axel Ovekrans",
    "Sound effects:",
    "beep by Empty bell CC-BY 3.0",
    "exasperated by Reitanna CC-0",
    "damn by Reitanna CC-0",
    "life lost game over by noirenex CC-0",
    "Beating wings by juskiddink CC-BY 3.0",
    "giggle by Reitanna CC-0",
    "low laugh by Reitanna CC-0",
    "Laser shotgun loading by beman87 CC-BY 3.0",
    "Explosion_17 by tcpp CC-BY 3.0",
    "don't be afraid by Reitanna CC-0",
    "plead three times by Reitanna CC-0",
    "",
};

#define CREDITS_LEN (sizeof(credits)/sizeof(credits[0]))
#define FRAMES_PER_STEP 2

Credits::Credits(int width, int height)
    : SpriteContainer()
    , m_width(width)
    , m_height(height)
    , m_text("...")
    , m_current_line(-1)
    , m_current_step(100)
    , m_current_frame(0)
{
    addChildFront(&m_text);
}

void
Credits::onBeforeDraw()
{
    m_current_frame++;
    if (m_current_frame >= ((stereo_enabled || stereo_anaglyph) ? FRAMES_PER_STEP * 2 : FRAMES_PER_STEP)) {
        m_current_frame = 0;

        m_current_step++;
        if (m_current_step >= 100) {
            m_current_line++;
            m_current_step = 0;

            if (m_current_line == CREDITS_LEN) {
                m_current_line = 0;
            }

            m_text.set(credits[m_current_line]);
        }
    }

    const float SCALE = 2.0;
    if (m_current_step < 20) {
        m_text.setDistance(SCALE * 0.05 * m_current_step);
        m_text.setScale(SCALE * 0.05 * m_current_step);
    } else if (m_current_step < 80) {
        m_text.setScale(SCALE);
        m_text.setDistance(SCALE * 1.f);
    } else {
        m_text.setScale(SCALE * 0.05 * (100-m_current_step));
        m_text.setDistance(SCALE * 0.05 * (100-m_current_step));
    }
    m_text.setOpacity(getOpacity());
    m_text.setPosition(m_width / 2 + 50 - m_current_step, m_height / 2 - 30);

    SpriteContainer::onBeforeDraw();
}

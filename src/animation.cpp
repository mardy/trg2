
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


/**
 * That Rabbit Game - Mini Animation Framework
 * Copyright (c) 2011-11-23 Thomas Perl <thp.io/about>
 **/

#include "animation.h"
#include "util.h"


void
Animation_TimerCallback(int interval, void *data)
{
    Animation *animation = (Animation*)data;
    animation->sdl_timer_callback();
}


Animation::Animation(float start, float end, int duration, bool loop)
    : _start(start)
    , _end(end)
    , started(0)
    , duration(duration)
    , timer(NULL)
    , forward(true)
    , loop(loop)
{
}

void
Animation::rewind()
{
    forward = false;

    if (timer != NULL) {
        int elapsed = currentTimeMillis() - started;
        int remaining = duration - elapsed;
        started = currentTimeMillis() - remaining;
    } else {
        updateValue(1.);
        started = currentTimeMillis();
        timer = new Timer(10, Animation_TimerCallback, (void*)this);
    }
}

void
Animation::restart()
{
    forward = true;
    updateValue(0.);
    started = currentTimeMillis();

    if (timer == NULL) {
        timer = new Timer(10, Animation_TimerCallback, (void*)this);
    }
}

void
Animation::stop()
{
    if (timer != NULL) {
        timer->dispose();
        timer = NULL;
    }

    updateValue(forward?1.:0.);
}

void
Animation::sdl_timer_callback()
{
    int now = currentTimeMillis();
    float t = ((float)(now - this->started)) / ((float)this->duration);

    if (t >= 1.) {
        if (this->loop) {
            this->restart();
        } else {
            this->stop();
            return;
        }
    }

    this->updateValue(this->forward?t:(1.-t));
}

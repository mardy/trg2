
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

#ifndef TRG_ANIMATION_H
#define TRG_ANIMATION_H

/**
 * That Rabbit Game - Mini Animation Framework
 * Copyright (c) 2011-11-23 Thomas Perl <thp.io/about>
 **/

#include "config.h"
#include "timer.h"


void
Animation_TimerCallback(int interval, void *data);

class Animation
{
    public:
        Animation(float start, float end, int duration, bool loop=false);

        void rewind();
        void restart();
        void stop();

        bool running() { return timer != NULL; }
        void setDuration(int duration) { this->duration = duration; }

        void sdl_timer_callback();

    protected:
        /* Override this to get a special easing curve */
        virtual float easeValue(float value) { return value; }

        /* Override this to receive animation values  */
        virtual void setValue(float value) = 0;

    private:
        float updateValue(float value) {
            setValue(easeValue(scaleValue(value)));
        }

        float scaleValue(float value) {
            return _start * (1.-value) + _end * value;
        }

        float _start;
        float _end;
        bool forward;
        bool loop;
        int started;
        int duration;
        Timer *timer;
};

#endif /* TRG_ANIMATION_H */

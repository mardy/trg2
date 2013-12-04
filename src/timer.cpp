
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

#include "timer.h"

#include <stdlib.h>

Timer::Timer(int interval, TimerCallback callback, void *data)
    : m_interval(interval)
    , m_callback(callback)
    , m_data(data)
    , m_last_tick(currentTimeMillis())
    , m_disposed(false)
    , m_next(m_timer)
{
    m_timer = this;
}

Timer::~Timer()
{
    if (m_timer == this) {
        m_timer = m_next;
    }
}

void
Timer::process()
{
    long now = currentTimeMillis();

    Timer *timer = m_timer;
    while (timer != NULL) {
        long next_tick = timer->m_last_tick + timer->m_interval;
        if (next_tick < now && !timer->m_disposed) {
            timer->m_last_tick = now;
            timer->m_callback(timer->m_interval, timer->m_data);
        }

        timer = timer->m_next;
    }

    timer = m_timer;
    while (timer != NULL) {
        Timer *next = timer->m_next;
        if (next && next->m_disposed) {
            timer->m_next = next->m_next;
            delete next;
        }
        timer = timer->m_next;
    }
}

Timer *
Timer::m_timer = NULL;

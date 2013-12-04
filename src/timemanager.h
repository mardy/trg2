
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

#ifndef TRG_TIMEMANAGER_H
#define TRG_TIMEMANAGER_H

#include "util.h"


class TimeManager
{
    static const int UPDATE_INTERVAL = 500;

    long duration;
    long elapsed;
    long lastUpdate;

public:
    TimeManager()
        : duration(DEFAULT_DURATION*1000)
        , elapsed(0)
        , lastUpdate(-1)
    {
    }

    void update() {
        long now = currentTimeMillis();
        if (now - lastUpdate > UPDATE_INTERVAL) {
            if (lastUpdate > 0) {
                elapsed += (now - lastUpdate);
            }
            lastUpdate = now;
        }
    }

    void onPause() {
        if (lastUpdate > 0) {
            elapsed += (currentTimeMillis() - lastUpdate);
        }
        lastUpdate = -1;
    }

    long getRemainingTimeMillis() {
        return std::max((long)0, duration - elapsed);
    }

    long getDuration() {
        return duration;
    }

    bool timeIsUp() {
        return getRemainingTimeMillis() == 0;
    }

    long getElapsed() {
        return elapsed;
    }

    void setElapsed(long elapsed) {
        this->elapsed = elapsed;
    }

    void reset() {
        lastUpdate = -1;
        elapsed = 0;
    }
};

#endif /* TRG_TIMEMANAGER_H */

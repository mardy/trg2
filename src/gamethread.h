
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

#ifndef TRG_GAMETHREAD_H
#define TRG_GAMETHREAD_H

#include "config.h"

#include "gamescene.h"
#include "physicalrabbit.h"
#include "landscape.h"
#include "crosshairs.h"
#include "timemanager.h"
#include "timer.h"


class Crosshairs;
class GameScene;
class Landscape;

void GameThread_TimerCallback(int interval, void *data);

class GameThread
{
    Timer *timer;

    GameScene *scene;
    PhysicalRabbit *rabbit;
    Crosshairs *crosshairs;
    Landscape *landscape;
    TimeManager *timeManager;
    long lastFlapSound;
    bool justLanded;
    int flapReleased;
    int liftedFromGround;

public:
    GameThread(GameScene *scene, PhysicalRabbit *rabbit, Landscape *landscape,
            Crosshairs *crosshairs, TimeManager *timeManager);

    void run() {
        timer = new Timer(10, GameThread_TimerCallback, this);
    }

    bool levelFinished();

    void doQuit() {
        timer->dispose();
    }

public:
    void step();
};

#endif /* TRG_GAMETHREAD_H */

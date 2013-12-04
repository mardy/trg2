
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

#include "gamethread.h"

#include "inputgesture.h"
#include "soundplayer.h"

#include <stdio.h>


void
GameThread_TimerCallback(int interval, void *data)
{
    GameThread *gameThread = (GameThread*)data;
    gameThread->step();
}

GameThread::GameThread(GameScene *scene, PhysicalRabbit *rabbit,
        Landscape *landscape, Crosshairs *crosshairs,
        TimeManager *timeManager)
    : timer(0)
    , scene(scene)
    , rabbit(rabbit)
    , crosshairs(crosshairs)
    , landscape(landscape)
    , timeManager(timeManager)
    , lastFlapSound(0)
    , justLanded(false)
    , flapReleased(0)
    , liftedFromGround(0)
{
}

bool
GameThread::levelFinished()
{
    return (rabbit->getCoinCount() == 0 || timeManager->timeIsUp());
}

void
GameThread::step()
{
    InputGesture gesture = GESTURE_NOTHING;

    switch (scene->getCurrentState()) {
        case GameScene::INTRO:
            if (scene->getNextInputGesture() != GESTURE_NOTHING) {
                scene->fadeTo(GameScene::RUNNING);
            }
            landscape->step();
            break;
        case GameScene::RUNNING:
            if (levelFinished()) {
                scene->setCurrentState(GameScene::EXTRO);
                return;
            } else if (scene->rabbitHitByStone()) {
                scene->setCurrentState(GameScene::DIED_STONE);
            }

            gesture = scene->getNextInputGesture();
            rabbit->processGesture(gesture);

            rabbit->move();
            crosshairs->ai();

            if (crosshairs->changeLoadingState()) {
                if (crosshairs->getIsLoaded()) {
                    SoundPlayer::play(SoundPlayer::LOAD, .5);
                } else {
                    SoundPlayer::play(SoundPlayer::DAMN, .5);
                }
            }

            if (rabbit->hasLanded()) {
                if (!justLanded) {
                    scene->rabbitGroundUpdate(true);
                    SoundPlayer::play(SoundPlayer::WTF, .5);
                    justLanded = true;
                }

                /* FIXME: Make sure the X-movement of rabbit is stopped */
            } else {
                if (justLanded) {
                    scene->rabbitGroundUpdate(false);
                    liftedFromGround = currentTimeMillis();
                    justLanded = false;
                }
            }

            if (liftedFromGround > 0) {
                if (liftedFromGround + TILT_HELP_DURATION < currentTimeMillis()) {
                    scene->liftedFromGround();
                    liftedFromGround = 0;
                }
            }

            rabbit->getSprite()->tick();
            landscape->step();
            timeManager->update();

            break;
        case GameScene::DIED_STONE:
        case GameScene::DIED_ARROW:
            rabbit->getSprite()->makeStoned();
            rabbit->move();
            rabbit->getSprite()->tick();
            landscape->step();
            if (rabbit->hasLanded()) {
                scene->getGameOver()->start();
                if (scene->getGameOver()->finished()) {
                    scene->fadeTo(GameScene::INTRO);
                }
            }
            break;
        case GameScene::EXTRO:
            if (!rabbit->getSprite()->wingFlapAnimationRunning()) {
                if (flapReleased == 0) {
                    rabbit->processGesture(GESTURE_TAP_BEGIN);
                    flapReleased = currentTimeMillis();
                } else {
                    rabbit->processGesture(GESTURE_TAP_END);
                    flapReleased = 0;
                }
            } else if (currentTimeMillis() - flapReleased > 500) {
                flapReleased = 0;
            }

            rabbit->move();
            landscape->step();

            rabbit->getSprite()->tick();

            rabbit->getSprite()->setScale(
                    rabbit->getSprite()->getScale()*.997);

            if (rabbit->getY() + rabbit->getSprite()->getHeight() < -40) {
                scene->finishLevel();
            }

            break;
    }
}

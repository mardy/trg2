
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

#ifndef TRG_GAMESCENE_H
#define TRG_GAMESCENE_H

#include <vector>

#include "config.h"
#include "event.h"

#include "sprite.h"
#include "crosshairs.h"
#include "landscape.h"
#include "physicalrabbit.h"
#include "inputgesture.h"
#include "timemanager.h"
#include "gamethread.h"
#include "stone.h"
#include "gameover.h"
#include "animation.h"
#include "menu.h"


class Crosshairs;
class GameThread;
class JiggleAnimation;
class StoneAnimation;
class BeginAnimation;

class GameScene
{
public:
    enum CurrentState {
        UNDEFINED,
        INTRO,
        RUNNING,
        DIED_STONE,
        DIED_ARROW,
        EXTRO,
    };

private:
    PhysicalRabbit *rabbit;
    Crosshairs *crosshairs;
    Landscape *landscape;
    JiggleAnimation *jiggleAnimation;
    Sprite *coin;
    Sprite *timeDisplay;
    GameThread *gameThread;
    TimeManager *timeManager;
    InputGesture input;
    CurrentState currentState;
    std::vector<StoneAnimation*> stones;
    GameOver *gameOver;
    Menu *menu;
    BeginAnimation *beginAnimation;
    Sprite *tapHelp;
    Sprite *tiltHelp;
    float currentTint;
    float masterScale;
    int w;
    int h;

    int viewport_width;
    int viewport_height;

public:
    void keyEvent(enum KeyEvent event, enum Key key);
    void touchEvent(enum TouchEvent event, float x, float y, int finger);
    void accelerometerEvent(float x, float y, float z);

    void jiggle();

    GameScene();

    virtual void initializeGL(int width, int height);
    virtual void paintGL();
    void paintSingle();

    GameOver *getGameOver() { return gameOver; }

    bool rabbitHitByStone();

    int width() { return this->w; }
    int height() { return this->h; }

    void restartGameThread();
    void stopGameThread();

    void fadeTo(CurrentState targetState);
    void setCurrentTint(float currentTint) {
        this->currentTint = currentTint;
    }

    void finishLevel() {
        fadeTo(INTRO);
    }

    CurrentState getCurrentState() { return currentState; }
    void setCurrentState(CurrentState currentState);

    InputGesture getNextInputGesture() {
        InputGesture result = input;
        input = GESTURE_NOTHING;
        return result;
    }

    void resetStones();

    void rabbitGroundUpdate(bool landed);
    void liftedFromGround();

};

class BeginAnimation : public Animation
{
    private:
        GameScene *scene;
        GameScene::CurrentState targetState;

    public:
        BeginAnimation(GameScene *scene)
            : Animation(0., 1., 1000)
            , scene(scene)
            , targetState(GameScene::UNDEFINED)
        {
        }

        void setTargetState(GameScene::CurrentState targetState) {
            this->targetState = targetState;
        }

        void setValue(float value) {
            switch (targetState) {
                case GameScene::RUNNING:
                    scene->setCurrentTint(DEFAULT_TINT_MENU*(1.-value));
                    break;
                case GameScene::INTRO:
                    scene->setCurrentTint(DEFAULT_TINT_MENU*value);
                    break;
                default:
                    break;
            }

            if (value == 1.) {
                scene->setCurrentState(targetState);
            }
        }
};

#endif /* TRG_GAMESCENE_H */

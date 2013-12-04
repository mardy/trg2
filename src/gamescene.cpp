
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

#include "gamescene.h"

#include "config.h"
#include "texture.h"
#include "timedisplay.h"
#include "physicalrabbit.h"
#include "rabbitsprite.h"
#include "stereo.h"

#include "text.h"

#include <algorithm>


GameScene::GameScene()
    : rabbit(NULL)
    , crosshairs(NULL)
    , landscape(NULL)
    , coin(NULL)
    , timeDisplay(NULL)
    , gameThread(NULL)
    , timeManager(new TimeManager())
    , input(GESTURE_NOTHING)
    , currentState(UNDEFINED)
    , stones()
    , gameOver(NULL)
    , menu(NULL)
    , beginAnimation(NULL)
    , tapHelp(NULL)
    , tiltHelp(NULL)
    , currentTint(DEFAULT_TINT_MENU)
    , masterScale(1.)
    , w(0)
    , h(0)
    , viewport_width(0)
    , viewport_height(0)
{
    setCurrentState(INTRO);
    beginAnimation = new BeginAnimation(this);
}

void
GameScene::initializeGL(int width, int height)
{
    viewport_width = width;
    viewport_height = height;

    this->w = width;
    this->h = height;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrthof(0, w, h, 0, 0, 1);

    if (h > w) {
        glTranslatef(w/2, h/2, 0);
        glRotatef(90, 0, 0, 1);
        glTranslatef(-h/2, -w/2, 0);
        std::swap(h, w);
    }

    masterScale = (float)h / 480. * 1.2;
    width = w = (float)w / masterScale;
    height = h = (float)h / masterScale;

    glClearColor(0, 0, 0, 0);

    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    Texture *mainTexture = Texture::l44();
    glBindTexture(GL_TEXTURE_2D, mainTexture->getTextureName());
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    rabbit = new PhysicalRabbit(this, new RabbitSprite(mainTexture), new Sprite(TextureParts::makeCoin(mainTexture)), width, height);
    rabbit->setPosition(width/2, height/2);
    rabbit->getSprite()->setHidden(true);
    rabbit->getSprite()->setDistance(1);

    crosshairs = new Crosshairs(this, mainTexture, width, height);
    crosshairs->setRabbit(rabbit);
    crosshairs->setDistance(0);

    landscape = new Landscape(mainTexture, width, height);
    landscape->setRabbit(rabbit);

    jiggleAnimation = new JiggleAnimation(landscape);

    coin = new Sprite(TextureParts::makeCoin(mainTexture));
    coin->setDistance(1);

    timeDisplay = new TimeDisplay(mainTexture, timeManager);
    timeDisplay->setPosition(width - timeDisplay->getWidth()-10, 10);
    timeDisplay->setDistance(0);

    for (int i=0; i<STONE_COUNT; i++) {
        Stone *stone = new Stone(mainTexture, this, i);
        stone->setDistance(0);
        StoneAnimation *stoneAnimation = new StoneAnimation(stone);
        stoneAnimation->restart();
        stones.push_back(stoneAnimation);
        landscape->addChildFront(stone);
    }

    gameOver = new GameOver(mainTexture);
    gameOver->setPosition(width/2, height/2);
    gameOver->reset();
    landscape->addChildFront(gameOver);

    menu = new Menu(mainTexture, width, height);

    tapHelp = new Sprite(TextureParts::makeHelpTap(mainTexture));
    tapHelp->setPosition(width/2, height/2);
    tapHelp->setPosition(width/2, tapHelp->getHeight()/2 + 40);
    tapHelp->setDistance(0);

    tiltHelp = new Sprite(TextureParts::makeHelpTilt(mainTexture));
    tiltHelp->setPosition(width/2, tiltHelp->getHeight()/2 + 40);
    tiltHelp->setDistance(0);

    restartGameThread();
}

void
GameScene::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT);

    if (stereo_enabled) {
        /* Paint left eye view */
        glViewport(0, 0, viewport_width/2, viewport_height);
        eye_offset = -4;
        landscape->reposition();
        paintSingle();

        /* Paint right eye view */
        glViewport(viewport_width/2, 0, viewport_width/2, viewport_height);
        eye_offset = 4;
        landscape->reposition();
        paintSingle();
    } else {
        glViewport(0, 0, viewport_width, viewport_height);
        eye_offset = 0;
        landscape->reposition();
        paintSingle();
    }
}

void
GameScene::paintSingle()
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glScalef(masterScale, masterScale, 1);

    if (landscape != NULL) {
        if (currentState != GameScene::RUNNING) {
            Sprite::tintBlack(currentTint);
        }
        landscape->draw();
    }

    if (currentState != GameScene::RUNNING) {
        menu->setOpacity(currentTint/DEFAULT_TINT_MENU);
        Sprite::tintBlack(0);
        menu->draw();
    }

    switch (currentState) {
        case GameScene::INTRO:
            break;

        case GameScene::RUNNING:
            if (crosshairs != NULL) {
                crosshairs->draw();
            }

            tapHelp->draw();
            tiltHelp->draw();

            /* fall through */

        case GameScene::EXTRO:
            if (rabbit != NULL && coin != NULL) {
                int coins = rabbit->getCoinCount();

                /* OSD Elements: */
                for (int i=0; i<coins; i++) {
                    coin->setPosition(20+i*coin->getWidth()/2, 20);
                    coin->draw();
                }

                if (timeDisplay != NULL) {
                    timeDisplay->draw();
                }
            }
            break;
    }
}


void
GameScene::restartGameThread()
{
    stopGameThread();

    if (rabbit && landscape && crosshairs && timeManager) {
        gameThread = new GameThread(this, rabbit, landscape, crosshairs,
                timeManager);
        gameThread->run();
    }
}


void
GameScene::stopGameThread()
{
    if (gameThread != NULL) {
        gameThread->doQuit();
        delete gameThread;
        gameThread = NULL;
    }

    if (timeManager != NULL) {
        timeManager->onPause();
    }
}

void
GameScene::keyEvent(enum KeyEvent event, enum Key key)
{
    if (event == KEY_DOWN) {
        if (key == K_UP) {
            input = GESTURE_TAP_BEGIN;
        } else if (key == K_LEFT) {
            input = GESTURE_LEFT;
        } else if (key == K_RIGHT) {
            input = GESTURE_RIGHT;
        }
    } else if (event == KEY_UP) {
        if (key == K_UP) {
            input = GESTURE_TAP_END;
        } else {
            input = GESTURE_NOTHING;
        }
    }
}

void
GameScene::touchEvent(enum TouchEvent event, float x, float y, int finger)
{
    if (event == TOUCH_DOWN) {
        input = GESTURE_TAP_BEGIN;
    } else if (event == TOUCH_UP) {
        input = GESTURE_TAP_END;
    }
}

void
GameScene::accelerometerEvent(float x, float y, float z)
{
    if (rabbit != NULL) {
        RabbitSprite *sprite = rabbit->getSprite();
        if (sprite != NULL) {
            sprite->accelerometerEvent(x, y, z);
        }
    }
}

void
GameScene::jiggle()
{
    landscape->repositionBloodStains();
    jiggleAnimation->restart();
}

void
GameScene::setCurrentState(CurrentState currentState)
{
    this->currentState = currentState;

    if (landscape != NULL) {
        switch (currentState) {
            case INTRO:
                input = GESTURE_NOTHING;
                rabbit->getSprite()->setHidden(true);
                setCurrentTint(DEFAULT_TINT_MENU);
                break;
            case EXTRO:
                rabbit->setBoundaryCheck(false);
                break;
            case RUNNING:
                tapHelp->setHidden(true);
                tiltHelp->setHidden(true);
                gameOver->reset();
                rabbit->resetMovement();
                rabbit->setPosition(width()/2, height()/2);
                timeManager->reset();
                rabbit->getSprite()->setHidden(false);
                resetStones();
                break;
            case DIED_STONE:
                gameOver->setGameOverType(GameOver::FAILED_STONE);
                break;
            case DIED_ARROW:
                break;
        }
    }
}

bool
GameScene::rabbitHitByStone()
{
    int rabbitX = rabbit->getX();
    int rabbitY = rabbit->getY();

    for (StoneAnimation *s: stones) {
        Stone *stone = s->getStone();
        int stoneX = stone->getX();
        int stoneY = stone->getY();
        float stoneScale = stone->getScale();

        if (pow((stoneX-rabbitX), 2.) + pow((stoneY-rabbitY), 2.) < pow(STONE_HIT_DISTANCE, 2.) && stoneScale > .5) {
            stone->setHidden(true);
            return true;
        }
    }

    return false;
}

void
GameScene::resetStones()
{
    for (StoneAnimation *s: stones) {
        s->restart();
        s->getStone()->setHidden(false);
    }
}

void
GameScene::fadeTo(CurrentState targetState)
{
    if (!beginAnimation->running()) {
        beginAnimation->setTargetState(targetState);
        beginAnimation->restart();
    }
}

void
GameScene::rabbitGroundUpdate(bool landed)
{
    tapHelp->setHidden(!landed);
    tiltHelp->setHidden(landed);
}

void
GameScene::liftedFromGround()
{
    tiltHelp->setHidden(true);
}

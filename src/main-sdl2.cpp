
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

#ifdef TRG_USE_SDL2

#include "rabbitgame.h"
#include "stereo.h"

#include "SDL.h"
#include <ctime>

int
main(int argc, char *argv[])
{
    srand(time(NULL));

    /* We're wayyy too shabby to use getopt or argp... */
    for (int i=1; i<argc; i++) {
        if (strcmp(argv[i], "--stereo") == 0) {
            stereo_enabled = true;
        } else if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0) {
            fprintf(stderr, "Usage: %s [--stereo]\n\n", argv[0]);
            fprintf(stderr, "    --stereo ...... Render in side-by-side stereo 3D\n");
            return 1;
        }
    }

    if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_GAMECONTROLLER) != 0) {
        fprintf(stderr, "SDL_Init failed: %s\n", SDL_GetError());
        return 1;
    }

    int flags = SDL_WINDOW_OPENGL;
#if defined(__wii__) || defined(__gamecube__)
    flags |= SDL_WINDOW_FULLSCREEN;
#endif
    SDL_Window *w = SDL_CreateWindow("That Rabbit Game 2",
                                     SDL_WINDOWPOS_UNDEFINED,
                                     SDL_WINDOWPOS_UNDEFINED,
                                     854, 480, flags);
    SDL_GL_CreateContext(w);

    int width, height;
    SDL_GetWindowSize(w, &width, &height);

    RabbitGame game;
    game.resize(width, height);

    SDL_Event event;
    while (true) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                goto quit;
            }
            if (event.type == SDL_MOUSEBUTTONDOWN) {
                game.touch(TOUCH_DOWN, 0, 0, 0);
            } else if (event.type == SDL_MOUSEBUTTONUP) {
                game.touch(TOUCH_UP, 0, 0, 0);
            } else if (event.type == SDL_KEYDOWN ||
                    event.type == SDL_KEYUP) {
                enum Key key = K_UNDEFINED;
                switch (event.key.keysym.sym) {
                    case SDLK_UP: key = K_UP; break;
                    case SDLK_DOWN: key = K_DOWN; break;
                    case SDLK_LEFT: key = K_LEFT; break;
                    case SDLK_RIGHT: key = K_RIGHT; break;
                    default: break;
                }
                game.key((event.type == SDL_KEYDOWN)?KEY_DOWN:KEY_UP, key);
            } else if (event.type == SDL_JOYDEVICEADDED) {
                if (SDL_IsGameController(event.jdevice.which)) {
                    SDL_GameController *controller = SDL_GameControllerOpen(event.jdevice.which);
                    if (SDL_GameControllerHasSensor(controller, SDL_SENSOR_ACCEL)) {
                        SDL_GameControllerSetSensorEnabled(controller, SDL_SENSOR_ACCEL, SDL_TRUE);
                    }
                } else {
                    SDL_JoystickOpen(event.jdevice.which);
                }
            } else if (event.type == SDL_JOYHATMOTION) {
                static Uint8 old = SDL_HAT_CENTERED;
                Uint8 changed = event.jhat.value ^ old;
                if (changed & SDL_HAT_LEFT)
                    game.key(event.jhat.value & SDL_HAT_LEFT ? KEY_DOWN:KEY_UP, K_LEFT);
                if (changed & SDL_HAT_RIGHT)
                    game.key(event.jhat.value & SDL_HAT_RIGHT ? KEY_DOWN:KEY_UP, K_RIGHT);
                if (changed & SDL_HAT_UP)
                    game.key(event.jhat.value & SDL_HAT_UP ? KEY_DOWN:KEY_UP, K_UP);
                if (changed & SDL_HAT_DOWN)
                    game.key(event.jhat.value & SDL_HAT_DOWN ? KEY_DOWN:KEY_UP, K_DOWN);
                old = event.jhat.value;
            } else if (event.type == SDL_CONTROLLERBUTTONDOWN) {
                if (event.cbutton.button == SDL_CONTROLLER_BUTTON_BACK ||
                    event.cbutton.button == SDL_CONTROLLER_BUTTON_START) {
                    goto quit;
                }
                game.touch(TOUCH_DOWN, 0, 0, 0);
            } else if (event.type == SDL_CONTROLLERBUTTONUP) {
                game.touch(TOUCH_UP, 0, 0, 0);
            } else if (event.type == SDL_CONTROLLERSENSORUPDATE &&
                       event.csensor.sensor == SDL_SENSOR_ACCEL) {
                /* This works for the wiimote, hopefully is correct for other
                 * accelerometers, too */
                game.accelerometer(0, event.csensor.data[2], 0);
            }
        }

        game.render();
        SDL_GL_SwapWindow(w);
    }

quit:
    return 0;
}

#endif /* TRG_USE_SDL2 */


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

#ifndef TRG_TRGJNI_H
#define TRG_TRGJNI_H

#include <jni.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Android MotionEvent */
#define ACTION_DOWN 0
#define ACTION_UP 1
#define ACTION_MOVE 2

jint JNI_OnLoad(JavaVM *vm, void *reserved);
void Java_io_thp_trg2_android_GameRenderer_nativeInit(JNIEnv *env, jobject o);
void Java_io_thp_trg2_android_GameRenderer_nativeResize(JNIEnv *env, jobject o, jint width, jint height);
void Java_io_thp_trg2_android_GameRenderer_nativeRender(JNIEnv *env, jobject o);
void Java_io_thp_trg2_android_GameView_nativeTouch(JNIEnv *env, jobject o, jint event, jfloat x, jfloat y, jint finger);
void Java_io_thp_trg2_android_GameActivity_nativeAccelerometer(JNIEnv *env, jobject o, jfloat x, jfloat y, jfloat z);

#ifdef __cplusplus
}
#endif

#endif /* TRG_TRGJNI_H */


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

#include "texture.h"

#include "config.h"

#include <stdlib.h>

#define STBI_HEADER_FILE_ONLY
#include "stb_image.c"

/* This is in code generated from l44_texture.png (see CMakeLists.txt) */
extern "C" {
    extern unsigned char l44_texture_png;
    extern unsigned int l44_texture_png_len;
};

Texture *
Texture::l44()
{
    int comp, width, height;
    unsigned char *data;

    data = stbi_load_from_memory(&l44_texture_png,
            l44_texture_png_len,
            &width, &height, &comp, STBI_default);

    Texture *result = new Texture(data, width, height,
            (comp==4)?(Texture::RGBA):(Texture::RGB));

    stbi_image_free(data);

    return result;
}

Texture::Texture(const unsigned char *data, int width, int height,
        enum Colorspace colorspace)
    : width(width),
      height(height),
      textureName(0)
{
    glGenTextures(1, &textureName);
    glBindTexture(GL_TEXTURE_2D, textureName);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0,
            (colorspace==Texture::RGBA)?GL_RGBA:GL_RGB,
            GL_UNSIGNED_BYTE, data);
}

Texture *
Texture::fromData(RGBATextureData data, bool autofree)
{
    Texture *result = new Texture(data.data, data.width, data.height, RGBA);
    if (autofree) {
        free(data.data);
    }
    return result;
}

void
Texture::updateFromData(RGBATextureData data, bool autofree)
{
    glBindTexture(GL_TEXTURE_2D, textureName);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, data.width, data.height, 0,
            GL_RGBA, GL_UNSIGNED_BYTE, data.data);

    width = data.width;
    height = data.height;

    if (autofree) {
        free(data.data);
    }
}

Texture::~Texture()
{
    glDeleteTextures(1, &textureName);
}

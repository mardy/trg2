
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

#include "textrenderer.h"

#include "vincent.h"

#include <stdlib.h>
#include <string.h>


TextRenderer::TextRenderer(const char *text)
    : m_text(strdup(text))
{
}

TextRenderer::~TextRenderer()
{
    free(m_text);
}


Texture *
TextRenderer::texture()
{
    return Texture::fromData(render(), true);
}

RGBATextureData
TextRenderer::render()
{
    RGBATextureData result;

    int count = strlen(m_text);

    int spacing = 0;
    int border = 1;

    result.width = (8+spacing)*count - spacing + border*2;
    result.height = 8 + border*2;

    /* Scanline length for RGBA */
    int pitch = (result.width*4);

    /* RGBA = 4 bytes per pixel */
    result.data = (unsigned char*)calloc(1, result.width * result.height * 4);

    int x = 1;
    for (int i=0; i<count; i++) {
        for (int row=0; row<8; row++) {
            int data = vincent_data[m_text[i]][row];
            int column;
            for (column=0; column<8; column++) {
                if (data & (1 << (7-column))) {
                    // 4 bytes for RGBA
                    *((int*)((unsigned char*)result.data + ((x+column)*4 + (row+1)*pitch))) = 0xffffffff;
                }
            }
        }

        x += 8+spacing;
    }

    return result;
}

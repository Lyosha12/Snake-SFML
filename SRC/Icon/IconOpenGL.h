//
// Created by Lyosha12 on 02.08.2018.
//

#ifndef SNAKE_ICONOPENGL_H
#define SNAKE_ICONOPENGL_H

typedef struct {
    unsigned int 	 width;
    unsigned int 	 height;
    unsigned int 	 bytes_per_pixel; /* 2:RGB16, 3:RGB, 4:RGBA */
    unsigned char	 pixel_data[32 * 24 * 4 + 1];
} IconOpenGL;
extern IconOpenGL snake_icon;

#endif //SNAKE_ICONOPENGL_H

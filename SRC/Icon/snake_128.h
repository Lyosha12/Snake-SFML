//
// Created by Lyosha12 on 30.07.2018.
//

#ifndef SNAKE_SNAKE_128_H
#define SNAKE_SNAKE_128_H

typedef struct {
    unsigned int 	 width;
    unsigned int 	 height;
    unsigned int 	 bytes_per_pixel; /* 2:RGB16, 3:RGB, 4:RGBA */
    unsigned char	 pixel_data[128 * 94 * 4 + 1];
} SnakeIcon;

extern SnakeIcon snake_icon;

#endif //SNAKE_SNAKE_128_H

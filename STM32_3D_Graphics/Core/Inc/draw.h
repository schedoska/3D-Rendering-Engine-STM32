#ifndef __DRAW_H
#define __DRAW_H

#include "stm32f4xx_hal.h"
#include "cube_3d.h"
#include "math.h"

#define WHIDTH 200
#define HEIGHT 200

#define TXT_SIZE 60

#define DRAW_PIXEL_AT(canvas,x,y,color) (canvas[((x) * WHIDTH + (y))] = color)

void draw_demo_page(uint16_t *canvas);
void draw_square_at(uint16_t *canvas, uint8_t x, uint8_t y, uint8_t width, uint8_t height);
void draw_square_at_point(uint16_t *canvas, point_3d *point, uint8_t width, uint8_t height);
void draw_vertex(uint16_t *canvas, vertex_3d *vertex, uint16_t color, float shade);
void draw_line(uint16_t *canvas, int16_t ax, int16_t ay, int16_t bx, int16_t by, uint16_t color);
void draw_cube(uint16_t *canvas);

void draw_line_textured(uint16_t *canvas, int16_t ax, int16_t ay, int16_t bx, int16_t by,
						float l, uint8_t txt_id, float shade);
void init_texture();

#endif

#ifndef INC_CUBE_3D_H_
#define INC_CUBE_3D_H_

#include "stm32f4xx_hal.h"
#include "math.h"

#define ROT_CENTER_X 100
#define ROT_CENTER_Y 100
#define ROT_CENTER_Z 0

#define CUBE_SIZE 50

typedef enum axis_3d{X_AXIS, Z_AXIS, Y_AXIS} axis_3d;

#define VERTEX_COUNT 12

typedef struct point_3d{
	int16_t x;
	int16_t y;
	int16_t z;
	float x_angle;
	float y_angle;
	float z_angle;
} point_3d;

typedef struct proxy_point_3d{
	int16_t x;
	int16_t y;
	int16_t z;
} proxy_point_3d;

typedef struct vertex_3d{
	point_3d a;
	point_3d b;
	point_3d c;
	point_3d normal_vec;
	uint8_t txt_id;
} vertex_3d;

vertex_3d cube_model[VERTEX_COUNT];

proxy_point_3d apply_rotation_to_point(point_3d *point);
float apply_rotation_to_point_only_z(point_3d *point);
void rotate_vertex(vertex_3d *vertex, float angle, axis_3d axis);
void rotate_cube(float angle, axis_3d axis);
void set_rotation_cube(float angle_x, float angle_y, float angle_z);
void init_cube();
void init_cube_2();
void translate_vertex(vertex_3d *vertex, int16_t dx, int16_t dy, int16_t dz);

#endif /* INC_CUBE_3D_H_ */

#include "draw.h"
#include "texture.h"

uint16_t color_array[] = {0x001f, 0x0be4, 0xeca0, 0xe816, 0xf880, 0x3475};

uint16_t texture_1[TXT_SIZE][TXT_SIZE];
uint16_t texture_2[TXT_SIZE][TXT_SIZE];

void init_texture(){
	for(uint8_t x = 0; x < TXT_SIZE; x++){
		for(uint8_t y = 0; y < TXT_SIZE; y++){
			texture_1[y][x] = texture_source[y * TXT_SIZE + x];
		}
	}
	for(uint8_t x = 0; x < TXT_SIZE; x++){
		for(uint8_t y = 0; y < TXT_SIZE; y++){
			texture_2[x][y] = texture_1[TXT_SIZE - 1 - x][TXT_SIZE - 1 - y];
		}
	}
}

void draw_demo_page(uint16_t *canvas){
	for(int i = 0; i < 200 * 200; i ++){
		canvas[i] = 0xffff;
	}
}

void draw_square_at(uint16_t *canvas, uint8_t x, uint8_t y, uint8_t width, uint8_t height){
	uint8_t x_start = x;
	uint8_t x_end = x + width;
	uint8_t y_start = y;
	uint8_t y_end = y + height;

	for(int m_x = x_start; m_x < x_end; m_x++){
		for(int m_y = y_start; m_y < y_end; m_y++){
			DRAW_PIXEL_AT(canvas,m_x,m_y,0xe8bb);
		}
	}
}

void draw_square_at_point(uint16_t *canvas, point_3d *point, uint8_t width, uint8_t height){
	proxy_point_3d proxy_point = apply_rotation_to_point(point);
	uint8_t x_start = proxy_point.x;
	uint8_t x_end = x_start + width;
	uint8_t y_start = proxy_point.y;
	uint8_t y_end = y_start + height;

	for(int m_x = x_start; m_x < x_end; m_x++){
		for(int m_y = y_start; m_y < y_end; m_y++){
			DRAW_PIXEL_AT(canvas,m_x,m_y,0xe8bb);
		}
	}
}

void draw_vertex(uint16_t *canvas, vertex_3d *vertex, uint16_t color, float shade){
	proxy_point_3d proxy_a = apply_rotation_to_point(&(vertex->a));
	proxy_point_3d proxy_b = apply_rotation_to_point(&(vertex->b));
	proxy_point_3d proxy_c = apply_rotation_to_point(&(vertex->c));

	//draw_line(canvas, proxy_a.x, proxy_a.y, proxy_b.x, proxy_b.y, 0);
	//draw_line(canvas, proxy_a.x, proxy_a.y, proxy_c.x, proxy_c.y, 0);
	//draw_line(canvas, proxy_c.x, proxy_c.y, proxy_b.x, proxy_b.y, 0);

	float AB_dist = sqrtf(powf(proxy_b.x - proxy_a.x, 2) + powf(proxy_b.y - proxy_a.y, 2));
	float AC_dist = sqrtf(powf(proxy_c.x - proxy_a.x, 2) + powf(proxy_c.y - proxy_a.y, 2));

	//int16_t AB_x_dist = proxy_b.x - proxy_a.x;
	//int16_t AC_x_dist = proxy_c.x - proxy_a.x;

	float L1_x = proxy_a.x;
	float L1_y = proxy_a.y;

	float L2_x = proxy_a.x;
	float L2_y = proxy_a.y;

	if(AC_dist > AB_dist){
		float AB_dx = (float)(proxy_b.x - proxy_a.x) / (float) AC_dist;
		float AB_dy = (float)(proxy_b.y - proxy_a.y) / (float) AC_dist;
		float AC_dx = (float)(proxy_c.x - proxy_a.x) / (float) AC_dist;
		float AC_dy = (float)(proxy_c.y - proxy_a.y) / (float) AC_dist;

		for(uint8_t i = 0; i < AC_dist; i++){
			//draw_line(canvas, L1_x, L1_y, L2_x, L2_y, color);
			draw_line_textured(canvas, L1_x, L1_y, L2_x, L2_y, (float)i / (float)AC_dist, vertex->txt_id, shade);
			L1_x += AC_dx;
			L1_y += AC_dy;
			L2_x += AB_dx;
			L2_y += AB_dy;
		}
	}
	else{
		float AB_dx = (float)(proxy_b.x - proxy_a.x) / (float) AB_dist;
		float AB_dy = (float)(proxy_b.y - proxy_a.y) / (float) AB_dist;
		float AC_dx = (float)(proxy_c.x - proxy_a.x) / (float) AB_dist;
		float AC_dy = (float)(proxy_c.y - proxy_a.y) / (float) AB_dist;

		for(uint8_t i = 0; i < AB_dist; i++){
			//draw_line(canvas, L1_x, L1_y, L2_x, L2_y, color);
			draw_line_textured(canvas, L1_x, L1_y, L2_x, L2_y, (float)i / (float)AB_dist, vertex->txt_id, shade);
			L1_x += AC_dx;
			L1_y += AC_dy;
			L2_x += AB_dx;
			L2_y += AB_dy;
		}
	}
}

void draw_line(uint16_t *canvas, int16_t ax, int16_t ay, int16_t bx, int16_t by, uint16_t color){
	if(abs(ax - bx) > abs(ay - by)){
		int8_t dx = ax < bx ? 1 : -1;
		float y = ay;
		float dy = (by - ay) / (float) abs(bx - ax);

		for(uint8_t x = ax; x != bx; x += dx){
			DRAW_PIXEL_AT(canvas,x,(int)y,color);
			//DRAW_PIXEL_AT(canvas,x + 1,(int)y,color);
			//DRAW_PIXEL_AT(canvas,x,(int)y + 1,color);
			y += dy;
		}
	}
	else{
		int8_t dy = ay < by ? 1 : -1;
		float x = ax;
		float dx = (bx - ax) / (float) abs(by - ay);

		for(uint8_t y = ay; y != by; y += dy){
			DRAW_PIXEL_AT(canvas,(int)x,y,color);
			//DRAW_PIXEL_AT(canvas,(int)x,y + 1,color);
			//DRAW_PIXEL_AT(canvas,(int)x + 1,y,color);
			x += dx;
		}
	}
}

void draw_cube(uint16_t *canvas){
	for(int i = 0; i < VERTEX_COUNT; i++){
		float normal_z = apply_rotation_to_point_only_z(&(cube_model[i].normal_vec));
		if(normal_z > 0) continue;
		float shade_value = -(float)normal_z / (float)11.0 + 0.1;
		draw_vertex(canvas, &(cube_model[i]), color_array[i%6], shade_value > 1 ? 1 : shade_value);

	}
}

void draw_line_textured(uint16_t *canvas, int16_t ax, int16_t ay, int16_t bx, int16_t by,
						float l, uint8_t txt_id , float shade){
	float L2_x = 0;
	float L2_y = (float)l * (float)TXT_SIZE;
	float L1_x = (float)l * (float)TXT_SIZE;
	float L1_y = (float)l * (float)TXT_SIZE;

	float Lx_diff = L1_x - L2_x;
	float Ly_diff = L1_y - L2_y;

	uint16_t (*used_texture)[TXT_SIZE];
	if(txt_id == 1) used_texture = texture_1;
	else used_texture = texture_2;

	if(abs(ax - bx) > abs(ay - by)){
		int8_t dx = ax < bx ? 1 : -1;
		float y = ay;
		float dy = (float)(by - ay) / (float) abs(bx - ax);

		int16_t road_to_do = abs(bx - ax);

		for(uint8_t x = ax; x != bx; x += dx){
			float progress = (float)abs(bx - x) / (float)road_to_do;
			float x_txt = (float)progress * (float)Lx_diff + L2_x;
			float y_txt = (float)progress * (float)Ly_diff + L2_y;

			uint16_t color = (uint16_t)((float)((used_texture[(uint8_t)y_txt][(uint8_t)x_txt] & 0xF800) >> 11) * (float)shade) << 11;
			color |= (uint16_t)((float)(((used_texture[(uint8_t)y_txt][(uint8_t)x_txt] & 0x7E0) >> 5) * (float)shade)) << 5;
			color |= (uint16_t)((float)(((used_texture[(uint8_t)y_txt][(uint8_t)x_txt] & 0x1F) >> 0) * (float)shade)) << 0;

			DRAW_PIXEL_AT(canvas,x,(int)y,color);
			//DRAW_PIXEL_AT(canvas,x+1,(int)y,color);
			DRAW_PIXEL_AT(canvas,x,(int)y+1,color);
			y += (float)dy;
		}
	}
	else{
		int8_t dy = ay < by ? 1 : -1;
		float x = ax;
		float dx = (float)(bx - ax) / (float) abs(by - ay);

		int16_t road_to_do = abs(by - ay);

		for(uint8_t y = ay; y != by; y += dy){
			float progress = (float)abs(by - y) / (float)road_to_do;
			float x_txt = (float)progress * (float)Lx_diff + L2_x;
			float y_txt = (float)progress * (float)Ly_diff + L2_y;

			uint16_t color = (uint16_t)((float)((used_texture[(uint8_t)y_txt][(uint8_t)x_txt] & 0xF800) >> 11) * (float)shade) << 11;
			color |= (uint16_t)((float)(((used_texture[(uint8_t)y_txt][(uint8_t)x_txt] & 0x7E0) >> 5) * (float)shade)) << 5;
			color |= (uint16_t)((float)(((used_texture[(uint8_t)y_txt][(uint8_t)x_txt] & 0x1F) >> 0) * (float)shade)) << 0;

			DRAW_PIXEL_AT(canvas,(int)x,y,color);
			DRAW_PIXEL_AT(canvas,(int)x+1,y,color);
			//DRAW_PIXEL_AT(canvas,(int)x,y+1,color);
			x += (float)dx;
		}
	}
}





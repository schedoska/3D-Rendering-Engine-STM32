#include "cube_3d.h"

// obrot Z -> y -> x
proxy_point_3d apply_rotation_to_point(point_3d *point){
	point->x -= 100;
	point->y -= 100;

	proxy_point_3d proxy_point;

	proxy_point.x = cos(point->z_angle) * cos(point->y_angle) * point->x;
	proxy_point.x += (cos(point->z_angle) * sin(point->y_angle) * sin(point->x_angle) -
					sin(point->z_angle) * cos(point->x_angle)) * point->y;
	proxy_point.x += (cos(point->z_angle) * sin(point->y_angle) * cos(point->x_angle) +
					sin(point->z_angle) * sin(point->x_angle)) * point->z;

	proxy_point.y = sin(point->z_angle) * cos(point->y_angle) * point->x;
	proxy_point.y += (sin(point->z_angle) * sin(point->y_angle) * sin(point->x_angle) +
					cos(point->z_angle) * cos(point->x_angle)) * point->y;
	proxy_point.y += (sin(point->z_angle) * sin(point->y_angle) * cos(point->x_angle) -
					cos(point->z_angle) * sin(point->x_angle)) * point->z;

	proxy_point.z = -sin(point->y_angle) * point->x;
	proxy_point.z += cos(point->y_angle) * sin(point->x_angle) * point->y;
	proxy_point.z += cos(point->y_angle) * cos(point->x_angle) * point->z;

	point->x += 100;
	point->y += 100;
	proxy_point.x += 100;
	proxy_point.y += 100;

	return proxy_point;
}

float apply_rotation_to_point_only_z(point_3d *point){
	point->x -= 100;
	point->y -= 100;
	float z = -sin(point->y_angle) * point->x;
	z += cos(point->y_angle) * sin(point->x_angle) * point->y;
	z += cos(point->y_angle) * cos(point->x_angle) * point->z;
	point->x += 100;
	point->y += 100;
	return z;
}

void rotate_vertex(vertex_3d *vertex, float angle, axis_3d axis){
	if(axis == X_AXIS){
		vertex->a.x_angle += angle;
		vertex->b.x_angle += angle;
		vertex->c.x_angle += angle;
		vertex->normal_vec.x_angle += angle;
	}
	else if(axis == Y_AXIS){
		vertex->a.y_angle += angle;
		vertex->b.y_angle += angle;
		vertex->c.y_angle += angle;
		vertex->normal_vec.y_angle += angle;
	}
	else{
		vertex->a.z_angle += angle;
		vertex->b.z_angle += angle;
		vertex->c.z_angle += angle;
		vertex->normal_vec.z_angle += angle;
	}
}

void rotate_cube(float angle, axis_3d axis){
	for(int i = 0; i < VERTEX_COUNT; i++){
		rotate_vertex(&(cube_model[i]), angle, axis);
	}
}

void set_rotation_cube(float angle_x, float angle_y, float angle_z){
	for(int i = 0; i < VERTEX_COUNT; i++){
		cube_model[i].a.x_angle = angle_x;
		cube_model[i].a.y_angle = angle_y;
		cube_model[i].a.z_angle = angle_z;

		cube_model[i].b.x_angle = angle_x;
		cube_model[i].b.y_angle = angle_y;
		cube_model[i].b.z_angle = angle_z;

		cube_model[i].c.x_angle = angle_x;
		cube_model[i].c.y_angle = angle_y;
		cube_model[i].c.z_angle = angle_z;

		cube_model[i].normal_vec.x_angle = angle_x;
		cube_model[i].normal_vec.y_angle = angle_y;
		cube_model[i].normal_vec.z_angle = angle_z;
	}
}

void init_cube(){
	vertex_3d vertex_1 =   {{CUBE_SIZE/2,CUBE_SIZE/2,-CUBE_SIZE/2, 0,0, 0},
		  		  	  	   {-CUBE_SIZE/2,CUBE_SIZE/2,-CUBE_SIZE/2, 0,0, 0},
		  				   {CUBE_SIZE/2,-CUBE_SIZE/2,-CUBE_SIZE/2, 0,0, 0},
						   {0,0,-10,0,0,0}};
	translate_vertex(&vertex_1, 100, 100, 0);

	  vertex_3d vertex_2 = {{-CUBE_SIZE,-CUBE_SIZE,-CUBE_SIZE, 0,0, 0},
			  	  	  	   {-CUBE_SIZE,CUBE_SIZE,-CUBE_SIZE, 0,0, 0},
						   {CUBE_SIZE,-CUBE_SIZE,-CUBE_SIZE, 0,0, 0},
						   {0,0,-10,0,0,0}};
	  translate_vertex(&vertex_2, 100, 100, 0);
//-------------------------------------------------------------
	  vertex_3d vertex_3 = {{-CUBE_SIZE,-CUBE_SIZE,-CUBE_SIZE, 0,0, 0},
	  		  	  	  	   {-CUBE_SIZE,CUBE_SIZE,-CUBE_SIZE, 0,0, 0},
	  					   {-CUBE_SIZE,CUBE_SIZE,CUBE_SIZE, 0,0, 0},
						   {-10,0,0,0,0,0}};
	  translate_vertex(&vertex_3, 100, 100, 0);

	  vertex_3d vertex_4 = {{-CUBE_SIZE,CUBE_SIZE,CUBE_SIZE, 0,0, 0},
	    		  	  	   {-CUBE_SIZE,-CUBE_SIZE,CUBE_SIZE, 0,0, 0},
	    				   {-CUBE_SIZE,-CUBE_SIZE,-CUBE_SIZE, 0,0, 0},
						   {-10,0,0,0,0,0}};
	  translate_vertex(&vertex_4, 100, 100, 0);
//-------------------------------------------------------------
  	  vertex_3d vertex_5 = {{-CUBE_SIZE,-CUBE_SIZE,-CUBE_SIZE, 0,0, 0},
  	  		  	  	  	   {-CUBE_SIZE,-CUBE_SIZE,CUBE_SIZE, 0,0, 0},
  	  					   {CUBE_SIZE,-CUBE_SIZE,-CUBE_SIZE, 0,0, 0},
						   {0,-10,0,0,0,0}};
  	  translate_vertex(&vertex_5, 100, 100, 0);

  	  vertex_3d vertex_6 = {{CUBE_SIZE,-CUBE_SIZE,-CUBE_SIZE, 0,0, 0},
  	    		  	  	   {-CUBE_SIZE,-CUBE_SIZE,CUBE_SIZE, 0,0, 0},
  	    				   {CUBE_SIZE,-CUBE_SIZE,CUBE_SIZE, 0,0, 0},
						   {0,-10,0,0,0,0}};
  	  translate_vertex(&vertex_6, 100, 100, 0);
//-------------------------------------------------------------
		vertex_3d vertex_7 = {{CUBE_SIZE,-CUBE_SIZE,-CUBE_SIZE, 0,0, 0},
							 {CUBE_SIZE,CUBE_SIZE,-CUBE_SIZE, 0,0, 0},
							 {CUBE_SIZE,CUBE_SIZE,CUBE_SIZE, 0,0, 0},
							 {10,0,0,0,0,0}};
		translate_vertex(&vertex_7, 100, 100, 0);

		vertex_3d vertex_8 = {{CUBE_SIZE,CUBE_SIZE,CUBE_SIZE, 0,0, 0},
							 {CUBE_SIZE,-CUBE_SIZE,CUBE_SIZE, 0,0, 0},
							 {CUBE_SIZE,-CUBE_SIZE,-CUBE_SIZE, 0,0, 0},
							 {10,0,0,0,0,0}};
		translate_vertex(&vertex_8, 100, 100, 0);
//-------------------------------------------------------------
		vertex_3d vertex_9 = {{-CUBE_SIZE,CUBE_SIZE,-CUBE_SIZE, 0,0, 0},
							 {CUBE_SIZE,CUBE_SIZE,-CUBE_SIZE, 0,0, 0},
							 {CUBE_SIZE,CUBE_SIZE,CUBE_SIZE, 0,0, 0},
							 {0,10,0,0,0,0}};
		translate_vertex(&vertex_9, 100, 100, 0);

		vertex_3d vertex_10 = {{CUBE_SIZE,CUBE_SIZE,CUBE_SIZE, 0,0, 0},
							 {-CUBE_SIZE,CUBE_SIZE,CUBE_SIZE, 0,0, 0},
							 {-CUBE_SIZE,CUBE_SIZE,-CUBE_SIZE, 0,0, 0},
							 {0,10,0,0,0,0}};
		translate_vertex(&vertex_10, 100, 100, 0);
//-------------------------------------------------------------
		vertex_3d vertex_11 =   {{CUBE_SIZE,CUBE_SIZE,CUBE_SIZE, 0,0, 0},
			  		  	  	   {-CUBE_SIZE,CUBE_SIZE,CUBE_SIZE, 0,0, 0},
			  				   {CUBE_SIZE,-CUBE_SIZE,CUBE_SIZE, 0,0, 0},
							   {0,0,10,0,0,0}};
		translate_vertex(&vertex_11, 100, 100, 0);

		  vertex_3d vertex_12 = {{-CUBE_SIZE,-CUBE_SIZE,CUBE_SIZE, 0,0, 0},
				  	  	  	   {-CUBE_SIZE,CUBE_SIZE,CUBE_SIZE, 0,0, 0},
							   {CUBE_SIZE,-CUBE_SIZE,CUBE_SIZE, 0,0, 0},
							   {0,0,10,0,0,0}};
		  translate_vertex(&vertex_12, 100, 100, 0);

  	cube_model[0] = vertex_1;
  	cube_model[1] = vertex_2;
  	cube_model[2] = vertex_3;
  	cube_model[3] = vertex_4;
  	cube_model[4] = vertex_5;
  	cube_model[5] = vertex_6;
  	cube_model[6] = vertex_7;
  	cube_model[7] = vertex_8;
  	cube_model[8] = vertex_9;
  	cube_model[9] = vertex_10;
  	cube_model[10] = vertex_11;
  	cube_model[11] = vertex_12;
}

void init_cube_2(){
	vertex_3d vertex_1 = {{-CUBE_SIZE,-CUBE_SIZE,-CUBE_SIZE, 0,0, 0},
			  		  	 {-CUBE_SIZE,CUBE_SIZE,-CUBE_SIZE, 0,0, 0},
						 {CUBE_SIZE,CUBE_SIZE,-CUBE_SIZE, 0,0, 0},
					     {0,0,-10,0,0,0}, 2};
	translate_vertex(&vertex_1, 100, 100, 0);

	vertex_3d vertex_2 = {{CUBE_SIZE,CUBE_SIZE,-CUBE_SIZE, 0,0, 0},
				  	  	 {CUBE_SIZE,-CUBE_SIZE,-CUBE_SIZE, 0,0, 0},
						 {-CUBE_SIZE,-CUBE_SIZE,-CUBE_SIZE, 0,0, 0},
						 {0,0,-10,0,0,0}, 1};
	translate_vertex(&vertex_2, 100, 100, 0);
	//-------------------------------------------------------------
	vertex_3d vertex_3 = {{-CUBE_SIZE,-CUBE_SIZE,-CUBE_SIZE, 0,0, 0},
		  		  	  	 {-CUBE_SIZE,CUBE_SIZE,-CUBE_SIZE, 0,0, 0},
		  				 {-CUBE_SIZE,CUBE_SIZE,CUBE_SIZE, 0,0, 0},
						 {-10,0,0,0,0,0}, 2};
	translate_vertex(&vertex_3, 100, 100, 0);

	vertex_3d vertex_4 = {{-CUBE_SIZE,CUBE_SIZE,CUBE_SIZE, 0,0, 0},
		    		  	 {-CUBE_SIZE,-CUBE_SIZE,CUBE_SIZE, 0,0, 0},
		    		     {-CUBE_SIZE,-CUBE_SIZE,-CUBE_SIZE, 0,0, 0},
						 {-10,0,0,0,0,0}, 1};
	translate_vertex(&vertex_4, 100, 100, 0);
	//-------------------------------------------------------------
	vertex_3d vertex_5 = {{-CUBE_SIZE,-CUBE_SIZE,-CUBE_SIZE, 0,0, 0},
	  	  		  	  	 {CUBE_SIZE,-CUBE_SIZE,-CUBE_SIZE, 0,0, 0},
	  	  				 {CUBE_SIZE,-CUBE_SIZE,CUBE_SIZE, 0,0, 0},
						 {0,-10,0,0,0,0}, 2};
	translate_vertex(&vertex_5, 100, 100, 0);

	vertex_3d vertex_6 = {{CUBE_SIZE,-CUBE_SIZE,CUBE_SIZE, 0,0, 0},
					     {-CUBE_SIZE,-CUBE_SIZE,CUBE_SIZE, 0,0, 0},
	  	    			 {-CUBE_SIZE,-CUBE_SIZE,-CUBE_SIZE, 0,0, 0},
						 {0,-10,0,0,0,0}, 1};
	translate_vertex(&vertex_6, 100, 100, 0);
	//-------------------------------------------------------------
	vertex_3d vertex_7 = {{CUBE_SIZE,-CUBE_SIZE,-CUBE_SIZE, 0,0, 0},
						 {CUBE_SIZE,CUBE_SIZE,-CUBE_SIZE, 0,0, 0},
						 {CUBE_SIZE,CUBE_SIZE,CUBE_SIZE, 0,0, 0},
						 {10,0,0,0,0,0}, 2};
	translate_vertex(&vertex_7, 100, 100, 0);

	vertex_3d vertex_8 = {{CUBE_SIZE,CUBE_SIZE,CUBE_SIZE, 0,0, 0},
						 {CUBE_SIZE,-CUBE_SIZE,CUBE_SIZE, 0,0, 0},
						 {CUBE_SIZE,-CUBE_SIZE,-CUBE_SIZE, 0,0, 0},
						 {10,0,0,0,0,0}, 1};
	translate_vertex(&vertex_8, 100, 100, 0);
	//-------------------------------------------------------------
	vertex_3d vertex_9 = {{-CUBE_SIZE,CUBE_SIZE,-CUBE_SIZE, 0,0, 0},
						 {CUBE_SIZE,CUBE_SIZE,-CUBE_SIZE, 0,0, 0},
						 {CUBE_SIZE,CUBE_SIZE,CUBE_SIZE, 0,0, 0},
						 {0,10,0,0,0,0}, 1};
	translate_vertex(&vertex_9, 100, 100, 0);

	vertex_3d vertex_10 = {{CUBE_SIZE,CUBE_SIZE,CUBE_SIZE, 0,0, 0},
						  {-CUBE_SIZE,CUBE_SIZE,CUBE_SIZE, 0,0, 0},
						  {-CUBE_SIZE,CUBE_SIZE,-CUBE_SIZE, 0,0, 0},
					      {0,10,0,0,0,0}, 2};
	translate_vertex(&vertex_10, 100, 100, 0);
	//-------------------------------------------------------------
	vertex_3d vertex_11 =   {{CUBE_SIZE,CUBE_SIZE,CUBE_SIZE, 0,0, 0},
							{-CUBE_SIZE,CUBE_SIZE,CUBE_SIZE, 0,0, 0},
				  			{-CUBE_SIZE,-CUBE_SIZE,CUBE_SIZE, 0,0, 0},
							{0,0,10,0,0,0}, 2};
	translate_vertex(&vertex_11, 100, 100, 0);

	vertex_3d vertex_12 = 	{{-CUBE_SIZE,-CUBE_SIZE,CUBE_SIZE, 0,0, 0},
							{CUBE_SIZE,-CUBE_SIZE,CUBE_SIZE, 0,0, 0},
							{CUBE_SIZE,CUBE_SIZE,CUBE_SIZE, 0,0, 0},
							{0,0,10,0,0,0}, 1};
	translate_vertex(&vertex_12, 100, 100, 0);


	cube_model[0] = vertex_1;
	cube_model[1] = vertex_2;
	cube_model[2] = vertex_3;
	cube_model[3] = vertex_4;
	cube_model[4] = vertex_5;
	cube_model[5] = vertex_6;
	cube_model[6] = vertex_7;
	cube_model[7] = vertex_8;
	cube_model[8] = vertex_9;
	cube_model[9] = vertex_10;
	cube_model[10] = vertex_11;
	cube_model[11] = vertex_12;
}

void translate_vertex(vertex_3d *vertex, int16_t dx, int16_t dy, int16_t dz){
	vertex->a.x += dx;
	vertex->a.y += dy;
	vertex->a.z += dz;

	vertex->b.x += dx;
	vertex->b.y += dy;
	vertex->b.z += dz;

	vertex->c.x += dx;
	vertex->c.y += dy;
	vertex->c.z += dz;

	vertex->normal_vec.x += dx;
	vertex->normal_vec.y += dy;
	vertex->normal_vec.z += dz;
}



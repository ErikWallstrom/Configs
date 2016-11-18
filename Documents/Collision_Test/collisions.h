#ifndef COLLISIONS_H
#define COLLISIONS_H

#define RECT_COLLIDED_ARGS \
		float x1, float y1, \
		float w1, float h1, \
		float vx1, float vy1, \
		float x2, float y2, \
		float w2, float h2, \
		float vx2, float vy2

int lines_intersect(
		float p0_x, float p0_y, 
		float p1_x, float p1_y, 
		float p2_x, float p2_y, 
		float p3_x, float p3_y);

int rect_collided_left(RECT_COLLIDED_ARGS);
int rect_collided_right(RECT_COLLIDED_ARGS);
int rect_collided_top(RECT_COLLIDED_ARGS);
int rect_collided_bottom(RECT_COLLIDED_ARGS);

#endif

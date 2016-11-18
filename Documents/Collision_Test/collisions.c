#include "collisions.h"

int lines_intersect(
		float p0_x, float p0_y, 
		float p1_x, float p1_y, 
		float p2_x, float p2_y, 
		float p3_x, float p3_y)
{
	float s1_x, s1_y, s2_x, s2_y;

    s1_x = p1_x - p0_x;
    s1_y = p1_y - p0_y;
    s2_x = p3_x - p2_x;
    s2_y = p3_y - p2_y;

    float s, t;
    s = (-s1_y * (p0_x - p2_x) + s1_x * (p0_y - p2_y))
		/ (-s2_x * s1_y + s1_x * s2_y);
    t = ( s2_x * (p0_y - p2_y) - s2_y * (p0_x - p2_x)) 
		/ (-s2_x * s1_y + s1_x * s2_y);

    if (s >= 0 && s <= 1 && t >= 0 && t <= 1)
        return 1;
    return 0;
}

int rect_collided_left(RECT_COLLIDED_ARGS)
{
	x2 += vx2;
	y2 += vy2;
	if(vx1 || vy1)
	{
		float test_y;
		if(y1 < y2)
		{
			if(y2 - y1 >= h1)
			{
				test_y = y1 + h1 - 1;
			}
			else
			{
				test_y = y1 + (y2 - y1) + 1;
			}
		}
		else
		{
			test_y = y1;
		}

		if(lines_intersect(
					x1,
					test_y,
					x1 + vx1,
					test_y,

					x2 + w2,
					y2 + 1,
					x2 + w2,
					y2 + h2 - 1))
		{
			return 1;
		}
	}
	return 0;
}

int rect_collided_right(RECT_COLLIDED_ARGS)
{
	x2 += vx2;
	y2 += vy2;
	if(vx1 || vy1)
	{
		float test_y;
		if(y1 < y2)
		{
			if(y2 - y1 >= h1)
			{
				test_y = y1 + h1 - 1;
			}
			else
			{
				test_y = y1 + (y2 - y1) + 1;
			}
		}
		else
		{
			test_y = y1;
		}

		if(lines_intersect(
					x1 + w1,
					test_y,
					x1 + vx1 + w1,
					test_y,

					x2,
					y2 + 1,
					x2,
					y2 + h2 - 1))
		{
			return 1;
		}
	}
	return 0;
}

int rect_collided_bottom(RECT_COLLIDED_ARGS)
{
	x2 += vx2;
	y2 += vy2;
	if(vx1 || vy1)
	{
		float test_x;
		if(x1 < x2)
		{
			if(x2 - x1 >= w1)
			{
				test_x = x1 + w1 - 1;
			}
			else
			{
				test_x = x1 + (x2 - x1) + 1;
			}
		}
		else
		{
			test_x = x1;
		}

		if(lines_intersect(
					test_x,
					y1 + h1,
					test_x,
					y1 + vy1 + h1,

					x2 + 1,
					y2,
					x2 + w2 - 1,
					y2))
		{
			return 1;
		}
	}
	return 0;
}

int rect_collided_top(RECT_COLLIDED_ARGS)
{
	x2 += vx2;
	y2 += vy2;
	if(vx1 || vy1)
	{
		float test_x;
		if(x1 < x2)
		{
			if(x2 - x1 >= w1)
			{
				test_x = x1 + w1 - 1;
			}
			else
			{
				test_x = x1 + (x2 - x1) + 1;
			}
		}
		else
		{
			test_x = x1;
		}

		if(lines_intersect(
					test_x,
					y1,
					test_x,
					y1 + vy1,

					x2 + 1,
					y2 + h2,
					x2 + w2 - 1,
					y2 + h2))
		{
			return 1;
		}
	}
	return 0;
}


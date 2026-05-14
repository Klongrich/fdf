#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <fcntl.h> 
#include <math.h>
#include "get_next_line.h"
#include <MLX42/MLX42.h>

#define WIDTH 600
#define HEIGHT 600
#define BUFFER_SIZE 1000

typedef struct points {
	int	x[50];
	int	y[50];
	int	z[50];
}		t_points;

void    put_line(t_points points, mlx_image_t *img, int i);



/*
	How to draw lines. 

	(x, y) to (x, y);
	
	4 Directions we have to place.

	say (0, 0) to (5, 1) -> right and down
	say (5, 1) to (0, 0) -> left and up
	say (0, 1) to (5, 0) -> right and up
	say (0, 5) to (1, 0) -> left and down
	say (0, 0) to (0, 5) -> vertical line
	say (0, 0) to (5, 0) -> horizontal line 

	0 [0, 1, 2, 3, 4, 5]
	1 [0, 1, 2, 3, 4, 5]
	2 [0, 1, 2, 3, 4, 5]
	3 [0, 1, 2, 3, 4, 5]
	

	Notes: 

	if moving up, add one 1 y value when p is greater than 0;
	if moving down, add subtract 1 from y value when p is greater than 0;

	p intial = sumY*2 - sumX;

	p < 0 = p + 2*sumY;
	p > 0 = p + 2*sumY - 2*sumx

	
	dx = amount of x points (5 - 0) = 5;
	dy = amouont of y points (1 - 0) = 1;

	5 total pixels
	
	p = when to jump y;

	if (p > 0)
		y++;
	p = amount of y points (1 * 2) - amoount of x points 5;

	p = 2 - 5;
	p = -3;
	while (i < dx) {
		(0, 0) -> p = -3;			
		(0, 0) -> p = p + 2y; (-3 + 2 * amount of y points (1)) = (-3 + 2) - -1;;
		(0, 0) -> p = -1 + 2 = (1)
		(0, 1) -> since p is greater than 0 -> p = (p + amount of y points * 2 - amount of x points * 2)
							   (1 + 2 - 10)
							   (1 - 8)
							   (-7)
		(0, 1)
	}	
	
	if (sum of x == 0)
		vertical line (increment by one)
	if (sum of y == 0)
		horztinal line (increment by one)

	

*/

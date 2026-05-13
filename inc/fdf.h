#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <MLX42/MLX42.h>

#define WIDTH 600
#define HEIGHT 600

typedef struct point {
	int	x1;
	int	x2;
	int 	y1;
	int	y2;
}		t_point;

void    put_line(t_point points, mlx_image_t *img);

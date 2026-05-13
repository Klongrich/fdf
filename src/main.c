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

void	put_slope_less_than_one(int dx, int dy, t_point points, mlx_image_t *img) {
	int p;
	int i;

	i = 0;
	p = 2 * dy - dx;
	mlx_put_pixel(img, points.x1, points.y1, 0xFF0000FF);
	while (i < dx) {
		points.x1 += 1;
		if (p < 0)
   			p = p + 2 * dy;
  		else {
   			points.y1 += 1;
   			p = p + 2 * dy - 2 * dx;
		}
		mlx_put_pixel(img, points.x1, points.y1,  0xFF0000FF);
		i++;
	}
}

void	put_slope_greater_than_one(int dx, int dy, t_point points, mlx_image_t *img) {
	int p;
	int i;

	i = 0;
	p = 2 * dx - dy;
	mlx_put_pixel(img, points.x1, points.y1, 0xFF0000FF);
	while (i < dy) {
		points.y1 += 1;
		if (p < 0)
			p = p + 2 * dx;
		else {
			points.x1 += 1;
   			p = p + 2 * dx - 2 * dy;
		}
		mlx_put_pixel(img, points.x1, points.y1, 0xFF0000FF);
		i++;
	}
}


int	abs(int n) {
	if (n < 0)
		return(-1 * n);
	return (n);
}

void	put_line(t_point points, mlx_image_t *img) {
	int dx;
	int dy;

	dx = points.x2 - points.x1;
	dy = points.y2 - points.y1;
	if (abs(dx) > abs(dy)) {
		put_slope_less_than_one(dx, dy, points, img);
	} else {
		put_slope_greater_than_one(dx, dy, points, img);
	}

}

int main(void) {
    	
	mlx_t *mlx = mlx_init(WIDTH, HEIGHT, "FDF", true);
	if (!mlx) {
		
		printf("error\n");
		fprintf(stderr, "%s", mlx_strerror(mlx_errno));
    		return EXIT_FAILURE;
	}

	mlx_image_t *img = mlx_new_image(mlx, WIDTH, HEIGHT);

	if (!img || (mlx_image_to_window(mlx, img, 0, 0) < 0)) {
		mlx_close_window(mlx);
		fprintf(stderr, "%s", mlx_strerror(mlx_errno));
		return EXIT_FAILURE;
	}

	int i;

	i = 0;
	while (i < 15) {
		mlx_put_pixel(img, i, 5, 0xFF0000FF);
		i++;
	}

	t_point points;

	points.x1 = 10;
	points.y1 = 15;
	points.x2 = 120;
	points.y2 = 130;

	put_line(points, img);

	mlx_loop(mlx);

	return (0);
}


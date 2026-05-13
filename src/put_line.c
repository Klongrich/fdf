#include "fdf.h"

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

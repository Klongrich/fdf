#include "fdf.h"

void	put_slope_less_than_one(int dx, int dy, int x, int y, t_points points, mlx_image_t *img)
{
	int	p;
	int	i;

	i = 0;
	p = 2 * dy - dx;
	mlx_put_pixel(img, points.x[x], points.y[y], 0xFF0000FF);
	while (i < dx)
	{
		points.x[x] += 1;
		if (p < 0)
			p = p + 2 * dy;
		else
		{
			points.y[y] += 1;
			p = p + 2 * dy - 2 * dx;
		}
		mlx_put_pixel(img, points.x[x], points.y[y], 0xFF0000FF);
		i++;
	}
}

void	put_slope_greater_than_one(int dx, int dy, int x, int y, t_points points, mlx_image_t *img)
{
	int	p;
	int	i;

	i = 0;
	p = 2 * dx - dy;
	mlx_put_pixel(img, points.x[x], points.y[y], 0xFF0000FF);
	while (i < dy)
	{
		points.y[y] += 1;
		if (p < 0)
			p = p + 2 * dx;
		else
		{
			points.x[x] += 1;
			p = p + 2 * dx - 2 * dy;
		}
		mlx_put_pixel(img, points.x[x], points.y[y], 0xFF0000FF);
		i++;
	}
}

void	put_line(t_points points, mlx_image_t *img, int x1, int y1, int x2, int y2)
{
	int	dx;
	int	dy;

	dx = points.x[x2] - points.x[x1];
	dy = points.y[y2] - points.y[y1];
	if (dx > dy)
	{
		put_slope_less_than_one(abs(dx), abs(dy), x1, y1, points, img);
		printf("slope less than\n");
	}
	else
	{
		put_slope_greater_than_one(abs(dx), abs(dy), x1, y1, points, img);
		printf("slope greater\n");
	}
}

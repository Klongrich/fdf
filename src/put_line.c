#include "fdf.h"




void	put_slope_less_than_one(int dx, int dy, int index, t_points points, mlx_image_t *img)
{
	int	p;
	int	i;

	i = 0;
	p = 2 * dy - dx;
	mlx_put_pixel(img, points.x[index], points.y[index], 0xFF0000FF);
	while (i < dx)
	{
		points.x[index] += 1;
		if (p < 0)
			p = p + 2 * dy;
		else
		{
			points.y[index] += 1;
			p = p + 2 * dy - 2 * dx;
		}
		mlx_put_pixel(img, points.x[index], points.y[index], 0xFF0000FF);
		i++;
	}
}

void	put_slope_greater_than_one(int dx, int dy, int index, t_points points, mlx_image_t *img)
{
	int	p;
	int	i;

	i = 0;
	p = 2 * dx - dy;
	mlx_put_pixel(img, points.x[index], points.y[index], 0xFF0000FF);
	while (i < dy)
	{
		points.y[index] += 1;
		if (p < 0)
			p = p + 2 * dx;
		else
		{
			points.x[index] += 1;
			p = p + 2 * dx - 2 * dy;
		}
		mlx_put_pixel(img, points.x[index], points.y[index], 0xFF0000FF);
		i++;
	}
}

void	put_line(t_points points, mlx_image_t *img, int i)
{
	int	dx;
	int	dy;

	dx = points.x[i + 1] - points.x[i];
	dy = points.y[i + 1] - points.y[i];
	if (dx > dy)
	{
		put_slope_less_than_one(abs(dx), abs(dy), i, points, img);
		printf("slope less than\n");
	}
	else
	{
		put_slope_greater_than_one(abs(dx), abs(dy), i, points, img);
		printf("slope greater\n");
	}
}

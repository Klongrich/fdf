#include "fdf.h"

void	isometric(t_points *points, int i)
{
	int	tmp;

	tmp = points->x[i];
	points->x[i] = (tmp - points->y[i]) * cos(0.523599);
	points->y[i] = (tmp + points->y[i]) * sin(0.523599) - points->z[i];
}

void	apply_zoom(t_points *points, int i, int zoom)
{
	points->x[i] = points->x[i] * zoom;
	points->y[i] = points->y[i] * zoom;
}

void	center_point(t_points *points, int i)
{
	points->x[i] = points->x[i] + (WIDTH / 2);
	points->y[i] = points->y[i] + (HEIGHT / 2);
}

void	convert_point(t_points *points, int i, int zoom)
{
	isometric(points, i);
	apply_zoom(points, i, zoom);
	center_point(points, i);
}

int	list_len(char **list) 
{
	int i;

	i = 0;
	while (list[i])
		i++;
	return (i);
}




int	main(int argc, char **argv)
{
	char	*str;
	char	**temp;
	int	fd;
	int	i;
	int	y;
	t_points	points;

	i = 0;
	y = 0;
	if (argc > 2)
		printf("too many args\n");
	if (argc == 1) {
		printf("no maps passed\n");
	} else {	
		str = (char *)malloc(sizeof(char) * BUFFER_SIZE);

		fd = open(argv[1], O_RDONLY, S_IRUSR);
		if (fd == -1) {
			printf("error opening file\n");
			free(str);
		} else {
			while(get_next_line(fd, &str)) {
				temp = ft_strsplit(str, ' ');
				printf("%s\n", str);
				printf("y-index:%d\n", y);
				printf("str_len: %d\n", list_len(temp));
				y++;
			}
			free(str);
		}

	
	
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

	while (i < 15) {
		mlx_put_pixel(img, i, 5, 0xFF0000FF);
		i++;
	}

	points.x[0] = 10;
	points.y[0] = 15;
	points.z[0] = 0;

	points.x[1] = 120;
	points.y[1] = 130;
	points.z[1] = 5;

	points.x[2] = 200;
	points.y[2] = 115;
	points.z[2] = 0;

	convert_point(&points, 0, 1);
	convert_point(&points, 1, 1);
	convert_point(&points, 2, 1);

	put_line(points, img, 0);	
	put_line(points, img, 1);
	mlx_loop(mlx);
	}
	return (0);
}


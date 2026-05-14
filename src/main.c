#include "fdf.h"

void  isometric(t_points *points, int i) {
	int tmp;

	tmp = points->x[i];
	points->x[i] = (tmp - points->y[i]) * cos(0.523599);
	points->y[i] = (tmp + points->y[i]) * sin(0.523599) - points->z[i];
}

void apply_zoom(t_points *points, int i, int zoom) {
	points->x[i] = points->x[i] * zoom;
	points->y[i] = points->y[i] * zoom;
}

void center_point(t_points *points, int i) {
	points->x[i] = points->x[i] + (WIDTH / 2);
	points->y[i] = points->y[i] + (HEIGHT / 2);
}

void	convert_point(t_points *points, int i, int zoom) {
	isometric(points, i);
	apply_zoom(points, i, zoom);
	center_point(points, i);
}

int main(int argc, char **argv) {
	char *str;
	int fd;
	int rd;

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
		}
		else {	
			rd = read(fd, str, BUFFER_SIZE);
			if (rd < 0 ) {
				printf("error reading file\n");
				free(str);
				close(fd);
			} else 
				printf("%s\n", str);
		}
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

	int i;

	i = 0;
	while (i < 15) {
		mlx_put_pixel(img, i, 5, 0xFF0000FF);
		i++;
	}

	t_points points;
//	int number_of_points;

	i = 0;
//	number_of_points = 3;

//	Hardcoded points	
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

	return (0);
}


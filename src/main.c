#include "fdf.h"

void	isometric(t_points *points, int i)
{
	int	tmp;

	tmp = points->x[i];
	points->x[i] = (tmp - points->y[i]) * cos(0.523599);
	points->y[i] = (tmp + points->y[i]) * sin(0.523599) - points->z[i];
}

void	apply_zoom(t_points *points, int i, int x_zoom, int y_zoom)
{
	points->x[i] = points->x[i] * x_zoom;
	points->y[i] = points->y[i] * y_zoom;
	points->z[i] = points->z[i] * y_zoom;
}

void	center_point(t_points *points, int i)
{
	points->x[i] = points->x[i] + (WIDTH / 2);
	points->y[i] = points->y[i] + (HEIGHT / 2);
}

void	convert_point(t_points *points, int i, int zoom)
{
	isometric(points, i);
//	apply_zoom(points, i, zoom);
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

void	set_points(char **str, int y, t_points *points)
{
	int	i;
	int index;

	i = 0;
	index = y * 19;
	while (str[i]) 
	{
		points->x[index + i] = i;
		points->y[index + i] = y;
		points->z[index + i] = ft_atoi(str[i]);
		i++;
	}
	printf("Done\n");
}

void	print_points(t_points points) {
	int i;

	i = 0;
	printf("print points\n");
	while (i < 190)
	{
		printf("i: %d - (%d, %d, %d)", i, points.x[i], points.y[i], points.z[i]);
		printf("\n");
		i++;
	}

}

void	init_points(t_points *points)
{
	int i;

	i = 0;
	while (i < 190) 
	{
		points->x[i] = 0;
		points->y[i] = 0;
		points->z[i] = 0;
		i++;	
	}
}

int	main(int argc, char **argv)
{
	char	*str;
	char	**temp;
	int	fd;
	int	i;
	int	y;
	int rd;
	int row_len;
	int	col_len;
	t_points	points;

	i = 0;
	y = 0;
	row_len = 0;
	col_len = 0;
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
			init_points(&points);
			rd = read(fd, str, BUFFER_SIZE);
			if (rd < 0)
			{
				printf("error reading\n");
				free(str);
				return(0);
			} 
			else
			{	
				printf("%s\n", str);
				temp = ft_strsplit(str, '\n');
				int j;
				char **temp2;

				j = 0;
				while (j < list_len(temp)) {
					printf("%s\n\n", temp[j]);
					if (j == 0)
						row_len = list_len(temp);
					if (row_len != list_len(temp))
					{
						printf("malformed data\n");
						free(str);
						free(temp);
						return (0);
					}
					temp2 = ft_strsplit(temp[j], ' ' );
					set_points(temp2, j, &points);
					free(temp2);
					j++;
				}
				col_len = j;
				free(temp);
				print_points(points);
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

	i = 0;
	int zoom;

	zoom = 30;
	while (i < 190)
	{
		apply_zoom(&points, i, zoom, zoom); 
		i++;
	}
	printf("\n\n--- zoom applied ---\n\n");
	print_points(points);
	
	i = 0;
	while (i < 190)
	{
		isometric(&points, i);
		//center_point(&points,i);
		i++;
	}

	printf("\n\n--- Isometric Applied ---\n\n");
	print_points(points);

	/*
		Horizontal
		(10, 0) -> (12, 0)
		(x, y) -> (x + 1, y) -> (x + 2, y) ....
		(x, y + 1) -> (x + 1, y + 1) -> (x + 2, y + 1) ...

		Vertical
		(0, 10) -> (0, 15)
		(x, y) - (x, y + 1) -> (x, y + 2) ...
		(x + 1, y) -  (x + 1, y + 1) - > (x + 1, y + 2) ... 

		to_draw
		(x1, y1) (x2, y2) 


	*/
	/*
	while (y < col_len)
	{
		x = 0;
		while (x < row_len)
		{
			
			put_line(points, img, x, y);
			x++;
		}
		y++;
	}
	*/
//	 put_line(t_points points, mlx_image_t *img, int x1, int y1, int x2, int y2);

	/*	
	int	x1;
	int x2;
	int y1;
	int y2;
	int x_dist;
	int	y_dist;
	int j;

	y1 = 0;
	y2 = 0;
	x1 = 0;
	x2 = 0;
	i = 0;
	j = 0;
	x_dist = 0;
	y_dist = 0;
	while (i < 190) {
		x1 = points.x[i];
		x2 = points.x[i + 1];

		y1 = points.y[i];
		y2 = points.y[i + 18];

		x_dist = x1 - x2;
		j = 0;
		while (j < abs(x_dist)) {
			mlx_put_pixel(img, x1, y1, 0xFF0000FF);
			j++;
			x1++;
		}
	
		y_dist = y1 - y2;
		j = 0;
		while (j < abs(y_dist)) {
			mlx_put_pixel(img, x1, y1, 0xFF000FF);
			j++;
			y1++;
		}
		i++;	
	}
	*/
	int x;
	int y;

	x = 0;
	y = 0;
	while (x < row_len)
	{
		y = 0;
		while (y < col_len)
		{
			put_line(points, img, x, y, x, y + 1);
			y++;
		}
		x++;
	}

	x = 0;
	y = 0;
	while (y < col_len)
	{
		x = 0;
		while (x < row_len)
		{
			put_line(points, img, x, y, x + 1, y);
			x++;
		}
		y++;
	}

	mlx_loop(mlx);
	}
	return (0);
}



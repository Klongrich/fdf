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

//Make sure they are numbers.
//Split by spaces.
//Even number of values in rows && columns (has to make a rectangle or square) 



//(x, y)
//x = WIDTH / ROW_SIZE
//y = HEIGHT / COLUMN_SIZE
//


void	set_points(char **str, int y, t_points *points)
{
	int	i;
	int index;

	i = 0;
	index = y * 19;
	printf("index: %d\n", index);
	while (str[i]) 
	{
		printf("index: %d - i: %d - y: %d\n", index, i, y);
		points->x[index + i] = i;
		points->y[index + i] = y;
		points->z[index] = ft_atoi(str[i]);
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
	t_points	points;

	i = 0;
	y = 0;
	row_len = 0;
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
					temp2 = ft_strsplit(temp[j], ' ' );
					set_points(temp2, j, &points);
					j++;
				}
				print_points(points);
			}
			/*
			while(get_next_line(fd, &str)) {
				temp = ft_strsplit(str, ' ');
				if (y == 0)
					row_len = list_len(temp);
				if (row_len != list_len(temp))
				{
					printf("rows malformed\n");
					free(str);
					return (0);
		
				}
				set_points(temp,  y, &points);
				y++;
			}
			print_points(points);
			*/
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


	/*
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
		*/
	mlx_loop(mlx);
	}
	return (0);
}



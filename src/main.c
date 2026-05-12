#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <MLX42/MLX42.h>

#define WIDTH 600
#define HEIGHT 600

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

	mlx_loop(mlx);

	return (0);
}


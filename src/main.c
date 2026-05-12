#include "mlx.h"
#include <stdlib.h>
#include <stdio.h>

int main(void)
{
    void    *mlx_ptr;
    void    *win_ptr;

    // 1. Initialize the connection to the graphical system
    mlx_ptr = mlx_init();
    if (mlx_ptr == NULL)
        return (1);

    // 2. Create the window (width, height, title)
    win_ptr = mlx_new_window(mlx_ptr, 640, 480, "FdF Project");
    if (win_ptr == NULL) {
        free(mlx_ptr); // Standard cleanup if window fails
        return (1);
    }

    // 3. Start the event loop (keeps window open and listening for input)
    mlx_loop(mlx_ptr);

    return (0);
}


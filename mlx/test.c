#include <mlx.h>
#include <stdio.h>
#include <unistd.h>

typedef struct	s_data {
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
}				t_data;

typedef struct	s_mlx
{
	t_data		data;
	void 		*mlx;
	void 		*window;
	int			side;
	int			screenWidth;
	int			screenHeight;
	int			mapHeight;
	int			mapWidth;
	double		posX;
	double		posY;
	char		**map;
}				t_mlx;


int	main(void)
{

    t_mlx mlx;
    mlx.side = 50;

    mlx.mlx = mlx_init();
    char *relative_path = "test.png";
    int img_width;
    int img_height;
  
    mlx.window = mlx_new_window(mlx.mlx, 1000, 1000, "so_long");
    mlx.data.img = mlx_new_image(mlx.mlx, 1000, 1000);
    mlx.data.addr = mlx_get_data_addr(mlx.data.img, &mlx.data.bits_per_pixel,
                                      &mlx.data.line_length, &mlx.data.endian);
    
  
    






	mlx.data.img = mlx_png_file_to_image(mlx, relative_path, &img_width, &img_height);
    mlx_put_image_to_window(mlx.mlx, mlx.window, mlx.data.img, 0, 0);
    mlx_loop(mlx.mlx);
    return 0;
}


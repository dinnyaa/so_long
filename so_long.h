#ifndef SO_LONG_H
# define SO_LONG_H

#include "mlx/mlx.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include "keys.h"

#define SIDE 50

extern int		is_pressed;
extern int 		move_count;
extern int 		c_count;

typedef struct	s_data {
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	int			height;
	int			width;
}				t_data;

typedef struct	s_mlx
{
	t_data		data;
	t_data		cat;
	t_data		wall;
	t_data 		cactus;
	t_data		rat;
	t_data		house;
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

void			my_mlx_pixel_put(t_data *data, int x, int y, int color);
int				get_color(t_data *data, int x, int y);
int				rgb(int r, int g, int b);
void			draw_map(t_mlx *mlx);
void 			draw_walls(t_mlx *mlx, int x, int y);
void 			draw_texture (t_mlx *mlx, int x, int y, t_data texture);
void			ft_background(t_mlx *mlx);
void 			parsing(t_mlx *mlx, char *argv);
int 			ft_close();
char			*ft_itoa(int n);
void    		set_images(t_mlx *mlx);
int 			ft_press(int key, t_mlx *mlx);
int				ft_release(int key);
void 			ft_sleep();
void 			clear(t_mlx *mlx);
int 			check_walls(t_mlx *mlx);
int				check_characters(t_mlx *mlx);
int 			check_rectengular(t_mlx *mlx);
int				validation(t_mlx *mlx);
int				is_wall(t_mlx mlx, int x, int y);
void    		player_pos(t_mlx *mlx, int x, int y);
void 			check_pos(t_mlx *mlx);
int 			walk(t_mlx *mlx);

#endif
#include "so_long.h"

void my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
    char *dst;

    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    *(unsigned int *)dst = color;
}

int		get_color(t_data *data, int x, int y)
{
	return (*(int *)(data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8))));
}

int rgb(int r, int g, int b)
{
    return r << 16 | g << 8 | b;
}

void draw_walls(t_mlx *mlx, int x, int y)
{
    for (int i = 0; i < mlx->wall.height; i++)
       for (int j = 0; j < mlx->wall.width; j++)
           my_mlx_pixel_put(&mlx->data, x + j, y + i, get_color(&mlx->wall, j, i));
    
}
void draw_texture (t_mlx *mlx, int x, int y, t_data texture)
{
    for (int i = 0; i < texture.height; i++)
        for (int j = 0; j < texture.width; j++)
        {
            unsigned int color = get_color(&texture, j, i);
            my_mlx_pixel_put(&mlx->data, x + j, y + i, color ==
            0xff000000 ? rgb(219,112,147) : color);
        }
}
void ft_background (t_mlx *mlx)
{
    int x, y;
    x = 0;
    while (x < mlx->screenHeight)
    {
        y = 0;
        while (y < mlx->screenWidth)
        {
            my_mlx_pixel_put(&mlx->data, y, x, rgb(219,112,147));
            y++;
        }
        x++;
    }
}
void draw_map(t_mlx *mlx)
{
    int x;
    int y = 0;
    ft_background(mlx);
    while (y < mlx->mapHeight)
    {
        x = 0;
        while (x < mlx->mapWidth)
        {
             if (mlx->map[y][x] == '1')
                draw_texture(mlx, x * SIDE, y * SIDE, mlx->wall);
            else if (mlx->map[y][x] == 'C')
                draw_texture(mlx, x * SIDE, y * SIDE, mlx->rat);
            else if (mlx->map[y][x] == 'P')
                player_pos(mlx,  x, y);
            else if (mlx->map[y][x] == 'N')
                draw_texture(mlx, x * SIDE, y * SIDE, mlx->cactus);
            else if (mlx->map[y][x] == 'E')
                draw_texture(mlx, x * SIDE, y * SIDE, mlx->house);
            ++x;
        }
        ++y;
    }
}









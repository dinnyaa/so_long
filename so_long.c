#include "so_long.h"

int is_pressed = 0;
int move_count = 0;
int c_count = 0;

void ft_sleep()
{
    int i = 0;
    while (i < 150000000)
        i++;
}

void clear(t_mlx *mlx)
{
    int x = 0;
    int y = 0;
    while (y < mlx->screenHeight)
    {
        x = 0;
        while (x < mlx->screenWidth)
        {
            my_mlx_pixel_put(&mlx->data, x, y, rgb(0, 0, 0));
            x++;
        }
        y++;
    }
}

int ft_close()
{
    exit(0);
    return (0);
}
int is_wall(t_mlx mlx, int x, int y)
{
    if (mlx.map[y][x] == '1')
        return (1);
    return (0);
}
int ft_press(int key, t_mlx *mlx)
{
    is_pressed = 1;
    if (key == KEY_W && !is_wall(*mlx, (int)mlx->posX,(int)mlx->posY - 1))
    {
        mlx->posY--;
        move_count++;
        printf("movement count ~ %d\n", move_count);
    }
    else if (key == KEY_A && !is_wall(*mlx, (int)mlx->posX - 1,(int)mlx->posY))
    {
        mlx->posX--;
        move_count++;
        printf("movement count ~ %d\n", move_count);
    }
    else if (key == KEY_S && !is_wall(*mlx, (int)mlx->posX,(int)mlx->posY + 1))
    {
       mlx->posY++;
       move_count++;
       printf("movement count ~ %d\n", move_count);
    }
    else if (key == KEY_D && !is_wall(*mlx, (int)mlx->posX + 1,(int)mlx->posY))
    {
        mlx->posX++;
        move_count++;
        printf("movement count ~ %d\n", move_count);
    }
    else if (key == KEY_ESC)
        ft_close();
    return (1);
}

int ft_release(int key)
{
    if (key == KEY_W || key == KEY_A || key == KEY_S || key == KEY_D)
        is_pressed = 0;
    return (1);
}

void    player_pos(t_mlx *mlx, int x, int y)
{
    mlx->map[y][x] = '0';
    mlx->posX = (double)x;
    mlx->posY = (double)y;
}

void check_pos(t_mlx *mlx)
{
    int x = (int)mlx->posX;
    int y = (int)mlx->posY;
    if (mlx->map[y][x] == 'C')
    {
        mlx->map[y][x] = '0';
        c_count--;
    }
    else if ((mlx->map[y][x] == 'E' && !c_count) || mlx->map[y][x] == 'N')
    {
        ft_sleep();
        ft_close();
    }
}

static int		len(int n)
{
	int len;

	len = 0;
	if (n <= 0)
		len++;
	while (n)
	{
		n /= 10;
		len++;
	}
	return (len);
}

char			*ft_itoa(int n)
{
	int		l;
	char	*ptr;
	long	num;

	num = n;
	l = len(num);
	ptr = (char*)malloc(sizeof(char) * (l + 1));
	if (!ptr)
		return (NULL);
	if (num == 0)
		ptr[0] = '0';
	ptr[l--] = '\0';
	while (num)
	{
		ptr[l] = num % 10 + '0';
		l--;
		num /= 10;
	}
	return (ptr);
}
int walk(t_mlx *mlx)
{    
    clear(mlx);
    draw_map(mlx);
    check_pos(mlx);
    mlx_put_image_to_window(mlx->mlx, mlx->window, mlx->data.img, 0, 0);
    mlx_put_image_to_window(mlx->mlx, mlx->window, mlx->cat.img, mlx->posX * 50, mlx->posY * 50);
    mlx_string_put(mlx->mlx, mlx->window, 20, 20, rgb(255,255,255),  "count = ");
    mlx_string_put(mlx->mlx, mlx->window, 100, 20, rgb(255,255,255),  ft_itoa(move_count));
    return (1);
}

void    set_images(t_mlx *mlx)
{
    mlx->data.img = mlx_new_image(mlx->mlx, mlx->screenWidth, mlx->screenHeight);
    mlx->cat.img = mlx_xpm_file_to_image(mlx->mlx, "./pics/cat.xpm", &mlx->cat.width, &mlx->cat.height);
    mlx->wall.img = mlx_xpm_file_to_image(mlx->mlx, "./pics/yellow.xpm", &mlx->wall.width, &mlx->wall.height);
    mlx->rat.img = mlx_xpm_file_to_image(mlx->mlx, "./pics/rat.xpm", &mlx->rat.width, &mlx->rat.height);
    mlx->cactus.img = mlx_xpm_file_to_image(mlx->mlx, "./pics/cactus.xpm", &mlx->cactus.width, &mlx->cactus.height);
    mlx->house.img = mlx_xpm_file_to_image(mlx->mlx, "./pics/house.xpm", &mlx->house.width, &mlx->house.height);
}
int main(int argc, char **argv)
{
    t_mlx mlx;
    mlx.mlx = mlx_init();
    if (argc == 2)
    {
        parsing(&mlx, argv[1]);
        if (!validation(&mlx))
            return (0);
        mlx.window = mlx_new_window(mlx.mlx, mlx.screenWidth, mlx.screenHeight, "./so long");
        set_images(&mlx);
    ////////////////////////////////
        mlx.data.addr = mlx_get_data_addr(mlx.data.img, &mlx.data.bits_per_pixel,
                            &mlx.data.line_length, &mlx.data.endian);
        mlx.wall.addr = mlx_get_data_addr(mlx.wall.img, &mlx.wall.bits_per_pixel,
                                &mlx.wall.line_length, &mlx.wall.endian);
        mlx.rat.addr = mlx_get_data_addr(mlx.rat.img, &mlx.rat.bits_per_pixel,
                                &mlx.rat.line_length, &mlx.rat.endian);    
        mlx.cactus.addr = mlx_get_data_addr(mlx.cactus.img, &mlx.cactus.bits_per_pixel,
                                &mlx.cactus.line_length, &mlx.cactus.endian);
        mlx.house.addr = mlx_get_data_addr(mlx.house.img, &mlx.house.bits_per_pixel,
                                &mlx.house.line_length, &mlx.house.endian);
        //////////////////////////////
        mlx_loop_hook(mlx.mlx, walk, &mlx);
        mlx_hook(mlx.window, 17, 1L << 17, ft_close, &mlx);
        mlx_hook(mlx.window, 2, 1L << 0, ft_press, &mlx);
        mlx_hook(mlx.window, 3, 1L << 0, ft_release, &mlx);   
        mlx_loop(mlx.mlx);

    }
    else
        printf("!!!The map was not found!!!\n");
    return (0);
}

#include "so_long.h"

static int word_count(char const *s, char c)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
			count++;
		i++;
	}
	return (count);
}

static int word_length(char const *s, char c)
{
	int i;

	i = 0;
	while (s[i] != c && s[i] != '\0')
		i++;
	return (i);
}

static char **matrix(char const *s, char c, char **result, int words_count)
{
	int i;
	int j;
	int w_len;

	while (*s == c)
		s++;
	i = -1;
	while (++i < words_count)
	{
		while (*s == c)
			s++;
		j = 0;
		w_len = word_length(s, c);
		if (!(result[i] = (char *)malloc(sizeof(char) * (w_len + 1))))
			return (NULL);
		while (j < w_len)
		{
			result[i][j] = *s;
			s++;
			j++;
		}
		result[i][j] = '\0';
	}
	result[i] = NULL;
	return (result);
}

static char **ft_split(char const *s, char c)
{
	char **result;
	int wcount;

	if (!s)
		return (NULL);
	wcount = word_count(s, c);
	if (!(result = (char **)malloc(sizeof(char *) * (wcount + 1))))
		return (NULL);
	result = matrix(s, c, result, wcount);
	return (result);
}

static char *ft_strcat(char *dest, char *src)
{
	int i;
	int j;

	i = 0;
	if (dest == NULL)
		return (src);
	while (dest[i] != '\0')
		i++;
	j = 0;
	while (src[j] != '\0')
	{
		dest[i + j] = src[j];
		j++;
	}
	dest[i + j] = '\0';

	return (dest);
}

static	int		ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

static	char *ft_strdup(char *s1)
{
	size_t len;
	char *str;
	char *tmp;

	len = ft_strlen(s1);
	str = (char *)malloc(sizeof(char) * len + 1);
	if (str == NULL)
		return (NULL);
	tmp = str;
	while (len--)
		*str++ = *s1++;
	*str = '\0';
	return (tmp);
}

int check_walls(t_mlx *mlx)
{
	int i;
	int j;

	i = 0;
	while (i < mlx->mapHeight)
	{
		j = 0;
		while (j < mlx->mapWidth)
		{
			if (i == 0 || i == mlx->mapHeight - 1 || j == mlx->mapWidth - 1 || j == 0)
			{
				if (mlx->map[i][j] != '1')
				{
					printf("\n!!!The map must be surrounded by walls!!!\n");
					return (0);
				}
			}
			j++;
		}
		i++;
	}
	return (1);
}
int check_rectengular(t_mlx *mlx)
{
	int i = 1;

	while (i < mlx->mapHeight)
	{
		if (mlx->mapWidth != ft_strlen(mlx->map[i]))
		{
			printf("\n!!!The map must be rectangular!!!\n");
			return (0);
		}
		i++;
	}
	return (1);	
}

int	check_characters(t_mlx *mlx)
{
	int i;
	int j;
	int	found_c = 0,found_p = 0, found_e = 0;

	i = 0;
	while (i < mlx->mapHeight)
	{
		j = 0;
		while (j < mlx->mapWidth)
		{
			if (mlx->map[i][j] == 'C')
				found_c++;
			else if (mlx->map[i][j] == 'P')
				found_p++;
			else if (mlx->map[i][j] == 'E')
				found_e++;
			j++;
		}
		i++;
	}
	c_count = found_c;
	if (found_p > 1 || found_e > 1)
	{
		printf("!!!Map must have  one collectible and one starting position.!!!\n");
		return (0);
	}
	if (!(found_c && found_p && found_e))
	{
		printf("!!!Not all the needed characters were found!!!\n");
		return (0);
	}
	return (1);
}
int	validation(t_mlx *mlx)
{
	int a = check_characters(mlx);
	int b = check_rectengular(mlx);
	int c = check_walls(mlx);
	if (!(a && b && c))
		return (0);
	return (1);
}

void parsing(t_mlx *mlx, char *argv)
{
	char *c = malloc(2);
	char *string = NULL;
	int n;
	int fd = open(argv, O_RDONLY);
	while ((n = read(fd, c, 1)) > 0)
		string = ft_strdup(ft_strcat(string, c));
	mlx->mapHeight = word_count(string, '\n');
	mlx->mapWidth = word_length(string, '\n');
	mlx->screenHeight = mlx->mapHeight * SIDE;
	mlx->screenWidth = mlx->mapWidth * SIDE;
	mlx->map = ft_split(string, '\n');
	free(c);
	free(string);
	close(fd);
}
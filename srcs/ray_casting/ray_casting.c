#include "cub3D.h"

t_position *create_position(double i, double j)
{
	t_position *pos;

	pos = malloc(sizeof(t_position));
	pos->x = j;
	pos->y = i;
	return (pos);
}

t_position *get_position(char **map)
{
	int i;
	int j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'N' || map[i][j] == 'E' || map[i][j] == 'S' || map[i][j] == 'W')
				return (create_position(i, j));
			j++;
		}
		i++;
	}
	return (NULL);
}

void ray_casting(t_cub *cub)
{

	t_position *pos = get_position(cub->file->map);
	cub->player_position = pos;
	printf("position : \t%f, %f\n", pos->x, pos->y);
	printf("orientation : \t%c\n", cub->file->map[(int)pos->y][(int)pos->x]);
}


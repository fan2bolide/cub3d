#include "cub3D.h"

double get_orientation(char **map, t_position *pos);

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
	cub->player_position = get_position(cub->file->map);
	cub->view_angle = get_orientation(cub->file->map, cub->player_position);
	printf("position : \t%f, %f\n", cub->player_position->x, cub->player_position->y);
	printf("orientation : \t%c\n", cub->file->map[(int)cub->player_position->y][(int)cub->player_position->x]);
}

double get_orientation(char **map, t_position *pos) {
	char orientation;

	orientation = map[(int)pos->y][(int)pos->x];
	if (orientation == 'N')
		return (M_PI_2);
	if (orientation == 'E')
		return (0);
	if (orientation == 'W')
		return (M_PI);
	if (orientation == 'S')
		return (3 * M_PI_2);
}

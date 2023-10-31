#include "cub3D.h"

double get_orientation(char **map, t_position *pos);

void get_front_distance(t_cub *cub);

void shoot_ray(t_position position, t_cub *cub);

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

int ray_casting(t_cub *cub)
{
	if (!cub->data->map)
		return (0);
	cub->player_position = get_position(cub->data->map);
	cub->player_position->x += 0.5;
	cub->player_position->y += 0.5;
//	printf("position : \t%f, %f\n", cub->player_position->x, cub->player_position->y);
//	printf("orientation : \t%c\n", cub->data->map[(int)cub->player_position->y][(int)cub->player_position->x]);
	get_front_distance(cub);
	return (1);
}

void	get_front_distance(t_cub *cub)
{
	t_position	ray_pos;

	ray_pos.x = cub->player_position->x;
	ray_pos.y = cub->player_position->y;
	shoot_ray(ray_pos, cub);
}

void print_distance(t_position ray, t_cub *cub)
{
	double distance;

	distance = sqrt((ray.x - cub->player_position->x) * (ray.x - cub->player_position->x) + (ray.y - cub->player_position->y) * (ray.y - cub->player_position->y));

	printf("distance = %f, view_angle = %f\n", distance, cub->view_angle);
}

void jesaispasencore(t_position ray, double ray_direction, t_position *delta, t_cub *cub)
{
	delta->y = 0;
	if (ray_direction == M_PI)
	{
		while (cub->data->map[(int)((int)ray.y + delta->y + 1)][(int)ray.x] == '0')
		{
			delta->y++;
		}
		print_distance(ray, cub);
	}
}

void get_delta_to_next_column(t_position ray, double ray_direction, t_position *delta)
{
	if (ray_direction < M_PI_2)
	{
		delta->x = 1 - (ray.x - (int)ray.x);
		delta->y = (sin(ray_direction) / cos(ray_direction)) * delta->x;
		return ;
	}
	if (ray_direction < M_PI)
	{
		delta->x = ray.x - (int)ray.x;
		delta->y = (ray.x - (int)ray.x) / cos(ray_direction) * -1;
		return ;
	}
	if (ray_direction < 3 * M_PI_2)
	{
//		delta->x = (int)ray.x;
//		delta->y = ((int)ray.x - ray.x) / cos(ray_direction) * -1;
		return ;
	}
//	delta->x = (int)ray.x + 1;
//	delta->y = ((int)ray.x - ray.x) / cos(ray_direction);
}

void get_delta_to_next_line(t_position ray, double ray_direction, t_position *delta)
{
	if (ray_direction < M_PI_2)
	{
		delta->y = 1 - (ray.y - (int)ray.y);
		delta->x = (cos(ray_direction) / sin(ray_direction)) * delta->y;
		return ;
	}
	if (ray_direction < M_PI)
	{
//		new->x = ;
//		new->y = ;
		return ;
	}
	if (ray_direction < 3 * M_PI_2)
	{
//		new->x = ;
//		new->y = ;
		return ;
	}
//	new->x = ;
//	new->y = ;
}

void apply_minimal_distance(t_position *ray, t_position delta_x, t_position delta_y)
{
	if (delta_x.x < delta_y.x && delta_x.y < delta_y.y)
	{
		ray->x += delta_x.x;
		ray->y += delta_x.y;
		printf("ray.x = %f \tray.y = %f\tapplying x\n", ray->x, ray->y);
		return ;
	}
	if (delta_x.x > delta_y.x && delta_x.y > delta_y.y)
	{
		ray->x += delta_y.x;
		ray->y += delta_y.y;
		printf("deltax = %f, deltay = %f\n", delta_x.x, delta_y.x);
		printf("ray.x = %f \tray.y = %f\tapplying y\n", ray->x, ray->y);
		return ;
	}
}

void shoot_ray(t_position ray, t_cub *cub)
{
	double		ray_direction;
	t_position	new_x;
	t_position	new_y;

	ray_direction = cub->view_angle;
	if (ray_direction == M_PI || ray_direction == M_PI_2 || ray_direction == 3 * M_PI_2 || ray_direction == 2 * M_PI)
		return (jesaispasencore(ray, ray_direction, &new_x, cub), (void)0);
	while (1)
	{
		new_x.x = 0;
		new_x.y = 0;
		new_y.x = 0;
		new_y.y = 0;
		get_delta_to_next_column(ray, ray_direction, &new_x);
		get_delta_to_next_line(ray, ray_direction, &new_y);
		if (new_x.x == new_y.x)
		{
			ray.x += (int)ray.x + 1;
			ray.y += (int)ray.y + 1;
		}
		else
			apply_minimal_distance(&ray, new_x, new_y);
//		if (ray.x == (int)ray.x || ray.y == (int)ray.y)
		if (cub->data->map[(int)ray.y][(int)ray.x] == '1')
			return print_distance(ray, cub);
	}
}

double get_orientation(char **map, t_position *pos) {
	char orientation;

//	orientation = map[(int)pos->y][(int)pos->x];
//	if (orientation == 'N')
//		return (M_PI_2);
//	if (orientation == 'E')
//		return (0);
//	if (orientation == 'W')
//		return (M_PI);
//	if (orientation == 'S')
//		return (3 * M_PI_2);
	return (M_PI_4);
}

/*
 * tracé de rayon :
 * calcul de la distance a la prochaine ligne en x
 * calcul de la distance a la prochaine ligne en y
 * calcul du minimum entre les deux distances
 * deplacement du point rayon par le minimum trouvé.
 */
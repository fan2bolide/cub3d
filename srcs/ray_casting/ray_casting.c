//#include <tclDecls.h>
#include <float.h>
#include "cub3D.h"

double get_orientation(char **map, t_position *pos);

void shoot_ray(t_position *ray, t_cub *cub, double angle);

int	ray_casting(t_cub *cub)
{
	t_position	ray_pos[cub->win_size[1] / 2];
	double		angle[cub->win_size[1] / 2];
	double		ray_spacing;
	int			i;

	i = 0;
	ray_spacing = cub->fov / (cub->win_size[1] - 1) * 2;
	while (i < cub->win_size[1] / 2)
	{
		ray_pos[i].x = cub->player_position->x;
		ray_pos[i].y = cub->player_position->y;
		angle[i] = cub->view_angle - (cub->fov / 2) + (i * ray_spacing);
		i++;
	}
	i = 0;
	while (i < cub->win_size[1] / 2)
	{
		shoot_ray(ray_pos + i, cub, angle[i]);
		i++;
	}
	render_minimap(cub, ray_pos, angle);
	return (1);
}

void print_distance(t_position ray, t_cub *cub)
{
	double distance;

	distance = sqrt((ray.x - cub->player_position->x) * (ray.x - cub->player_position->x) + (ray.y - cub->player_position->y) * (ray.y - cub->player_position->y));

//	printf("distance = %f, view_angle = %f\n", distance, cub->view_angle);
}

void jesaispasencore(t_position *ray, double ray_direction, t_position *delta, t_cub *cub)
{
	delta->y = 0;
	if (ray_direction == M_PI_2)
	{
		while (cub->data->map[(int)((int)ray->y + delta->y + 1)][(int)ray->x] == '0')
		{
			delta->y++;
		}
		ray->y += delta->y;
		print_distance(*ray, cub);
	}
}

void get_delta_to_next_column(t_position ray, double ray_direction, t_position *delta)
{
	if (cos(ray_direction) > 0)
	{
		delta->x = 1.0 - (ray.x - (int)ray.x); //a droite
		delta->y = tan(ray_direction) * delta->x;
		return ;
	}

	delta->x = -(ray.x - (int)ray.x) - (ray.x == (int)ray.x); //a gauche
	delta->y = tan(ray_direction) * delta->x;
}

void get_delta_to_next_line(t_position ray, double ray_direction, t_position *delta)
{
	if (sin(ray_direction) > 0)
	{
		delta->y = 1 - (ray.y - (int)ray.y); // en haut
		delta->x = delta->y / tan(ray_direction);
		return ;
	}
	delta->y = -(ray.y - (int)ray.y + ((int)ray.y == ray.y)); // en bas
	delta->x = delta->y / tan(ray_direction);
}

double v_norm(t_position ray) {
	return sqrt(ray.x * ray.x + ray.y * ray.y);
}

void apply_minimal_distance(t_position *ray, t_position delta_x, t_position delta_y)
{
	if (v_norm(delta_x) < v_norm(delta_y))
	{
		ray->x += delta_x.x;
		ray->y += delta_x.y;
		return ;
	}
	ray->x += delta_y.x;
	ray->y += delta_y.y;
}

void shoot_ray(t_position *ray, t_cub *cub, double angle)
{
	t_position		new_x;
	t_position		new_y;

	while (1)
	{
		get_delta_to_next_column(*ray, angle, &new_x);
		get_delta_to_next_line(*ray, angle, &new_y);
		if (fabs(new_x.x - new_y.x) < FLT_EPSILON)
		{
			printf("Really cool stuff happened\n");
			return;
			ray->x += (int)ray->x * sin(angle) + cos(angle);
			ray->y += (int)ray->y * sin(angle) + cos(angle);
			// TODO make cool stuff
		}
		else {
			apply_minimal_distance(ray, new_x, new_y);
	//		if (ray.x == (int)ray.x)
	//			if (cub->data->map[(int)ray.y][(int)ray.x - (cos(angle) < 0)] == '1')
	//				return print_distance(ray, cub), render_minimap(cub, ray);
	//		if (ray.y == (int)ray.y)
	//			if (cub->data->map[(int)ray.y - (sin(angle) < 0)][(int)ray.x] == '1')
	//				return print_distance(ray, cub), render_minimap(cub, ray);
//			printf("\n\nsin < 0 : %d\tcos < 0 : %d\n\n\n", sin(angle) < 0, cos(angle) < 0);
//			printf("checking %d %d\n", (int)ray->y, (int)ray->x - (cos(angle) < 0));
			if (ray->y < 0 || ray->x < 0 || cub->data->map[(int)ray->y - (ray->y == (int)ray->y && sin(angle) < 0)][(int)ray->x - (ray->x == (int)ray->x &&(cos(angle) < 0))] == '1')
				return ;
//			printf("\tray.y = %f\tray.x = %f\n", ray->y, ray->x);
		}
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
	return (-M_PI_4);
}

/*
 * tracé de rayon :
 * calcul de la distance a la prochaine ligne en x
 * calcul de la distance a la prochaine ligne en y
 * calcul du minimum entre les deux distances
 * deplacement du point rayon par le minimum trouvé.
 */
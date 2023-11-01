#include "cub3D.h"

void	fdf_pixel_put(t_image *data, int x, int y, int color);
static void	fdf_put_line(t_cub *cub, t_position a, t_position b, int color);

void put_wall(t_cub *cub, int i, int j, int scale)
{
	int pixel_x;
	int pixel_y;
	int savej;
	unsigned int color;

	pixel_y = 0;
	if (j % 2) {
		if (i % 2) {
			color = 0x0000FF00;
		} else {
			color = 0x000000FF;
		}
	} else {
		if (i % 2) {
			color = 0x000000FF;
		} else {
			color = 0x0000FF00;
		}
	}
	i *= scale;
	j *= scale;
	savej = j;
	while (pixel_y < scale)
	{
		pixel_x = 0;
		j = savej;
		while (pixel_x < scale)
		{
			fdf_pixel_put(&cub->img, j, i, color);
//			fdf_pixel_put(&cub->img, j, i, pixel_y * 10 + pixel_x);
			pixel_x++;
			j++;
		}
		pixel_y++;
		i++;
	}
}

void render_minimap(t_cub *cub, t_position ray_collision)
{
	int i;
	int j;
	int scale;
	t_position player_dupl;

	cub->img.img = mlx_new_image(cub->mlx, 1440, 900);
	cub->img.addr = mlx_get_data_addr(cub->img.img, &cub->img.bits_per_pixel, &cub->img.line_length, &cub->img.endian);
	scale = 50;
	i = 0;
	while (cub->data->map[i])
	{
		j = 0;
		while (cub->data->map[i][j])
		{
			if (cub->data->map[i][j] == '1')
				put_wall(cub, i, j, scale);
			j++;
		}
		i++;
	}
	ray_collision.x *= scale;
	ray_collision.y *= scale;
	player_dupl.x = cub->player_position->x * scale;
	player_dupl.y = cub->player_position->y * scale;
	fdf_put_line(cub, player_dupl, ray_collision, 0xFF0000);
	mlx_put_image_to_window(cub->mlx, cub->win, cub->img.img, 0, 0);
}

void	fdf_pixel_put(t_image *data, int x, int y, int color)
{
	char	*dst;

	if (y >= 900 || x >= 1440)
		return printf("out_of_range\n"), (void)0;
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

static void	fdf_put_line(t_cub *cub, t_position a, t_position b, int color)
{
	int		i;
	int		steps;
	double	x;
	double	y;

	steps = ft_max(fabs(b.x - a.x), fabs(b.y - a.y));
	x = a.x;
	y = a.y;
	i = 0;
	while (i <= steps)
	{
		if (round(x) >= 0 && round(x) < cub->win_size[1] && round(y) >= 0
			&& round(y) < cub->win_size[0])
			fdf_pixel_put(&cub->img, (int)round(x), (int)round(y), color);
		x += (b.x - a.x) / (double)steps;
		y += (b.y - a.y) / (double)steps;
		i++;
	}
}
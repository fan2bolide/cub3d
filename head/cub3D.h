/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaust <nfaust@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 06:30:22 by nfaust            #+#    #+#             */
/*   Updated: 2023/12/18 14:35:51 by bajeanno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

//=================== INCLUDES =====================//

# include "error_codes.h"
# include <unistd.h>
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <math.h>
# include "mlx.h"
# include "libft.h"
# include <errno.h>
# include <sys/time.h>
# include <pthread.h>

//=================== DEFINES  =====================//

// X11 masks
# define NO_EVENT_MASK				0
# define KEY_PRESS_MASK				1
# define KEY_RELEASE_MASK			2
# define BUTTON_PRESS_MASK			4
# define BUTTON_RELEASE_MASK		8
# define ENTER_WINDOW_MASK			16
# define LEAVE_WINDOW_MASK			32
# define POINTER_MOTION_MASK		64
# define POINTER_MOTION_HINT_MASK	128
# define BUTTON_1_MOTION_MASK		256
# define BUTTON_2_MOTION_MASK		512
# define BUTTON_3_MOTION_MASK		1024
# define BUTTON_4_MOTION_MASK		2048
# define BUTTON_5_MOTION_MASK		4096
# define BUTTON_MOTION_MASK			8192
# define KEY_MAP_STATE_MASK			16384
# define EXPOSURE_MASK				32768
# define VISIBILITY_CHANGE_MASK		65536
# define STRUCTURE_NOTIFY_MASK		131072
# define RESIZE_REDIRECT_MASK		262144
# define SUBSTRUCTURE_NOTIFY_MASK	524288
# define SUBSTRUCTURE_REDIRECT_MASK	1048576
# define FOCUS_CHANGE_MASK			2097152
# define PROPERTY_CHANGE_MASK		4194304
# define COLOR_MAP_CHANGE_MASK		8388608
# define OWNER_GRAB_BUTTON_MASK		16777216

# define PRESSED    1
# define RELEASED   0
# define SPEED		0
# define SENSI		1

// ========================= PATHS ============================= //
# define BJ_PATH		"textures/bajeanno.xpm"
# define BLUE_PATH		"textures/blue_portal.xpm"
# define ORG_PATH		"textures/orange_portal.xpm"
# define BLUE_TR_PATH	"textures/blue_portal_transparent.xpm"
# define ORG_TR_PATH	"textures/orange_portal_transparent.xpm"
# define BLUE_OUT_P		"textures/outline_blue.xpm"
# define OR_OUT_P		"textures/outline_orange.xpm"
# define LOAD_SCREEN	"textures/load_screen.xpm"
# define MENU_BG		"textures/menu_bg.xpm"
# define BUTTON			"textures/button.xpm"
# define BUTTON_SH		"textures/button_shadow.xpm"
# define CHECK			"textures/check.xpm"
# define CURSOR			"textures/cursor.xpm"
# define RESET			"textures/reset.xpm"
# define DOOR			"textures/wolfenstein/wood.xpm"
# define DOOR_HINT		"textures/hint.xpm"
# define PORTAL_GUN_B	"textures/portal_gun_b.xpm"
# define PORTAL_GUN_O	"textures/portal_gun_o.xpm"
# define RICKS_GUN		"textures/rick_portal_gun.xpm"
# define MC_GLASS		"textures/minecraft_glass.xpm"
# define RICKS_PORTAL	"textures/rick_portal.xpm"
# define VALVE_GUY		"textures/valve_guy.xpm"

# ifndef NB_THREADS
#  define NB_THREADS	16
# endif
# if defined (__APPLE__)
#  define MACOS
# else
#  define LINUX
# endif

// X11 events
# define KEY_PRESS			2
# define KEY_RELEASE		3
# define BUTTON_PRESS		4
# define BUTTON_RELEASE		5
# define MOTION_NOTIFY		6
# define ENTER_NOTIFY		7
# define LEAVE_NOTIFY		8
# define FOCUS_IN			9
# define FOCUS_OUT			10
# define KEY_MAP_NOTIFY		11
# define EXPOSE				12
# define GRAPHICS_EXPOSE	13
# define NO_EXPOSE			14
# define VISIBILITY_NOTIFY	15
# define CREATE_NOTIFY		16
# define DESTROY_NOTIFY		17
# define UNMAP_NOTIFY		18
# define MAP_NOTIFY			19
# define MAP_REQUEST		20
# define REPARENT_NOTIFY	21
# define CONFIGURE_NOTIFY	22
# define CONFIGURE_REQUEST	23
# define GRAVITY_NOTIFY		24
# define RESIZE_REQUEST		25
# define CIRCULATE_NOTIFY	26
# define CIRCULATE_REQUEST	27
# define PROPERTY_NOTIFY	28
# define SELECTION_CLEAR	29
# define SELECTION_REQUEST	30
# define SELECTION_NOTIFY	31
# define COLOR_MAP_NOTIFY	32
# define CLIENT_MESSAGE		33
# define MAPPING_NOTIFY		34
# define GENERIC_EVENT		35
# define LAST_EVENT			36

# if defined(__APPLE__)

enum e_mouse_buttons
{
	BUTTON_LEFT = 1,
	BUTTON_RIGHT = 2,
	SCROLL_DOWN = 4,
	SCROLL_UP = 5,
};
# elif defined(__linux__)

enum e_mouse_buttons
{
	BUTTON_LEFT = 1,
	BUTTON_RIGHT = 3,
	SCROLL_DOWN = 5,
	SCROLL_UP = 4,
};
# else
#  error "Unsuported OS"
# endif

# if defined(__APPLE__)

enum e_key_codes
{
	KEY_A = 0,
	KEY_B = 11,
	KEY_C = 8,
	KEY_D = 2,
	KEY_E = 14,
	KEY_F = 3,
	KEY_G = 5,
	KEY_H = 4,
	KEY_I = 34,
	KEY_J = 38,
	KEY_K = 40,
	KEY_L = 37,
	KEY_M = 46,
	KEY_N = 45,
	KEY_O = 31,
	KEY_P = 35,
	KEY_Q = 12,
	KEY_R = 15,
	KEY_S = 1,
	KEY_T = 17,
	KEY_U = 32,
	KEY_V = 9,
	KEY_W = 13,
	KEY_X = 7,
	KEY_Y = 16,
	KEY_Z = 6,
	KEY_ESC = 53,
	KEY_SPACE = 49,
	KEY_SLASH = 44,
	KEY_L_SHIFT = 257,
	KEY_R_SHIFT = 258,
	KEY_R_CTRL = 269,
	KEY_UP = 126,
	KEY_DOWN = 125,
	KEY_LEFT = 123,
	KEY_RIGHT = 124,
	KEY_DOT = 47,
	KEY_S_QUOTE = 39,
	KEY_SEMI_COLON = 41,
	KEY_COMMAND = 259,
	KEY_BACKSPACE = 51,
	KEY_RETURN	= 36,
	KEY_TAB = 48,
	KEY_F11 = 321
};
# elif defined(__linux__)

enum e_key_codes
{
	KEY_A = 97,
	KEY_B = 98,
	KEY_C = 99,
	KEY_D = 100,
	KEY_E = 101,
	KEY_F = 102,
	KEY_G = 103,
	KEY_H = 104,
	KEY_I = 105,
	KEY_J = 106,
	KEY_K = 107,
	KEY_L = 108,
	KEY_M = 109,
	KEY_N = 110,
	KEY_O = 111,
	KEY_P = 112,
	KEY_Q = 113,
	KEY_R = 114,
	KEY_S = 115,
	KEY_T = 116,
	KEY_U = 117,
	KEY_V = 118,
	KEY_W = 119,
	KEY_X = 120,
	KEY_Y = 121,
	KEY_Z = 122,
	KEY_ESC = 65307,
	KEY_SPACE = 32,
	KEY_SLASH = 47,
	KEY_L_SHIFT = 65505,
	KEY_R_SHIFT = 65506,
	KEY_R_CTRL = 65508,
	KEY_UP = 65362,
	KEY_DOWN = 65364,
	KEY_LEFT = 65361,
	KEY_RIGHT = 65363,
	KEY_DOT = 46,
	KEY_S_QUOTE = 39,
	KEY_SEMI_COLON = 59,
	KEY_COMMAND = 65507,
	KEY_BACKSPACE = 65288,
	KEY_TAB	= 65289,
	KEY_RETURN	= 65293,
	KEY_F11 = 65480
};
# else
#  error "Unsuported OS"
# endif

# define SCREEN_DISTANCE	0.8
# define HEIGHT 0
# define WIDTH 1

//=================== STRUCTURES ====================//
typedef struct s_color{
	unsigned char	blue;
	unsigned char	green;
	unsigned char	red;
	unsigned char	transparency;
}	t_color;

typedef struct s_iposition
{
	size_t	x;
	size_t	y;
}	t_iposition;

typedef struct s_data{
	char		**map;
	char		**wall_sur;
	char		*texture[4];
	t_color		*ceiling_color;
	t_color		*floor_color;
}	t_data;

typedef struct s_image
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		width;
	int		height;
}	t_image;

typedef struct s_cursor
{
	int	x;
	int y;
	bool	is_pressed;
	int press_x;
	int press_y;
	t_iposition initial_pos;
}			t_cursor;

typedef struct s_menu
{
	t_image	menu_bg;
	t_image	checker_plain;
	t_image	button;
	t_image	button_shadow;
	t_image	cursor;
	t_image reset;
	int		x;
	int		y;
	t_cursor	cursors[2];
	t_cursor	reseters[2];
	bool	on_screen;
	int		cross_hair;
	int		outline;
}			t_menu;

typedef struct s_position
{
	double	x;
	double	y;
}	t_position;

typedef struct s_door
{
	double opening_percent;
	bool	is_open;
	size_t x;
	size_t y;
}	t_door;

typedef struct s_portal
{
	t_position	position;
	double		distance;
	int			height;
	double		angle;
}	t_portal;

typedef struct s_prtl_list
{
	t_portal				*portal;
	struct s_prtl_list	*prev;
	struct s_prtl_list	*next;
}	t_prtl_list;

typedef struct s_hint
{
	bool	is_displayed;
	int 	x;
	int		y;
}	t_hint;

typedef struct s_ray_shoot
{
	t_position	*ray;
	t_position	ray_start;
	char		collision_point;
	double		*angle;
	double		*distance;
	bool		is_in_glass;
}	t_ray_shoot;

typedef struct s_cub
{
	t_image			load_screen;
	t_data			*data;
	void			*mlx;
	void			*win;
	int				keys_states[65509];
	int				last_mouse_pos;
	int				win_size[2];
	t_image			img;
	t_image			textures[18];
	t_position		player_position;
	t_position		last_player_pos;
	double			view_angle;
	double			fov;
	double			*wall_distance;
	t_position		*rays;
	double			*angles;
	char			orange_prtl;
	char			blue_prtl;
	char			rick_prtl;
	int				*wall_heights;
	char			cross_hair;
	int				player_speed;
	double			sensivity;
	t_menu			menu;
	t_prtl_list		**portals;
	t_prtl_list		**doors;
	t_prtl_list		**glass;
	t_door			*doors_status;
	t_hint			door_hint;
	bool			program_ends;
	pthread_mutex_t	program_ends_mutex;
	pthread_mutex_t	ray_mutex;
	pthread_mutex_t finished_mutex;
	int				next_ray_to_compute;
	pthread_t		*threads;
	bool			threads_finished_rendering[NB_THREADS];
	bool 			is_frame_rendered;
	double			gun_movement;
	t_iposition		gun_position;
	t_iposition		gun_size;
	char			last_portal_placed;
	t_position		random_position;
	double			random_angle;
}	t_cub;

typedef struct s_render_thread
{
	t_cub			*cub;
	int				id;
}	t_render_thread;

//==================== PARSING =====================//
# define ALLOWED_CHARS		"NSEW01DG "
# define NOT_WALLS_CHARS	"NSEWD0G"
# define ALLOWED_IN_FILE	"10NSEWDG \n"
t_data		*parsing(char **argv);
int			parse_textures(t_data *data, t_list *file);
t_data		*get_data(char **argv);
t_list		*skip_metadata_in_file(t_list *file);
int			check_file_path(t_data *data);
int			parse_map(char **map);
int			get_colors(t_data *data, t_list *file);
int			check_for_illegal_char(t_list *file);
char		**get_map_from_file(t_list *file);
t_list		*list_from_file(char *file_path);

//================= RAY RELATIVES ==================//
void		clear_lists(t_cub *cub);
int			shoot_door_ray(t_ray_shoot *ray_attr, t_cub *cub);
int			shoot_portal_ray(t_ray_shoot *ray_attr, t_cub *cub, char prtl_id);
int			shoot_glass_ray(t_ray_shoot *ray_attr, t_cub *cub);
void		init_ray_attr(t_cub *cub, t_position *ray, double *angle,
				t_ray_shoot *ray_attr);
int			shoot_special_rays(t_cub *cub, t_ray_shoot *ray_attr);

//===================== UTILS ======================//
void		destroy_data(t_data *data);
int			refactor_spaces(t_list *list);
int			ray_casting(t_cub *cub);
void		cub_pixel_put(t_image *data, int x, int y, int color);
void		render_minimap(t_cub *cub, t_position *ray_collision, \
							double *angle, int *wall_height);
int			render_frame(t_cub *cub);
size_t		get_time(void);
int			is_directory(char *path);
size_t		get_size(char **tab);
int			check_definition(t_data *data);
int			check_assignation(t_data *data);
int			check_format(t_data *data);
t_position	get_position(char **map);
int			get_wall_surroundment(t_data *data);
void		clear_line(char **w_surr, t_iposition *cur_pos);
void		fill_wall_surr_map(char **map, char **wall_surr, int x, int y);
void		set_portal_on_map(t_cub *cub, char prtl_id);
void		set_portal_texture(int *texture_id, size_t *texture_x,
							   int x, t_cub *cub);
void		display_crosshair(t_cub *cub);
int			teleport_ray(t_cub *cub, t_position *ray, double *angle,
				char entry_portal);
int			close_window(t_cub *cub);
double		compute_distance(t_position player, t_position ray);

//============== TEXTURES RENDERING ===============//
int	get_texture_pixel_color(t_cub *cub, int texture_id, size_t x, size_t y);
int	set_texture_id_and_x(size_t *texture_x, t_position ray_collision, t_cub *cub, double angle);
void	set_door_texture(int *texture_id, size_t *texture_x, int x, t_cub *cub);
int	set_custom_texture(int texture_id, double angle,
						  t_position ray_collision, t_cub *cub);
void	portal_put_wall_slice(t_cub *cub, int x, t_iposition texture,
							  int texture_id);
void	put_door_wall_slice(t_cub *cub, int texture_id, int x,
							t_iposition texture);
void	glass_put_wall_slice(t_cub *cub, int x, t_iposition texture,
							 int texture_id);
void	put_outline_wall_slice(t_cub *cub, int x, int texture_id,
							   t_iposition texture);
void	put_wall_slice(t_cub *cub, int x, int texture_id, t_iposition texture);
void	put_transparency(t_cub *cub, int x, int y, int texture_id);
bool	is_portal_middle(t_cub *cub, t_iposition texture, int texture_id);
void	glass_put_transparency(int x, t_cub *cub, int wall_height);
void put_outline_texture(int x, t_cub *cub, t_position ray_collision);

//===================== MENU ======================//
void		summon_game_menu(t_cub *cub, int dir);
void		load_game_menu(t_cub *cub);
void		handle_menu(t_cub *cub);
int			set_cursor_color(t_cub *cub, int texture_x, int texture_y);
int			set_button_color(t_cub *cub, int texture_x, int texture_y);
void		init_reseters(int coords[4], t_cursor *reseters);
void		mouse_get_pos(t_cub *cub, int *x, int *y);
void		cub_mouse_move(t_cub *cub, int x, int y);
void		cub_mouse_show(t_cub *cub);
void		cub_mouse_hide(t_cub *cub);
int			compute_ray(t_cub *cub, int ray_id, double segments_size);
int			create_threads(t_cub *cub);

//===================== DOORS ======================//
# define	DOOR_MAX_OPENING 2
void		open_door(t_cub *cub);
int			init_doors(t_cub *cub);
t_iposition get_door_index(t_position pos, double angle);
void	cub_door_texture_put(int x, t_cub *cub, t_position *ray_collision);
t_door		*get_door(t_position ray_collision, double angle, t_cub *cub);
void		cub_display_door_hint(t_cub *cub);
void		cub_update_doors(t_cub *cub);

//===================== GUNS =======================//
void display_portal_gun(t_cub *cub);

//==================== PLAYER ======================//
void	teleport_player(double new_x, double new_y, char prtl_id, t_cub *cub);

//=================== HANDLERS =====================//
int	cub_handle_mouse_move(int x, int y, t_cub *cub);
int	cub_handle_mouse(int button, int x, int y, t_cub *cub);
int cub_handle_mouse_release(int button, int x, int y, t_cub *cub);
int cub_handle_key_press(int keycode, t_cub *cub);
int	cub_handle_key_release(int keycode, t_cub *cub);
int	update_frame(t_cub *cub);

void set_random_position(t_cub *cub);
void put_pixel_transparent(t_image *data, int x, int y, unsigned int color);

int		init_game(t_cub *cub);
double	get_orientation(char **map, const t_position pos);
void	display_load_screen(t_cub *cub);
void	remove_load_screen(t_cub *cub);
void	cub_mlx_config(t_cub *cub);
int		cub_handle_key_press(int keycode, t_cub *cub);
int		close_window(t_cub *cub);
void	cub_update_player_position(int keycode, t_cub *cub);
void	cub_update_view_angle(int keycode, t_cub *cub);
void	convert_path_to_mlx_img(t_cub *cub);
int		init_mutex(t_cub *cub);
int	display_valve_guy(t_cub *cub);

#endif
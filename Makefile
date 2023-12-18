#===========================VARIABLE===============================#
SRCS		:=	cub3D.c\
				close_window.c\
				init_textures.c\
				mouse/mouse_utils_linux.c\
				mouse/mouse_utils_apple.c\
				player/player_handling.c\
				player/view_handling.c\
				player/teleport_player.c\
				parsing/parsing.c\
				parsing/get_data.c\
				parsing/parse_map.c\
				parsing/parse_colors.c\
				parsing/parse_textures.c\
				parsing/file_path_checking.c\
				parsing/list_from_file.c\
				parsing/map_from_list.c\
				parsing/map_getters.c\
				utils/free_data.c\
				utils/refactor_spaces.c\
				utils/utils.c\
				utils/mlx_config.c\
				utils/texture_utils.c\
				ray_casting/ray_casting.c\
				ray_casting/compute_ray.c\
				ray_casting/shoot_ray_utils.c\
				ray_casting/more_ray_utils.c\
				rendering/render_view.c\
				rendering/render_mini_map.c\
				rendering/render_mini_map_walls.c\
				rendering/graphic_utils.c\
				rendering/texture_put.c\
				rendering/render_frame.c\
				rendering/time.c\
				rendering/texture_put_utils.c\
				rendering/put_wall_slices.c\
				rendering/more_texture_put_utils.c\
				portal/portal.c\
				portal/set_map.c\
				portal/set_texture.c\
				portal/teleport_ray.c\
				portal/portal_utils.c\
				portal/set_random_position.c\
				game_menu/game_menu.c\
				game_menu/init.c\
				game_menu/color_setters.c\
				game_menu/menu_mouse_handling.c\
				multithreading/create_threads.c\
				multithreading/threads_routine.c\
				doors/doors.c\
				doors/init_doors.c\
				doors/doors_utils.c\
				guns/guns.c\
				init_game/init_game.c\
				load_screen/load_screen.c\
				load_screen/valve_guy.c\
				key_handlers/key_handlers.c\
				update_frame/update_frame.c\

SRCS_D		:=	srcs/

OBJS_D		:=	objs/

OBJS		:=	$(SRCS:%.c=$(OBJS_D)%.o)

DEPS		:=	$(SRCS:%.c=$(OBJS_D)%.d)

HEAD		:=	\
				cub3D.h\
				error_codes.h\
				rendering.h\

HEAD_D		:=	head/

HEAD_A		:=	$(addprefix $(HEAD_D), $(HEAD))

NAME		:=	cub3D

LIB			:=	libft.a

LIB_D		:=	libft/

LIB_H		:=	$(LIB_D)$(HEAD_D)

LIB_A		:=	$(LIB_D)$(LIB)


UNAME := $(shell uname)

ifeq ($(UNAME), Linux)
	MLX_D	=	minilibx-linux
    MLX 	= $(MLX_D)/libmlx_Linux.a
    MLX_FLAGS = -Lminilibx-linux -Lusr/lib -lXext -lX11 -lm -lz
else ifeq ($(UNAME), Darwin)
	MLX_D = mlx
    MLX = $(MLX_D)/libmlx.a
    MLX_LIB		=	${DIR_LIB}${MLX}.a
    MLX_FLAGS		=	-framework OpenGL -framework AppKit
    DEFINE_OS		=	-D OS_DARWIN=1
endif

#=========================FLAG===============================#
CC			:=	cc

RM			:=	rm -rf

CFLAGS		=	-Wall -Wextra -g3 -Ofast -flto

DFLAGS		:=	-MP -MMD

#=========================DEBUG==============================#
ASAN_F		:=	-fsanitize=address
TSAN_F		:=	-fsanitize=thread

ENV			:=	env -i

IGN_LEAK	:=	valgrind_ignore_leaks.txt

VALGRIND	:=	valgrind --suppressions=valgrind_ignore_leaks.txt --leak-check=full --show-leak-kinds=all\
				--track-fds=yes --show-mismatched-frees=yes --read-var-info=yes -s

PARAMETERS	:= test.cub

#========================EXEC===============================#

all			:	$(NAME)

$(NAME)		:	$(LIB_A) $(OBJS_D) $(OBJS) $(MLX)
			$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIB_A) $(MLX) $(MLX_FLAGS)

$(MLX)		:
			$(MAKE) -C $(MLX_D)

$(OBJS)		:	$(OBJS_D)%.o: $(SRCS_D)%.c $(HEAD_A) $(LIB_H)libft.h $(MLX_D)/mlx.h
			$(CC) $(CFLAGS) $(DFLAGS) -I$(HEAD_D) -I$(LIB_H) -I$(MLX_D) -c $< -o $@

$(OBJS_D)	:
			@mkdir -p $(OBJS_D)
			@mkdir -p $(OBJS_D)parsing
			@mkdir -p $(OBJS_D)utils
			@mkdir -p $(OBJS_D)ray_casting
			@mkdir -p $(OBJS_D)rendering
			@mkdir -p $(OBJS_D)portal
			@mkdir -p $(OBJS_D)multithreading
			@mkdir -p $(OBJS_D)game_menu
			@mkdir -p $(OBJS_D)doors
			@mkdir -p $(OBJS_D)guns
			@mkdir -p $(OBJS_D)mouse
			@mkdir -p $(OBJS_D)load_screen
			@mkdir -p $(OBJS_D)init_game
			@mkdir -p $(OBJS_D)player
			@mkdir -p $(OBJS_D)key_handlers
			@mkdir -p $(OBJS_D)update_frame

$(LIB_A)	:	$(LIB_D)
			make -C $(LIB_D)

$(IGN_LEAK)	:
			@echo "{"								> $(IGN_LEAK)
			@echo "	leak mlx_mouse_hide"			>> $(IGN_LEAK)
			@echo "		Memcheck:Leak"				>> $(IGN_LEAK)
			@echo "		..."						>> $(IGN_LEAK)
			@echo "		fun:mlx_mouse_hide" 		>> $(IGN_LEAK)
			@echo "}"								>> $(IGN_LEAK)

leaks		:	CFLAGS += -g3
leaks		:	all $(IGN_LEAK)
			$(VALGRIND) ./$(NAME) $(PARAMETERS)

clean		:
			$(RM) $(OBJS) $(OBJS_D) $(OBJSB_D)
			make clean -C $(LIB_D)

fclean		:	clean
			$(RM) $(NAME) $(BONUS)
			make fclean -C $(LIB_D)
			$(RM) $(IGN_TXT)

fsan_a		:	CFLAGS += $(ASAN_F)
fsan_a		:	lib_fsan_a $(NAME)

rfsan_a		: fclean fsan_a

lib_fsan_a:
			make fsan_a -C $(LIB_D)

fsan_t		:	CFLAGS += $(TSAN_F)
fsan_t		:	lib_fsan_t $(NAME)

rfsan_t		: fclean fsan_t

lib_fsan_t:
			make fsan_t -C $(LIB_D)

re			:	fclean all

.PHONY		:	all clean fclean re leaks env_leaks fsan_a rfsan_a lib_fsan_a fsan_t rfsan_t lib_fsan_t

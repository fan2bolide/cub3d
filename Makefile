#===========================VARIABLE===============================#
SRCS		:=	cub3D.c\
				parsing/parsing.c\
				parsing/get_map.c\
				parsing/parse_textures.c\
				parsing/file_path_checking.c\
				utils/free_data.c\
				utils/refactor_spaces.c\
				ray_casting/ray_casting.c\

SRCS_D		:=	srcs/

OBJS_D		:=	objs/

OBJS		:=	$(SRCS:%.c=$(OBJS_D)%.o)

DEPS		:=	$(SRCS:%.c=$(OBJS_D)%.d)

HEAD		:=	\
				cub3D.h\
				error_codes.h\
				mlx.h\

HEAD_D		:=	head/

HEAD_A		:=	$(addprefix $(HEAD_D), $(HEAD))

NAME		:=	cub3D

LIB			:=	libft.a

LIB_D		:=	libft/

LIB_H		:=	$(LIB_D)$(HEAD_D)

LIB_A		:=	$(LIB_D)$(LIB)

UNAME := $(shell uname)

ifeq ($(UNAME), Linux)
    MLX = lib/libmlx_macos.a
else ifeq ($(UNAME), Darwin)
    MLX = mlx/libmlx.a
    MLX_LIB		=	${DIR_LIB}${MLX}.a
    MLX_FLAGS		=	-framework OpenGL -framework AppKit
    DEFINE_OS		=	-D OS_DARWIN=1
endif

#=========================FLAG===============================#
CC			:=	cc

RM			:=	rm -rf

CFLAGS		:=	-Wall -Wextra -Werror

DFLAGS		:=	-MP -MMD

#=========================DEBUG==============================#
ASAN_F		:=	-g3 -fsanitize=address

ENV			:=	env -i

VALGRIND	:=	valgrind --leak-check=full --show-leak-kinds=all\
				--track-fds=yes --show-mismatched-frees=yes --read-var-info=yes -s

#========================EXEC===============================#

all			:	$(NAME)

$(NAME)		:	$(OBJS_D) $(OBJS) $(LIB_A) $(MLX)
			$(CC) $(CFLAGS) $(ASAN_F) $(MLX_FLAGS) -o $(NAME) $(OBJS) $(LIB_A) $(MLX)

$(MLX)		:
			$(MAKE) -C mlx

$(OBJS)		:	$(OBJS_D)%.o: $(SRCS_D)%.c $(HEAD_A) $(LIB_H)libft.h
			$(CC) $(CFLAGS) $(ASAN_F) $(DFLAGS) -I$(HEAD_D) -I$(LIB_H) -c $< -o $@

$(OBJS_D)	:
			@mkdir -p $(OBJS_D)
			@mkdir -p $(OBJS_D)parsing
			@mkdir -p $(OBJS_D)utils
			@mkdir -p $(OBJS_D)ray_casting

$(LIB_A)	:	$(LIB_D)
			make -C $(LIB_D)

leaks		:	all $(IGN_TXT)
			$(VALGRIND) ./$(NAME)

env_leaks	:	all $(IGN_TXT)
			 $(ENV) $(LEAKS) ./$(NAME)

clean		:
			$(RM) $(OBJS) $(OBJS_D) $(OBJSB_D)
			make clean -C $(LIB_D)

fclean		:	clean
			$(RM) $(NAME) $(BONUS)
			make fclean -C $(LIB_D)
			$(RM) $(IGN_TXT)

re			:	fclean all

.PHONY		:	all clean fclean re leaks env_leaks

#===========================VARIABLE===============================#
SRCS		:=	cub3D.c\
				parsing/parsing.c\
				parsing/get_map.c\

SRCS_D		:=	srcs/

OBJS_D		:=	objs/

OBJS		:=	$(SRCS:%.c=$(OBJS_D)%.o)

DEPS		:=	$(SRCS:%.c=$(OBJS_D)%.d)

HEAD		:=	\
				cub3D.h\

HEAD_D		:=	head/

HEAD_A		:=	$(addprefix $(HEAD_D), $(HEAD))

NAME		:=	cub3D

LIB			:=	libft.a

LIB_D		:=	libft/

LIB_H		:=	$(LIB_D)$(HEAD_D)

LIB_A		:=	$(LIB_D)$(LIB)

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

$(NAME)		:	$(OBJS_D) $(OBJS) $(LIB_A)
			$(CC) $(CFLAGS) $(ASAN_F) -o $(NAME) $(OBJS) $(LIB_A)

$(OBJS)		:	$(OBJS_D)%.o: $(SRCS_D)%.c $(HEAD_A) $(LIB_H)libft.h
			$(CC) $(CFLAGS) $(ASAN_F) $(DFLAGS) -I$(HEAD_D) -I$(LIB_H) -c $< -o $@

$(OBJS_D)	:
			@mkdir -p $(OBJS_D)
			@mkdir -p $(OBJS_D)parsing

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

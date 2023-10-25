# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bajeanno <bajeanno@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/17 16:28:53 by bajeanno          #+#    #+#              #
#    Updated: 2023/10/25 06:39:38 by bajeanno         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d

FLAGS = -Werror -Wall -Wextra -I libft/head -I head

DEBUG_FLAGS = -fsanitize=address -g3

LIBFT = libft/libft.a

SRC = 	cub3d.c \
		srcs\parsing.c \

DEPENDS	:=	$(addprefix obj/,$(SRC:.c=.d))

OBJ = $(addprefix obj/,$(SRC:.c=.o))

all : lib
	$(MAKE) $(NAME)

$(NAME) : $(OBJ)
	$(CC) $(OBJ) $(LIBFT) $(STACK_LIB) $(FLAGS) -o $(NAME)

create_obj_folder :
	mkdir -p obj

obj/%.o : src/%.c Makefile
	cc -Wall -Wextra -Werror -c $< -MD -I libft/headers -I head -o $@

debug : lib
	$(CC) $(OBJ) $(LIBFT) $(FLAGS) $(DEBUG_FLAGS) -o debug$(NAME)

lib : $(LIBFT)

$(LIBFT) : libft
	$(MAKE) -C libft

libft :
	git clone git@github.com:fan2bolide/libft.git

run : all
	./a.out

clean :
	$(RM) $(OBJ) $(BONUS_OBJ) $(DEPENDS)
	$(RM) -r $(NAME).dSYM
	$(MAKE) clean -C libft
	
fclean : clean
	$(RM) $(NAME)
	$(RM) .main .bonus
	$(MAKE) fclean -C libft

rm_lib :
	$(RM) -r libft

re : fclean
	$(MAKE) all

.PHONY : all lib run re clean fclean bonus rm_lib

-include $(DEPENDS)
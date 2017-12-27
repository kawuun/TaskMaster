# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dvdovenk <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/02/07 09:26:14 by dvdovenk          #+#    #+#              #
#    Updated: 2017/11/11 19:08:07 by dvdovenk         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME_P = server
NAME_C = client

NOC=\033[0m
OKC=\033[94;1m
ERC=\033[31m
WAC=\033[33m

G = gcc
FLAGS = -Wall -Wextra -Werror
GFLAGS = -Wall -Wextra -Werror -ltermcap

SRC_PATH_P = ./srcs/

SRC_NAME_P =   fork.c \
				load_prog.c \
				main.c \
				monitoring.c \
				parse.c \
				settings.c \
				change_proc.c \
				response.c \
				control_proc.c \
				re_start.c \
				signals.c \
				parse_1.c \
				parse_2.c \
				parse_3.c \
				parse_4.c \
				toolkit.c \
				timing.c

OBJ_PATH_P = ./srcs/

OBJ_NAME_P = $(SRC_NAME_P:.c=.o)

SRC_P = $(addprefix $(SRC_PATH_P), $(SRC_NAME_P))
OBJ_P = $(addprefix $(OBJ_PATH_P), $(OBJ_NAME_P))

GCFLAGS_P = -I./srcs/ -I./libft/
SRC_PATH_C = ./srcs/
SRC_NAME_C = client.c \
				input_keys.c \
				input_keys_2.c \
				msh_action_keys.c \
				msh_ctrl_r.c \
				msh_move_keys.c \
				msh_read_init.c \
				msh_special_keys.c \
				msh_tab.c \
				msh_termcap.c \
				msh_termcap2.c \
				msh_termios.c \
				msh_toolkit.c \
				take_input.c 

OBJ_PATH_C = ./srcs/
OBJ_NAME_C = $(SRC_NAME_C:.c=.o)

SRC_C = $(addprefix $(SRC_PATH_C), $(SRC_NAME_C))
OBJ_C = $(addprefix $(OBJ_PATH_C), $(OBJ_NAME_C))

GCFLAGS_C = -I./includes/ -I./libft/
LIBFT = libft/libft.a

all: $(NAME_P) $(NAME_C)
$(NAME_P): $(OBJ_P)
	@make -C libft/
	@echo "$(OKC)$(NAME_P): Creating $(NAME_P)..."
	@$(G) $(FLAGS) -g $(GCFLAGS_P) -o $@ $(OBJ_P) $(LIBFT)
	@echo "$(WAC)$(NAME_P): Compilation success!$(NOC)"

$(NAME_C): $(OBJ_C)
	@echo "$(OKC)$(NAME_C): Creating $(NAME_C)..."
	@$(G) $(GFLAGS) $(GCFLAGS_C) -o $@ $(OBJ_C) $(LIBFT)
	@echo "$(WAC)$(NAME_C): Compilation success!$(NOC)"

$(OBJ_PATH_P)%.o: $(SRC_PATH_P)%.c
	@$(G) $(FLAGS) $(GCFLAGS_P) -o $@ -c $<

$(OBJ_PATH_C)%.o: $(SRC_PATH_C)%.c
	@$(G) $(FLAGS) $(GCFLAGS_C) -o $@ -c $<

%.o: %.c
	$(G) $(FLAGS) -c $< -o $@

clean:
	@make -C libft/ clean
	@rm -f $(OBJ_P)
	@rm -f $(OBJ_C)

fclean: clean
	@make -C libft/ fclean
	@rm -f $(NAME_P) $(NAME_C)

re: fclean all
	@make -C libft/ re

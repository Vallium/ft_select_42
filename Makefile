# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aalliot <aalliot@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/09/21 15:39:41 by aalliot           #+#    #+#              #
#    Updated: 2016/11/28 14:52:49 by aalliot          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= ft_select
NAME_DEBUG	= ft_select_debug
 
SRC			= 	main.c			\
				free_entries.c	\
				ft_error.c		\
				ft_goto_up.c	\
				ft_goto_down.c	\
				ft_goto_left.c	\
				ft_goto_right.c	\
				ft_reset_term.c	\
				init_entries.c	\
				init_term.c		\
				keypress.c		\
				print.c			\
				signals.c		\
				singleton.c		\
				winsize.c

HEAD_DIR	= includes
SRC_DIR		= src
DEBUG_DIR	= debug
STATIC_DIR	= static
DEP_DIR		= dep

LIB_STATIC	= libft/libft.a
LIB_DEBUG	= libft/libft_debug.a
LIB_HEAD	= libft/includes

UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S),Linux)
	INCLUDES	=
	LIBS		=
endif

ifeq ($(UNAME_S),Darwin)
	INCLUDES	=
	LIBS		=
endif

OBJ			= $(patsubst %.c,$(STATIC_DIR)/%.o,$(SRC))
OBJ_DEBUG	= $(patsubst %.c,$(DEBUG_DIR)/%.o,$(SRC))
DEPS		= $(patsubst %.c,$(DEP_DIR)/%.d,$(SRC))

CC			= gcc
FLAGS		= #-Wall -Wextra -Werror
OPTI		= -O3
DEPENDS 	= -MT $@ -MD -MP -MF $(subst .o,.d,$@)


$(shell mkdir -p $(STATIC_DIR) $(DEBUG_DIR) $(DEP_DIR))

.PHONY: clean fclean re debug

all: $(NAME)

$(NAME): $(OBJ) $(LIB_STATIC)
	$(CC) $(FLAGS) $(OPTI) -I $(HEAD_DIR) -I $(LIB_HEAD) -lncurses -o $@ $(OBJ) $(LIB_STATIC)
	@echo "Compilation terminee. (realease)"

debug: $(OBJ_DEBUG) $(LIB_DEBUG)
	$(CC) $(FLAGS) $(OPTI) -I $(HEAD_DIR) -I $(LIB_HEAD) -o $(NAME_DEBUG) $(OBJ_DEBUG) $(LIB_DEBUG) -g
	@echo "Compilation terminee. (debug)"

-include $(OBJ:.o=.d)

$(STATIC_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(FLAGS) $(OPTI) $(DEPENDS) -I $(HEAD_DIR) -I $(LIB_HEAD) -o $@ -c $<

$(DEBUG_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(FLAGS) $(OPTI) $(DEPENDS) -I $(HEAD_DIR) -I $(LIB_HEAD) -o $@ -c $< -g

$(LIB_STATIC):
	make -C libft/ libft.a

$(LIB_DEBUG):
	make -C libft/ libft_debug.a

clean:
	make -C libft clean
	rm -f $(OBJ) $(OBJ_DEBUG) $(DEPS)

fclean: clean
	make -C libft fclean
	rm -f $(NAME) $(NAME_DEBUG)

re: fclean
	make

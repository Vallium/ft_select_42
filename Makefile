# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aalliot <aalliot@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/09/21 15:39:41 by aalliot           #+#    #+#              #
#*   Updated: 2015/11/19 15:09:59 by aalliot          ###   ########.fr       *#
#                                                                              #
# **************************************************************************** #

NAME		= ft_select
NAME_DEBUG	= ft_select_debug

SRC			= main.c

HEAD_DIR	= includes
SRC_DIR		= src
DEBUG_DIR	= debug
STATIC_DIR	= static
DEP_DIR		= dep


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
OPTI		= -O3
DEPENDS 	= -MT $@ -MD -MP -MF $(subst .o,.d,$@)


$(shell mkdir -p $(STATIC_DIR) $(DEBUG_DIR) $(DEP_DIR))

.PHONY: clean fclean re debug

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OPTI) -I $(HEAD_DIR) $(INCLUDES) -lncurses -o $@ $(OBJ) $(LIBS)
	@echo "Compilation terminee. (realease)"

debug: $(OBJ_DEBUG)
	$(CC) $(OPTI) -I $(HEAD_DIR) $(INCLUDES) -o $(NAME_DEBUG) $(OBJ_DEBUG) $(LIBS) -g
	@echo "Compilation terminee. (debug)"

-include $(OBJ:.o=.d)

$(STATIC_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(OPTI) $(DEPENDS) -I $(HEAD_DIR) $(INCLUDES) -o $@ -c $<

$(DEBUG_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(OPTI) $(DEPENDS) -I $(HEAD_DIR) $(INCLUDES) -o $@ -c $< -g

clean:
	rm -f $(OBJ) $(OBJ_DEBUG) $(DEPS)

fclean: clean
	rm -f $(NAME) $(NAME_DEBUG)

re: fclean
	make

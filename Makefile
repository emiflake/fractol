# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: nmartins <nmartins@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2019/04/18 20:11:18 by nmartins       #+#    #+#                 #
#    Updated: 2019/06/25 19:39:55 by nmartins      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

#############
# variables #
#############

# configure
NAME=fractol

MAIN=			fractol
OBJECT_NAMES=	\
				my_render \
				my_keys \
				my_mouse \
				my_misc_events \
				state \
				my_update \
				julia \
				mandlebrot \
				sierpinski \
				koch \



# dependencies
#
# MINILIBX, LIBFT, LIBGFX

MINILIB=./minilibx_macos
LIBFT=./libft
LIBGFX=./libgfx

# do not configure
CC=gcc
INCLUDES=-I./inc -I./libft -I./$(MINILIB) -I./$(LIBGFX)/inc
SRC=./src
OBJ=./.obj
EXTRA=
CFLAGS=-Werror -Wall -Wextra $(EXTRA) -pthread
FRAMEWORKS=-framework OpenGL -framework AppKit
LFLAGS=-L$(LIBFT) -lft -L$(MINILIB) -lmlx -L$(LIBGFX) -lgfx
OBJECTS=$(patsubst %, $(OBJ)/%.o, $(MAIN) $(OBJECT_NAMES))
SOURCES=$(patsubst %, $(SRC)/%.c, $(MAIN) $(OBJECT_NAMES))

# colors feel free to add more as you need them
OK_COLOR=\x1b[32;01m
RESET=\x1b[0m
UNDERLINE=\x1b[4m
BLUE=\x1b[36m
RED=\x1b[31m

#########
# rules #
#########
all: $(NAME)

$(LIBFT)/libft.a:
	@echo ">>= Making libft"
	@$(MAKE) -C $(LIBFT)
	@echo ">>= Done making libft"

libft_clean:
	@$(MAKE) -C $(LIBFT) clean

libft_fclean:
	@$(MAKE) -C $(LIBFT) fclean

$(LIBGFX)/libgfx.a:
	@echo ">>= Making libgfx"
	@$(MAKE) -C $(LIBGFX) EXTRA=$(EXTRA) LIBFT_LOC=../$(LIBFT) MINILIB_LOC=../$(MINILIB)
	@echo ">>= Done making libgfx"

libgfx_clean:
	@$(MAKE) -C $(LIBGFX) clean

libgfx_fclean:
	@$(MAKE) -C $(LIBGFX) fclean

$(MINILIB)/libmlx.a:
	@echo ">>= Making minilibx"
	@$(MAKE) -C $(MINILIB)
	@echo ">>= Done making minilibx"

minilib_clean:
	@$(MAKE) -C $(MINILIB) clean

$(NAME): $(LIBFT)/libft.a $(MINILIB)/libmlx.a $(LIBGFX)/libgfx.a $(OBJECTS)
	@printf " λ Linking $(UNDERLINE)$(BLUE)$@$(RESET)\n"
	@$(CC) -o $@ $(FRAMEWORKS) $(OBJECTS) $(LFLAGS)

$(OBJ)/%.o: $(SRC)/%.c
	@mkdir -p $(OBJ)
	@printf " λ Making object $(UNDERLINE)$(BLUE)$^$(RESET)\n"
	@$(CC) -c -o $@ $^ $(CFLAGS) $(INCLUDES)

clean: minilib_clean libft_clean libgfx_clean
	@echo "$(RED)Cleaning objects$(RESET)"
	@rm -rf $(OBJ)

fclean: libft_fclean libgfx_fclean clean
	@echo "$(RED)Cleaning $(NAME) and $(TEST_NAME)$(RESET)"
	@rm -rf $(NAME)
	@rm -rf $(TEST_NAME)

re:
	$(MAKE) fclean
	$(MAKE) all
quickre:
	@rm -rf $(OBJ)
	@rm -rf $(NAME)
	@$(MAKE) -C .

superfast:
	@$(MAKE) EXTRA=-O2 re -C . 

.SECONDARY: $(OBJECTS)
.PHONY: all debug libft clean fclean re

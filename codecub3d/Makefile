NAME = cub3D

CC = gcc
CFLAGS = -Wall -Wextra -Werror -g
MLXDIR = minilibx-linux
MLXFLAGS = -L$(MLXDIR) -lmlx -lXext -lX11 -lm -lz
LIBFTDIR = libft
LIBFT = $(LIBFTDIR)/libft.a

SRCSDIR = srcs
INCDIR = includes
OBJDIR = obj

SRCS = $(SRCSDIR)/main.c \
       $(SRCSDIR)/check/check_args.c \
       $(SRCSDIR)/parsing/parse_file.c \
       $(SRCSDIR)/parsing/parse_colors.c \
       $(SRCSDIR)/parsing/parse_textures.c \
       $(SRCSDIR)/parsing/map_validator.c \
       $(SRCSDIR)/parsing/map_reader.c \
       $(SRCSDIR)/parsing/map_grid.c \
	   $(SRCSDIR)/textures/load_textures.c \
	   $(SRCSDIR)/player/init_player.c \
	   $(SRCSDIR)/raycasting/init_ray.c \
	   $(SRCSDIR)/rendering/render.c \
	   $(SRCSDIR)/rendering/draw.c \
	   $(SRCSDIR)/rendering/texture.c \
	   $(SRCSDIR)/events/handle_input.c \
	   $(SRCSDIR)/cleanup/cleanup.c \

OBJS = $(patsubst $(SRCSDIR)/%.c,$(OBJDIR)/%.o,$(SRCS))

all: mlx libft $(NAME)

mlx:
	@$(MAKE) -C $(MLXDIR) > /dev/null 2>&1

libft:
	@$(MAKE) -C $(LIBFTDIR) > /dev/null 2>&1

$(NAME): $(OBJS) $(LIBFT)
	@$(CC) $(CFLAGS) $(OBJS) $(MLXFLAGS) -L$(LIBFTDIR) -lft -o $(NAME)
	@echo "\033[0;32m"
	@echo "   _____ _    _ ____  ____  _____  "
	@echo "  / ____| |  | |  _ \|___ \|  __ \ "
	@echo " | |    | |  | | |_) | __) | |  | |"
	@echo " | |    | |  | |  _ < |__ <| |  | |"
	@echo " | |____| |__| | |_) |___) | |__| |"
	@echo "  \_____|\____/|____/|____/|_____/ "
	@echo "\033[0m"
	@echo "\033[1;36mCompilation successful!\033[0m"

$(OBJDIR)/%.o: $(SRCSDIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -I$(INCDIR) -I$(MLXDIR) -I$(LIBFTDIR)/inc -c $< -o $@

clean:
	@rm -rf $(OBJDIR)
	@$(MAKE) -C $(MLXDIR) clean > /dev/null 2>&1
	@$(MAKE) -C $(LIBFTDIR) clean > /dev/null 2>&1
	@echo "\033[0;33mCleaned object files\033[0m"

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) -C $(LIBFTDIR) fclean > /dev/null 2>&1
	@echo "\033[0;31mFull clean completed\033[0m"

re: fclean all

.PHONY: all clean fclean re mlx libft
NAME = libft.a

CC = cc
CFLAGS = -Wall -Wextra -Werror -Iinc -fPIE


OBJ_DIR = objects/
OBJ_LIBFT_DIR = $(OBJ_DIR)libft/
OBJ_PRINTF_DIR = $(OBJ_DIR)printf/
OBJ_GNL_DIR = $(OBJ_DIR)gnl/

SRC_LIBFT = src/libft/ft_atoi.c \
            src/libft/ft_split.c \
            src/libft/ft_bzero.c \
			src/libft/ft_calloc.c \
			src/libft/ft_isalnum.c \
			src/libft/ft_isalpha.c \
			src/libft/ft_isascii.c \
			src/libft/ft_isdigit.c \
			src/libft/ft_isprint.c \
			src/libft/ft_itoa.c \
			src/libft/ft_lstadd_back_bonus.c \
			src/libft/ft_lstadd_front_bonus.c \
			src/libft/ft_lstclear_bonus.c \
			src/libft/ft_lstdelone_bonus.c \
			src/libft/ft_lstiter_bonus.c \
			src/libft/ft_lstlast_bonus.c \
			src/libft/ft_lstmap_bonus.c \
			src/libft/ft_lstnew_bonus.c \
			src/libft/ft_lstsize_bonus.c \
			src/libft/ft_memchr.c \
			src/libft/ft_memcmp.c \
			src/libft/ft_memcpy.c \
			src/libft/ft_memmove.c \
			src/libft/ft_memset.c \
			src/libft/ft_putchar_fd.c \
			src/libft/ft_putendl_fd.c \
			src/libft/ft_putnbr_fd.c \
			src/libft/ft_putstr_fd.c \
			src/libft/ft_strchr.c \
			src/libft/ft_strdup.c \
			src/libft/ft_striteri.c \
			src/libft/ft_strjoin.c \
			src/libft/ft_strlcat.c \
			src/libft/ft_strlcpy.c \
			src/libft/ft_strlen.c \
			src/libft/ft_strmapi.c \
			src/libft/ft_strncmp.c \
			src/libft/ft_strnstr.c \
			src/libft/ft_strrchr.c \
			src/libft/ft_strtrim.c \
			src/libft/ft_substr.c \
			src/libft/ft_tolower.c \
			src/libft/ft_toupper.c

SRC_PRINTF = src/ft_printf/ft_printf.c \
             src/ft_printf/utilsputnbr.c \
             src/ft_printf/utils.c 

SRC_GNL = src/get_next_line/get_next_line.c \

OBJ_LIBFT = $(patsubst src/libft/%.c,$(OBJ_LIBFT_DIR)%.o,$(SRC_LIBFT))
OBJ_PRINTF = $(patsubst src/ft_printf/%.c,$(OBJ_PRINTF_DIR)%.o,$(SRC_PRINTF))
OBJ_GNL = $(patsubst src/get_next_line/%.c,$(OBJ_GNL_DIR)%.o,$(SRC_GNL))

OBJ = $(OBJ_LIBFT) $(OBJ_PRINTF) $(OBJ_GNL)

all: create_dirs $(NAME)

create_dirs:
	@mkdir -p $(OBJ_LIBFT_DIR) $(OBJ_PRINTF_DIR) $(OBJ_GNL_DIR)

$(OBJ_LIBFT_DIR)%.o: src/libft/%.c
	@$(CC) $(CFLAGS) -c $< -o $@


$(OBJ_PRINTF_DIR)%.o: src/ft_printf/%.c
	@$(CC) $(CFLAGS) -c $< -o $@


$(OBJ_GNL_DIR)%.o: src/get_next_line/%.c
	@$(CC) $(CFLAGS) -c $< -o $@


$(NAME): $(OBJ)
	@ar rcs $(NAME) $(OBJ)

clean:
	@rm -rf $(OBJ_DIR)


fclean: clean
	@rm -f $(NAME)


re: fclean all

.PHONY: all clean fclean re create_dirs
CC = clang

NAME = fdf

DIR_S = srcs/

HEADER = inc/

SOURCES =   main.c \
			utils.c \
			input_utils.c \
			tools.c \
			get_next_line.c \
			get_next_line_utils.c \
			ft_split.c

SRCS = $(addprefix $(DIR_S),$(SOURCES))

OBJS = $(SRCS:.c=.o)

CFLAGS = -g3 -Wall -Werror -Wextra -I $(HEADER)

FLAGS = -L $(LIB)mlx_linux -lmlx -lm -lX11 -lXext -lpthread

all: $(NAME)

$(NAME): $(OBJS) $(HEADER)
	$(CC)	$(CFLAGS)	$(OBJS)	$(FLAGS) -o	$(NAME)

norme:
	@echo
	norminette	./$(HEADER)
	@echo
	norminette	./$(DIR_S)

bonus: all

clean:
	@rm -f $(OBJS)

fclean: clean
	@rm -f $(NAME)

re: fclean all
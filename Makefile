NAME = philo
SRC = philo.c
FLAGS = -Wall -Wextra -Werror
CC = cc
RM = rm -f
LIBFTDIR = My_C_Library/
LIBFT = My_C_Library/libft.a

all: $(NAME)

$(NAME):
	make -C $(LIBFTDIR)
	$(CC) $(CFLAGS) $(SRC) -L$(LIBFTDIR) -lft -o $(NAME)

clean:
	$(RM) $(NAME)

fclean: clean
	make fclean -C $(LIBFTDIR)

re: fclean make

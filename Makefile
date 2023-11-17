NAME = philo
SRC = src/actions.c src/init.c src/philo.c src/routine.c src/utils.c src/utils1.c
CFLAGS = -Wall -Wextra -Werror -pthread -g #-fsanitize=thread -g
CC = cc
RM = rm -f

OBJ := $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(SRC) -o $(NAME)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re

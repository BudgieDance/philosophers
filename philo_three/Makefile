NAME = philo_three

HEADER = philo_three.h

SRC = action.c \
	initialize.c \
	main.c \
	threads.c \
	utils.c \
	utils2.c 

OBJ = $(SRC:.c=.o)

FLAGS = -Wall -Wextra -Werror -pthread

all: $(NAME)

$(NAME): $(OBJ) $(HEADER)
	gcc -o $(NAME) $(OBJ) $(FLAGS)

%.o:%.c
	gcc -o $@ -c $< $(FLAGS)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

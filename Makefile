CC = cc
CFLAGS = -Wall -Werror -Wextra

NAME = philo

SRCS =	philo_folder/init_philo.c	\
		philo_folder/main.c			\
		philo_folder/philo_funcs.c	\
		philo_folder/philo_aux.c	\
		philo_folder/free.c

OBJS = $(SRCS:.c=.o)

all: $(NAME) 

$(NAME): $(OBJS)
	$(CC) $(OBJS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean $(NAME)

.PHONY: clean fclean re
CC = cc
CFLAGS = -Wall -Werror -Wextra

NAME = philo
#NAME_BONUS = philo_bonus

SRCS =	philo_folder/init_philo.c	\
		philo_folder/main.c			\
		philo_folder/philo_funcs.c
#BONUS_SRCS =

OBJS = $(SRCS:.c=.o)
#BONUS_OBJS = $(BONUS_SRCS:.c=.o)

all: $(NAME) 

$(NAME): $(OBJS)
	$(CC) $(OBJS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -Imlx -c $< -o $@

#bonus: $(NAME_BONUS)

#$(NAME_BONUS): $(BONUS_OBJS)
#	$(CC) $(BONUS_OBJS) -o $(NAME_BONUS)

clean:
	rm -rf $(OBJS)
#	rm -rf $(BONUS_OBJS)

fclean: clean
	rm -rf $(NAME)
#	rm -rf $(NAME_BONUS)

re: fclean $(NAME)

.PHONY: clean fclean re
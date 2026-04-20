NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror

OBJDIR = build

SRCS = action.c utils.c philo.c
OBJS = $(addprefix $(OBJDIR)/, $(SRCS:.c=.o))

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

$(OBJDIR)/%.o: %.c
	mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJDIR)

fclean: clean
	rm -rf $(NAME)

re: fclean all

leaks: $(NAME)
	valgrind --leak-check=full --show-leak-kinds=all --track-fds=yes \
		--track-origins=yes ./$(NAME)

threads: $(NAME)
	valgrind --tool=helgrind --log-file=helgrind.log --verbose --history-level=full  ./$(NAME)

.PHONY: all clean fclean re

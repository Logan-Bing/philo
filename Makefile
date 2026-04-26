NAME = philo/philo
CC = cc
CFLAGS = -Wall -Wextra -Werror

OBJDIR = build
SRCS_DIR = philo/

SRCS_FILES = main.c action.c clear.c utils.c routine.c shared_helpers.c shared_access.c parsing.c init.c
SRCS = $(addprefix $(SRCS_DIR), $(SRCS_FILES))
OBJS = $(addprefix $(OBJDIR)/, $(SRCS_FILES:.c=.o))

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

$(OBJDIR)/%.o: $(SRCS_DIR)/%.c
	mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJDIR)

fclean: clean
	rm -rf $(NAME)

re: fclean all

lazy: CFLAGS =
lazy: re

leaks: $(NAME)
	valgrind --leak-check=full --show-leak-kinds=all --track-fds=yes \
		--track-origins=yes ./$(NAME)

threads: $(NAME)
	valgrind --tool=helgrind --verbose --history-level=full  ./$(NAME)

.PHONY: all clean fclean re

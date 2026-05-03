NAME = philo/philo
BONUS_NAME = philo_bonus/philo_bonus
CC = cc
CFLAGS = -Wall -Wextra -Werror

OBJDIR = build
OBJDIR_BONUS = build_bonus
SRCS_DIR = philo/
BONUS_DIR = philo_bonus/

BONUS_FILES = main.c clear.c parsing.c init.c utils.c action.c shared_access.c shared_helpers.c routine.c
BONUS_SRCS = $(addprefix $(BONUS_DIR), $(BONUS_FILES))
BONUS_OBJS = $(addprefix $(OBJDIR_BONUS)/, $(BONUS_FILES:.c=.o))

SRCS_FILES = main.c action.c clear.c utils.c routine.c shared_helpers.c shared_access.c parsing.c init.c
SRCS = $(addprefix $(SRCS_DIR), $(SRCS_FILES))
OBJS = $(addprefix $(OBJDIR)/, $(SRCS_FILES:.c=.o))

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

$(OBJDIR)/%.o: $(SRCS_DIR)/%.c
	mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

bonus: $(BONUS_NAME)

$(BONUS_NAME): $(BONUS_OBJS)
	$(CC) $(CFLAGS) $(BONUS_OBJS) -o $(BONUS_NAME)

$(OBJDIR_BONUS)/%.o: $(BONUS_DIR)/%.c
	mkdir -p $(OBJDIR_BONUS)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJDIR)
	rm -rf $(OBJDIR_BONUS)

fclean: clean
	rm -rf $(NAME)
	rm -rf $(BONUS_NAME)

re: fclean all

re_bonus: fclean bonus

leaks: $(NAME)
	valgrind --leak-check=full --show-leak-kinds=all --track-fds=yes \
		--track-origins=yes ./$(NAME)

threads: $(NAME)
	valgrind --tool=helgrind --verbose --history-level=full  ./$(NAME)

.PHONY: all clean fclean re

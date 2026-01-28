NAME = studies
CC = cc
CFLAGS = -Wall -Wextra -Werror
INCLUDE = -I./include/

SRCS_DIR = src/
SRCS = stack.c \
	balanced_parentheses.c
OBJS_DIR = objs/
OBJS = $(SRCS:%.c=$(OBJS_DIR)%.o)

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(OBJS) -o $(NAME)
	@echo -n "\033[0;32mGenerated studies\n"

$(OBJS_DIR)%.o: $(SRCS_DIR)%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@
	@echo "\033[95mCompiling $(notdir $<)"

clean:
	@echo "\033[0;34mCleaning studies objects"
	@rm -rf $(OBJS_DIR)

fclean: clean
	@echo "\033[0;34mCleaning studies"
	@rm -f $(NAME)

re: fclean all

run: re
	./studies

.PHONY: $(LIBFT) clean fclean re
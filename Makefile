
NAME := philo
CC := cc
FLAGS := -arch x86_64 -masm=intel -g  -Wall -Wextra -Werror  -fsanitize=thread #-fsanitize=address

# Source files
SRCS := src/main.c        \
        src/parsing.c     \
        src/utils.c       \
        src/mem_utils.c   \
        src/philo.c       \
        src/print.c       \

# Object files
OBJS := $(SRCS:.c=.o)
DEPS := includes/philo.h

# Color codes for terminal output
CLR_RMV := \033[0m
GREEN := \033[1;32m
YELLOW := \033[1;33m
CYAN := \033[1;36m

total_files := $(words $(SRCS))
current_file := 0
progress := 0

define progress_bar
	@$(eval current_file=$(shell echo $$(($(current_file) + 1))))
	@$(eval progress=$(shell echo $$(($(current_file) * 100 / $(total_files)))))
	@printf "\r$(GREEN)Compiling $(YELLOW)%s$(CLR_RMV)...  [%-3d%%] %d/%d $(CYAN)" $< $(progress) $(current_file) $(total_files)
endef

define print_completion
	@printf "$(GREEN)\nCompilation of $(YELLOW)$(NAME) $(GREEN)complete ✔️\n$(CLR_RMV)"
endef

all: nothing $(NAME)

$(NAME): $(OBJS)
	@echo "$(YELLOW)Done !$(CLR_RMV)"
	@$(CC) $(FLAGS) -o $(NAME) $(OBJS)
	@$(call print_completion)

%.o: %.c $(DEPS)
	@$(CC) $(FLAGS) -c $< -o $@
	$(call progress_bar)

clean:
	@$(RM) $(OBJS)
	@echo "$(GREEN)Deleting $(YELLOW)$(NAME)$(CLR_RMV) objs ✔️"

fclean: clean
	@$(RM) $(NAME)
	@echo "$(GREEN)Deleting $(YELLOW)$(NAME)$(CLR_RMV) binary ✔️"

re: fclean all

nothing:
	@if [ -f "$(NAME)" ] && [ -z "$$(find $(SRCS) -newer $(NAME))" ]; then \
		echo "$(CYAN)Nothing has been updated.$(CLR_RMV)"; \
	fi

.PHONY: all re clean fclean nothing

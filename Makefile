NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror -g
ODIR = ./odir/
SRCDIR = ./src/

# Color definitions
BLUE = \033[34m
GREEN = \033[32m
RESET = \033[0m

SRC = $(SRCDIR)main.c ${SRCDIR}ph_parsing.c ${SRCDIR}ph_init.c \
      ${SRCDIR}ph_clean.c  ${SRCDIR}ph_utilis.c \
      ${SRCDIR}ph_routine.c ${SRCDIR}ph_end_philo.c
OBJ = $(SRC:$(SRCDIR)%.c=$(ODIR)%.o)

all: $(ODIR) $(NAME) 

$(NAME): $(OBJ)
	@echo  "$(GREEN)Linking objects...$(RESET)"
	@$(CC) $(CFLAGS) $(LIBFT) $(OBJ) -o $(NAME)

$(ODIR)%.o: $(SRCDIR)%.c
	@mkdir -p $(ODIR)
	@echo "$(BLUE)Compiling $<...$(RESET)"
	$(CC) $(CFLAGS) -c $< -o $@ 

$(ODIR):
	@mkdir -p $(ODIR)

clean:
	@echo "$(BLUE)Cleaning up...$(RESET)"
	@rm -rf $(ODIR)

fclean: clean
	@echo "$(RED)Removing executable...$(RESET)"
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

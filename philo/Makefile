CC = gcc
CFLAGS = -g -pthread -Wall -Wextra -Werror 
SDIR = sources
ODIR = objects
HDIR = headers
NAME = philo
SRC = ph_main.c ph_argcheck.c ph_utils1.c ph_utils2.c ft_atol.c list_utils.c time_funcs.c \
		display_message.c threads.c destroy_funcs.c setup_funcs.c

$(NAME): $(foreach file,$(SRC:.c=.o),$(ODIR)/$(file))
	$(CC) $(CFLAGS) -o $@ $(foreach src,$(SRC:.c=.o),$(ODIR)/$(src))

$(ODIR)/%.o: $(SDIR)/%.c $(HDIR)/philo.h
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: all clean fclean re bonus fcleanall
all:
	make $(NAME)
clean:
	rm -f objects/*.o
fclean:
	make clean
	rm -f $(NAME)
re:
	make clean
	make all
bonus:
	make $(NAME)
fcleanall:
	make fclean
	$(MAKE) fcleanall --directory=mylib
	$(MAKE) fcleanall --directory=pipex
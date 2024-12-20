CC = gcc
CFLAGS = -Wall -Wextra -O2

CFILES = data_management.c
OFILES = $(CFILES:.c=.o)
NAME = libdata.a

all: $(NAME)

$(NAME): $(OFILES)
	ar rcs $(NAME) $(OFILES)

clean:
	rm -f $(OFILES)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
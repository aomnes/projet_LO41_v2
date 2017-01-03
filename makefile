NAME = usine.out
CC = gcc
INCLUDE = header.h
SRCS = creation_convoyeur.c robot_in.c useful_function.c creation_machine.c\
	main.c robot_out.c creation_piece.c superviseur.c robot_install_table.c
CFLAGS = -Wall -Wextra -Werror
COPTIONS = -o $(NAME) -I $(INCLUDE)

all: $(NAME)

$(NAME):
	$(CC) $(CFLAGS) $(COPTIONS) $(SRCS)

clean:
	/bin/rm -f header.h.gch

fclean: clean
	/bin/rm -f usine.out

re: clean all

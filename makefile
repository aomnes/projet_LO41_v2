NAME = usine.out
CC = gcc
INCLUDE = header.h
SRC = robot_in.c useful_function.c creation_machine.c\
      main.c robot_out.c creation_piece.c superviseur.c robot_install_table.c

OBJET = $(SRC:.c=.o)
FLAGS = -Wall -Wextra
LIB_THREAD = -pthread

all: $(NAME)

$(NAME):
	gcc -c $(FLAGS) $(LIB_THREAD) $(SRC)
	gcc -o $(NAME) $(OBJET)

clean:
	rm -rf $(OBJET)

fclean: clean
	rm -rf $(NAME)

re: fclean all

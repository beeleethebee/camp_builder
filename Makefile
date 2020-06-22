CC = gcc
NAME = campbuilder
SRC  = 	./src/campbuilder.c \
		./src/functions/get_option.c \
		./src/functions/linked_list.c \
		./src/functions/delete_spaces.c \
		./src/functions/extract_num.c \
		./src/functions/format_input.c \
		./src/functions/operators.c \
		./src/functions/validators.c \
		./src/functions/tokenize_input.c \
	
OBJ = ${SRC:.c=.o}

CFLAGS = -Wextra -Wall -std=c11
RM = rm -f


$(NAME):	${OBJ}
			$(CC)  $(OBJ) -o $(NAME) $(CFLAGS)
			${RM} ${OBJ}
clean: 		
			${RM} ${OBJ}

all : 		${NAME}

fclean:		clean
			${RM} ./${NAME}
			${RM} my_ls

re:			fclean all

.PHONY:		re fclean all clean campbuilder
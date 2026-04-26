##
## EPITECH PROJECT, 2026
## Makefile
## File description:
## Makefile
##

CC				=	cc

SRC 			= 	src/hash.c			\
					src/init_map.c		\
					src/map_insert.c	\
					src/map_at.c		\
					src/map_erase.c		\
					src/map_size.c		\
					src/map_empty.c		\
					src/map_max_size.c	\
					src/map_swap.c		\
					src/map_merge.c		\
					src/map_find.c		\
					src/map_count.c		\
					src/map_clear.c		\

SRC_DEV			=	src/main.c

SRC_TESTS		=	tests/test_map.c

OBJ_DEV			=	$(SRC_DEV:.c=.o)

OBJ				=	$(SRC:.c=.o)

OBJ_TESTS		=	$(SRC_TESTS:.c=.o)

CPPFLAGS		=	-Iinclude/

CFLAGS			=	-Wall -Wextra

CRITERION_FLAGS	=	$(shell pkg-config --cflags --libs criterion)

NAME			=	c_map.a

TESTS_BIN		=	unit_tests

all:			$(NAME)

$(NAME):		$(OBJ)
				$(AR) rcs $(NAME) $(OBJ)

dev:			$(NAME) $(OBJ_DEV)
				$(CC) $(CFLAGS) $(OBJ_DEV) $(NAME) -o dev

tests_run:		$(NAME) $(OBJ_TESTS)
				$(CC) $(CFLAGS) $(OBJ_TESTS) $(NAME) $(CRITERION_FLAGS) -o $(TESTS_BIN)
				./$(TESTS_BIN)

clean:
				$(RM) $(OBJ) $(OBJ_TESTS) $(TESTS_BIN)

fclean:			clean
				$(RM) $(NAME) dev

re:				fclean all

debug:			CPPFLAGS += -ggdb3
debug:			dev

.PHONY:			$(NAME) dev all clean fclean re debug run_tests

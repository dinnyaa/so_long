SRCS = so_long.c so_long_utils.c parsing.c
OBJS = ${SRCS:.c=.o}
NAME = so_long
CC   = gcc
FLAGS = -Wall -Wextra -Werror
MLXFLAGS = -lmlx -framework OpenGL -framework AppKit

${NAME} : ${OBJS}
	${CC} ${FLAGS} ${MLXFLAGS} ${SRCS} -o ${NAME}

all : ${NAME}

clean :
		rm ${OBJS}

fclean : clean
		rm ${NAME}

re : fclean all

.PHONY :
		all clean fclean
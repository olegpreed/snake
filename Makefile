NAME	= snake

CC		= gcc
FLAGS	= -Wall -Wextra -Werror -g
LFLAGS	= -lncurses
RM		= rm -rf
HDR_DIR = inc/
SRC_DIR = src/
OBJ_DIR = obj/
HDR		= ${wildcard $(HDR_DIR)*.h} 
SRC		= ${wildcard $(SRC_DIR)*.c} 
OBJ		= ${SRC:$(SRC_DIR)%.c=$(OBJ_DIR)%.o}

${OBJ_DIR}%.o: $(SRC_DIR)%.c ${HDR} Makefile
	${CC} ${FLAGS} -I$(HDR_DIR) -c $< -o $@

.PHONY: all clean fclean re

all: ${NAME}

${OBJ_DIR}:
	mkdir -p $@

${NAME}: $(OBJ_DIR) ${OBJ} ${HDR} Makefile
	${CC} ${FLAGS} ${OBJ} -o ${NAME} ${LFLAGS}

clean:
	${RM} ${OBJ}

fclean: clean
	${RM} ${NAME}

re: fclean all
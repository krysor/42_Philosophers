CFILES	= 	\
			main.c \
			ft_atoi.c \
			routine.c \
			init_vars.c \
			utils.c
			
SRCS 	= $(addprefix src/, ${CFILES})

OBJS	= ${SRCS:.c=.o}

NAME	= philo

CC		= cc
RM		= rm -f

CFLAGS	= -Wall -Wextra -Werror -O3

${NAME}:	${OBJS}
			${CC} ${CFLAGS} -o ${NAME} ${OBJS}

all:		${NAME}

clean:
			${RM} ${OBJS} ${bOBJS}

fclean:		clean
			${RM} ${NAME}

re:			fclean all

.PHONY:		all bonus clean fclean re
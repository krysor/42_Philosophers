CFILES	= 	\
			main.c \
			ft_atoi.c \
			philo_utils.c \
			routine.c \
			init_vars.c \
			
SRCS 	= $(addprefix src/, ${CFILES})

OBJS	= ${SRCS:.c=.o}

NAME	= philo

CC		= cc
RM		= rm -f

CFLAGS	= -Wall -Wextra -Werror -pthread #-fsanitize=thread #-fsanitize=address

${NAME}:	${OBJS}
			${CC} ${CFLAGS} -o ${NAME} ${OBJS}

all:		${NAME}

clean:
			${RM} ${OBJS} ${bOBJS}

fclean:		clean
			${RM} ${NAME}

re:			fclean all

.PHONY:		all bonus clean fclean re
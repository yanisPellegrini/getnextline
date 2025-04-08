SRCS    = ft_printf.c ft_puthex.c

OBJS    = ${SRCS:.c=.o}

NAME    = ft_printf.a

CC        = cc
RM        = rm -f

CFLAGS     = -Wall -Wextra -Werror -D BUFFER_SIZE=n

all:        ${NAME}

.c.o:
		${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

${NAME}:    ${OBJS}
			ar rcs ${NAME} ${OBJS}

clean:
			${RM} ${OBJS}

fclean:        clean
			${RM} ${NAME}

bonus: all

re:            fclean all

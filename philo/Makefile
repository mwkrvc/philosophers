NAME	= 	philo

HEADER	=	philo.h

SRCS	=	philo.c utils.c routine.c setup.c

OBJS	=	$(SRCS:.c=.o)

CC		=	gcc -Wall -Werror -Wextra

RM		=	rm -f

all:			$(NAME)

$(NAME):		$(OBJS) $(HEADER)
				@$(CC) $(OBJS) -o $(NAME)

clean:
				$(RM) $(OBJS)

fclean:			clean
				$(RM) $(NAME)

re:				fclean all

.PHONY:			all clean fclean re


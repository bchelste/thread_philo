# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bchelste <bchelste@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/08/25 11:38:47 by bchelste          #+#    #+#              #
#    Updated: 2021/09/02 23:34:03 by bchelste         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

DEFAULT_COLOR	= '\033[00m'

GREEN_COLOR		= '\033[01;32m'

YELLOW_COLOR	= '\033[01;33m'

NAME			= philo

CC				= gcc

CFLAGS			= -Wall -Werror -Wextra

OPTFLAGS		= -O3

RM				= rm -f

THREADS			= -pthread

SRCS			= \
				main.c \
				ft_philo.c \
				ft_error.c \
				utils.c

OBJS			= $(SRCS:%.c=%.o)

%.o: %.c
				$(CC) $(CFLAGS) $(OPTFLAGS) -c $< -o $@

.PHONY:			all clean fclean re

all:			$(NAME)

$(NAME):		$(OBJS)
				$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(THREADS)
				@echo $(GREEN_COLOR)[philo create] $(DEFAULT_COLOR)

clean:
				$(RM) $(OBJS)
				@echo $(YELLOW_COLOR)[objects files delete] $(DEFAULT_COLOR)
			
fclean:			clean
				$(RM) $(NAME)
				@echo $(YELLOW_COLOR)[executable files delete] $(DEFAULT_COLOR)

re:				fclean all
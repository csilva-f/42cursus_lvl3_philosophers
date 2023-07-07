# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: csilva-f <csilva-f@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/03 19:15:48 by csilva-f          #+#    #+#              #
#    Updated: 2023/07/03 23:21:49 by csilva-f         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := philo
BONUS := philo_bonus

CC := cc -pthread
CFLAGS := -Wall -Werror -Wextra -O3 -march=native

ifdef DEBUG
		CFLAGS += -fsanitize=address
endif

ifdef RACES
		CFLAGS += -fsanitize=thread
endif

SRCS :=		srcs/main.c							srcs/ft_check.c			\
			srcs/ft_eat.c						srcs/ft_forks.c 		\
			srcs/ft_initialize.c				srcs/ft_simulate.c		\
			srcs/ft_utils.c

SRCS_BONUS := 

OBJS := $(SRCS:.c=.o)

OBJS_BONUS := $(SRCS_BONUS:.c=.o)

all:	$(NAME)

$(NAME):	$(OBJS)
			$(CC) $(CFLAGS) -lm $(OBJS) $(LIBFT) -o $(NAME)
			echo "\033[1m $(NAME) ready \033[0m"

bonus:	$(BONUS)

$(BONUS):	$(OBJS_BONUS)
			$(CC) $(CFLAGS) -lm $(OBJS_BONUS) -o $(BONUS)
			echo "\033[1m $(BONUS) ready \033[0m"

clean:
		rm -rf $(OBJS)
		rm -rf $(OBJS_BONUS)
		echo "OBJS deleted"

fclean:	clean
		rm -rf $(NAME)
		rm -rf $(BONUS)
		echo "$(NAME) deleted"
		echo "$(BONUS) deleted"

re:	fclean all

.SILENT:

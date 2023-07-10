# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ledos-sa <ledos-sa@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/07 22:35:27 by ledos-sa          #+#    #+#              #
#    Updated: 2023/07/09 21:40:07 by ledos-sa         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := philo_bonus

CC := cc -pthread
CFLAGS := -Wall -Werror -Wextra -O3 -march=native

ifdef DEBUG
		CFLAGS += -fsanitize=address
endif

ifdef RACES
		CFLAGS += -fsanitize=thread
endif

SRCS :=		srcs/main.c				srcs/ft_philo.c				 srcs/ft_utils.c

OBJS := $(SRCS:.c=.o)

all:	$(NAME)

$(NAME):	$(OBJS)
			$(CC) $(CFLAGS) -lm $(OBJS) $(LIBFT) -o $(NAME)
			echo "\033[1m $(NAME) ready \033[0m"

clean:
		rm -rf $(OBJS)
		echo "OBJS deleted"

fclean:	clean
		rm -rf $(NAME)
		rm -rf $(BONUS)
		echo "$(NAME) deleted"

re:	fclean all

.SILENT:

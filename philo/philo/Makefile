# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jtollena <jtollena@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/30 13:47:45 by jtollena          #+#    #+#              #
#    Updated: 2024/01/15 14:32:10 by jtollena         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SOURCES = srcs/main.c \
			srcs/utils.c \
			srcs/philo.c \
			srcs/circleof_1.c \
			srcs/circleof_2.c \
			srcs/threads.c \
			srcs/tick.c \
			srcs/atoi.c

OBJECTS = $(SOURCES:.c=.o)
INCLUDES = includes
FLAGS = -Wall -Wextra -Werror

%.o: %.c
	gcc $(FLAGS) -I $(INCLUDES) -c $< -o $@

all: $(NAME)

clean:
	rm $(OBJECTS)
	
$(NAME): $(OBJECTS) $(INCLUDES)
	gcc $(OBJECTS) -lpthread -o $(NAME)

fclean: clean
	rm $(NAME)

re: fclean $(NAME)

.PHONY: re fclean clean all
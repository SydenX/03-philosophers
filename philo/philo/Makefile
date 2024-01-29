# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jtollena <jtollena@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/30 13:47:45 by jtollena          #+#    #+#              #
#    Updated: 2024/01/29 12:24:43 by jtollena         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SOURCES = srcs/main.c \
			srcs/utils.c \
			srcs/atoi.c \
			srcs/cycle.c \
			srcs/init.c \
			srcs/philo.c

OBJECTS = $(SOURCES:.c=.o)
INCLUDES = includes
FLAGS = -Wall -Wextra -Werror

%.o: %.c
	gcc $(FLAGS) -I $(INCLUDES) -c $< -o $@

all: $(NAME)

clean:
	rm $(OBJECTS)
	
$(NAME): $(OBJECTS) $(INCLUDES)
	gcc $(FLAGS) $(OBJECTS) -lpthread -o $(NAME)

fclean: clean
	rm $(NAME)

re: fclean $(NAME)

.PHONY: re fclean clean all
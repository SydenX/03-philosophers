# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jtollena <jtollena@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/30 13:47:45 by jtollena          #+#    #+#              #
#    Updated: 2024/01/17 15:28:28 by jtollena         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SOURCES = srcs/main.c \
			srcs/utils.c \
			srcs/philo.c \
			srcs/cycle.c \
			srcs/cycle_state.c \
			srcs/threads.c \
			srcs/tick.c \
			srcs/atoi.c

OBJECTS = $(SOURCES:.c=.o)
INCLUDES = includes
FLAGS = #-Wall -Wextra -Werror

%.o: %.c
	gcc $(FLAGS) -I $(INCLUDES) -c $< -o $@

all: $(NAME)

clean:
	rm $(OBJECTS)
	
$(NAME): $(OBJECTS) $(INCLUDES)
	gcc $(OBJECTS) -lpthread -o $(NAME)
	make clean

fclean: clean
	rm $(NAME)

re: fclean $(NAME)

.PHONY: re fclean clean all
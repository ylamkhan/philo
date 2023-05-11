# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ylamkhan <ylamkhan@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/11 01:03:05 by ylamkhan          #+#    #+#              #
#    Updated: 2023/05/11 01:03:12 by ylamkhan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = philosophers
SRC = philosophers.c tools.c
OBJ = $(SRC:.c=.o)
//CFLAGS = -Wall -Wextra -Werror
CC = cc
RM = rm -f
LIB = philosophers.h

all : $(NAME)

$(NAME) : $(OBJ)
	$(CC) $(SRC) -o $(NAME)

%.o : %.c $(LIB)
	$(CC) $(CFLAGS) -c $<

clean:
	$(RM) $(OBJ)

fclean : clean
	$(RM) $(NAME)

re : fclean all

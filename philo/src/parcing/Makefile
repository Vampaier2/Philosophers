# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: xalves <xalves@student.42lisboa.com>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/02/17 15:26:23 by xalves            #+#    #+#              #
#    Updated: 2026/02/17 15:26:25 by xalves           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = parcing.a
AUXS = parcing.c ft_str_isdigit.c	

COMP_LIB = ar rcs
RM = rm -f
CC = cc
CC_FLAGS = -Wall -Wextra -Werror

OBJS = $(AUXS:.c=.o)

%.o : %.c
	$(CC) $(CC_FLAGS) -c $< -o $@

all: $(NAME)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

$(NAME): $(OBJS)
	$(COMP_LIB) $(NAME) $(OBJS)

.PHONY: all clean fclean re

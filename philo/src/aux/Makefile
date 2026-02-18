# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: xalves <xalves@student.42lisboa.com>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/02/17 15:25:45 by xalves            #+#    #+#              #
#    Updated: 2026/02/17 15:25:48 by xalves           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = lib_aux.a
AUXS = ft_atoi.c ft_calloc.c odd_or_even.c aux_function.c ft_putstr_fd.c

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

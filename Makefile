# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dehamad <dehamad@student.42abudhabi.ae>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/25 03:20:29 by dehamad           #+#    #+#              #
#    Updated: 2024/01/09 11:25:40 by dehamad          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = gnl.a
SOURCES = \
	get_next_line.c get_next_line_utils.c
BSOURCES = \
	get_next_line_bonus.c get_next_line_utils_bonus.c
OBJECTS = $(SOURCES:.c=.o)
BOBJECTS = $(BSOURCES:.c=.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror
AR = ar

all: $(NAME)

$(NAME): $(OBJECTS)
	$(AR) -rcs $@ $?

bonus: $(OBJECTS) $(BOBJECTS)
	$(AR) -rcs $(NAME) $?

%.o: %.c
	$(CC) -c $(CFLAGS) $?

clean:
	rm -f $(OBJECTS) $(BOBJECTS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all bonus clean fclean re

# all:
# 	@cc main.c get_next_line.c get_next_line_utils.c
# 	@./a.out

# bonus:
# 	@cc main.c get_next_line_bonus.c get_next_line_utils_bonus.c
# 	@./a.out
	
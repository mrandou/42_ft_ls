# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mrandou <mrandou@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/01/15 13:40:23 by mrandou           #+#    #+#              #
#    Updated: 2018/04/30 13:55:56 by mrandou          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME		=		ft_ls

INCLUDE		 =		ft_ls.h

SRC			=		ft_ls.c \
					ls_parse.c \
					ls_options.c \
					ls_merge_sort.c \
					ls_time_sort.c \
					ls_recursive.c \
					ls_list.c \
					ls_infos.c

OBJS		=		$(SRC:.c=.o)

CC			=		gcc

CFLAGS		+=		-Wall -Wextra -Werror -g

all:				$(NAME)

$(NAME):			$(OBJS)
					make -C "./libft"
					$(CC) -I"libft" -L"libft" -lft -o $(NAME) $(OBJS)

clean:
					make -C "./libft" clean
					$(RM) $(OBJS)

fclean:				clean
					make -C "./libft" fclean
					$(RM) $(NAME)

re:					fclean all

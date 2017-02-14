# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hkalia <hkalia@student.42.us.org>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/11/03 11:52:51 by hkalia            #+#    #+#              #
#    Updated: 2017/02/14 13:37:44 by hkalia           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:=	ft_ls
CC			:=	gcc
CFLAGS		+=	-Wall -Wextra
CFLAGS		+=	-Werror
CFLAGS		+=	-I includes -I libarr/includes -I libft/includes -I libftprintf/includes
LDFLAGS		+=	-L libarr -larr -L libft/ -lft -L libftprintf -lftprintf
ifdef ALLOCWRAP
	LDFLAGS += $(HOME)/lib/alloc_wrap.c -ldl
endif
LIBARR		:=	libarr/libarr.a
LIBFT		:=	libft/libft.a
LIBFTPRINTF	:=	libftprintf/libftprintf.a

FILES		:=	main

SRC			:=	$(addprefix srcs/, $(addsuffix .c, $(FILES)))
OBJ			:=	$(SRC:.c=.o)

# MATH

MAX			:=	$(words $(OBJ))
n			:=	x
increment	=	$1 x
COUNTER		=	$(words $n)$(eval n := $(call increment,$n))

# RULES

.PHONY: all clean

all: $(NAME)

$(LIBARR):
	@make -C libarr

$(LIBFT):
	@make -C libft

$(LIBFTPRINTF):
	@make -C libftprintf

$(OBJ): %.o: %.c
	@printf "\r\e[31mCompiling...(%d/%d)\e[0m" $(COUNTER) $(MAX)
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(LIBARR) $(LIBFT) $(LIBFTPRINTF) $(OBJ)
	@printf "\r\e[32mCompiling...(%d/%d)[DONE]\n\e[0m" $(MAX) $(MAX)
	@printf "\e[32mLinking... \e[0m"
	@$(CC) $(LDFLAGS) -o $@ $^
	@printf "\e[32m[DONE]\e[0m\n"

clean:
	@make -C libarr clean
	@make -C libft clean
	@make -C libftprintf clean
	@printf "\e[31mDeleting object files... \e[0m"
	@rm -f $(OBJ)
	@printf "\e[32m[DONE]\e[0m\n"

fclean: clean
	@make -C libarr fclean
	@make -C libft fclean
	@make -C libftprintf fclean
	@printf "\e[31mDeleting %s... \e[0m" $(NAME)
	@rm -f $(NAME)
	@printf "\e[32m[DONE]\e[0m\n"

re: fclean all

test: re
	@make -C libarr clean
	@make -C libft clean
	@make -C libftprintf clean
	@printf "\e[31mDeleting object files... \e[0m"
	@rm -f $(OBJ)
	@printf "\e[32m[DONE]\e[0m\n"

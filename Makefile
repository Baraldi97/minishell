# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rcosta <rcosta@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/06/13 22:00:00 by rcosta            #+#    #+#              #
#    Updated: 2026/06/13 22:00:00 by rcosta           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	minishell

CC			=	cc
CFLAGS		=	-Wall -Wextra -Werror -I.
RM			=	rm -f

LIBFT_DIR	=	libft
LIBFT		=	$(LIBFT_DIR)/libft.a
PRINTF_DIR	=	libft/printf
PRINTF		=	$(PRINTF_DIR)/libftprintf.a

LIBS		=	$(LIBFT) $(PRINTF) -lreadline

SRCS		=	main.c \
				expander/expander.c \
				expander/expander_utils.c \
				expander/expander_split.c \
				expander/expander_split2.c \
				lexer/lexer.c \
				lexer/lexer_utils.c \
				parser/parser.c \
				parser/parser_utils.c \
				parser/parser_free.c \
				executor/executor.c \
				executor/exec_utils.c \
				executor/pipeline.c \
				executor/redirections.c \
				executor/heredocs.c \
				executor/path.c \
				executor/signals.c \
				executor/cleanup.c \
				executor/builtins/builtin.c \
				executor/builtins/cd.c \
				executor/builtins/echo.c \
				executor/builtins/env.c \
				executor/builtins/exit.c \
				executor/builtins/export.c \
				executor/builtins/export_print.c \
				executor/builtins/pwd.c \
				executor/builtins/unset.c \
				executor/builtins/env/env_init.c \
				executor/builtins/env/env_utils.c

OBJS		=	$(SRCS:.c=.o)

all:		$(NAME)

$(NAME):	$(LIBFT) $(PRINTF) $(OBJS)
			$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(NAME)

%.o:		%.c minishell.h
			$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
			$(MAKE) -C $(LIBFT_DIR)

$(PRINTF):
			$(MAKE) -C $(PRINTF_DIR)

clean:
			$(RM) $(OBJS)
			$(MAKE) -C $(LIBFT_DIR) clean
			$(MAKE) -C $(PRINTF_DIR) clean

fclean:		clean
			$(RM) $(NAME)
			$(MAKE) -C $(LIBFT_DIR) fclean
			$(MAKE) -C $(PRINTF_DIR) fclean

re:			fclean all

.PHONY:		all clean fclean re

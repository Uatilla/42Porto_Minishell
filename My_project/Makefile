# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lebarbos <lebarbos@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: Invalid date        by                   #+#    #+#              #
#    Updated: 2024/06/10 20:57:16 by lebarbos         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #



.SILENT:

# Colors
RESET 		=	\033[0m	
BLACK 		=	\033[1;30m
RED 		=	\033[1;31m
GREEN 		=	\033[1;32m
YELLOW 		=	\033[1;33m
BLUE 		=	\033[1;34m
PURPLE 		=	\033[1;35m
CYAN 		=	\033[1;36m
WHITE 		=	\033[1;37m

NAME		=	minishell

# Commands
CC			= cc
RM			= rm -rf

# Diretories
SRCS_DIR	=	srcs
OBJS_DIR	=	objs
LIBFT_DIR	=	./libraries/libft
INCLUDES	=	includes
SUB_DIR		=	environment exit input signals tokenization parsing exec builtins\
builtins
#SUB_DIR		=	environment exit input signals tokenization
ALL_OBJS_DIR	= $(foreach dir, $(SUB_DIR), $(addprefix $(OBJS_DIR)/, $(dir)))

# Flags
CFLAGS		= -Wall -Wextra -Werror -g -O0 #-fsanitize=address
#LFLAGS		=	-L ${LIBFT_PATH} -lft -lreadline
#MK_FLAG		= --no-print-directory

# Files
SRCS		=	main.c print.c \
				environment/environment.c \
				exit/exit.c exit/cleaning_tree.c\
				signals/signals.c signals/signals_heredoc.c \
				input/input_checker.c input/input_checker_utils.c \
				input/sintax_valid.c \
				tokenization/tokens.c tokenization/tokens_aux.c \
				tokenization/rename_tkn_typ.c \
				parsing/building_tree.c parsing/construct_tree.c \
				tokenization/expander.c \
				tokenization/expander_aux.c tokenization/lexer.c \
				tokenization/lexer_aux.c tokenization/path.c \
				tokenization/path_aux.c tokenization/handle_heredoc.c \
				tokenization/handle_heredoc_aux.c \
				exec/exec_tree.c \
				builtins/check_builtins.c builtins/env.c builtins/chdir.c \
				builtins/chdir_aux.c builtins/pwd.c builtins/builtins_aux.c \
				builtins/echo.c builtins/unset.c builtins/export.c \
				builtins/export_aux.c
OBJS		=	$(SRCS:%.c=$(OBJS_DIR)/%.o)
LIBFT		=	./libraries/libft/libft.a

#	$(CC) $(CFLAGS) $(OBJS) -L $(LIBFT) -lft -lreadline -o $(NAME)
# Rules
all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -lreadline -o $(NAME)
	printf "Compiling		$(GREEN)[OK]$(RESET)\n"

$(OBJS_DIR):
	mkdir -p $(OBJS_DIR) $(ALL_OBJS_DIR)
	printf "Objects directories  	$(YELLOW)[OK]$(RESET)\n"

$(OBJS): $(OBJS_DIR)/%.o : $(SRCS_DIR)/%.c | $(OBJS_DIR)
	$(CC) -I $(INCLUDES) $(CFLAGS) -c $< -o $@
	printf "Making binary files	$(YELLOW)[OK]$(RESET)\n"

#$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c 
#	mkdir -p $(@D)
#	$(CC) -I $(INCLUDES) $(CFLAGS) -c $< -o $@
#	printf "Making binary files	$(YELLOW)[OK]$(RESET)\n"


$(LIBFT):
	printf "Making Libft		$(YELLOW)[OK]$(RESET)\n"
	$(MAKE)  -sC $(LIBFT_DIR)

clean:
	$(RM) $(OBJS_DIR)
	printf "clean Minishell files	$(CYAN)[OK]$(RESET)\n"
	$(MAKE) $(MK_FLAG) clean -sC $(LIBFT_DIR)

fclean: clean
	$(RM) $(NAME)
	$(MAKE) $(MK_FLAG) fclean -sC $(LIBFT_DIR)
	printf "fclean			$(CYAN)[OK]$(RESET)\n"

leaks: readline.supp
	valgrind --suppressions=readline.supp --leak-check=full --show-leak-kinds=all --trace-children=yes --track-fds=yes --log-file=output.log ./minishell

readline.supp:
	echo "{" > readline.supp
	echo "    leak readline" >> readline.supp
	echo "    Memcheck:Leak" >> readline.supp
	echo "    ..." >> readline.supp
	echo "    fun:readline" >> readline.supp
	echo "}" >> readline.supp
	echo "{" >> readline.supp
	echo "    leak add_history" >> readline.supp
	echo "    Memcheck:Leak" >> readline.supp
	echo "    ..." >> readline.supp
	echo "    fun:add_history" >> readline.supp
	echo "}" >> readline.supp

	
re: fclean all

.PHONY: all clean fclean re

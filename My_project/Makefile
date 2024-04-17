# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: uviana-a <uviana-a@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/11 20:00:01 by uviana-a          #+#    #+#              #
#    Updated: 2024/04/11 20:00:03 by uviana-a         ###   ########.fr        #
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
SUB_DIR		=	environment exit
ALL_OBJS_DIR	= $(foreach dir, $(SUB_DIR), $(addprefix $(OBJS_DIR)/, $(dir)))

# Flags
CFLAGS		= -Wall -Wextra -Werror -g -O0
#MK_FLAG		= --no-print-directory

# Files
SRCS		=	main.c \
				environment/env.c exit/exit.c
OBJS		=	$(SRCS:%.c=$(OBJS_DIR)/%.o)
LIBFT		=	./libraries/libft/libft.a

# Rules
all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)
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
	printf "clean FdF files		$(CYAN)[OK]$(RESET)\n"
	$(MAKE) $(MK_FLAG) clean -sC $(LIBFT_DIR)

fclean: clean
	$(RM) $(NAME)
	$(MAKE) $(MK_FLAG) fclean -sC $(LIBFT_DIR)
	printf "fclean			$(CYAN)[OK]$(RESET)\n"
	
re: fclean all

.PHONY: all clean fclean re

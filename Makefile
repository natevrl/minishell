# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nabentay <nabentay@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/20 19:39:21 by nabentay          #+#    #+#              #
#    Updated: 2022/02/16 09:08:28 by nabentay         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
BONUS_NAME = minishell_bonus

CC = gcc
INCLUDE = include
CFLAGS = -Werror -Wextra -Wall
LFLAGS = -lreadline
RM = rm -rf

FILES = minishell \
		parsing/parsing_cmd	\
		parsing/parsing_assemble	\
		parsing/utils_parsing_cmd	\
		parsing/convert	\
		parsing/redirection	\
		builtin/echo \
		builtin/unset \
		builtin/env \
		builtin/cd \
		builtin/exit \
		builtin/pwd \
		builtin/export \
		builtin/load_builtin \
		execve/execve \
		execve/redirection \
		memory/memory0		\
		memory/memory1		\
		get_next_line/get_next_line \
		env/env		\
		env/add_basic_env		\
		env/env_utils		\
		signal/signaux		\

FILES_B = minishell \

SRCS_DIR = ./
SRCS = $(addprefix $(SRCS_DIR), $(addsuffix .c, $(FILES)))

BONUS_DIR = ./
BONUS = $(addprefix $(SRCS_DIR), $(addsuffix .c, $(FILES_B)))

OBJS_B_DIR = ./objs_b/
OBJS_B = $(addprefix $(OBJS_B_DIR), $(addsuffix .o, $(FILES_B)))

OBJS_DIR = ./objs/
OBJS = $(addprefix $(OBJS_DIR), $(addsuffix .o, $(FILES)))

all: $(OBJS_DIR) $(NAME)

$(OBJS_DIR)%.o: $(SRCS_DIR)%.c
		@echo "\033[1;31m************ $< COMPILED SUCESSFULLY ************"
		@$(CC) -o $@ -c $< $(CFLAGS) -I $(INCLUDE)

$(NAME): $(OBJS)
		@make -C libft all
		@make -C libft bonus
		@$(CC) $(CFLAGS) -I $(INCLUDE) -o $@ $^ $(LFLAGS) libft/libft.a
		@echo "\033[1;31m************ $@ SUCESS ************"

$(OBJS_DIR):
		@mkdir $@
		@mkdir objs/parsing
		@mkdir objs/builtin
		@mkdir objs/memory
		@mkdir objs/env
		@mkdir objs/signal
		@mkdir objs/execve
		@mkdir objs/get_next_line

$(OBJS_B_DIR):
		@mkdir $@

$(OBJS_B_DIR)%.o: $(BONUS_DIR)%.c
		@echo "\033[1;31m************ $< COMPILED SUCESSFULLY ************"
		@$(CC) -o $@ -c $< $(CFLAGS) -I $(INCLUDE)

bonus: $(OBJS_B_DIR) $(BONUS_NAME)

$(BONUS_NAME): $(OBJS_B)
		@make -C libft all
		$(CC) $(CFLAGS) $(OBJS_B) -o $@

clean:
		@echo "\033[1;31m************ $(OBJS_DIR) DELETE SUCESS ************"
		@make -C libft clean
		@$(RM) $(OBJS_DIR) $(OBJS_B_DIR)

fclean: clean
		@rm -f $(NAME)
		@rm -f libft/libft.a
		@echo "\033[1;31m************ $(NAME) DELETE SUCESS ************"

re: clean all

.PHONY: bonus all clean fclean re

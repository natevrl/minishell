# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nabentay <nabentay@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/20 19:39:21 by nabentay          #+#    #+#              #
#    Updated: 2022/02/25 23:37:13 by nabentay         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
BONUS_NAME = minishell_bonus

CC = gcc
INCLUDE = include
CFLAGS = -Werror -Wextra -Wall
DEBUG = -g
LFLAGS = -lreadline
RM = rm -rf

FILES = minishell \
		parsing/parsing_cmd	\
		parsing/parsing_assemble_utils	\
		parsing/parsing_assemble	\
		parsing/utils_parsing_cmd	\
		parsing/ft_split_token	\
		parsing/ft_split_token_utils	\
		parsing/convert	\
		parsing/redirection	\
		builtin/echo \
		builtin/unset \
		builtin/env \
		builtin/cd \
		builtin/exit \
		builtin/pwd \
		builtin/export \
		builtin/utils_export \
		builtin/load_builtin \
		execve/execve \
		execve/path_utils \
		execve/redirection \
		execve/pipe_utils \
		execve/pipe \
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
		@$(CC) -o $@ -c $< $(CFLAGS) -I $(INCLUDE)
		@echo "$(GREEN)************ $< COMPILED SUCESSFULLY$(RST)"

$(NAME): $(OBJS)
		@make -C libft all --no-print-directory
		@make -C libftim all --no-print-directory
		@make -C libft bonus --no-print-directory
		@$(CC) $(CFLAGS) -I $(INCLUDE) -o $@ $^ $(LFLAGS) libft/libft.a libftim/libftim.a
		@echo "$(GREEN)************ $@ SUCESS$(RST)"
		@echo "$(CYAN)┌────────────────────────────────────┐$(RST)"
		@echo "$(CYAN)│             Minishell              │$(RST)"
		@echo "$(CYAN)│ Authors                            │$(RST)"
		@echo "$(CYAN)│                                    │$(RST)"
		@echo "$(CYAN)│ Bentayeb Naofel                    │$(RST)"
		@echo "$(CYAN)│ Benhado Nathan                     │$(RST)"
		@echo "$(CYAN)└────────────────────────────────────┘$(RST)"

$(OBJS_DIR):
		@mkdir $@
		@mkdir objs/parsing
		@mkdir objs/builtin
		@mkdir objs/memory
		@mkdir objs/env
		@mkdir objs/signal
		@mkdir objs/execve
		@mkdir objs/get_next_line
		@echo "$(GREEN)************ OBJS FOLDER CREATED$(RST)"

$(OBJS_B_DIR):
		@mkdir $@

$(OBJS_B_DIR)%.o: $(BONUS_DIR)%.c
		@$(CC) -o $@ -c $< $(CFLAGS) -I $(INCLUDE)
		@echo "$(GREEN)************ $< COMPILED SUCESSFULLY$(RST)"

debug: $(OBJS_DIR) $(OBJS)
		@make -C libft all --no-print-directory
		@make -C libftim all --no-print-directory
		@make -C libft bonus --no-print-directory
		@$(CC) $(DEBUG) -I $(INCLUDE) -o $(NAME) $(OBJS) $(LFLAGS) libft/libft.a libftim/libftim.a
		@echo "$(YELLOW)**/ DEBUG MODE (wo/ flags w/ -g) \**$(RST)"


bonus: $(OBJS_B_DIR) $(BONUS_NAME)

$(BONUS_NAME): $(OBJS_B)
		@make -C libft all --no-print-directory
		@make -C libftim all --no-print-directory
		@$(CC) $(CFLAGS) $(OBJS_B) -o $@

clean:
		@make -C libft clean --no-print-directory
		@make -C libftim clean --no-print-directory
		@$(RM) $(OBJS_DIR) $(OBJS_B_DIR)
		@echo "$(GREEN)************ OBJS DELETE SUCESS$(RST)"

fclean: clean
		@rm -f $(NAME)
		@rm -f libft/libft.a
		@rm -f libftim/libftim.a
		@echo "$(GREEN)************ $(NAME) DELETE SUCESS$(RST)"

re: clean all

.PHONY: bonus all clean fclean re

#COLORS
RED = \033[1;31m
GREEN = \033[1;32m
YELLOW = \033[1;33m
CYAN = \033[1;36m
RST = \033[0m

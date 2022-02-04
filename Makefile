# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/20 19:39:21 by nabentay          #+#    #+#              #
#    Updated: 2022/02/04 20:19:58 by ubuntu           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
BONUS_NAME = minishell_bonus

CC = gcc
INCLUDE = ./include/
CFLAGS = -Werror -Wextra -Wall
LFLAGS = -lreadline
RM = rm -rf

FILES = minishell \

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
		$(CC) -o $@ -c $< $(CFLAGS) -I $(INCLUDE)

$(NAME): $(OBJS)
		make -C libft
		@$(CC) $(CFLAGS) -o $@ $^ $(LFLAGS)
		@echo "\033[1;31m************ $@ SUCESS ************"

$(OBJS_DIR):
		@mkdir $@

$(OBJS_B_DIR):
		@mkdir $@

$(OBJS_B_DIR)%.o: $(BONUS_DIR)%.c
		@echo "\033[1;31m************ $< COMPILED SUCESSFULLY ************"
		@$(CC) -o $@ -c $< $(CFLAGS) -I $(INCLUDE)

bonus: $(OBJS_B_DIR) $(BONUS_NAME)

$(BONUS_NAME): $(OBJS_B)
		@make -C $(LIBFT) all
		$(CC) $(CFLAGS) $(OBJS_B) -o $@

clean:
		@echo "\033[1;31m************ $(OBJS_DIR) DELETE SUCESS ************"
		@$(RM) $(OBJS_DIR) $(OBJS_B_DIR)

fclean: clean
		@rm -f $(NAME) $(BONUS_NAME)
		@echo "\033[1;31m************ $(NAME) DELETE SUCESS ************"

re: clean all

.PHONY: bonus all clean fclean re

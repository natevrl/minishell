# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nabentay <nabentay@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/20 19:39:21 by nabentay          #+#    #+#              #
#    Updated: 2022/02/02 00:21:41 by nabentay         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
BONUS_NAME = philo_bonus

CC = gcc
INCLUDE = ./
CFLAGS = -Werror -Wextra -Wall -pthread
RM = rm -rf

FILES = philo	\
		philo_utils \
		action \
		free \
		init \
		time \
		execute_thread \
		death \

FILES_B = philo	\
		philo_utils \
		action \
		free \
		init \
		time \
		execute_thread \
		death \

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
		@echo "\x1b[1m************ $< COMPILED SUCESSFULLY ************"
		@$(CC) -o $@ -c $< $(CFLAGS) -I $(INCLUDE)

$(NAME): $(OBJS)
		@$(CC) $(CFLAGS) -o $@ $^
		@echo "\x1b[1m************ $@ SUCESS ************"

$(OBJS_DIR):
		@mkdir $@

$(OBJS_B_DIR):
		@mkdir $@

$(OBJS_B_DIR)%.o: $(BONUS_DIR)%.c
		@echo "\x1b[1m************ $< COMPILED SUCESSFULLY ************"
		@$(CC) -o $@ -c $< $(CFLAGS) -I $(INCLUDE)

bonus: $(OBJS_B_DIR) $(BONUS_NAME)

$(BONUS_NAME): $(OBJS_B)
		@make -C $(LIBFT) all
		$(CC) $(CFLAGS) $(OBJS_B) -o $@

clean:
		@echo "\x1b[1m************ $(OBJS_DIR) DELETE SUCESS ************"
		@$(RM) $(OBJS_DIR) $(OBJS_B_DIR)

fclean: clean
		@rm -f $(NAME) $(BONUS_NAME)
		@echo "\x1b[1m************ $(NAME) DELETE SUCESS ************"

re: clean all

.PHONY: bonus all clean fclean re

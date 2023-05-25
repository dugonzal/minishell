# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sizquier <sizquier@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/10 09:40:27 by ciclo             #+#    #+#              #
#    Updated: 2023/05/25 18:50:58 by sizquier         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:= minishell

CC			:= clang -g3

CFLAGS		:= -Wall -Wextra -Werror

SRC_DIR		:= src/

OBJ_DIR		:= obj/

INC_DIR		:= include/

# folders for sources
parser_dir 	:= parser/
parser		:= split_token split_token_utils parser parser_utils lexer lexer_utils utils

builtins_dir 	:= builtins/
builtins		:= builtins exit echo pwd export builtin_extra unset env

SRC_FILES 	+= $(addprefix $(parser_dir),$(parser))
SRC_FILES 	+= $(addprefix $(builtins_dir),$(builtins))

SRC_FILES	+=	minishell  utils signals exec expanser redirect

SRC			:= $(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC_FILES)))
OBJ			:= $(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC_FILES)))

DEFAULT	= \033[0;39m
GRAY 	= \033[0;90m
RED 	= \033[0;91m
GREEN 	= \033[0;92m
YELLOW 	= \033[0;93m
BLUE 	= \033[0;94m
MAGENTA = \033[0;95m
CYAN 	= \033[0;96m
WHITE 	= \033[0;97m

OS := $(shell uname)

ifeq ($(OS), Darwin)
	readline := -lreadline -L${HOME}/.brew/opt/readline/lib  -I${HOME}/.brew/opt/readline/lib/include
else
	readline :=	-L/usr/include -lreadline 
endif

ifndef verbose
.SILENT:
endif

$(NAME): $(OBJ)
	make -C libft && mkdir -p bin && mv libft/libft.a bin
	$(CC) $(CFLAGS) $(OBJ) -o $@ -L bin -lft -I $(INC_DIR) $(readline)
	printf	"$(BLUE) 🚀 $@ $(DEFAULT)\n"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	mkdir -p $(OBJ_DIR)
	mkdir -p $(OBJ_DIR)$(parser_dir)
	mkdir -p $(OBJ_DIR)$(builtins_dir)
	if [[ ! -d "libft" ]]; then git clone https://github.com/dugonzal/libft.git; fi
	$(CC) $(CFLAGS) -c $< -o $@ -I $(INC_DIR)* -I libft 
	printf  "$(GREEN) 🚀  $< $(DEFAULT)\n"

all: $(NAME)

clean:
	make -C libft clean
	rm -rf $(NAME)
	printf "$(YELLOW) Cleaning $(NAME) $(DEFAULT)"

fclean: clean
	rm -rf bin  $(OBJ_DIR)
	make -C libft fclean
	printf "$(BLUE)Cleaning $(OBJ_DIR) and bin $(DEFAULT)\n"

val: $(NAME)
	valgrind --track-origins=yes --leak-check=full --show-leak-kinds=all --log-file=valgrind.log  cat command | ./minishell; cat valgrind.log 

re: fclean all val 

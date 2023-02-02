# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: valentin <valentin@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/22 19:19:43 by valentin          #+#    #+#              #
#    Updated: 2023/02/03 00:41:14 by valentin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = minishell

COLOUR_GREEN=\033[0;32m
COLOUR_END=\033[0m

C_FILES = src/minishell.c src/builtins/cd.c src/builtins/echo.c src/builtins/pwd.c \
			src/error_free/free.c src/exec/exec_builtins.c src/exec/pipe.c \
			src/utils/utils.c src/error_free/error.c src/redir/redir.c \
			src/redir/redir2.c src/signal.c src/exec/exec.c src/utils/utils2.c \
			src/redir/here_doc.c src/utils/ft_split2.c src/builtins/export.c \
			src/get_env.c src/utils/utils_list.c src/exec/exec2.c src/redir/redir_utils.c \
			src/redir/redir_utils2.c src/utils/check_quotes.c \
			
DIR_OBJ = objs/

SRC_DIR = ./src/

INCS	= -I ./include/

OBJS = ${C_FILES:%.c=%.o}

CFLAGS += -Wall -Wextra -Werror 

LIBSFLAGS	=  libft/libft.a

CC		= cc
RM		= rm -f

$(NAME): ${OBJS} maker
		@$(CC) $(OBJS) $(CFLAGS) $(LIBSFLAGS) -lreadline -o $(NAME)
		@echo " [ $(COLOUR_GREEN)OK$(COLOUR_END) ] ./minishell"
		
all: ${NAME}

maker:
		@make bonus -s -C libft
		@echo "[ OK ] libft"

clean:
		@${RM} ${SRC_DIR}/*.o
		@${RM} ${SRC_DIR}/builtins/*.o
		@${RM} ${SRC_DIR}/utils/*.o
		@${RM} ${SRC_DIR}/exec/*.o
		@${RM} ${SRC_DIR}/redir/*.o
		@${RM} ${SRC_DIR}/error_free/*.o
		@make fclean -s -C libft

fclean:	clean
		@${RM} ${NAME}
		@echo " [ OK ] minishell clean"

re:		fclean all

norm:
	norminette $(SRC_DIR)*.c $(BUIL_DIR)*.c include/*.h 

.PHONY:         all clean fclean bonus re
# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vescaffr <vescaffr@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/26 00:08:06 by vescaffr          #+#    #+#              #
#    Updated: 2022/05/04 17:16:16 by vescaffr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #
NAME = libft.a

SRCS = ft_isalpha.c \
       ft_memchr.c \
       ft_split.c \
       ft_strlcat.c \
       ft_strnstr.c \
       ft_toupper.c \
       ft_atoi.c \
       ft_isascii.c \
       ft_memcmp.c \
       ft_strchr.c \
       ft_strlcpy.c \
       ft_strrchr.c \
       ft_bzero.c \
       ft_isdigit.c \
       ft_memcpy.c \
       ft_strdup.c \
       ft_strlen.c \
       ft_strtrim.c \
       ft_calloc.c \
       ft_isprint.c \
       ft_memmove.c \
       ft_striteri.c \
       ft_strmapi.c \
       ft_substr.c \
       ft_isalnum.c \
       ft_itoa.c \
       ft_memset.c \
       ft_strjoin.c \
       ft_strncmp.c \
       ft_tolower.c \
       ft_putchar_fd.c \
       ft_putstr_fd.c \
       ft_putendl_fd.c \
       ft_putnbr_fd.c

OBJS = ${SRCS:.c=.o}

BONUS = ft_lstnew_bonus.c \
	ft_lstadd_front_bonus.c \
	ft_lstsize_bonus.c \
	ft_lstlast_bonus.c \
	ft_lstadd_back_bonus.c \
	ft_lstdelone_bonus.c \
	ft_lstclear_bonus.c \
	ft_lstiter_bonus.c \
	ft_lstmap_bonus.c

OBJSBONUS = ${BONUS:.c=.o}

CC		= gcc
RM		= rm -f

CFLAGS = -Wall -Wextra -Werror

.c.o:
		${CC} ${CFLAGS} -g -c $< -o ${<:.c=.o}

$(NAME): ${OBJS}
		ar rcs ${NAME} ${OBJS}

bonus:	${OBJS} ${OBJSBONUS}
		ar rcs ${NAME} ${OBJS} ${OBJSBONUS}

all:	${NAME}

clean:
		${RM} ${OBJS} ${OBJSBONUS}

fclean:	clean
		${RM} ${NAME}

re:		fclean all

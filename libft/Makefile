# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rodantec <rodantec@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/13 16:22:33 by rodantec          #+#    #+#              #
#    Updated: 2025/05/18 10:21:14 by rodantec         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS    =	ft_atoi.c \
ft_bzero.c \
ft_calloc.c \
ft_isalnum.c \
ft_isalpha.c \
ft_isascii.c \
ft_isdigit.c \
ft_isprint.c \
ft_itoa.c \
ft_memchr.c \
ft_memcmp.c \
ft_memcpy.c \
ft_memmove.c \
ft_memset.c \
ft_putchar_fd.c \
ft_putendl_fd.c \
ft_putnbr_fd.c \
ft_putstr_fd.c \
ft_split.c \
ft_strchr.c \
ft_strdup.c \
ft_striteri.c \
ft_strjoin.c \
ft_strlcat.c \
ft_strlcpy.c \
ft_strlen.c \
ft_strmapi.c \
ft_strncmp.c \
ft_strnstr.c \
ft_strrchr.c \
ft_strtrim.c \
ft_substr.c \
ft_tolower.c \
ft_toupper.c \
ft_strcmp.c \
ft_print_array.c \
ft_free_array.c \
ft_atol.c \
# ft_printf.c \
# ft_voidpointer.c \
# ft_unsignedi.c \
# ft_iitoa.c \
# ft_hexamin.c \
# ft_hexamaj.c \
# ft_size_n_hexa.c \
# ft_size_n_deci.c \
# ft_percent.c \
# ft_printchar.c \
# ft_printstr_fd.c \


SRCS_B = ft_lstnew.c \
ft_lstadd_front.c \
ft_lstsize.c \
ft_lstlast.c \
ft_lstadd_back.c \
ft_lstdelone.c \
ft_lstclear.c

OBJS    = ${SRCS:.c=.o}
OBJS_B  = ${SRCS_B:.c=.o}
INCS    = includes
NAME    = libft.a
LIBC    = ar rc
LIBR    = ranlib
CC        = gcc
RM        = rm -f
CFLAGS    = -Wall -Wextra -Werror

.c.o:
		${CC} ${CFLAGS} -I ./ -c $< -o ${<:.c=.o} -I ${INCS}

${NAME}: ${OBJS}
	${LIBC} ${NAME} ${OBJS}

all: ${NAME}

bonus: ${OBJS} ${OBJS_B}
	${LIBC} ${NAME} ${OBJS} ${OBJS_B}

clean:
		${RM} ${OBJS} ${OBJS_B}

fclean: clean
	${RM} ${NAME}

re: fclean all

.PHONY:	all bonus clean fclean re
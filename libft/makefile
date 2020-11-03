# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hbaudet <hbaudet@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/08/13 19:19:11 by hbaudet           #+#    #+#              #
#    Updated: 2020/11/03 23:30:50 by hbaudet          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS	=	ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c \
			ft_isascii.c ft_isdigit.c ft_islower.c ft_isprint.c ft_isupper.c \
			ft_itoa.c ft_memccpy.c ft_memchr.c ft_memcmp.c ft_memcpy.c \
			ft_memmove.c ft_memset.c ft_putchar_fd.c ft_putendl_fd.c \
			ft_putnbr_fd.c ft_putstr_fd.c ft_split.c ft_strchr.c ft_strcmp.c \
			ft_strcpy.c ft_strdup.c ft_strjoin.c ft_strlcat.c ft_strlcpy.c \
			ft_strlen.c ft_strmapi.c ft_strncmp.c ft_strncpy.c \
			ft_strnstr.c ft_strrchr.c ft_strtrim.c ft_substr.c ft_tolower.c \
			ft_toupper.c ft_zero.c
			
BONUS	=	ft_lstnew_bonus.c ft_lstadd_front_bonus.c ft_lstsize_bonus.c \
			ft_lstlast_bonus.c ft_lstadd_back_bonus.c ft_lstdelone_bonus.c \
			ft_lstclear_bonus.c ft_lstiter_bonus.c ft_lstmap_bonus.c

OBJS	=	$(SRCS:.c=.o)

OBJS_B	=	$(BONUS:.c=.o)

NAME	=	libft.a

CC		=	clang

RM		=	rm -f

CFLAGS 	=	-Wall -Wextra -Werror

%.o:		%.c
			$(CC) $(CFLAGS) -c  $< -o $(<:.c=.o)

$(NAME):	$(OBJS)
			ar rc $(NAME) $(OBJS)


all:		bonus

clean:
			$(RM) $(OBJS) $(OBJS_B)

fclean:		clean
			${RM} ${NAME}

re:			fclean all

bonus:		${OBJS} ${OBJS_B}
			ar rc ${NAME} ${OBJS} ${OBJS_B}

o:			re
			${MAKE} clean

.PHONY:		all clean fclean re bonus o

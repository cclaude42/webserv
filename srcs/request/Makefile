# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hbaudet <hbaudet@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/26 18:03:34 by hbaudet           #+#    #+#              #
#    Updated: 2020/11/08 14:24:38 by cclaude          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS			=	main.cpp \
					Request.cpp \
					RequestMembers.cpp \
					Strings.cpp

BONUS			=

OBJS_DIR		=	objs_dir/

OBJS			=	$(addprefix $(OBJS_DIR), $(SRCS:.cpp=.o))

PATH_LIBFT		=	../../libft

LIBFT			=	libft.a

NAME			=	weebserv

CC				=	clang++

RM				=	rm -f

LINK			=	-L $(PATH_LIBFT) -lft

CFLAGS 			=	-Wall -Wextra -Werror

all:			$(LIBFT) $(NAME)

$(OBJS_DIR)%.o:	%.cpp | $(OBJS_DIR)
				$(CC) $(CFLAGS) -I $(PATH_LIBFT)/includes -I ../../includes -c  $< -o $@

$(NAME):		$(OBJS_DIR) $(OBJS)
				$(CC) -o $(NAME) $(OBJS) $(LINK)

$(OBJS_DIR):
				mkdir -p $(OBJS_DIR)$(REQUEST)

$(LIBFT):
				$(MAKE) -C $(PATH_LIBFT)

clean:
				$(RM) -rf $(OBJS_DIR)
				$(MAKE) clean -C $(PATH_LIBFT)

fclean:			clean
				$(RM) $(PATH_LIBFT)$(LIBFT)
				$(RM) $(NAME)

re:				fclean all

bonus:

fsan:			$(OBJS)
				$(CC) $(FRAMEWORK) $(LINK) -fsanitize=address -o $(NAME) $(OBJS)

.PHONY:			all clean fclean re bonus fsan

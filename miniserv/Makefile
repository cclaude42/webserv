NAME = miniserv

CC = clang++

CFLAGS = -Wall -Wextra -Werror -std=c++98 -I includes/

HEADER = miniserv.hpp

LIST = miniserv header ntoh tools

SRC = $(addprefix srcs/, $(addsuffix .cpp, $(LIST)))

OBJ = $(SRC:cpp=o)

all: $(NAME)

$(NAME): $(OBJ)
	@echo "\n"
	@echo "\033[0;32mCompiling miniserv..."
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ)
	@echo "\n\033[0mDone !"

%.o: %.cpp
	@printf "\033[0;33mGenerating miniserv objects... %-33.33s\r" $@
	@${CC} ${CFLAGS} -c $< -o $@

clean:
	@echo "\nDeleting objects..."
	@rm -f $(OBJ)
	@echo "\033[0m"

fclean:
	@echo "\nDeleting objects..."
	@rm -f $(OBJ)
	@echo "\nDeleting executable..."
	@rm -f $(NAME)
	@echo "\033[0m"

re: fclean all

test: re
	./miniserv

norm:
	norminette $(SRC) includes/$(HEADER)

.PHONY: clean fclean re test

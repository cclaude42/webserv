NAME = webserv

CC = clang++

CFLAGS = -Wall -Wextra -Werror -I includes/ -I srcs/classes/

HEADER = webserv.hpp

MAIN = webserv

TOOLS = ntoh cstring

CLASSES = Response ResponseHeader Server

SRC = $(addprefix srcs/, $(addsuffix .cpp, $(MAIN))) \
	$(addprefix srcs/tools/, $(addsuffix .cpp, $(TOOLS))) \
	$(addprefix srcs/classes/, $(addsuffix .cpp, $(CLASSES))) \

OBJ = $(SRC:cpp=o)

all: $(NAME)

$(NAME): $(OBJ)
	@echo "\n"
	@echo "\033[0;32mCompiling miniserv..."
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ)
	@echo "\n\033[0mDone !"

%.o: %.cpp
	@printf "\033[0;33mGenerating webserv objects... %-33.33s\r" $@
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
	./webserv

norm:
	norminette $(SRC) includes/$(HEADER)

.PHONY: clean fclean re test norm

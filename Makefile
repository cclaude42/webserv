NAME = webserv

CC = clang++

CFLAGS = -Wall -Wextra -Werror

INCLUDES = -I includes/ -I srcs/config/ -I srcs/response/ -I srcs/server/

HEADER = webserv.hpp

MAIN = webserv

CONFIG = Config ConfigReader ConfigServer

RESPONSE = Response ResponseHeader

SERVER = Server

TOOLS = ntoh cstring

SRC = $(addprefix srcs/, $(addsuffix .cpp, $(MAIN))) \
	$(addprefix srcs/response/, $(addsuffix .cpp, $(RESPONSE))) \
	$(addprefix srcs/server/, $(addsuffix .cpp, $(SERVER))) \
	$(addprefix srcs/tools/, $(addsuffix .cpp, $(TOOLS))) \


OBJ = $(SRC:cpp=o)

all: $(NAME)

$(NAME): $(OBJ)
	@echo "\n"
	@echo "\033[0;32mCompiling miniserv..."
	@$(CC) $(CFLAGS) $(INCLUDES) -o $(NAME) $(OBJ)
	@echo "\n\033[0mDone !"

%.o: %.cpp
	@printf "\033[0;33mGenerating webserv objects... %-33.33s\r" $@
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

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

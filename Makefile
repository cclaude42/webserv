##################################################
# COMPILER
##################################################

NAME = webserv

CC = clang++

CFLAGS = -Wall -Wextra -Werror -g

##################################################
# INCLUDES
##################################################

INCLUDES = -I includes -I libft/includes

CLASSES = -I srcs/config -I srcs/request -I srcs/response -I srcs/server

HEADER = webserv.hpp

LIBFT = libft/libft.a

##################################################
# FILES
##################################################

MAIN = webserv

CONFIG = Config ConfigReader ConfigServer

REQUEST = Request RequestMembers

RESPONSE = Response ResponseHeader

SERVER = Server Cluster

TOOLS = ntoh string

##################################################
# SRC
##################################################

SRC = $(addsuffix .cpp, $(MAIN)) \
	$(addprefix config/, $(addsuffix .cpp, $(CONFIG))) \
	$(addprefix request/, $(addsuffix .cpp, $(REQUEST))) \
	$(addprefix response/, $(addsuffix .cpp, $(RESPONSE))) \
	$(addprefix server/, $(addsuffix .cpp, $(SERVER))) \
	$(addprefix utils/, $(addsuffix .cpp, $(TOOLS))) \

SRC_DIR = srcs

OBJ = $(addprefix $(OBJ_DIR)/, $(addsuffix .o, $(MAIN))) \
	$(addprefix $(OBJ_DIR)/, $(addsuffix .o, $(CONFIG))) \
	$(addprefix $(OBJ_DIR)/, $(addsuffix .o, $(REQUEST))) \
	$(addprefix $(OBJ_DIR)/, $(addsuffix .o, $(RESPONSE))) \
	$(addprefix $(OBJ_DIR)/, $(addsuffix .o, $(SERVER))) \
	$(addprefix $(OBJ_DIR)/, $(addsuffix .o, $(TOOLS))) \

OBJ_DIR = objs

OBJ_SUBDIR = $(addprefix $(OBJ_DIR)/, config request response server utils)

OBJ_BUILD = $(addprefix $(OBJ_DIR)/, $(SRC:cpp=o))

##################################################
# METHODS
##################################################

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ_DIR) $(OBJ_BUILD)
	@echo "\n"
	@echo "\033[0;32mCompiling webserv..."
	@$(CC) $(CFLAGS) $(INCLUDES) $(CLASSES) -o $(NAME) $(OBJ_BUILD) -L libft/ -lft
	@echo "\n\033[0mDone !"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@printf "\033[0;33mGenerating webserv objects... %-33.33s\r" $@
	@$(CC) $(CFLAGS) $(INCLUDES) $(CLASSES) -o $@ -c $<

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(OBJ_SUBDIR)

$(LIBFT):
	@make --no-print-directory -C libft/

clean:
	@echo "\n\033[0;31mCleaning libft..."
	@make fclean --no-print-directory -C libft/
	@echo "\n\033[0;31mDeleting objects..."
	@rm -rf $(OBJ_DIR) $(OBJ_SUBDIR)
	@echo "\033[0m"

fclean: clean
	@echo "\033[0;31mDeleting executable..."
	@rm -f $(NAME)
	@echo "\033[0m"

re: fclean all

test: re clean
	./webserv webserv.conf

.PHONY: libft clean fclean re test

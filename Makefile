##################################################
# COMPILER
##################################################

NAME = webserv

CC = clang++

CFLAGS = -Wall -Wextra -Werror -g -std=c++98# -fsanitize=address

#DEFINES = -D OUT=0# -D TIME=1

ifeq ($(shell uname -s),Darwin)
OS = mac
else
OS = linux
endif

PWD = $(shell pwd)

##################################################
# INCLUDES
##################################################

INCLUDES = -I includes -I libft/includes

CLASSES = -I srcs/autoindex -I srcs/cgi -I srcs/config -I srcs/request -I srcs/response -I srcs/server

HEADER = webserv.hpp

LIBFT = libft/libft.a

##################################################
# FILES
##################################################

MAIN = webserv

AUTOINDEX = AutoIndexGenerator

CGI = CgiHandler

CONFIG = Config ConfigHelperFunctions ConfigReader ConfigServer RequestConfig

REQUEST = Request RequestMembers

RESPONSE = Response ResponseHeader

SERVER = Server Cluster

TOOLS = list_sort ntoh string pathIsFile

##################################################
# SRC
##################################################

SRC = $(addsuffix .cpp, $(MAIN)) \
	$(addprefix autoindex/, $(addsuffix .cpp, $(AUTOINDEX))) \
	$(addprefix cgi/, $(addsuffix .cpp, $(CGI))) \
	$(addprefix config/, $(addsuffix .cpp, $(CONFIG))) \
	$(addprefix request/, $(addsuffix .cpp, $(REQUEST))) \
	$(addprefix response/, $(addsuffix .cpp, $(RESPONSE))) \
	$(addprefix server/, $(addsuffix .cpp, $(SERVER))) \
	$(addprefix utils/, $(addsuffix .cpp, $(TOOLS))) \

SRC_DIR = srcs

OBJ = $(addprefix $(OBJ_DIR)/, $(addsuffix .o, $(MAIN))) \
	$(addprefix $(OBJ_DIR)/, $(addsuffix .o, $(AUTOINDEX))) \
	$(addprefix $(OBJ_DIR)/, $(addsuffix .o, $(CGI))) \
	$(addprefix $(OBJ_DIR)/, $(addsuffix .o, $(CONFIG))) \
	$(addprefix $(OBJ_DIR)/, $(addsuffix .o, $(REQUEST))) \
	$(addprefix $(OBJ_DIR)/, $(addsuffix .o, $(RESPONSE))) \
	$(addprefix $(OBJ_DIR)/, $(addsuffix .o, $(SERVER))) \
	$(addprefix $(OBJ_DIR)/, $(addsuffix .o, $(TOOLS))) \

OBJ_DIR = objs

OBJ_SUBDIR = $(addprefix $(OBJ_DIR)/, autoindex cgi config request response server utils)

OBJ_BUILD = $(addprefix $(OBJ_DIR)/, $(SRC:cpp=o))

##################################################
# MAKING
##################################################

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ_DIR) $(OBJ_BUILD)
	@echo "\n"
	@echo "\033[0;32mCompiling webserv..."
	@$(CC) $(CFLAGS) $(INCLUDES) $(DEFINES) $(CLASSES) -o $(NAME) $(OBJ_BUILD) -L libft/ -lft
	@echo "\n\033[0mDone !"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@printf "\033[0;33mGenerating webserv objects... %-38.38s\r" $@
	@$(CC) $(CFLAGS) $(INCLUDES) $(DEFINES) $(CLASSES) -o $@ -c $<

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(OBJ_SUBDIR)

$(LIBFT):
	@make --no-print-directory -C libft/

##################################################
# CLEANING
##################################################

clean:
	@echo "\n\033[0;31mCleaning libft..."
	@make fclean --no-print-directory -C libft/
	@echo "\n\033[0;31mDeleting objects..."
	@rm -rf $(OBJ_DIR) $(OBJ_SUBDIR)
	@rm -rf test_us/root
	@rm -rf client
	@rm -rf YoupiBanane/put_here
	@echo "\033[0m"

fclean: clean
	@echo "\033[0;31mDeleting executable..."
	@rm -f $(NAME)
	@echo "\033[0m"

re: fclean all

##################################################
# TESTING
##################################################

test: test_$(OS)

test_setup: all
	@rm -rf test_us/root
	@mkdir -p test_us/root
	@cp test_us/index/* test_us/root/
	@cp test_us/root/index.html test_us/root/index_permission.html
	@chmod 000 test_us/root/index_permission.html
	@clang++ -o client test_us/client.cpp

test_mac: test_setup
	@osascript -e 'tell application "Terminal" to do script "cd $(PWD) && clear && ./client"'
	@osascript -e 'tell application "Terminal" to activate'
	./webserv test_us/conf/webserv.conf

test_linux: test_setup
	@x-terminal-emulator --working-directory=$$(pwd) -x "./client"
	./webserv test_us/conf/webserv.conf

bocal: bocal_$(OS)

bocal_mac: all
	@mkdir -p YoupiBanane/put_here
	@osascript -e 'tell application "Terminal" to do script "cd $(PWD) && clear && time ./test_mac/macos_tester http://localhost:8000"'
	@osascript -e 'tell application "Terminal" to activate'
	./webserv test_mac/mac.conf

bocal_linux: all
	@mkdir -p YoupiBanane/put_here
	@x-terminal-emulator --working-directory=$$(pwd) -x "time ./test_linux/ubuntu_tester http://localhost:8000"
	./webserv test_linux/linux.conf

.PHONY: libft clean fclean re test test_setup test_mac test_linux bocal bocal_mac bocal_linux

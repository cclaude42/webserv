# ___COMPILATION___

CPP= c++
FLAGS= -Wall -Wextra -Werror -fsanitize=address
SRCS=	ConfigReader.cpp\
		ConfigHelperFunctions.cpp\
		Config.cpp\
		ConfigServer.cpp\
		RequestConfig.cpp\
		main.cpp

NAME= configParser
OBJS= ${SRCS:.cpp=.o}
INCLUDE_DIRS = -I . -I /Users/frthierr/studlife/webserv/includes/ -I /Users/frthierr/studlife/webserv/srcs/request -I /Users/frthierr/studlife/webserv/libft/includes


.cpp.o:
	@printf "${LIGHT_BLUE}=>	"
	${CPP} ${FLAGS} ${INCLUDE_DIRS} -c $< -o ${<:.cpp=.o}
	@printf "${NC}"

# ___COLORS___

GREEN=\033[0;32m
LIGHT_BLUE=\033[0;34m
RED=\033[0;31m
YELLOW=\033[0;33m
NC=\033[0m

all: ${NAME}

${NAME}: libft ${OBJS}
	@printf "=>	"
	${CPP} ${FLAGS} ${INCLUDE_DIRS} ../../libft/libft.a ${OBJS} -o ${NAME} -L ../../libft/ -lft
	@echo "${GREEN}✓ ${NAME} compiled${NC}"

libft:
	make -C ../../libft

start: all
	@./${NAME}

valgrind_start: all
	@valgrind --leak-check=full --show-leak-kinds=definite ./${NAME}

clean:
	make clean -C ../../libft
	@printf "${RED}X "
	rm -rf ${OBJS}
	@printf "${NC}"
	@echo "${GREEN}✓ ${NAME} clean${NC}"

fclean: clean
	make fclean -C ../../libft
	@printf "${RED}X "
	rm -rf ${NAME}
	@printf "${NC}"

re: fclean all

.PHONY: all clean fclean re start

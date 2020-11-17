# ___COMPILATION___

CPP= c++
FLAGS= -Wall -Wextra -Werror
SRCS=	ConfigReader.cpp\
		Config.cpp\
		ConfigServer.cpp\
		Location.cpp\
		RequestConfig.cpp\
		main.cpp

NAME= configParser
OBJS= ${SRCS:.cpp=.o}
INCLUDE_DIRS = -I .


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

${NAME}: ${OBJS}
	@printf "=>	"
	${CPP} ${FLAGS} ${INCLUDE_DIRS} ${OBJS} -o ${NAME}
	@echo "${GREEN}✓ ${NAME} compiled${NC}"

start: all
	@./${NAME}

valgrind_start: all
	@valgrind --leak-check=full --show-leak-kinds=definite ./${NAME}

clean:
	@printf "${RED}X "
	rm -rf ${OBJS}
	@printf "${NC}"
	@echo "${GREEN}✓ ${NAME} clean${NC}"

fclean: clean
	@printf "${RED}X "
	rm -rf ${NAME}
	@printf "${NC}"

re: fclean all

.PHONY: all clean fclean re start


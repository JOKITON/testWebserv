NAME = exec

SRCS = tcpServer.cpp main.cpp

FLAGS = -Wall -Wextra
CPP = c++

all: $(NAME)

$(NAME) : $(SRCS)
	$(CPP) $(SRCS) -o $(NAME)

fclean:
	rm $(NAME)

re: fclean all
NAME = conveyorBelt
CC = clang++
CFLAGS = -Wall -Wextra -Werror
STD = -std=c++11
ifdef DEV
	DEV_FLAGS = -g3 -fsanitize=address -D VERBOSE=true
	# DEV_FLAGS = -Wno-shadow
else
	DEV_FLAGS =
endif


FACTORY = Factory Factory_utils Factory_exceptions Factory_gettersSetters

SRCS =		main.cpp $(addprefix Factory/, $(addsuffix .cpp, $(FACTORY)))

OBJS = $(SRCS:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(STD) $(DEV_FLAGS) $(OBJS) -o $(NAME)

%.o: %.cpp
	$(CC) $(CFLAGS) $(STD) $(DEV_FLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)
fclean : clean
	rm -f $(NAME)
re: fclean all
.PHONY: all clean fclean re

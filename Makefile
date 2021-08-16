NAME = containers
CC = g++ -std=c++14
CXXFLAGS = -Wall -Wextra -Werror
OBJDIR = objects
SRCDIR = catch2tests

_SRCS = catch.cpp \
		main.cpp \
		list_tests.cpp \
		map_tests.cpp \
		queue_tests.cpp \
		stack_tests.cpp \
		vector_tests.cpp
SRCS = $(addprefix $(SRCDIR)/, $(_SRCS))

_OBJS = $(addprefix $(OBJDIR)/, $(notdir $(_SRCS)))
OBJS = $(_OBJS:.cpp=.o)

all: $(NAME)

objects/%.o: catch2tests/%.cpp
	@mkdir -p $(OBJDIR)
	$(CC) $(CXXFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	$(CC) $(CXXFLAGS) $(OBJS) -o $(NAME)

clean:
	@rm -rf $(OBJDIR)

fclean: clean
	@rm -rf $(NAME)

re: fclean all

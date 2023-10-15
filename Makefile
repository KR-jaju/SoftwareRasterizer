CXX = c++
CXXFLAGS = -Wall -Wextra -Werror -std=c++98
SRC = main.cpp
OBJ = $(SRC:.cpp=.o)
NAME = rasterizer
LIBMLX = ./mlx/libmlx.a
ADD = 

%.o : %.cpp
	$(CXX) $(CXXFLAGS) $(ADD) -I. -c -o $@ $<

all : $(NAME)

debug :
	make re ADD=-g

$(LIBMLX) :
	make -C ./mlx

$(NAME) : $(LIBMLX) $(OBJ)
	$(CXX) $(CXXFLAGS) $(LIBMLX) -framework OpenGL -framework AppKit $(OBJ) -o $(NAME)

clean :
	make -C ./mlx clean
	rm -rf $(OBJ)

fclean : clean
	rm -rf $(NAME)

re : fclean all
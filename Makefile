NAME = monazil_almilafat

CPPFLPAGS = -std=c++17 -lcurl
CC = c++
SRC = main.cpp download.cpp

RM = rm -rf $(NAME)

all: $(SRC)
	$(CC) $(CPPFLPAGS) $(SRC) -o $(NAME)

clean:
	@$(RM) $(NAME)
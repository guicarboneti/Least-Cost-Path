NAME	=	escolha
CC		=	gcc
CXX		=	g++
DEBUG		+=	-Wall
CFLAGS		+=	
CXXFLAGS	+=	-std=c++17

EXE			=	$(NAME)
CFILES		=	$(wildcard *.c)
CXXFILES	=	$(wildcard *.cpp)
OBJECTS		=	$(CFILES:.c=.o) $(CXXFILES:.cpp=.o)

all : escolha
	@echo "Building..."

escolha : conversor.cpp
	$(CXX) conversor.cpp $(CXXFLAGS) $(DEBUG) -o $@

primeira_imp : transmissao.c
	$(CC) transmissao.c $(CFLAGS) $(DEBUG) -o $@

menor_caminho : menor_caminho.cpp
	$(CXX) transmissao.c $(CXXFLAGS) $(DEBUG) -o $@

# $(EXE) : $(OBJECTS)
# 	$(LD) $^ $(CFLAGS) $(LDFLAGS) -o $@

# %.o : %.c
# 	$(CC) $(CFLAGS) -c $< -o $@

# %.o : %.cpp
# 	$(CXX) $(CXXFLAGS) -c $< -o $@

clean :	
	rm -rf escolha *.o

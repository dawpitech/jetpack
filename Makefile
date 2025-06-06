##
## EPITECH PROJECT, 2025
## Makefile
## File description:
## Makefile
##

CXX	:=	g++
CC	:=	gcc

CXXFLAGS	=	-std=c++20
CXXFLAGS	+=	-W
CXXFLAGS	+=	-Wall
CXXFLAGS	+=	-Wextra
CXXFLAGS	+=	-Wundef
CXXFLAGS	+=	-Wshadow
CXXFLAGS	+=	-Wunreachable-code
CXXFLAGS	+=	-pedantic
CXXFLAGS	+=	-iquote .
CXXFLAGS	+=	-iquote common
CXXFLAGS	+=	-MMD -MP
CXXFLAGS	+=	-lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
CXXFLAGS	+=	-DCAN_CLOSE

CFLAGS		=	-std=gnu11
CFLAGS		+=	-W
CFLAGS		+=	-Wall
CFLAGS		+=	-Wextra
CFLAGS		+=	-Wundef
CFLAGS		+=	-Wshadow
CFLAGS		+=	-Wunreachable-code
CFLAGS		+=	-Wmissing-prototypes
CFLAGS		+=	-pedantic
CFLAGS		+=	-iquote server/include
CFLAGS		+=	-iquote common
CFLAGS		+=	-MMD -MP

BDIR		=	.build

CLIENT_SRC	=	$(shell find client -name "*.cpp")
SERVER_SRC	=	$(shell find server/src -name "*.c")

CLIENT_OBJ	=	$(CLIENT_SRC:%.cpp=$(BDIR)/client/%.o)
SERVER_OBJ	=	$(SERVER_SRC:%.c=$(BDIR)/server/%.o)

CLIENT_NAME	=	jetpack_client
SERVER_NAME	=	jetpack_server

.DEFAULT_GOAL := all

.PHONY: all
all: client server

$(BDIR)/client/%.o: %.cpp
	@ mkdir -p $(dir $@)
	$(CXX) -o $@ -c $< $(CXXFLAGS)

$(BDIR)/server/%.o: %.c
	@ mkdir -p $(dir $@)
	$(CC) -o $@ -c $< $(CFLAGS)

client: $(CLIENT_OBJ)
	$(CXX) $^ $(CXXFLAGS) -o $(CLIENT_NAME)

server: $(SERVER_OBJ)
	$(CC) $^ $(CFLAGS) -o $(SERVER_NAME)

.PHONY: clean
clean:
	@ rm -rf $(BDIR)

.PHONY: fclean
fclean: clean
	@ rm -f $(CLIENT_NAME)
	@ rm -f $(SERVER_NAME)

.NOTPARALLEL: re
.PHONY: re
re: fclean all

-include $(CLIENT_OBJ:.o=.d)
-include $(SERVER_OBJ:.o=.d)

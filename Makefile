# NAME
# **************************************************************************** #
BINARY				= ircserv
BINARY_CLIENT		= client

# FILES
# **************************************************************************** #
SRCS				= main.cpp\
						Channel.cpp\
						Client.cpp\
						Server.cpp

SRCS_CLIENT			= main.cpp

MK					= Makefile

OBJS				=${addprefix ${OBJS_DIR}, ${SRCS:.cpp=.o}}
DEPS				=${addprefix ${OBJS_DIR}, ${SRCS:.cpp=.d}}

OBJS_CLIENT				=${addprefix ${OBJS_DIR_C}, ${SRCS_CLIENT:.cpp=.o}}
DEPS_CLIENT				=${addprefix ${OBJS_DIR_C}, ${SRCS_CLIENT:.cpp=.d}}

# DIRECTORY
# **************************************************************************** #
OBJS_DIR			= objs/
SRCS_DIR			= srcs/
INC_DIR				= inc

OBJS_DIR_C			= objsC/
SRCS_DIR_C			= srcsC/
INC_DIR_C			= incC

# COMPILATION
# **************************************************************************** #
LINK				= c++
CC					= c++ -c
DEPFLAGS			= -MMD -MP
CFLAGS				= -Wall -Wextra -Werror -std=c++98 -Wshadow -Wno-shadow 
RM					= rm -rf
INCLUDE				= -I $(INC_DIR)

# RULES
# **************************************************************************** #
all:	$(BINARY) $(BINARY_CLIENT)

$(OBJS_DIR)%.o:	$(SRCS_DIR)%.cpp $(MK)
					@mkdir -p $(dir $@)
					$(CC) $(CFLAGS) $(DEPFLAGS) $(INCLUDE) $< -o $@

$(BINARY): $(OBJS)
					$(LINK) $(CFLAGS) $(INCLUDE) -o $@ $^ $(LIBS)

$(OBJS_DIR_C)%.o:	$(SRCS_DIR_C)%.cpp $(MK)
					@mkdir -p $(dir $@)
					$(CC) $(CFLAGS) $(DEPFLAGS) $(INCLUDE) $< -o $@

$(BINARY_CLIENT): $(OBJS_CLIENT)
					$(LINK) $(CFLAGS) $(INCLUDE) -o $@ $^ $(LIBS)

clean:
					@$(RM) $(OBJS_DIR) $(OBJS_CLIENT)

fclean: clean
					@$(RM) $(BINARY) $(BINARY_CLIENT)

re: fclean all

-include ${DEPS}
-include ${DEPS_CLIENT}

.PHONY: all bonus clean fclean re
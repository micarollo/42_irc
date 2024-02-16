# NAME
# **************************************************************************** #
BINARY				= ircserv

# FILES
# **************************************************************************** #
SRCS				= main.cpp\
						Channel.cpp\
						Client.cpp\
						Server.cpp\
						Parser.cpp\
						Command.cpp\
						Executor.cpp\
						ErrorHandling.cpp\
						commands/user.cpp\
						commands/pass.cpp\
						commands/nick.cpp\
						commands/privmsg.cpp\
						commands/invite.cpp\
						commands/join.cpp\
						commands/part.cpp\
						commands/kick.cpp\
						commands/cap.cpp\
						commands/mode.cpp\
						commands/topic.cpp\
						commands/ping.cpp

MK					= Makefile

OBJS				=${addprefix ${OBJS_DIR}, ${SRCS:.cpp=.o}}
DEPS				=${addprefix ${OBJS_DIR}, ${SRCS:.cpp=.d}}

# DIRECTORY
# **************************************************************************** #
OBJS_DIR			= objs/
SRCS_DIR			= srcs/
INC_DIR				= inc

# COMPILATION
# **************************************************************************** #
LINK				= c++
CC					= c++ -c
DEPFLAGS			= -MMD -MP
CFLAGS				= -Wall -Wextra -Werror -Wshadow -Wno-shadow 
RM					= rm -rf
INCLUDE				= -I $(INC_DIR)

# RULES
# **************************************************************************** #
all:	$(BINARY)

$(OBJS_DIR)%.o:	$(SRCS_DIR)%.cpp $(MK)
					@mkdir -p $(dir $@)
					$(CC) $(CFLAGS) $(DEPFLAGS) $(INCLUDE) $< -o $@

$(BINARY): $(OBJS)
					$(LINK) $(CFLAGS) $(INCLUDE) -o $@ $^ $(LIBS)

clean:
					@$(RM) $(OBJS_DIR)

fclean: clean
					@$(RM) $(BINARY)

re: fclean all

-include ${DEPS}

.PHONY: all bonus clean fclean re
NAME = minitalk
SERVER = server
CLIENT = client

SRCS_SERVER = server.c utils.c
SRCS_CLIENT = client.c utils.c

OBJS_SERVER = $(SRCS_SERVER:.c=.o)
OBJS_CLIENT = $(SRCS_CLIENT:.c=.o)

CC = cc 
CFLAG = -Wall -Wextra -Werror
RM = rm -f

all: $(CLIENT) $(SERVER)

$(SERVER): $(OBJS_SERVER)
	$(CC) $(CFLAG) $(OBJS_SERVER) -o $(SERVER)

$(CLIENT): $(OBJS_CLIENT)
	$(CC) $(CFLAG) $(OBJS_CLIENT) -o $(CLIENT)

%.o: %.c
	$(CC) $(CFLAG) -c $< -o $@

clean:
	$(RM) $(OBJS_SERVER) $(OBJS_CLIENT)

fclean: clean
	$(RM) $(SERVER) $(CLIENT)

re: fclean all

.PHONY: all clean fclean re 
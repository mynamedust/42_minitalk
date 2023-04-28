# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: almeliky <almeliky@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/22 22:07:15 by almeliky          #+#    #+#              #
#    Updated: 2023/04/26 16:52:22 by almeliky         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SERVER			=	server

CLIENT			=	client

SERVER_b		=	server_bonus

CLIENT_b		=	client_bonus

SRCS_server		=	server.c

SRCS_client		=	client.c

SRCS_server_b	=	server_bonus.c

SRCS_client_b	=	client_bonus.c

OBJS_server		=	$(SRCS_server:%.c=%.o)

OBJS_client		=	$(SRCS_client:%.c=%.o)

OBJS_server_b	=	$(SRCS_server_b:%.c=%.o)

OBJS_client_b	=	$(SRCS_client_b:%.c=%.o)

CC				=	cc

CFLAGS			=	-Wall -Wextra -Werror

all: $(SERVER) $(CLIENT)

%.o : %.c
	$(CC) $(CFLAGS) -o $@ -c $<

$(SERVER): $(OBJS_server)
	$(CC) $(CFLAGS) $(OBJS_server) -o $(SERVER)

$(CLIENT): $(OBJS_client)
	$(CC) $(CFLAGS) $(OBJS_client) -o $(CLIENT)

clean:
	rm -rf $(OBJS_client) $(OBJS_client_b) $(OBJS_server) $(OBJS_server_b)

fclean:
	rm -rf $(OBJS_client) $(OBJS_client_b) $(OBJS_server) $(OBJS_server_b) $(SERVER) $(CLIENT) $(SERVER_b) $(CLIENT_b)

re: clean fclean all

bonus: $(SERVER_b) $(CLIENT_b)

$(SERVER_b): $(OBJS_server_b)
	$(CC) $(CFLAGS) $(OBJS_server_b) -o $(SERVER_b)

$(CLIENT_b): $(OBJS_client_b)
	$(CC) $(CFLAGS) $(OBJS_client_b) -o $(CLIENT_b)

.PHONY : all clean fclean bonus re
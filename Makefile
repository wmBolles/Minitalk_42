# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wabolles <wabolles@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/10 06:28:09 by wabolles          #+#    #+#              #
#    Updated: 2024/03/06 03:45:28 by wabolles         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CFLAGS = -Wall -Wextra -Werror
CC = cc
HEADER = includes/minitalk.h

################################## PRINTF ######################################

FMT = printf/fmt
ROOT = printf

FMT_FILES = $(FMT)/print_addr.c \
			$(FMT)/print_base.c \
			$(FMT)/print_cs.c   \
			$(FMT)/print_nbrs.c \
			$(FMT)/which_format.c

ROOT_FILES = $(ROOT)/ft_printf.c

PRINTF_FILES = $(ROOT) $(FMT)
PRINTF_OBJC = $(FMT_FILES:.c=.o) $(ROOT_FILES:.c=.o)

################################# MINITALK ####################################

SERVER = server
CLIENT = client

SERVER_BNS = server_bonus
CLIENT_BNS = client_bonus

SRV = mandatory/server.c garbage_collector/cleaner_at_destructor.c $(PRINTF_FILES)
CLT = mandatory/client.c garbage_collector/cleaner_at_destructor.c $(PRINTF_FILES)

SRV_OBJ = mandatory/server.o garbage_collector/cleaner_at_destructor.o $(PRINTF_OBJC)
CLT_OBJ = mandatory/client.o garbage_collector/cleaner_at_destructor.o $(PRINTF_OBJC)

SRV_BNS = bonus/advanced_server.c garbage_collector/cleaner_at_destructor.c $(PRINTF_FILES)
CLT_BNS = bonus/advanced_client.c garbage_collector/cleaner_at_destructor.c $(PRINTF_FILES)

SRV_BNS_OBJ = bonus/advanced_server.o garbage_collector/cleaner_at_destructor.o $(PRINTF_OBJC)
CLT_BNS_OBJ = bonus/advanced_client.o garbage_collector/cleaner_at_destructor.o $(PRINTF_OBJC)

all: $(SERVER) $(CLIENT)

$(SERVER): $(SRV_OBJ)
	@$(CC) $(CFLAGS) $(SRV_OBJ) -o $(SERVER)
$(CLIENT): $(CLT_OBJ)
	@$(CC) $(CFLAGS) $(CLT_OBJ) -o $(CLIENT)

$(SERVER_BNS): $(SRV_BNS_OBJ)
	@$(CC) $(CFLAGS) $(SRV_BNS_OBJ) -o $(SERVER_BNS)
$(CLIENT_BNS): $(CLT_BNS_OBJ)
	@$(CC) $(CFLAGS) $(CLT_BNS_OBJ) -o $(CLIENT_BNS)

bonus: fclean $(SERVER_BNS) $(CLIENT_BNS)

%.o: %.c $(HEADER)
	@$(CC) $(CFLAGS) -c -o $@ $<
	@echo "\033[1;34mCompile C file"

$(NAME):
	rm -f garbage_collector/cleaner_at_destructor.o

clean: $(NAME)
	@rm -rf $(SRV_BNS_OBJ) $(CLT_BNS_OBJ) $(SRV_OBJ) $(CLT_OBJ)
	@echo "\033[1;33mClean object files... ✅\033[1;0m"

fclean: clean
	@rm -rf	$(CLIENT) $(SERVER) $(CLIENT_BNS) $(SERVER_BNS)
	@echo "\033[1;33mClean executables... ✅\033[1;0m"

re: fclean all

.PHONY: clean
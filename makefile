NAME = server client

BONUS = server_bonus client_bonus

RM = rm -rf

CFLAGS = -Wall -Werror -Wextra

${NAME} : server.c client.c 
	cc ${CFLAGS}  client.c -o client
	cc ${CFLAGS}  server.c -o server
	@echo "donne"

${BONUS} : server_bonus.c client_bonus.c
	cc ${FLAGS} client_bonus.c -o client_bonus
	cc ${FLAGS} server_bonus.c -o server_bonus
	@echo "bonus is done"
 
all : ${NAME}

bonus : ${BONUS}

clean: 
	@${RM} ${NAME} ${BONUS}
	@echo "clean is done"
re: clean ${NAME}


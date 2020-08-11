CC=gcc
OBJ=server
all:
	$(CC) -o $(OBJ) *.h  pool.c server.c -lpthread -I/usr/include/mysql -L/usr/lib64/mysql -lmysqlclient -g
clean:
	rm -f *.o












#my_server: my_server.o my_chat.o
#	gcc my_server.o my_chat.o -o my_server
#my_server.o: my_server.c
#	gcc -c my_server.c
#my_chat.o: my_chat.c
#	gcc -c my_chat.c
#clean:
#	rm -f *.o

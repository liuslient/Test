CC=gcc
OBJ=server
all:
	$(CC) -o $(OBJ) *.h  pool.c server.c -lpthread -I/usr/include/mysql -L/usr/lib64/mysql -lmysqlclient -g
clean:
	rm -f *.o


#clean:
#	rm -f *.o

# Set the compiler and compiler flags
CC = gcc
CFLAGS = -I include -lws2_32 -fexec-charset=CP932

# Define the source and object files
CLIENT_SOURCE = tank_client.c
SERVER_SOURCE = tank_server.c
CLIENT_OBJECT = tank_client.o
SERVER_OBJECT = tank_server.o

# Build rules
all: tank_client tank_server

tank_client: $(CLIENT_OBJECT)
	$(CC) $(CLIENT_OBJECT) $(CFLAGS) -o tank_client

tank_server: $(SERVER_OBJECT)
	$(CC) $(SERVER_OBJECT) $(CFLAGS) -o tank_server

%.o: %.c
	$(CC) -c $< $(CFLAGS) -o $@

clean:
	rm -f tank_client tank_server $(CLIENT_OBJECT) $(SERVER_OBJECT)

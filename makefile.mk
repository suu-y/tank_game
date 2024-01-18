# Set the compiler and compiler flags
# copy this command: mingw32-make -f makefile.mk
CC = gcc
CFLAGS = -I include -lws2_32 -fexec-charset=CP932

# Define the source and object files
CLIENT_SOURCE = tank_client.c
CLIENT2_SOURCE = tank_client_cannon.c
CLIENT_OBJECT = tank_client.o
CLIENT2_OBJECT = tank_client_cannon.o

# Build rules
all: tank_client tank_client_cannon

tank_client: $(CLIENT_OBJECT)
	$(CC) $(CLIENT_OBJECT) $(CFLAGS) -o tank_client

tank_client_cannon: $(CLIENT2_OBJECT)
	$(CC) $(CLIENT2_OBJECT) $(CFLAGS) -o tank_client_cannon

%.o: %.c
	$(CC) -c $< $(CFLAGS) -o $@

clean:
	rm -f tank_client tank_client_cannon $(CLIENT_OBJECT) $(CLIENT2_OBJECT)

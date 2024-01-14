# copy this command: mingw32-make -f makefile.mk
# Set the compiler and compiler flags
CC = gcc
CFLAGS = -I include -lws2_32 -fexec-charset=CP932

# Define the source and object files
CLIENT_SOURCE = tank_client.c
CLIENT_OBJECT = tank_client.o

# Build rules
all: tank_client

tank_client: $(CLIENT_OBJECT)
	$(CC) $(CLIENT_OBJECT) $(CFLAGS) -o tank_client

%.o: %.c
	$(CC) -c $< $(CFLAGS) -o $@

clean:
	rm -f tank_client $(CLIENT_OBJECT)

CC = gcc
OUTPUT = builds/bot
CFLAGS = -Wall -c 
LFLAGS = -Wall -pthread -ldiscord -lcurl
INCLUDE = -I.
OBJDIR = objects
OBJECTS = $(OBJDIR)/ping.o $(OBJDIR)/timestamp.o $(OBJDIR)/slashy_ping.o

.SUFFIXES: .c .o

.PHONY: clean all

# .c.o: 
# 	$(CC) $(CFLAGS) $(INCLUDE) $< -o $(OBJDIR)/$@
# I still havent figured a proper use for the above rule

all: src/bot.c

builds/bot: src/commands/ping.c src/slash_commands/slashy_ping.c src/utils/timestamp.c 
	$(CC) src/bot.c $(INCLUDE) -o bot $(LFLAGS)
src/bot.c: $(OBJECTS)
	$(CC) src/bot.c $(INCLUDE) $(OBJECTS) -o $(OUTPUT) $(LFLAGS)


$(OBJDIR):
	mkdir -p $(OBJDIR)

$(OBJDIR)/ping.o: src/commands/ping.c include/apiPing.h
	$(CC) $(CFLAGS) $(INCLUDE) src/commands/ping.c -o objects/ping.o

$(OBJDIR)/timestamp.o: src/utils/timestamp.c include/timestamp.h
	$(CC) $(CFLAGS) $(INCLUDE) src/utils/timestamp.c -o objects/timestamp.o

$(OBJDIR)/slashy_ping.o: src/slash_commands/slashy_ping.c include/apiPing.h
	$(CC) $(CFLAGS) $(INCLUDE) src/slash_commands/slashy_ping.c -o objects/slashy_ping.o

clean:
	rm -f $(OUTPUT) $(OBJECTS)



## What exactly do -ldiscord and -lcurl do?
# -ldiscord is a flag that tells the linker to look for a library called "discord."
# the linker looks for these libraries in the /usr/lib/ directory, and,
# if it finds them, it links them into the binary.
# Here the linker finds /usr/local/lib/libdiscord.a through -ldiscord. 
# so, basically, a .a file is an "archive." I know that sounds dumb, but, back in the day,  
# you could actually use what we now call "C libraries" as backup files... really.   
# so, the linker just expands that archive file 
# (the same way that a tarfile would get expanded, or, Windows Explorer expanding a zipfile), and, 
# it reads all of the symbol tables in all of the objects in there. \ 
# one of those is gonna contain the function you're after, so, 
# the linker picks that object file and links it into the binary. 

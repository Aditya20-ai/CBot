build:
	gcc src/bot.c ping.o timestamp.o slashy_ping.o -o builds/bot -pthread -ldiscord -lcurl

clean:
	rm -rf builds/bot
	
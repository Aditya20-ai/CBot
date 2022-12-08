build:
	gcc src/bot.c ping.o timestamp.o -o builds/bot -pthread -ldiscord -lcurl

clean:
	rm -rf builds/bot
	
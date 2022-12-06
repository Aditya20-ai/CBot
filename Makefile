build:
	gcc src/bot.c -o builds/bot -pthread -ldiscord -lcurl

clean:
	rm -rf builds/bot




	
	
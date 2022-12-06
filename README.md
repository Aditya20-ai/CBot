# Self hosting CBot

## Prerequisites
* A Discord bot token
* Windows Subsystem for Linux (WSL) installed on your Windows system (Preferably Ubuntu 22.04 LTS)
* A C compiler (such as GCC) installed on your WSL system
* Install Concord library on your system. More instructions on that [here](https://github.com/Cogmasters/concord#setting-up-your-environment)  

* A text editor or IDE installed on your Windows system (Preferably VSCode with WSL extension)
### Step 1: Clone the bot repo
```
git clone https://github.com/Aditya20-ai/CBot.git
```

### Step 2: Rename config.json.example to config.json

* Fill in the required fields in config.json

### Step 3: Compile the bot 
* Run `make` in the root directory of the bot 
* If you get an error, try running `make clean` and then `make` again
* Then run `cd builds && ./bot` to start the bot


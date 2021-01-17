# 0.1 how to start with:
There are 3 options to control lights via this project:
1. The ESP32 will host a local webserver/webpage, which allows to control the lights via your brwoser.
2. A python-Bot for Discord will read commands, which were send to it via private chats and groups, and will try to send commands to the ESP32 via http.
3. A python-Bot for Telegram, which does the same as the Discord-Bot.

# 0.2 Hardware
I use 3 PNP Transistors to control a 12V LED-Stripe via the ESP32. Connect the transistors to the ESP-ports and to the LED-stripe cables.
Make shure that your ESP32 can power the transistors. 3 1ampere could not be powered, if the ESP32 has only e.g. 5V 2A


# 1. Webinterface on the ESP32
I flashed the ESP32 by using the Arduino IDE.
After the IDE is configured you can upload the Script


# 2. DiscordToESP32
The python script will run a Discord-Bot.
The py-script will send get()-requests to the esp32

# Run the Python script
First you'll need to install python3 and pip.
sudo apt-get install python3
sudo apt-get install python3-pip

Next you'll need to install discord.py
sudo pip install discord.py

# Discord API
To use the Discord API you'll need to sign in to discord.com/developers and create your Bot-Token.
Copy it to the python script

execute the Bot-script with python3


# 3. TelegramToESP32
The python script will run a Telegram-Bot.
The py-script will send get()-requests to the esp32

# Run the Python script
First you'll need to install python3 and pip.
sudo apt-get install python3
sudo apt-get install python3-pip

Next you'll need to install pyTelegramBotAPI
sudo pip install pyTelegramBotAPI

# Telegram API
To use the Telegram API you'll need to sign in to https://core.telegram.org/bots#botfather and create your Bot-Token.
Copy it to the python script

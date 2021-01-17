# DiscordToESP32
A way to Control some lights via Discord using python with discord.py and C on ESP32

The python script is needed to get commands via discord. Therefor it is needed to run a Discord-Bot.
Also the py-script will send get()-requests to the esp32, which executes a webserver (which can also be accessed in the network) and control a 12V LED-Strip
# Run the Python script
First you'll need to install python3 and pip.
sudo apt-get install python3
sudo apt-get install python3-pip

Next you'll need to install discord.py
sudo pip install discord.py

# Discord API
To use the Discord API you'll need to sign in to discord.com/developers and create your Bot-Token.
Copy it to the python script

# Run the C Script
I flashed the ESP32 by using the Arduino IDE.
After the IDE is configured you can upload the Script

# Hardware
I use 3 PNP Transistors to control the 12V LED-Stripes

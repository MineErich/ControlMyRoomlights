import discord
import requests
import time

ipESP = "YourIP"

def executer(eCommand):
	global deactivateLED
	print("received " + eCommand)
	if eCommand == "/off":
		deactivateLED = True
		requests.get(ipESP + "/off")
	else:
		requestLED(eCommand)

def requestLED(rColor):
	global deactivateLED
	if deactivateLED == False:
			requests.get(ipESP + rColor)
	else:
		deactivateLED = False
		requests.get(ipESP + "/on")
		time.sleep(1)
		requests.get(ipESP + rColor)


class MyClient(discord.Client):
	global deactivateLED
	deactivateLED = True
	#log in
	async def on_ready(self):
		print("client startet")
		if requests.get(ipESP).status_code == 200:
			print("Connected to ESP32")
		else:
			print("Network Error occurred: No Connection to ESP32")

	async def on_message(self, message):
		if message.author == client.user:
			return
		if message.content.lower() == "off":
			executer("/off")
			await message.channel.send ("deactivated LEDs")
		elif message.content.lower() == "red":
			executer("/re")
			await message.channel.send ("changed to red")
		elif message.content.lower() == "green":
			executer("/gr")
			await message.channel.send ("changed to green")
		elif message.content.lower() == "blue":
			executer("/bl")
			await message.channel.send ("changed to blue")
		elif message.content.lower() == "yellow":
			executer("/ye")
			await message.channel.send ("changed to yellow")
		elif message.content.lower() == "cyan":
			executer("/cy")
			await message.channel.send ("changed to cyan")
		elif message.content.lower() == "pink":
			executer("/pi")
			await message.channel.send ("changed to pink")
		elif message.content.lower() == "help":
			await message.channel.send("type red, green, blue, yellow, cyan or pink in the chat and the lights at fabians home will change color.")


client = MyClient()
client.run("YourToken")

import telebot
from telebot import types
import requests
import time

ipESP = "YourESPIP"
bot = telebot.TeleBot("YourTelebotID", parse_mode=None)

global deactivateLED
deactivateLED = True

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


@bot.message_handler(commands=['start'])
def send_welcome(message):
	markup = types.ReplyKeyboardMarkup()
	itembtnr = types.KeyboardButton('/red')
	itembtng = types.KeyboardButton('/green')
	itembtnb = types.KeyboardButton('/blue')
	itembtny = types.KeyboardButton('/yellow')
	itembtnc = types.KeyboardButton('/cyan')
	itembtnp = types.KeyboardButton('/pink')
	markup.row(itembtnr, itembtng, itembtnb)
	markup.row(itembtny, itembtnc, itembtnp)
	bot.reply_to(message, "Choose Color:", reply_markup=markup)
	
	
@bot.message_handler(commands=['help'])
def send_help(message):
	bot.reply_to(message, "send colors like /red, /green, /blue, /pink, /yellow or /cyan")

@bot.message_handler(commands=['off'])
def send_red(message):
	bot.reply_to(message, "turned off")
	bla = executer("/off")
	print("off")

@bot.message_handler(commands=['red'])
def send_red(message):
	bot.reply_to(message, "changed color")
	executer("/re")


@bot.message_handler(commands=['green'])
def send_green(message):
	bot.reply_to(message, "changed color")
	executer("/gr")

@bot.message_handler(commands=['blue'])
def send_blue(message):
	bot.reply_to(message, "changed color")
	executer("/bl")

@bot.message_handler(commands=['yellow'])
def send_yellow(message):
	bot.reply_to(message, "changed color")
	executer("/ye")

@bot.message_handler(commands=['cyan'])
def send_cyan(message):
	bot.reply_to(message, "changed color")
	executer("/cy")

@bot.message_handler(commands=['pink'])
def send_pink(message):
	bot.reply_to(message, "changed color")
	executer("/pi")


bot.polling()

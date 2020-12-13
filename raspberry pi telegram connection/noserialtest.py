import serial
import logging

from telegram import Update
from telegram.ext import Updater, CommandHandler, CallbackContext

port="/dev/ttyACM0"
serialFromArduino =serial.Serial(port,9600)
serialFromArduino.flushInput()
telegram_id = '1136975061'

while True:
    
    input_s =  serialFromArduino.readline()
    temp = int(input_s)
    print(temp)
    
    
    
def main():
    """Run bot."""
    # Create the Updater and pass it your bot's token.
    # Make sure to set use_context=True to use the new context based callbacks
    # Post version 12 this will no longer be necessary
    updater = Updater("1448411155:AAHxLlxCtNOIBnyeIRu3zyRPuQvVl3Fg6nU", use_context=True)

    # Get the dispatcher to register handlers
    dispatcher = updater.dispatcher

    # on different commands - answer in Telegram
    dispatcher.add_handler(CommandHandler("stat", stat))


    # Start the Bot
    updater.start_polling()

    # Block until you press Ctrl-C or the process receives SIGINT, SIGTERM or
    # SIGABRT. This should be used most of the time, since start_polling() is
    # non-blocking and will stop the bot gracefully.
    updater.idle()
    
    
def stat(update: Update, context: CallbackContext) -> None:
    update.message.reply_text('Hi! Use /set <seconds> to set a timer')
    
    
    

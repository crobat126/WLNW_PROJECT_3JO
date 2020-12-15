import serial  # serial 모듈 선언
import logging  # 로깅 모듈 선언

# 텔레그램 사용할 때 필요한 모듈들 선언
from telegram import Update
from telegram.ext import Updater, CommandHandler, CallbackContext

port = "/dev/ttyACM0"  # 아두이노 포트
serialFromArduino = serial.Serial(port, 9600)  # 아두이노 포트 9600번 사용
serialFromArduino.flushInput()  # 도착한 모든 바이트 읽기

token = "1448411155:AAHxLlxCtNOIBnyeIRu3zyRPuQvVl3Fg6nU"  # 텔레그램 토큰
input_s = ""
cmd = "sensorVal"  # 아두이노의 토양 수분 센서 값을 cmd라고 명칭함.

# Enable logging
logging.basicConfig(
    format='%(asctime)s - %(name)s - %(levelname)s - %(message)s', level=logging.INFO
)

logger = logging.getLogger(__name__)


# Define a few command handlers. These usually take the two arguments update and
# context. Error handlers also receive the raised TelegramError object in error.
def start(update: Update, context: CallbackContext) -> None:
    update.message.reply_text('Hi! Use /set <seconds> to set a timer')

def test(update: Update, context: CallbackContext) -> None:  # test라는 함수 선언
    update.message.reply_text('Checking...')  # 시작하자마자 checking이라는 text를 호출
    seri = serial.Serial(port, baudrate=9600, timeout=None)
    print(seri.name)

    seri.write(cmd.encode())
    flag = 1 # flag 1로 설정 (반복문 용)

    # 텔레그램으로 사용자에게 메세지 보내는 코드
    while flag:
        if seri.in_waiting != 0:
            content = seri.readline()
            text = content[:-2].decode()
            update.message.reply_text(text) # 토양 수분 센서로 얻은 수치 값 텔레그램으로 전송
            i_text = int(text)

            # 토양이 건조할 경우 (기준 600)
            if i_text > 600:
                text = "I'm Watering it now !" # 물이 필요하므로 물을 준다
            # 토양이 습할 경우 (기준 600)
            else:
                text = "Enough Water" # 물이 충분함

            update.message.reply_text(text) # 상황에 따른 메시지 텔레그램으로 전송
            flag = 0 # flag 0으로 설정하여 반복문 탈출


def alarm(context):
    """Send the alarm message."""
    job = context.job
    context.bot.send_message(job.context, text='Beep!')


def remove_job_if_exists(name, context):
    """Remove job with given name. Returns whether job was removed."""
    current_jobs = context.job_queue.get_jobs_by_name(name)
    if not current_jobs:
        return False
    for job in current_jobs:
        job.schedule_removal()
    return True


def set_timer(update: Update, context: CallbackContext) -> None:
    """Add a job to the queue."""
    chat_id = update.message.chat_id
    try:
        # args[0] should contain the time for the timer in seconds
        due = int(context.args[0])
        if due < 0:
            update.message.reply_text('Sorry we can not go back to future!')
            return

        job_removed = remove_job_if_exists(str(chat_id), context)
        context.job_queue.run_once(
            alarm, due, context=chat_id, name=str(chat_id))

        text = 'Timer successfully set!'
        if job_removed:
            text += ' Old one was removed.'
        update.message.reply_text(text)

    except (IndexError, ValueError):
        update.message.reply_text('Usage: /set <seconds>')


def unset(update: Update, context: CallbackContext) -> None:
    """Remove the job if the user changed their mind."""
    chat_id = update.message.chat_id
    job_removed = remove_job_if_exists(str(chat_id), context)
    text = 'Timer successfully cancelled!' if job_removed else 'You have no active timer.'
    update.message.reply_text(text)


def main():
    """Run bot."""
    updater = Updater(
        "1448411155:AAHxLlxCtNOIBnyeIRu3zyRPuQvVl3Fg6nU", use_context=True)

    # Get the dispatcher to register handlers
    dispatcher = updater.dispatcher

    # on different commands - answer in Telegram
    dispatcher.add_handler(CommandHandler("start", start))
    dispatcher.add_handler(CommandHandler("help", start))
    dispatcher.add_handler(CommandHandler("set", set_timer))
    # check라는 단어를 쓰면 위에 함수가 실행되게 선언.
    dispatcher.add_handler(CommandHandler("check", test))
    dispatcher.add_handler(CommandHandler("unset", unset))

    # Start the Bot
    updater.start_polling()

    # Block until you press Ctrl-C or the process receives SIGINT, SIGTERM or
    # SIGABRT. This should be used most of the time, since start_polling() is
    # non-blocking and will stop the bot gracefully.
    updater.idle()


if __name__ == '__main__':
    main()

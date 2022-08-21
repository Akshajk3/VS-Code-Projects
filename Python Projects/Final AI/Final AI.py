import imp
from traceback import print_tb
from neuralintents import GenericAssistant
import random
import speech_recognition
import sys
import pyttsx3 as tts
from tkinter import*
import pyglet
from datetime import datetime


recognizer = speech_recognition.Recognizer()
done = False
speaker = tts.init()
speaker.setProperty('rate', 150)

def greeting():
    greetings = ["Hello!", "Hello sir it is good to see you :)", "How are you doing?", "Hi it's been a while since I last saw you. How have you been doing?"]
    result = random.choice(greetings)
    print(result)
    speaker.say(result)
    speaker.runAndWait()

def goodbye():
    goodbyes = ["Bye", "I am sad to see you go :(", "See you later, have a greate day!", "Goodbye hope to see you soon!"]
    result = random.choice(goodbyes)
    print(result)
    speaker.say(result)
    speaker.runAndWait()
    exit()

def stocks():
    print("You own the following shares: ABBV, AAPL, FB, NVDA and an ETF of the S&P 500 Index!")
    speaker.say("You own the following shares: ABBV, AAPL, FB, NVDA and an ETF of the S&P 500 Index!")
    speaker.runAndWait()

def time():
    now = datetime.now()

    current_time = now.strftime("%H:%M:%S")
    print(f"The Current Time is {current_time}")
    speaker.say(f"The Current Time is {current_time}")
    speaker.runAndWait()


mappings = {
    'greeting': greeting,
    'goodbye': goodbye,
    'stocks': stocks,
    'time': time
}

assistant = GenericAssistant('chatbot.json', intent_methods=mappings)
assistant.train_model()
assistant.save_model()
assistant.load_model()

print("Bot is now currently running!")

while not done:
    try:
        with speech_recognition.Microphone() as mic:
            recognizer.adjust_for_ambient_noise(mic, duration=0.2)
            audio = recognizer.listen(mic)

            messages = recognizer.recognize_google(audio)
            messages = messages.lower()

        assistant.request(messages)

    except speech_recognition.UnknownValueError:
        recognizer = speech_recognition.Recognizer()

    if messages == "Stop":
        done = True
        
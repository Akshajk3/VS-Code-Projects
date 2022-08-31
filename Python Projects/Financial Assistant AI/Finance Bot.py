from neuralintents import GenericAssistant
import matplotlib as plt
import pandas as pd
import pandas_datareader as web
import mplfinance as mpf

import pickle
import sys
import datetime as dt
import random

portfolio = {'AAPL': 20, 'TSLA': 5, 'GS': 10}

with open('portfolio.pkl', 'rb') as f:
    portfolio = pickle.load(f)

print(portfolio)

def save_portfolio():
    with open('portfolio.pkl', 'wb') as f:
        pickle.dump(portfolio, f)

def add_portfolio():
    ticker = input("Which stock do you want to add: ")
    amount = int(input("How many shares do you want to add: "))
    if ticker in portfolio.keys():
        portfolio[ticker] += amount
    else:
        portfolio[ticker] = amount

    save_portfolio()

def remove_portfolio():
    ticker = input("Which stock do you want to sell: ")
    amount = int(input("How many stocks do you want to sell: "))
    if ticker in portfolio.keys():
        if amount <= portfolio[ticker]:
            portfolio[ticker] -= amount
            save_portfolio()
        else:
            print("Invalid: You dont own enough shares")
    else:
        print(f"Invalid: You dont any shares of {ticker}")
    
def show_portfolio():
    print("Your Portfolio:")
    for ticker in portfolio.keys():
        print(f"You own {portfolio[ticker]} shares of {ticker}")

def portfolio_worth():
    sum = 0
    shares = 0
    for ticker in portfolio.keys():
        shares += 1 
    for ticker in portfolio.keys():
        data = web.DataReader(ticker, 'yahoo')
        price = data['Close'].iloc[-1]
        sum += price * shares
        print(f"Your portfolio is worth {sum} USD")

def portfolio_gains():
    starting_date = input("Enter a date for comaprison (YYYY-MM-DD): ")

    sum_now = 0
    sum_then = 0

    try:
        for ticker in portfolio.keys():
            data = web.DataReader(ticker, 'yahoo')
            price_now = data['Close'].iloc[-1]
            price_then = data.location[data.index == starting_date]['Close'].values[0]
            sum_now += price_now
            sum_then += price_then

            print(f"Relative Gains: {((sum_now - sum_then)/sum_then) * 100}%")
            print(f"Absolute Gains: {sum_now - sum_then}USD")
    except IndexError:
        print("There was no trading on this day!")

def plot_chart():
    ticker = input("Chose a ticker symbol: ")
    starting_string = input("Chose a starting date (DD/MM/YYYY): ")

    plt.style.use('dark_background')
    start = dt.datetime.strptime(starting_string, "%d/%m/%Y")
    end = dt.datetime.now()

    data = web.DataReader(ticker, 'yahoo', start, end)

    colors = mpf.make_marketcolors(up='#00ff00', down='#ff0000', wick='inherit', edge='inherit', volume='in')
    mpf_style = mpf.make_mpf_style(base_mpf_style='nightclouds', marketcolors=colors)
    mpf.plot(data, type='candle', style=mpf_style, volume=True)





def bye():
    print("Goodbye")
    sys.exit(0)

mappings = {
    'plot_chart': plot_chart,
    'add_portfolio': add_portfolio,
    'remove_portfolio': remove_portfolio,
    'show_portfolio': show_portfolio,
    'portfolio_worth': portfolio_worth,
    'portfolio_gains': portfolio_gains,
    'goodbye': bye
}

assistant = GenericAssistant('finance_bot.json', mappings, "Financial_Assistant_Model")

assistant.train_model()
assistant.save_model()

while True:
    message = input("Enter a command: ")
    assistant.request(message)
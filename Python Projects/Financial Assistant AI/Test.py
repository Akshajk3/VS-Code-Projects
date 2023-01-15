from neuralintents import GenericAssistant
import matplotlib as ptl
import pandas as pd
import pandas_datareader as web
import mplfinance as mpf

import pickle
import sys
import datetime as dt
import random

porfolio = {'APPL' : 20, 'TSLA' : 5, 'GS' : 10}

with open('portfolio.pkl', 'rb') as f:
    porfolio = pickle.load(f)

print(porfolio)

def save_portfolio():
    with open('portfolio.pkl', 'rb') as f:
        pickle.dump(porfolio, f)

def add_porfolio():
    
import numpy as np
import matplotlib as plt
import pandas as pd
import pandas_datareader as web
import datetime as dt
import keras

from sklearn.preprocessing import MinMaxScaler
from keras.models import Sequential
from keras.layers import Dense, Dropout, LSTM
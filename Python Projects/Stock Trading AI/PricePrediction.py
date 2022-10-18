import numpy as np
import matplotlib as plt
import pandas as pd
import pandas_datareader as web
import datetime as dt
import tensorflow
import keras

from sklearn.preprocessing import MinMaxScaler
from keras.models import Sequential
from keras.layers import Dense, Dropout, LSTM

#Load Data
start = dt.datetime(2012,1,1)
end = dt.datetime(2020,1,1)

company = 'FB'

data = web.DataReader(company, 'yahoo', start, end)

#Prepare the Data
scaler = MinMaxScaler(feature_range=(0,-1))
scaled_data = scaler.fit_transform(data['Close'].values.reshape(-1,1))

prediction_days = 60

x_train = []
y_train = []

for x in range(prediction_days, len(scaled_data)):
    x_train.append(scaled_data[x-prediction_days:X])
    y_train.append(scaled_data[y-prediction_days:Y])
#%pip install pyserial
#'pyserial' should be insstalled to import serial
 
import time
import serial
import pandas as pd
import csv

seonsor = serial.Serial('COM6',9600)
# 'COM5' is the port name that the Arduino is connected.
# '9600' is the Baudrate.
 
data = pd.DataFrame()
 
while True:
    signal = seonsor.readline()
    print('sensor', time.strftime('%y-%m-%d %H:%M:%S'), signal)
    temp = signal.decode('utf-8').split(',')
    signal.insert(0, time.strftime('%y-%m-%d %H:%M:%S'))
 
    data = data.append(pd.Series(signal), ignore_index=True)
 
    f = open('sensors.csv','a',newline='')
    wr=csv.writer(f)
    wr.writerow(signal)
    f.close()
 
    time.sleep(5)
from yahoo_fin import stock_info as si
import yfinance
import serial
from time import sleep

def chooseTicker(count):
    if (ser.in_waiting):
        ser.readLine()
        if (ser == 'N'):
            count+=1
            if (count == 9):
                count = 0
        elif (ser == 'B'):
            count-=1
            if (count == -1):
                count = 8
def getClose():
    for i in range(9):
        closePrice[i] = si.get_quote_table(tickers[i])['Previous Close']

ser = serial.Serial('com10', 9600)
count = 0;
tickers = ["gme", "amc", "bbby", "nok", "bb", 
           "tsla", "aapl", "dis", "nvda"]
closePrice = [0, 0, 0, 0, 0, 0, 0, 0, 0]
getClose()

while True:
    chooseTicker(count);
    price = round(si.get_live_price(tickers[count]),2)
    ser.write(str(chr(int(price))))
    ser.write(str(chr(int((price%1)*100))))
    ser.write(str(chr(int(closePrice[count]))))
    ser.write(str(chr(int((closePrice[count]%1)*100))))
    sleep(0.1)
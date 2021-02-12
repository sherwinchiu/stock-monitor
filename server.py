from yahoo_fin import stock_info as si
import serial
from time import sleep

ser = serial.Serial('com10', 9600)
while True:
    price = round(si.get_live_price("gme"),2)
    ser.write(str(chr(int(price))))
    ser.write(str(chr(int((price%1)*100))))
    sleep(0.1)
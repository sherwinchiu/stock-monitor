from yahoo_fin import stock_info as si
import serial
import time

ArduinoUnoSerial = serial.Serial('com10', 9600)

print (ArduinoUnoSerial.readline())

print(round(si.get_live_price("gme"),2))
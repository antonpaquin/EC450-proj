#LMAOO

import RPi.GPIO as GPIO
import time

GPIO.setmode(GPIO.BOARD)

CLK = 23
MOSI = 19
MISO = 21
SSEL = 24

GPIO.setup(CLK, GPIO.OUT)
GPIO.setup(MOSI, GPIO.OUT)
GPIO.setup(SSEL, GPIO.OUT)
GPIO.setup(MISO, GPIO.IN)

GPIO.output(SSEL, 1)
GPIO.output(CLK, 0)

def write_byte(data):
    GPIO.output(SSEL, 0)
    for i in range(8):
        bit = data % 2
        data = data // 2
        GPIO.output(MOSI, bit)
        GPIO.output(CLK, 1)
        #time.sleep(0.01)
        GPIO.output(CLK, 0)
        #time.sleep(0.01)

    GPIO.output(SSEL, 1)

def gpio_close():
    GPIO.cleanup()

#!/usr/bin/env python3

import glob
import serial
import time
import subprocess

def wait_for_ttyusb():
    while True:
        ports = glob.glob('/dev/ttyUSB*')
        if ports:
            print(f"Serial port(s) detected: {ports}")
            return ports[0]
        print("No serial ports detected. Waiting for 5 seconds...")
        time.sleep(5)

port = wait_for_ttyusb()
baudrate = 9600
locked = False
try:
    ser = serial.Serial(port, baudrate, timeout=1)
    print(f"Reading from{port}...")

    while True:
        if ser.in_waiting > 0:
            data = ser.read(1).decode('utf-8')
            print(f"Recieved: {data}")
            if data == "1":
                if locked == True:
                    subprocess.Popen(["pkill", "-usr1", "hyprlock"])
                    ser.reset_input_buffer()
                    locked = False
                    time.sleep(2)
                    ser.reset_input_buffer()
                else:
                    subprocess.Popen(["hyprctl", "--instance",  "0",  "dispatch",  "exec", "hyprlock"])
                    ser.reset_input_buffer()
                    locked = True
                    time.sleep(2)
                    ser.reset_input_buffer()

except serial.SerialException as e:
    print(f"Error: {e}")
except KeyboardInterrupt:
    print("\nBye bye...")
    ser.close()



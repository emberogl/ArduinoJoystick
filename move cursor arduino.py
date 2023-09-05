import threading
import serial
import pyautogui
import time
from datetime import datetime

# Assignment to port Arduino is using
ser = serial.Serial('COM3', 9600)
ser.flushInput()
time.sleep(2)
x, y = 0, 0
buttonState = 0

# Reading port to retrieve position and button data and assigning to variables
def read_serial():
    global x, y, buttonState
    while True:
            data = ser.readline().decode().strip().split(',')
            if len(data) == 3:
                x, y, buttonState = map(int, data)

# Moving Windows cursor by incrementing the cursor position with the joystick using pyautogui
def move_cursor():
    global x, y, buttonState
    while True:
        print(x,y,buttonState)
        x_scaled = -((x - 512) / 10) # Scaling factor for sensitivity
        y_scaled = -((y - 512) / 10)
        cur_x, cur_y = pyautogui.position()
        pyautogui.moveTo(cur_x + x_scaled, cur_y - y_scaled)

        if buttonState == 0:
            pyautogui.click()

# Appends argument to file output.txt
def write_to_file(message):
     with open("output.txt", "a") as file:
        file.write(message + "\n")

# Initial messages before reading serial
write_to_file(f"Started logging on {datetime.today()}")
write_to_file(f"Listening on {ser.port}")

# Checks port buffer then writes the data to output.txt
def read_from_port():
     while True:
          if ser.in_waiting > 0:
               global x, y, buttonState
               write_to_file("Received: " + f"X: {x}, Y: {y}, Button: {buttonState} " + "at " + str(datetime.now()))

# Creating threads to independently read from port and move cursor from that retrieved data, and append to file
t1 = threading.Thread(target=read_serial)
t2 = threading.Thread(target=move_cursor)
t3 = threading.Thread(target=read_from_port)

# Start threads
t1.start()
t2.start()
t3.start()
import getch
import sys
import serial
import time
ser = serial.Serial("/dev/serial0", 115200)
while True:
	data = [0,0,0]
	val = getch()
	if val == 'w':
		data = [1,0,0]
	elif val == 's':
		data = [-1,0,0]
	elif val == 'a':
		data = [0,-1,0]
	elif val == 'd':
		data = [0,1,0]
	elif val == 'j':
		data = [0,0,1]
	elif val == 'l':
		data = [0,0,-1]
	else:
		exit()
	ser.write(b"s\n")
	ser.write(f"{data[0]}\n".encode())
	ser.write(f"{data[1]}\n".encode())
	ser.write(f"{data[2]}\n".encode())
	print(data)
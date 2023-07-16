import serial
import struct
import time
# Connect to Arduino using the appropriate serial port and baud rate
usb_port = 'COM4'  # Choose the port to interrogate
baud_rate = 115200  # Baud rate for Arduino communication
ser = serial.Serial(usb_port, baud_rate, timeout=0.1)  # Serial communication between the Arduino board and the computer
time.sleep(2)  # Wait until Arduino has beeen connected

# Generate an array of float numbers
numbers = [1.23, 4.56, 1.00, -5.32]  # Numbers that we want to do a sum
arraySize = len(numbers)

# Send the array size to Arduino
ser.write(struct.pack('<H', arraySize))  # Assuming arraySize is less than or equal to 65535

# Convert float numbers to bytes and send them to Arduino
ser.write(struct.pack('<' + 'f' * arraySize, *numbers))

# Wait for the Arduino to process the numbers and receive the sum
sum = ser.readline().decode().strip()

print(f"Sum received from Arduino: {sum}")
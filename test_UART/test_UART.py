import serial
import time

# Open serial port (replace 'COMx' with your port, e.g., 'COM3' for Windows or '/dev/ttyUSB0' for Linux/macOS)
ser = serial.Serial('/dev/ttyUSB1', baudrate=115200, timeout=1)  # Adjust COM port and baudrate accordingly

def send_data(message):
    # Send data to ESP32
    ser.write(message.encode('utf-8'))  # Encode the string into bytes and send it
    print(f"Sent: {message.strip()}")  # Strip trailing newlines for better output formatting

def receive_data():
    # Check if there is data waiting to be read
    if ser.in_waiting > 0:
        while(ser.in_waiting > 0):
            # Read available data from ESP32
            received_data = ser.readline().decode('utf-8').strip()  # Read a line, decode it, and strip extra spaces/newlines
            if received_data:
                print(f"Received: {received_data}")

def run():
    while(True):
        print("send 'Start' to turn ON the led")
        print("send 'Stop' to turn OFF the led")
        send_data(input("enter your command : "))
        time.sleep(0.5)
        receive_data()

def main():
    try:
            run()
    except KeyboardInterrupt:
        print("Program interrupted by user")
    finally:
        ser.close()  # Close the serial port when done

if __name__ == "__main__":
    main()

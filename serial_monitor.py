import serial

with serial.Serial("COM8", 115200, timeout=1) as board:
    print("STM32 Connected")

    while True:
        data = board.readline()

        if data:
            print(data.decode("ascii", errors="replace").strip())

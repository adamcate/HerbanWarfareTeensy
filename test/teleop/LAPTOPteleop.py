# # THIS CODE SENDS ARROW KEY COMMANDS -> PI -> TEENSY

import socket
import msvcrt
import time

#PI_IP = "10.24.239.209" ## SCHOOL IP
PI_IP = "192.168.7.172" ## HOME IP
PI_PORT = 5005

current_cmd = "STOP"
last_sent = 0
SEND_INTERVAL = 0.2

sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

print("Arrow keys to drive, Q to quit")

while True:
    if msvcrt.kbhit():
        key = msvcrt.getch()

        if key == b'q':
            break
        elif key == b'H':
            current_cmd = "FWD"
        elif key == b'P':
            current_cmd = "REV"
        elif key == b'K':
            current_cmd = "LEFT"
        elif key == b'M':
            current_cmd = "RIGHT"
        elif key == b' ':
            current_cmd = "STOP"
        print(current_cmd)



    if time.time() - last_sent > SEND_INTERVAL:
        sock.sendto(current_cmd.encode(), (PI_IP, PI_PORT))
        last_sent = time.time()

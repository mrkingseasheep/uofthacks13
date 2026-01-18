import keyboard
import serial
# import antigravity
import time



alphanumeric = 'abcdefghijklmnopqrstuvwxyz1234567890-=[];\'<>/`\\' # 48 characters to make a 4x4x3 matrix (right key is omitted on last)

port = serial.Serial('COM8', 9600, timeout=0.1) # port to read from

press_to_key = [
    [[1,2,3],[4,5,6],[7,8,9],[10,11,12]],
    [[13,14,15],[16,17,18],[19,20,21],[22,23,24]],
    [[25,26,27],[28,29,30],[31,32,33],[34,35,36]],
    [[37,38,39],[40,41,42],[43,44,45],[46,47,48]]
] # our matrix

def toIndex(ind): # quick converter
    if ind == 'UP':
        return 0
    elif ind == "DOWN":
        return 1
    elif ind == "LEFT":
        return 2
    elif ind == "RIGHT":
        return 3 

# keys to record
key_one = None
key_two = None
key_three = None
key_four = None

# reset keys
def clear():
    key_one = None
    key_two = None
    key_three = None
    key_four = None

# read and clear the key inputs
def parse():
    if key_one == "DOWN":
        keyboard.press_and_release('backspace')
        clear()
    elif key_one == "UP":
        base = 'shift + '
        return
    elif key_one == "RIGHT":
        keyboard.press_and_release('enter')
        clear()
        return
    elif key_one == "LEFT":
        base = ''
    if not key_two or not key_three or not key_four: 
        clear() 
        return
    if key_four == "RIGHT":
        clear()
        return
    keyboard.press_and_release(press_to_key[toIndex(key_two)][toIndex(key_three)][toIndex(key_four)])
    clear()
    return

# add the next input on the list
def addInput(input):
    if input == "RIGHT" or "DOWN":
        parse()
    if not key_one:
        key_one = input
    elif not key_two:
        key_two = input
    elif not key_three:
        key_three = input
    elif not key_four:
        key_four = input
        parse()

# loopread the port
while True:
    data = port.readline().decode().strip()
    if data:
        print(data)
        time.sleep(0.1)

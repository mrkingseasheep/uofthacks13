import serial
import time
import keyboard 

# -------- CONFIG --------
PORT = "/dev/tty.usbmodem2101"  # replace with your serial port
BAUD = 9600
TIMEOUT_MS = 2000      # reset sequence after 2 seconds
SEQ_LEN = 2            # using 2-input sequences

# -------- KEYBOARD MAPPING --------
SEQ_TO_CHAR = {
    # A–H (UP first)
    ("UP", "UP"): "a",
    ("UP", "RIGHT"): "b",
    ("UP", "DOWN"): "c",
    ("UP", "LEFT"): "d",
    ("UP", "UP-RIGHT"): "e",
    ("UP", "DOWN-RIGHT"): "f",
    ("UP", "DOWN-LEFT"): "g",
    ("UP", "UP-LEFT"): "h",

    # I–P (RIGHT first)
    ("RIGHT", "UP"): "i",
    ("RIGHT", "RIGHT"): "j",
    ("RIGHT", "DOWN"): "k",
    ("RIGHT", "LEFT"): "l",
    ("RIGHT", "UP-RIGHT"): "m",
    ("RIGHT", "DOWN-RIGHT"): "n",
    ("RIGHT", "DOWN-LEFT"): "o",
    ("RIGHT", "UP-LEFT"): "p",

    # Q–X (DOWN first)
    ("DOWN", "UP"): "q",
    ("DOWN", "RIGHT"): "r",
    ("DOWN", "DOWN"): "s",
    ("DOWN", "LEFT"): "t",
    ("DOWN", "UP-RIGHT"): "u",
    ("DOWN", "DOWN-RIGHT"): "v",
    ("DOWN", "DOWN-LEFT"): "w",
    ("DOWN", "UP-LEFT"): "x",

    # Y–Z (LEFT first)
    ("LEFT", "UP"): "y",
    ("LEFT", "RIGHT"): "z",   

    # Special
    ("LEFT-RIGHT", "UP"): " ",
    ("LEFT-RIGHT", "DOWN"): ".",
}

# -------- STATE --------
sequence = []
last_input_time = None

# -------- SERIAL --------
ser = serial.Serial(PORT, BAUD, timeout=0.1)
print("Listening on serial...")

while True:
    line = ser.readline().decode(errors="ignore").strip()
    now = time.time() * 1000  # ms

    if not line:
        continue

    # ignore Arduino boot message
    if line == "System up":
        continue

    # reset sequence if timeout exceeded
    if last_input_time is not None and now - last_input_time > TIMEOUT_MS:
        sequence.clear()

    last_input_time = now
    sequence.append(line)

    print("Sequence:", sequence)  # optional debug

    # check completion
    if len(sequence) == SEQ_LEN:
        key = tuple(sequence)
        char = SEQ_TO_CHAR.get(key)

        if char is not None:
            keyboard.write(char)  # type it on your computer
            print(f"Typed: {repr(char)}")
        else:
            print("Unknown sequence:", key)

        sequence.clear()

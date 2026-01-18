int LIGHT = 21;
int UP = 0;
int DOWN = 1;
int LEFT = 3;
int RIGHT = 2;

// track if buttons are currently held
bool buttonHeld = false;

// buffer time for diagonals
const unsigned long bufferTime = 50;

void setup() {
  Serial.begin(9600);
  Serial.println("System up");

  pinMode(UP, INPUT_PULLUP);
  pinMode(DOWN, INPUT_PULLUP);
  pinMode(LEFT, INPUT_PULLUP);
  pinMode(RIGHT, INPUT_PULLUP);
  pinMode(LIGHT, OUTPUT);
}

void loop() {
  // read button states
  bool up = digitalRead(UP) == LOW;
  bool down = digitalRead(DOWN) == LOW;
  bool left = digitalRead(LEFT) == LOW;
  bool right = digitalRead(RIGHT) == LOW;

  bool anyPressed = up || down || left || right;

  // only trigger when not already held
  if (anyPressed && !buttonHeld) {
    buttonHeld = true;       // mark buttons as held
    delay(bufferTime);       // small buffer to combine diagonals

    // re-read after buffer
    up = digitalRead(UP) == LOW;
    down = digitalRead(DOWN) == LOW;
    left = digitalRead(LEFT) == LOW;
    right = digitalRead(RIGHT) == LOW;

    // CANONICAL ORDER: UP → DOWN → LEFT → RIGHT
    String direction = "";
    if (up) direction += "UP";
    if (down) {
      if (direction.length()) direction += "-";
      direction += "DOWN";
    }
    if (left) {
      if (direction.length()) direction += "-";
      direction += "LEFT";
    }
    if (right) {
      if (direction.length()) direction += "-";
      direction += "RIGHT";
    }

    if (direction.length()) {
      Serial.println(direction);
      digitalWrite(LIGHT, HIGH);
    }

    // wait here until all buttons are released
    while (digitalRead(UP) == LOW || digitalRead(DOWN) == LOW ||
           digitalRead(LEFT) == LOW || digitalRead(RIGHT) == LOW) {
      // do nothing
    }

    digitalWrite(LIGHT, LOW);
    buttonHeld = false; // ready for next press
  }
}


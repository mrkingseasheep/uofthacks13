int LIGHT = 21;
int UP = 0;
int DOWN = 1;
int LEFT = 3;
int RIGHT = 2;

// previous states
bool prevUp = false;
bool prevDown = false;
bool prevLeft = false;
bool prevRight = false;

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
  bool up = digitalRead(UP) == LOW;
  bool down = digitalRead(DOWN) == LOW;
  bool left = digitalRead(LEFT) == LOW;
  bool right = digitalRead(RIGHT) == LOW;

  bool pressedNow =
    (up && !prevUp) ||
    (down && !prevDown) ||
    (left && !prevLeft) ||
    (right && !prevRight);

  if (pressedNow) {
    delay(bufferTime);

    // re-read after buffer
    up = digitalRead(UP) == LOW;
    down = digitalRead(DOWN) == LOW;
    left = digitalRead(LEFT) == LOW;
    right = digitalRead(RIGHT) == LOW;

    String direction = "";

    // CANONICAL ORDER (never changes)
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
  }

  if (!up && !down && !left && !right) {
    digitalWrite(LIGHT, LOW);
  }

  prevUp = up;
  prevDown = down;
  prevLeft = left;
  prevRight = right;
}


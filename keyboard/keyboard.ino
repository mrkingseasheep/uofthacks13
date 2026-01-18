  int LIGHT = 21;
  int UP = 0;
  int DOWN = 1;
  int LEFT = 2;
  int RIGHT = 3;

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
  if (digitalRead(DOWN) == LOW) {
    Serial.println("DOWN");
    digitalWrite(LIGHT, HIGH);
  } else if (digitalRead(UP) == LOW) {
    Serial.println("UP");
    digitalWrite(LIGHT, HIGH);
  } else if (digitalRead(LEFT) == LOW) {
    Serial.println("LEFT");
    digitalWrite(LIGHT, HIGH);
  } else if (digitalRead(RIGHT) == LOW) {
    Serial.println("RIGHT");
    digitalWrite(LIGHT, HIGH);
  } else {
    digitalWrite(LIGHT, LOW);
  }
}
int LIGHT = 21;
int UP = 0;
int RIGHT = 1;
int DOWN = 2;
int LEFT = 3;
int BUFF_TIME_MS = 500;
unsigned long click_init_ms = 0;
bool held_down[] = {false, false, false, false};
bool clicked_in_period[] = {false, false, false, false};
bool pressed = false;
bool first_press = true;

void setup() {
  Serial.begin(9600);
  Serial.println("System up");
  pinMode(UP, INPUT_PULLUP);
  pinMode(RIGHT, INPUT_PULLUP);
  pinMode(DOWN, INPUT_PULLUP);
  pinMode(LEFT, INPUT_PULLUP);
  pinMode(LIGHT, OUTPUT);
}

void button_pressed(int dir) {
  if (!held_down[dir]) {
    pressed = true;
    held_down[dir] = true;
    clicked_in_period[dir] = true;
    digitalWrite(LIGHT, HIGH);
  }
}

void loop() {
  digitalWrite(LIGHT, LOW);
  if (digitalRead(UP) == LOW) {
    button_pressed(0);
  } else {
    held_down[0] = false;
    digitalWrite(LIGHT, HIGH);
  }

  if (digitalRead(RIGHT) == LOW) {
    button_pressed(1);
  } else {
    held_down[1] = false;
  }

  if (digitalRead(DOWN) == LOW) {
    button_pressed(2);
  } else {
    held_down[2] = false;
  }

  if (digitalRead(LEFT) == LOW) {
    button_pressed(3);
  } else {
    held_down[3] = false;
  }

  if (millis() > click_init_ms + BUFF_TIME_MS) {
    if (clicked_in_period[0]) {
      Serial.println("UP");
    }
    if (clicked_in_period[1]) {
      Serial.println("DOWN");
    }
    first_press = true;
    for (int i = 0; i < 4; i++) {
      clicked_in_period[i] = false;
    }
  }

  if (pressed && first_press) {
    click_init_ms = millis();
    first_press = false;
    for (int i = 0; i < 4; i++) {
      clicked_in_period[i] = false;
    }
  }
}
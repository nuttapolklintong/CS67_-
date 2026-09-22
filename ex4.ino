const int PIN_RED   = 8;
const int PIN_GREEN = 9;
const int PIN_BLUE  = 10;

const unsigned long BLINK_ON  = 200;
const unsigned long BLINK_OFF = 200;
const unsigned long PAUSE_TIME = 1000;

struct BlinkLED {
  int pin;
  int totalBlinks;
  int currentBlink;
  bool ledState;
  bool isPausing;
  unsigned long lastChangeTime;
};

BlinkLED greenLED = {PIN_GREEN, 2, 0, false, false, 0};
BlinkLED blueLED  = {PIN_BLUE,  3, 0, false, false, 0};

void setup() {
  pinMode(PIN_RED, OUTPUT);
  pinMode(PIN_GREEN, OUTPUT);
  pinMode(PIN_BLUE, OUTPUT);

  digitalWrite(PIN_RED, HIGH);
  digitalWrite(PIN_GREEN, LOW);
  digitalWrite(PIN_BLUE, LOW);
}

void updateBlink(BlinkLED &led) {
  unsigned long now = millis();

  if (led.isPausing) {
    if (now - led.lastChangeTime >= PAUSE_TIME) {
      led.isPausing = false;
      led.currentBlink = 0;
      led.lastChangeTime = now;
    }
    return;
  }

  if (led.ledState) {
    if (now - led.lastChangeTime >= BLINK_ON) {
      digitalWrite(led.pin, LOW);
      led.ledState = false;
      led.lastChangeTime = now;
      led.currentBlink++;

      if (led.currentBlink >= led.totalBlinks) {
        led.isPausing = true;
      }
    }
  } else {
    if (led.isPausing) return;
    if (now - led.lastChangeTime >= BLINK_OFF) {
      digitalWrite(led.pin, HIGH);
      led.ledState = true;
      led.lastChangeTime = now;
    }
  }
}

void loop() {
  updateBlink(greenLED);
  updateBlink(blueLED);
}
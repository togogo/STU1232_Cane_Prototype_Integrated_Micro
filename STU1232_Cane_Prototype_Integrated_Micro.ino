#define LED_PIN 13
#define LED 9

int brightness = 0;
int fadeAmount = 5;

void setup() {
  // put your setup code here, to run once:

  pinMode(LED, OUTPUT);//for led

}

void loop() {
  // put your main code here, to run repeatedly:

  //for the white led...could be refined.
  analogWrite(LED, brightness);
  brightness = brightness + fadeAmount;
  if (brightness <= 0 || brightness >= 255) {
    fadeAmount = -fadeAmount;
  }

}

const int pin[3] = {
  7, 8, 9};  // pin number mortor
const int MEAN = 3;
int o_val[2] = {
  0, 0};  // old value mortor
int r_val = 0;  // resistance value mortor
int dir = 0;  // stop: 0, forward: 1, reverse: -1
int SPEED = 220;

void setup() {
  pinMode(pin[0], OUTPUT);
  pinMode(pin[1], OUTPUT);
  Serial.begin(9600);

  //establishContact();
}

void loop() {
  Serial.flush();
  r_val = analogRead(0);

  if(Serial.available() > 0) {
    dir = Serial.read();
  }
  if(dir == 0){
    digitalWrite(pin[0], LOW);
    digitalWrite(pin[1], LOW);
  }
  else if(dir == 1){
    //analogWrite(pin[2], SPEED);
    digitalWrite(pin[0], HIGH);
    digitalWrite(pin[1], LOW);
  }
  else if(dir == 2){
    //analogWrite(pin[2], SPEED);
    digitalWrite(pin[0], LOW);
    digitalWrite(pin[1], HIGH);
  }
  int output = noiseCut(r_val);
  Serial.println(output);
}

int noiseCut(int in) {
  int out = (in + o_val[0] + o_val[1]) / MEAN;
  o_val[1] = o_val[0];
  o_val[0] = in;
  return out;
}

void establishContact() {
  while(Serial.available() <= 0) {
    Serial.println('0');
    delay(300);
  }
}









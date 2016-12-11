const int pin[3] = {3, 4, 5};  // pin number mortor
int dir = 0;  // stop: 0, forward: 1, reverse: -1
int SPEED = 230;

void setup() {
  pinMode(pin[0], OUTPUT);
  pinMode(pin[1], OUTPUT);
  Serial.begin(115200);
}

void loop() {
  int val_res = rCFilter(analogRead(0));
  
  Serial.write('H');
  Serial.write(highByte(val_res));
  Serial.write(lowByte(val_res));

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
}

int rCFilter(int val) {
  static int val_cur;
  static int val_hist;
  
  val_cur = 0.97*val_hist + 0.03*val;
  val_hist = val_cur;
  return val_cur;
}

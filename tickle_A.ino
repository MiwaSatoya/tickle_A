const int pin[3] = {3, 4, 5};  // pin number mortor
int val_res = 0;
int dir = 0;  // stop: 0, forward: 1, reverse: -1
int SPEED = 230;

void setup() {
  pinMode(pin[0], OUTPUT);
  pinMode(pin[1], OUTPUT);
  Serial.begin(115200);
}

void loop() {
  int val_a = analogRead(0);
  if( isChanged(val_a) ) {
    val_res = averageStream(val_a);
  }
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

int averageStream(int val){
  static const int MODULUS = 5;
  static int val_hist[MODULUS];
  static int sum  = 0;
  static byte i_mod = 0;

  sum += (val-val_hist[i_mod]);
  val_hist[i_mod] = val;
  i_mod = ++i_mod % MODULUS;
  return sum / MODULUS;
}

boolean isChanged(int val) {
  static const int MODULUS = 5;
  static int val_hist[MODULUS];
  static byte i_mod = 0;

  val_hist[i_mod] = val;
  i_mod = ++i_mod % MODULUS;
  for(int i=0; i < MODULUS-1; i++) {
    if(val == val_hist[ (i_mod+i) % MODULUS] ) return false;
  }
  return true;
}

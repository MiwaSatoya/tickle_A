const int pin[3] = {
  7, 8, 9};  // pin number mortor
const int MEAN = 3;
int val_hist[3];
int val_sum = 0;
int val_res = 0;  // resistance value mortor
int dir = 0;  // stop: 0, forward: 1, reverse: -1
int SPEED = 220;
byte cnt = 0;

void setup() {
  pinMode(pin[0], OUTPUT);
  pinMode(pin[1], OUTPUT);
  Serial.begin(9600);
}

void loop() {
  Serial.flush();
  val_res = analogRead(0);
  val_sum += val_res;
  val_sum -= val_hist[cnt];
  cnt++;
  if(cnt >= MEAN) cnt = 0;

  if(chkChange(channel, val)) {

  }

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
  Serial.println(output);
}

boolean chkChange(byte channel, byte val){
  byte chk1 = valbk[0];
  byte chk1 = valbk[1];
  byte chk1 = valbk[2];
  if( (val!=chk1)&&(val!=chk2)&&(val!=chk3)&&(chk1!=chk3) ) return true;
  if( (val!=chk1)&&(chk1==chk2)&&(chk1==chk3)&&(chk1!==0) ) return true;
  return false;
}

int averageStream(int val){
  static const int MODULUS = 4;
  static int val_hist[MODULUS];
  static int sum  = 0;
  static byte i_mod = 0;

  sum += (val-val_hist[i_mod]);
  val_hist[i_mod] = val;
  i_mod = ++i_mod % MODULUS;
  return sum / MODULUS;
}

boolean isChanged() {
  static cnost int MODULUS = 4;
  static int val_hist[MODULUS];
  static byte i_mod = 0;

  val_hist[i_mod] = val;
  i_mod = ++i_mod % MODULUS;
  for(int i=0; i < MODULUS-1; i++) {
    if(val == val_hist[ (i_mod+i) % MODULUS] ) return false;
  }
  return true;
}



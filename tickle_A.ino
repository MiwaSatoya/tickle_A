#define pin1 7
#define pin2 8
#define pinA 9
#define MEAN 3
unsinged long duration;

int dir = 0;  // stop: 0, forward: 1, reverse: -1
int o_val1 = 0;  // old value 1
int o_val2 = 0;  // old value 2
byte valbk[] = {0, 0, 0};
int vol
byte r_val = 0;  // resistance value


void setup() {
  pinMode(pin1, OUTPUT);
  pinMode(pin2, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  vol = analogRead(A0);
  vol >>= 3;
  r_val = (byte)vol;
  
  if(ckchange(channel , r_val)) {
    valbk[2] = valvk[1];
    valvk[1] = valvk[0];
    valvk[0] = r_val;
    delay(10);
  }
  
  if(Serial.available() > 0) {
    dir = Serial.read();
  }
  if(dir == 0){
    digitalWrite(pin1, LOW);
    digitalWrite(pin2, LOW);
  }
  else if(dir == 1){
    digitalWrite(pin1, HIGH);
    digitalWrite(pin2, LOW);
  }
  else if(dir == 2){
    digitalWrite(pin1, LOW);
    digitalWrite(pin2, HIGH);
  }

  Serial.println(r_val);
}

int NoiseCut(int in) {
  int out = (in + o_val1 + o_val2) / MEAN;
  o_val2 = o_val1;
  o_val1 = r_val;
  return out;
}

boolean ckchange(byte channel, byte val) {
  byte chk0 = valvk[0];
  byte chk1 = valvk[1];
  byte chk2 = valvk[2];
  if((val != chk0)&&(val != chk1)&&(val != chk2)&&(chk1 != chk3)){
    return true;
  }
  if((val != chk0)&&(val != chk1)&&(val != chk2)&&(chk1 == 0)){
    return true;
  }
  return false;
} 


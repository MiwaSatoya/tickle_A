#define pin1 7
#define pin2 8
#define pinA 9
#define MEAN 3

int dir = 0;  // stop: 0, forward: 1, reverse: -1
int o_val1 = 0;  // old value 1
int o_val2 = 0;  // old value 2
byte r_val = 0;  // resistance value


void setup() {
  pinMode(pin1, OUTPUT);
  pinMode(pin2, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  Serial.flush();
  r_val = analogRead(A0);
  
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
  
  int output = r_val;
  output = NoiseCut(r_val);
  Serial.println(output);
}

int NoiseCut(int in) {
  int out = (in + o_val1 + o_val2) / MEAN;
  o_val2 = o_val1;
  o_val1 = r_val;
  return out;
}

const int pinA[3] = {
  6, 8, 9};  // pin number mortorA
const int pinB[3] = {
  5, 10, 11};  //pin number mortorB
const int MEAN = 3;
int o_valA[2] = {
  0};  // old value mortorA
int o_valB[2] = {
  0};  // old value mortorB
int r_valA = 0;  // resistance value mortorA
int r_valB = 0;  // resistance value mortorB
int dir = 0;  // stop: 0, forward: 1, reverse: -1
int SPEED = 220;

void setup() {
  pinMode(pinA[0], OUTPUT);
  pinMode(pinA[1], OUTPUT);
  pinMode(pinB[0], OUTPUT);
  pinMode(pinB[1], OUTPUT);
  Serial.begin(9600);
  
  establishContact();
}

void loop() {
  Serial.flush();
  r_valA = analogRead(0);
  r_valB = analogRead(1);

  if(Serial.available() > 0) {
    int outputA = noiseCut(r_valA, o_valA[0], o_valA[1]);
    int outputB = noiseCut(r_valB, o_valB[0], o_valB[1]);
    Serial.print(outputA);
    Serial.print(",");
    Serial.println(outputB);
    dir = Serial.read();
  }
  if(dir == 0){
    digitalWrite(pinA[0], LOW);
    digitalWrite(pinA[1], LOW);
  }
  else if(dir == 1){
    //analogWrite(pinA[2], SPEED);
    digitalWrite(pinA[0], HIGH);
    digitalWrite(pinA[1], LOW);
  }
  else if(dir == 2){
    //analogWrite(pinA[2], SPEED);
    digitalWrite(pinA[0], LOW);
    digitalWrite(pinA[1], HIGH);
  }
  else if(dir == 3){
    digitalWrite(pinB[0], LOW);
    digitalWrite(pinB[1], LOW);
  }
  else if(dir == 4){
    //analogWrite(pinB[2], SPEED);
    digitalWrite(pinB[0], HIGH);
    digitalWrite(pinB[1], LOW);
  }
  else if(dir == 5){
    //analogWrite(pinB[2], SPEED);
    digitalWrite(pinB[0], LOW);
    digitalWrite(pinB[1], HIGH);
  }
}

int noiseCut(int in, int o_val0, int o_val1) {
  int out = (in + o_val0 + o_val1) / MEAN;
  o_val1 = o_val0;
  o_val0 = in;
  return out;
}

void establishContact() {
  while(Serial.available() <= 0) {
    Serial.println("0,0");
    delay(300);
  }
}








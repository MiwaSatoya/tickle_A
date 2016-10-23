#define pin1 7
#define pin2 8
#define pinA 9
#define MEAN 3
#define SPEED 220
int limit_t=895;
int limit_b=818;

int dir = 0;  // stop: 0, forward: 1, reverse: -1
int o_val1 = 0;  // old value 1
int o_val2 = 0;  // old value 2
int r_val = 0;  // resistance value
static int filter[3] = {
  0};
int a = 0.9;

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
    analogWrite(pinA, SPEED);
    digitalWrite(pin1, HIGH);
    digitalWrite(pin2, LOW);
  }
  else if(dir == 2){
    analogWrite(pinA, SPEED);
    digitalWrite(pin1, LOW);
    digitalWrite(pin2, HIGH);
  }

  int output = r_val;
  output = noiseCut(r_val);
  //output = rcFilter(r_val);
  Serial.println(output);
}

int noiseCut(int in) {
  int out = (in + o_val1 + o_val2) / MEAN;
  o_val2 = o_val1;
  o_val1 = r_val;
  return out;
}

int rcFilter(int val) {
  filter[1] =  a * filter[0] + (1-a) * val;
  filter[0] = filter[1];
  return filter[0];
}



/*
 * Identifying prime number between 0-9
 * if it is prime, the buzzer will on in 200Hz
 * using combinatorial logic
 */
#define P_BUZZER 3
#define N_KEY 4
#define NO_KEY -1

int p_row[N_KEY] = {12, 11, 10, 9};
int p_col[N_KEY] = {8, 7, 6, 5};

int keyPressed(){
  for (int i=0; i<N_KEY; i++) {
    digitalWrite(p_row[i], LOW);
    delay(10);
    for (int j=0; j<N_KEY; j++) {
      int key = digitalRead(p_col[j]);
      if (key == LOW){
        digitalWrite(p_row[i],HIGH);
        return (i*N_KEY) + j;
      }
    }
    digitalWrite(p_row[i], HIGH);
  }
  return NO_KEY;
}

void keyInit(){
  for (int i=0; i<N_KEY; i++){
    pinMode(p_row[i],OUTPUT);
    pinMode(p_col[i],INPUT_PULLUP);
    
    digitalWrite(p_row[i],LOW);
  }
}

void setup() {
  Serial.begin(9600);
  pinMode(P_BUZZER, OUTPUT);
  keyInit();
}

boolean isPrime(int number){
  boolean b[N_KEY];
  for (int i=0; i<N_KEY; i++){
    b[i] = number & 1;
    number = number >> 1;
    Serial.println(b[i]);
  }
  //Combinatorial
  return (!b[3]*!b[2]*b[1]*!b[0])+(b[3]*!b[2]*!b[1]*!b[0])+(!b[3]*!b[1]*b[0]);
}

void loop() {
  int number = keyPressed();
  if (number != NO_KEY){
    if(isPrime(number) == true){
      tone(P_BUZZER, 200, 1023);
    }
    Serial.println(number);
  }
  delay(100);
}

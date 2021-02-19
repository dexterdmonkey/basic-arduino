/*
 *Program that make the buzzer on corresponding
 *what the keypad pressed (1 = do, 2 = re, etc) 
 */

#define P_BUZZER 3
#define N_KEY 4
#define NO_KEY -1
#define buzzerOn(freq) tone(P_BUZZER, freq, 100)

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

int freq[] = {
 262, 294, 330, 0,
 349, 394, 440, 0,
 494, 523, 587, 622,
 659, 699, 784, 0
};

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

void loop() {
  int note = keyPressed();
  if (note != NO_KEY){
    buzzerOn(freq[note]);
    Serial.print("key: ");
    Serial.println(note);
    delay(50);
  }
  
}





int switch_01 = 4;
int switch_02 = 5;
int switch_03 = 6;
int switch_04 = 7;

void setup() {

  
  pinMode(switch_01, OUTPUT);
  pinMode(switch_02, OUTPUT);
  pinMode(switch_03, OUTPUT);
  pinMode(switch_04, OUTPUT);
  
  digitalWrite(switch_01, LOW);
  digitalWrite(switch_02, LOW);
  digitalWrite(switch_03, LOW);
  digitalWrite(switch_04, LOW);
  
  Serial.begin(9600); 
} 

void loop() {
  if (Serial.available() > 0) {
    int keyboard_button = Serial.read();
    
    switch (keyboard_button) {
      case '1':
       digitalWrite(switch_01, HIGH); 
        break;

      case '0':
        digitalWrite(switch_01, LOW); 
        break;
    }  
  }
} 

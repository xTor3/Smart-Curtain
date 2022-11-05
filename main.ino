#include <IRremote.h>

int RECV_PIN = 6;
IRrecv irrecv(RECV_PIN);
decode_results results;

int r2 = 2;
int r3 = 3; 
int r4 = 4;
int r5 = 5;

int tempoapertura = 5000;
int tempochiusura = 6000;

bool aperto = 0;
bool chiuso = 1; 
bool apertura = 0;
bool chiusura = 0;


void setup() {
  Serial.begin(9600);
  
  irrecv.enableIRIn(); 
  
  pinMode(13, OUTPUT);

  pinMode(r2, OUTPUT);
  pinMode(r3, OUTPUT);
  pinMode(r4, OUTPUT);
  pinMode(r5, OUTPUT);

  digitalWrite(r2, HIGH);
  digitalWrite(r3, HIGH);
  digitalWrite(r4, HIGH);
  digitalWrite(r5, HIGH);
}

void loop() {
  if (irrecv.decode(&results)){
    Serial.println(results.value);
    delay(100);

    if(results.value == 281551326 && chiuso == 1){
      Serial.println("la tenda si sta aprendo");

      
      digitalWrite(13, HIGH);
      delay(300);
      digitalWrite(13, LOW);

      digitalWrite(r2, LOW);
      digitalWrite(r3, HIGH);
      digitalWrite(r4, HIGH);
      digitalWrite(r5, LOW);

      apertura = 1;
      chiuso = 0;
    }

    if(results.value == 281592126 && aperto == 1){
      Serial.println("la tenda si sta chiudendo");

      digitalWrite(13, HIGH);
      delay(300);
      digitalWrite(13, LOW);

      digitalWrite(r2, HIGH);
      digitalWrite(r3, LOW);
      digitalWrite(r4, LOW);
      digitalWrite(r5, HIGH);

      chiusura = 1;
      aperto = 0;
    }
    delay(50);
    irrecv.resume();
  }
  
  if(apertura == 1){
      delay(tempoapertura);
      fermo();
      
      aperto = 1;
      apertura = 0;
    }

  if(chiusura == 1){
    delay(tempochiusura);
    fermo();
    
    chiuso = 1;
    chiusura = 0;
    }
}

void fermo(){
  digitalWrite(r2, HIGH);
  digitalWrite(r3, HIGH);
  digitalWrite(r4, HIGH);
  digitalWrite(r5, HIGH);
  delay(500);
}

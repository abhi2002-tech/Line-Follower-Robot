  int leftIR = 2;
  int rightIR = 3;
  int left_M1 = 4;
  int left_M2 = 5;  
  int right_M1 = 6;
  int right_M2 = 7;
  int left_en =9;
  int right_en =10; 
  int button = 12;
  bool last ;
  bool button_stat ;
void setup() {
  // put your setup code here, to run once:
  // TCCR0B=TCCR0B & B11111000 | B00000010 ;
  pinMode(A3 ,INPUT);
  pinMode(leftIR,INPUT);
  pinMode(rightIR,INPUT);
  pinMode(button,INPUT);
  pinMode(left_M1,OUTPUT);
  pinMode(left_M2,OUTPUT);
  pinMode(right_M1,OUTPUT);
  pinMode(right_M2,OUTPUT);
  pinMode(left_en,OUTPUT);
  pinMode(right_en,OUTPUT);
  digitalWrite(left_M1,LOW);
  digitalWrite(left_M2,LOW);
  digitalWrite(right_M1,LOW);
  digitalWrite(right_M2,LOW);
  button_stat = LOW ;
  last=HIGH;
  Serial.begin(9600);
  
}

void loop() {
  // a=left ;b =right;1=black;0=white
 
  bool st =digitalRead(button);
  if(last == HIGH && st ==LOW){
    button_stat = !button_stat;}
    last = st;
 if(button_stat == HIGH){
  
int a= digitalRead(leftIR);
int b=digitalRead(rightIR);
int pot=analogRead(A3);
  int spdvlue = pot/4;
    
 /*Serial.print(a);
  Serial.print(b);
  Serial.println();
  delay(2000);*/
  analogWrite(left_en , spdvlue);
  Serial.println(spdvlue);
  analogWrite(right_en , spdvlue);
  Serial.println("exe\n");
  motorrotate(a,b);
      
  
  }
 else{
  digitalWrite(left_M1,LOW);
  digitalWrite(left_M2,LOW);
  digitalWrite(right_M1,LOW);
  digitalWrite(right_M2,LOW);
 }
Serial.print(button_stat);
Serial.println();
 //delay(1000);
 }

  
 void motorrotate(int a ,int b){
   if(a==LOW&&b==LOW){
  digitalWrite(left_M1,HIGH);
  digitalWrite(left_M2,LOW);
  digitalWrite(right_M1,LOW);
  digitalWrite(right_M2,HIGH);
     Serial.println("straight");
            
  }
  else if(a==HIGH&&b==LOW){
  digitalWrite(left_M1,HIGH);
  digitalWrite(left_M2,LOW);
  digitalWrite(right_M1,HIGH);
  digitalWrite(right_M2,LOW);
     Serial.println("left");       
  }
  else if(a==LOW&&b==HIGH){
  digitalWrite(left_M1,LOW);
  digitalWrite(left_M2,HIGH);
  digitalWrite(right_M1,LOW);
  digitalWrite(right_M2,HIGH);
            Serial.println("right");
  }


  else {
  digitalWrite(left_M1,LOW);
  digitalWrite(left_M2,LOW);
  digitalWrite(right_M1,LOW);
  digitalWrite(right_M2,LOW);
    Serial.println("Stop"); 
       
  }}

#include "Adafruit_VL53L0X.h"
Adafruit_VL53L0X lox = Adafruit_VL53L0X();

float EMA=0;

float temp=0;
int triggerV=8;
int echoV=9;
int triggerA=7;
int echoA=6;

int tiempoV;
int tiempoA;

float disV; //Distancia ultra frente
float disA; //Distancia ultra atrás

int motor2=2;
int motor4=4;
int motor1=12;
int motor3=3;

int buzer=11;
int luz=5;
int estado=1;
//////////////////////////
void setup() {
 Serial.begin(9600);
//Ultra verde
pinMode(triggerV,OUTPUT);
pinMode(echoV,INPUT);
////Ultra azul
pinMode(triggerA,OUTPUT);
pinMode(echoA,INPUT);
////
pinMode(motor2,OUTPUT);
pinMode(motor4,OUTPUT);

pinMode(motor1,OUTPUT);
pinMode(motor3,OUTPUT);

pinMode(buzer,OUTPUT);
pinMode(luz,OUTPUT);

  while (! Serial) {
    delay(1);
  }
    if (!lox.begin()) {
    Serial.println(F("error de inicializacion"));
    while(1);
  }  
}


void loop() {

VL53L0X_RangingMeasurementData_t measure;
//temp=(measure.RangeMilliMeter)/10;
lox.rangingTest(&measure, false); 
if(0<((measure.RangeMilliMeter)/10)<60){temp=measure.RangeMilliMeter/10;}else{temp=65;}

////Ultra verde
digitalWrite(triggerV,HIGH);
 delay(1);
digitalWrite(triggerV,LOW);
tiempoV= pulseIn(echoV,HIGH);
disV=tiempoV/58.2;
//if(disV<0)
//{disV=400;}
////Ultra azul
digitalWrite(triggerA,HIGH);
 delay(1);
digitalWrite(triggerA,LOW);
tiempoA= pulseIn(echoA,HIGH);
disA=tiempoA/58.2;

  if (measure.RangeStatus != 4&&disV>0) {  
    Serial.print(temp);Serial.print(",Verde: ");Serial.print(disV);Serial.print(",Azul: ");Serial.println(disA);}else {
    Serial.println(" out of range ");
  }

/////////////Puro pa' delante/////////
switch (estado)
{
  case 1: //padelante
    Padelante();
    if ( disV < 30)
      {estado = 2;}   
    break;
  case 2: //detener
    //digitalWrite(luz,HIGH);
    //delay(500);
    Detener();
           
    if (temp <= 20&&disV>20)
      {estado = 3;}
      
    if (temp <= 20&&disV<20)
      {estado = 5;}
      
    if (temp > 20)
      {estado = 4;}
      
    if (disV <20)
      {estado = 5;}  
    break;
    
  case 3: //izquierda
    Izquierda();
    if (disV > 25)
      {estado = 1;} 
            
    if (disV < 25)
      {estado = 3;}    
    break;
    
  case 4: //derecha
    Derecha();
    if (disV > 30)
      {estado = 1;} 
       
    if (disV < 25)
      {estado = 4;}  
    break;
    
  case 5: //atras
      digitalWrite(luz,HIGH);
      delay(80);
      digitalWrite(luz,LOW);
      Patras();
    if (disV < 30 && disA < 30 && temp <20)
      {estado = 6;}
  
    if (disV > 30 && temp > 20)
      {estado = 4;}
        
    if (disV > 30  && temp < 20)
      {estado = 3;}
        
    if (disV< 20&&disA > 30)
      {estado = 5;}
      
    if(disV>30||disA<30)
    {estado=2;}                        
    break;
    
  case 6: //error
    Error();
    delay(2000);     
    break; 
}
}

void Padelante() {
digitalWrite(motor3,HIGH);
delay(20);
digitalWrite(motor1,HIGH);
digitalWrite(motor2,LOW);
digitalWrite(motor4,LOW);
}

void Detener(){
digitalWrite(motor3,LOW);
digitalWrite(motor1,LOW);
digitalWrite(motor2,LOW);
digitalWrite(motor4,LOW);
delay(2000);
}
  
void Derecha(){
digitalWrite(motor3,HIGH);
digitalWrite(motor1,LOW);
digitalWrite(motor2,LOW);
digitalWrite(motor4,LOW);
delay(80);
}
               
void Izquierda(){
digitalWrite(motor3,LOW);
digitalWrite(motor1,HIGH);
digitalWrite(motor2,LOW);
digitalWrite(motor4,LOW);
delay(50);
}
                 
void Patras(){
digitalWrite(motor3,LOW);
digitalWrite(motor1,LOW);
digitalWrite(motor2,HIGH);
digitalWrite(motor4,HIGH);
delay(100);
}

void Error(){
digitalWrite(motor3,LOW);
digitalWrite(motor1,LOW);
digitalWrite(motor2,LOW);
digitalWrite(motor4,LOW);
digitalWrite(buzer,HIGH);
}

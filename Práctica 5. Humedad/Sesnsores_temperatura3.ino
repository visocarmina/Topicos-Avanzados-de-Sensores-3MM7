#include <Wire.h>
#include <Adafruit_MPL3115A2.h>
#include <Adafruit_AHTX0.h>

Adafruit_AHTX0 aht;
Adafruit_MPL3115A2 mpl = Adafruit_MPL3115A2();



 int leer=0;
 float templm;

void setup(){
pinMode(A0,INPUT);
  Serial.begin(115200);

//Sensor de humedad
Serial.println("Adafruit AHT10/AHT20 demo!");

  if (! aht.begin()) {
    Serial.println("Could not find AHT? Check wiring");
    while (1) delay(10);
  }
  Serial.println("AHT10 or AHT20 found");

//Sensor de peresion
Serial.println("Iniciando...");
  
  if (!mpl.begin()) {
    Serial.println("No se pudo encontrar el módulo MPL3115A2, compruebe la conexión.");
    while (1);
  }
  
  Serial.println("Módulo MPL3115A2 iniciado correctamente.");

  
}

void loop() {
leer=analogRead(A0);

//sesnor de presion
float temp = mpl.getTemperature();
Serial.print("Sensor de presion: " );
Serial.println(temp);

//sesnor de humedad
sensors_event_t humidity, temph;
aht.getEvent(&humidity, &temph);// populate temp and humidity objects with fresh data
Serial.print("Temperatura sesnor humedad: "); Serial.print(temph.temperature); Serial.println(" degrees C");
  Serial.print("Humidity: "); Serial.print(humidity.relative_humidity); Serial.println("% rH");


//lm35
templm=((leer*5000)/1023);
Serial.print("Temperatura LM35: ");Serial.println(templm);

delay(300);

}

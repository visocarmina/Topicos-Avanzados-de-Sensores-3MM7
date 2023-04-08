#include <Adafruit_MPL3115A2.h>

Adafruit_MPL3115A2 baro;
float presion,temperatura,densidad,densidad2,h;
void setup() {
  Serial.begin(9600);
  while(!Serial);
  Serial.println("Adafruit_MPL3115A2 test!");

  if (!baro.begin()) {
    Serial.println("Could not find sensor. Check wiring.");
    while(1);
  }

  // use to set sea level pressure for current location
  // this is needed for accurate altitude measurement
  // STD SLP = 1013.26 hPa
  baro.setSeaPressure(1013.26);
}

void loop() {
  float pressure = baro.getPressure();
  float altitude = baro.getAltitude();
  float temperature = baro.getTemperature();
  presion=pressure*0.0295;
  temperatura=temperature*1.8+32;
  densidad=0.075*(presion/29.92)*(530/(460+temperatura));
  densidad2=densidad*(0.454)*(1/0.0283);
  h=(pressure*100)/(densidad2*9.81);
  Serial.println("-----------------");
  Serial.print("presion = "); Serial.print(pressure); Serial.println(" hPa");
  Serial.print("altitud = "); Serial.print(altitude); Serial.println(" m");
  Serial.print("temperatura = "); Serial.print(temperature); Serial.println(" C");
  Serial.print("densidad= "); Serial.print(densidad2); Serial.println("kg/m^3");
  Serial.print("Altura de la columna de aire= "); Serial.print(h); Serial.println("m");

  

  delay(250);
}

//Sensor de gas MiCS5524
//Datos analogicos de concentracion.
float Value;

void setup() {
  Serial.begin(9600);
}

void loop() {
  Value=analogRead(A0);
  Serial.print("PPM de alcohol, aprox: ");
  Serial.println(Value/4);
  
  float porcentaje=(Value*0.1)/104;
  Serial.print("Porcentaje de alcohol: ");
  Serial.println(porcentaje);
  delay(1000);
}
volatile int Pulsos;
int PinSensor = 2;
float K = 6;
void ContPulsos() {
  Pulsos++;
}
int ObtenerFrecuencia() {
  int Frecuencia;
  Pulsos = 0;
  interrupts();
  delay(1000);
  noInterrupts();
  Frecuencia = Pulsos;
  return Frecuencia;
}
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(PinSensor, INPUT);
  attachInterrupt(0, ContPulsos, RISING);
}

void loop() {
  // put your main code here, to run repeatedly:
  float Frecuencia = ObtenerFrecuencia();
  float Caudal_L_m = Frecuencia / K;
  float Caudal_L_h = Caudal_L_m * 60;
  Serial.print("Frecuencia: ");
  Serial.print(Frecuencia, 0);
  Serial.print("Hz  ");
  Serial.print("Caudal: ");
  Serial.print(Caudal_L_m, 4);
  Serial.print("L/m ");
  Serial.print("Caudal: ");
  Serial.print(Caudal_L_h, 4);
  Serial.println("L/h");
}

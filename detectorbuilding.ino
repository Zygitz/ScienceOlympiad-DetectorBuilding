int ThermistorPin = 0;
int Vo;
float R1 = 10000;
float logR2, R2, T, ppm;
float c1 = 1.009249522e-03, c2 = 2.378405444e-04, c3 = 2.019202697e-07;
const int ppm1 = 1501; //set hot parameter
const int ppm2 = 3101; //set cold parameter

void setup() {
  pinMode(A0, INPUT);
  pinMode(13, OUTPUT); //blue
  pinMode(12, OUTPUT); //green
  pinMode(11, OUTPUT); //red
  Serial.begin(9600);
}
void loop() {
  Vo = analogRead(ThermistorPin);
  R2 = R1 * (1023.0 / (float)Vo - 1.0);
  logR2 = log(R2);
  T = (1.0 / (c1 + c2*logR2 + c3*logR2*logR2*logR2));
  T = T - 273.15;
  T = (T * 9.0)/ 5.0 + 32.0;
  Serial.print("Temperature: ");
  Serial.print(T);
  Serial.println(" F");
  Serial.print(Vo);
  Serial.println(" V");
  ppm = Vo * 2;
  Serial.print(ppm);
  Serial.println(" ppm");

  if (T < ppm1) { //blue
    digitalWrite(13, HIGH);
    digitalWrite(12, LOW);
    digitalWrite(11, LOW);
  }
  else if (T >= ppm2) { //red
    digitalWrite(13, LOW);
    digitalWrite(12, LOW);
    digitalWrite(11, HIGH);
  }
  else { //green
    digitalWrite(13, LOW);
    digitalWrite(12, HIGH);
    digitalWrite(11, LOW);
  }
delay(500);
}
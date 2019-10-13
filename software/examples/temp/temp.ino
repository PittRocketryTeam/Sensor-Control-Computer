int mode = 0;
int baseline;

float inverse_beta = 1.0 / 3380.0;
float inverse_t0 = 1.0 / 298.15;

void setup()
{
  Serial.begin(9600);
  pinMode(0, INPUT);
  pinMode(1, INPUT);
  pinMode(2, INPUT);
}

void loop()
{
  
  int black = analogRead(0);
  int red = analogRead(1);
  int ref = analogRead(2);

  float c1 = 1.0 / (inverse_t0 + inverse_beta * (log(1023.0 / (float)black - 1.0)));
  c1 -= 273.15;

  Serial.print("raw: ");
  Serial.print(black);
  Serial.print(", ");
  Serial.println(red);
  Serial.print("t: ");
  Serial.print(c1);
  //Serial.print(", ");
  //Serial.println(red);
  Serial.println();

  delay(500);
}

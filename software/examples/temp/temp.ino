int mode = 0;
int baseline;

float inverse_beta = 1.0 / 3380.0;
float inverse_t0 = 1.0 / 298.15;

#define R0 10000

void setup()
{
  Serial.begin(9600);
  pinMode(0, INPUT);
  pinMode(1, INPUT);
  pinMode(2, INPUT);
}

float getr(int val)
{
  float out = R0 * ((1023.0 / (float)val) - 1);
  //Serial.println(out);
  return out;
}

void loop()
{
  
  int black = analogRead(0);
  int red = analogRead(1);

  float c1 = 1.0 / (inverse_t0 + inverse_beta * log((1023.0 / black) - 1));
  c1 -= 273.15;

  Serial.print("raw: ");
  Serial.print(getr(black));
  Serial.print(", ");
  Serial.print(red);
  Serial.print("\tt: ");
  Serial.print(c1);
  //Serial.print(", ");
  //Serial.println(red);
  Serial.println();

  delay(500);
}

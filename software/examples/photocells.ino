int mode = 0;
int baseline;

void setup()
{
  Serial.begin(9600);
  pinMode(0, INPUT);
  pinMode(4, INPUT_PULLUP);
}

void loop()
{
  
  int raw = analogRead(0);

  if (digitalRead(4) == LOW)
  {
    mode = !mode;
    delay(1000);
  }

  if (mode == 0) // startup
  {
    baseline = raw;
    Serial.print("baseline ");
    Serial.println(baseline);
  }
  else if (mode == 1) // launch
  {
    int diff = raw - baseline;
    Serial.print("launch ");
    Serial.println(diff);
  }

  delay(500);
}

void setup() 
{
  // put your setup code here, to run once:
    pinMode(19, INPUT);  // RX1 Serial Port 1
    pinMode(18, OUTPUT); // TX1
    Serial.begin(115200);
}

void loop() 
{
  // put your main code here, to run repeatedly:
  Serial.print("160d0a");
  delay(100);
}

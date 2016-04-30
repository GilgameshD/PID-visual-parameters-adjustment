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
  Serial.println("Max_acceleration_x: ");
  delay(100);
  Serial.println("Max_acceleration_y: ");
  delay(100);
  Serial.println("Max speed X: ");
  delay(100);
  Serial.println("Max speed Y: ");
  delay(100);
  Serial.println("Moving to initial position...");
  delay(100);
}

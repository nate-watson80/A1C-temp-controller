/* test_units.ino
 * setup() - this function runs once when you turn your Arduino on
 * We initialize the serial connection with the computer
 */
int fanPin = 5;
int heaterPin = 10;

void setup() {
  Serial.begin(9600);  //Start the serial connection with the computer
  pinMode(fanPin, OUTPUT);
  pinMode(heaterPin, OUTPUT);
}

void loop() {
  digitalWrite(fanPin, HIGH);
  digitalWrite(heatPin, LOW);
  delay(2000);
  digitalWrite(fanPin, LOW);
  digitalWrite(heatPin, HIGH);
  delay(2000);
}

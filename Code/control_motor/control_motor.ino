void setup() {
  pinMode(A0,INPUT);
  Serial1.begin(9600);

  Serial1.print("S255\r");
  Serial1.print("M50\r");
  Serial1.print("D20\r");
  Serial1.print("E\r");
  Serial1.print("Y\r");
}

void loop() {
 float pot =  analogRead(A0);
 float pot_map = map(pot,0,1023,-255,255);
 //Serial.println(pot_map);
 Serial1.print("S"+String(int(pot_map))+"\r");
 
}

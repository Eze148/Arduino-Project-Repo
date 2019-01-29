const int row[8] = {
  1, 2, 3, 4, 5, 6, 7, 8
};

// 2-dimensional array of column pin numbers:
const int col[8] = {
  9, 10, 11, 12, 13, 14, 15, 16
};
void setup() {
  // put your setup code here, to run once:
  for (int thisPin = 0; thisPin < 8; thisPin++) {
    // initialize the output pins:
    pinMode(col[thisPin], OUTPUT);
    pinMode(row[thisPin], OUTPUT);
    // take the col pins (i.e. the cathodes) high to ensure that the LEDS are off:
    digitalWrite(col[thisPin], LOW);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  for(int x = 0; x<8;x++){
    digitalWrite(col[x], HIGH);
    for(int y =1; y <7; y++){
      digitalWrite(row[y], HIGH);
    }
  }
  delay(10);
  for(int x = 0; x<8;x++){
    digitalWrite(col[x], LOW);
    for(int y =1; y <7; y++){
      digitalWrite(row[y], LOW);
    }
  }
  for(int x = 3; x<5;x++){
    digitalWrite(col[x], HIGH);
  }
  delay(10);
}

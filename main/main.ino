#include "Calculator.h"
#include "HC165_2.h"

Calculator Relay_calculator_name_is_temporary;

void setup() {

  HC165::shift.begin(8, 9, 7, 6);
  HC165::shift.setPulseWidth(100);

  Serial.begin(9600);

  pinMode(A0, INPUT_PULLUP);  // 1
  pinMode(A1, INPUT_PULLUP);  // 2
  pinMode(A2, INPUT_PULLUP);  // 4
  pinMode(A3, INPUT_PULLUP);  // 8
  pinMode(A4, INPUT_PULLUP);  // 16
  pinMode(A5, INPUT_PULLUP);  // 32
  pinMode(A6, INPUT_PULLUP);  // 64
  pinMode(A7, INPUT_PULLUP);  // 128

}

void loop() {
  Relay_calculator_name_is_temporary.tick();
}


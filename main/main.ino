#include "Calculator.h"

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

// void midi(float freq) {
//   freq = (1 / freq) * 1000;
//   uint16_t times = 10;
//   while (times) {
//     for (int i = 0; i <= 15; i++) {
//       HC595::reg.write(i, 1);
//       HC595::reg.update();
//       delay(freq);
//       HC595::reg.write(i, 0);
//       HC595::reg.update();
//     }
//     times;
//   }
// }

// int8_t currentSymbol() {
//   int8_t tmp = -1;
//   if (!HC165::shift.state(6) && !HC165::shift.state(7) && !HC165::shift.state(5)) tmp = 0;
//   if (!HC165::shift.state(4) && !HC165::shift.state(7)) tmp = 1;
//   if (!HC165::shift.state(4) && !HC165::shift.state(12)) tmp = 2;
//   if (!HC165::shift.state(4) && !HC165::shift.state(14)) tmp = 3;
//   if (!HC165::shift.state(7) && !HC165::shift.state(15)) tmp = 4;
//   if (!HC165::shift.state(12) && !HC165::shift.state(15)) tmp = 5;
//   if (!HC165::shift.state(14) && !HC165::shift.state(15)) tmp = 6;
//   if (!HC165::shift.state(7) && !HC165::shift.state(8)) tmp = 7;
//   if (!HC165::shift.state(8) && !HC165::shift.state(12)) tmp = 8;
//   if (!HC165::shift.state(8) && !HC165::shift.state(14)) tmp = 9;
//   if (!HC165::shift.state(9) && !HC165::shift.state(10)) tmp = '=';                           //61 =
//   if (!HC165::shift.state(6) && !HC165::shift.state(12) && !HC165::shift.state(5)) tmp = 46;  // .
//   if (!HC165::shift.state(10) && !HC165::shift.state(15)) tmp = 42;                           // *
//   if (!HC165::shift.state(10) && !HC165::shift.state(4)) tmp = 45;                            // -
//   if (!HC165::shift.state(5) && !HC165::shift.state(10) && !HC165::shift.state(6)) tmp = 43;  // +
//   if (!HC165::shift.state(10) && !HC165::shift.state(8)) tmp = 47;                            // /
//   if (!HC165::shift.state(9) && !HC165::shift.state(7)) tmp = 99;                             // clear
//   if (!HC165::shift.state(11) && !HC165::shift.state(14)) tmp = 's';                          // sqrt
//   if (!HC165::shift.state(9) && !HC165::shift.state(14)) tmp = '%';                           // %
//   if (!HC165::shift.state(9) && !HC165::shift.state(12)) tmp = 'r';                           // reg switch
//   return tmp;
// }

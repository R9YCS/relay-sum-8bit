#include "HC165_2.h"
#include "HC595_4.h"
#include "CalcRelay.h"
#include "DynamicIndication.h"
#include "KeyBoard.h"
#include <Vector.h>

DynamicIndication IV28;
Keyboard BM23;
RelayCalc calc;

const int ELEMENT_COUNT_MAX = 5;
typedef Vector<int> Elements;
const size_t DELAY = 500;

uint8_t multA = 0;
uint8_t multB = 0;
uint8_t currentOperation = 0;

bool flag = 1;

uint32_t btnTimer = 0;
uint32_t clearTimer = 0;

void setup() {

  HC165::shift.begin(8, 9, 7, 6);
  HC165::shift.setPulseWidth(100);

  Serial.begin(9600);
  
  
  pinMode(A0, INPUT_PULLUP); // 1
  pinMode(A1, INPUT_PULLUP); // 2
  pinMode(A2, INPUT_PULLUP); // 4
  pinMode(A3, INPUT_PULLUP); // 8
  pinMode(A4, INPUT_PULLUP); // 16
  pinMode(A5, INPUT_PULLUP); // 32
  pinMode(A6, INPUT_PULLUP); // 64
  pinMode(A7, INPUT_PULLUP); // 128
  

  int storage_array[ELEMENT_COUNT_MAX];
  Elements vector;
  vector.setStorage(storage_array);

}
void midi(float freq) {
  freq = (1/freq) * 1000;
  uint16_t times = 10;
  while(times) {
  for(int i = 0; i <= 15; i++) {
  HC595::reg.write(i, 1);
  HC595::reg.update();
  delay(freq);
  HC595::reg.write(i, 0);
  HC595::reg.update();
  }
  times;
  }
}

int8_t currentSymbol() {
  int8_t tmp = -1;
      if(!HC165::shift.state(6) && !HC165::shift.state(7) && !HC165::shift.state(5)) tmp = 0;  
      if(!HC165::shift.state(4) && !HC165::shift.state(7)) tmp = 1;  
      if(!HC165::shift.state(4) && !HC165::shift.state(12)) tmp = 2; 
      if(!HC165::shift.state(4) && !HC165::shift.state(14)) tmp = 3; 
      if(!HC165::shift.state(7) && !HC165::shift.state(15)) tmp = 4; 
      if(!HC165::shift.state(12) && !HC165::shift.state(15)) tmp = 5;
      if(!HC165::shift.state(14) && !HC165::shift.state(15)) tmp = 6;
      if(!HC165::shift.state(7) && !HC165::shift.state(8)) tmp = 7;  
      if(!HC165::shift.state(8) && !HC165::shift.state(12)) tmp = 8; 
      if(!HC165::shift.state(8) && !HC165::shift.state(14)) tmp = 9; 
      if(!HC165::shift.state(9) && !HC165::shift.state(10)) tmp = '='; //61 =
      if(!HC165::shift.state(6) && !HC165::shift.state(12) && !HC165::shift.state(5)) tmp = 46; // .
      if(!HC165::shift.state(10) && !HC165::shift.state(15)) tmp = 42; // *
      if(!HC165::shift.state(10) && !HC165::shift.state(4)) tmp = 45; // -
      if(!HC165::shift.state(5) && !HC165::shift.state(10) && !HC165::shift.state(6)) tmp = 43; // +
      if(!HC165::shift.state(10) && !HC165::shift.state(8)) tmp = 47; // /
      if(!HC165::shift.state(9) && !HC165::shift.state(7)) tmp = 99; // clear
      if(!HC165::shift.state(11) && !HC165::shift.state(14)) tmp = 's'; // sqrt
      if(!HC165::shift.state(9) && !HC165::shift.state(14)) tmp = '%'; // %
      if(!HC165::shift.state(9) && !HC165::shift.state(12)) tmp = 'r'; // reg switch
      return tmp;
}

void mathOperation() {

  if(currentSymbol() >= 0 && currentSymbol() <= 9 ) {
    IV28.screenPrint(currentSymbol(),0);
  }

  switch(currentSymbol()) {
    case '/':
    currentOperation = '/';
    if (multA == 0) {
      multA = IV28.returnNumber();
    } else {
      multB = IV28.returnNumber();
    }
      break;

    case '*':
    currentOperation = '*';
      if (multA == 0) {
      multA = IV28.returnNumber();
    } else {
      multB = IV28.returnNumber();
    }
      break;
    
    case '-':
    currentOperation = '-';
    if (multA == 0) {
      multA = IV28.returnNumber();
    } else {
      multB = IV28.returnNumber();
    }
      break;
    
    case '+':
    currentOperation = '+';
    if (multA == 0) {
      multA = IV28.returnNumber();
    } else {
      multB = IV28.returnNumber();
    }
      break;

    case 's':
    currentOperation = 's';
      IV28.writeNumber(calc.Sqrt(IV28.returnNumber(), 50));
      break;

    case '%':
    if (multA != 0) {
      float tmpP = calc.division(multA, 10, 1, 50);
      multB = IV28.returnNumber();
      // multB = calc.multiplication(multB, tmpP, 50);
      IV28.writeNumber((float)multB * tmpP / 10);
    }
      break;

    case 'r':
    if (multA != 0) {
      uint16_t tmpR = multA;
      multA = IV28.returnNumber();
      multB = tmpR;
      IV28.writeNumber(multB);
    }
      break;
    
    case '=':
      if(multA != 0) {
        multB = IV28.returnNumber();
      }
      int32_t tmp123;
      switch(currentOperation) {
        case '/':
        if(multA != 0 && multB != 0) {
          tmp123 = calc.division(multA, multB, 1, 50);
          IV28.writeNumber(tmp123);
          multA = 0;
          multB = 0;
        } else {
          IV28.err();
        }
          break;
        case '*':
          tmp123 = calc.multiplication(multA, multB, 50);
          IV28.writeNumber(tmp123);
          multA = 0;
          multB = 0;
          break;
        case '-':
          tmp123 = calc.Subtraction(multA, multB, 50);
          IV28.writeNumber(tmp123);
          multA = 0;
          multB = 0;
          break;
        case '+':
          tmp123 = calc.CalcSum(multA, multB, 50);
          IV28.writeNumber(tmp123);
          multA = 0;
          multB = 0;
          break;
      }
      break;

    case 'c':
     clearTimer = millis();
     if(millis() - clearTimer > 2000) {
      IV28.clear();
      clearTimer = millis();
     }
      IV28.clearSymbol();
      break;
  }
}
void loop() {

if(HC165::shift.update() && millis() - btnTimer > 100) {
  btnTimer = millis();
  mathOperation();
} 
IV28.refScreen();



// } 

//  for(int i = 16; i < 24; i++) {
//  HC595::reg.write(i, 1);
//  HC595::reg.update();
//  delay(500);
//  HC595::reg.write(i, 0);
//  HC595::reg.update();
//  }

//  for(int i = 24; i < 32; i++) {
//  HC595::reg.write(i, 1);
//  HC595::reg.update();
//  }
//  HC595::reg.write(30, 0);
//  HC595::reg.write(24, 1);
//  HC595::reg.update();
//

  
//  calc.bencmark();
//  for(int i = 0; i <10; i++) {
//  uint32_t sum = calc.multiplication(i, i, 15);
//  Serial.print("Sum = ");
//  Serial.println(sum);
//  Serial.print("I = ");
//  Serial.println(i);
//  Serial.println("------------------------------------------");
//  }
//for(int i = 100; i < 2000; i+=10) {
//  midi(i);
//}
//  uint8_t a = 120;
//  uint8_t b = 10;
//  uint32_t sum = calc.multiplication(a, b, 50);
//  Serial.print("Sum = ");
//  Serial.println(sum);
//   Serial.print("SumW = ");
//  Serial.println(a * b);
//  while(a >= 1) {


//    a = calc.CalcSum(calc.invert(b), a, 100);
//  Serial.println(a);
//  Serial.println((int8_t)b);


// if (Serial.available()) {
//    uint8_t tmp = Serial.parseInt();
//    uint8_t tmp1 = Serial.parseInt();-
//    Serial.print(tmp);
//    Serial.print(" * ");
//    Serial.print(tmp1);
//    Serial.print(" = ");
//    Serial.println(calc.multiplication(20, 20, 60));
// if(HC165::shift.update()) {
//    for(int i = 0; i < 16; i++) {
//     Serial.print(i);
//     Serial.print(" = ");
//     Serial.print(HC165::shift.state(i));
//     Serial.print("  ");
//    }
//   Serial.println();
//   !HC165::shift.state(5) ?  HC595::reg.write(1, 1) : HC595::reg.write(1, 0);
//   !HC165::shift.state(6) ?  HC595::reg.write(2, 1) : HC595::reg.write(2, 0);
//   !HC165::shift.state(7) ?  HC595::reg.write(3, 1) : HC595::reg.write(3, 0);
//   !HC165::shift.state(8) ?  HC595::reg.write(4, 1) : HC595::reg.write(4, 0);
//   !HC165::shift.state(9) ?  HC595::reg.write(5, 1) : HC595::reg.write(5, 0);
//   !HC165::shift.state(10) ?  HC595::reg.write(6, 1) : HC595::reg.write(6, 0);
//   !HC165::shift.state(11) ?  HC595::reg.write(7, 1) : HC595::reg.write(7, 0);
//   !HC165::shift.state(13) ?  HC595::reg.write(8, 1) : HC595::reg.write(8, 0);
//   HC595::reg.update();
// }



//  }
// for (int i = 14; i <= 21; i++) {
//         Serial.print("Pin ");
//         Serial.print(i);
//         Serial.print(" = ");
//         Serial.println(!digitalRead(i));
//   }
  
//      Serial.println(calc.multiplication(65, 2, 60));
//      Serial.println(calc.Subtraction(100, 8, 50));
//    Serial.println(calc.division(3, 2, 3, 100));

//uint16_t tmp = calc.multiplication(7,7,30);
//uint16_t tmp1 = calc.multiplication(7,7,30);
//uint16_t tmp2 = calc.multiplication(32, 32, 26);
//  Serial.println(tmp2);
//calc.bencmark();
//    Serial.println(calc.CalcSum(58,42,50));
//  }
//  calc.invert();

//  HC595::reg.write(2, 1); 
//  HC595::reg.write(4, 1); 
//  HC595::reg.write(10, 1);
//  HC595::reg.write(8, 1);
//  HC595::reg.update();
//   delay(2000);
//  HC595::reg.write(0, 1);
//  HC595::reg.write(1, 1);  
//  HC595::reg.write(2, 1);
//  
//  HC595::reg.write(8, 1);
//  HC595::reg.write(9, 1);  
//  HC595::reg.write(10, 1);
  
//  for(int i = 2; i <= 9; i++) {
//      Serial.println(!digitalRead(i));
//    }
//
//    for(int i = 0; i <= 16; i++) {
//      HC595::reg.write(i, 0);
//       HC595::reg.update();
//      delay(50);
//    }

}

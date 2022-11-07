#include "Calculator.h"

// namespace VECTOR{
  // const int ELEMENT_COUNT_MAX = 5;
  // typedef Vector<int> Elements;
  // static int storage_array[ELEMENT_COUNT_MAX];
  // static Elements vector;
  // vector.setStorage(storage_array);
// }

void Calculator::mainLogic() {

  if (currentSymbol() >= 0 && currentSymbol() <= 9) {
    IV28.screenPrint(currentSymbol(), 0);
  }

  switch (currentSymbol()) {
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
      if (multA != 0) {
        multB = IV28.returnNumber();
      }
      int32_t tmp123;
      switch (currentOperation) {
        case '/':
          if (multA != 0 && multB != 0) {
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
      if (millis() - clearTimer > 2000) {
        IV28.clear();
        clearTimer = millis();
      }
      IV28.clearSymbol();
      break;
  }
}
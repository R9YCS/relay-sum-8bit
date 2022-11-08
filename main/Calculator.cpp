#include "Calculator.h"

void Calculator::mainLogic() {
  Serial.println("mainLogic in");
  Serial.println("currentSymbol");
  Serial.println(BM23.currentSymbol());
  
  if (BM23.currentSymbol() >= 0 && BM23.currentSymbol() <= 9) {
    IV28.screenPrint(BM23.currentSymbol(), 0);
  }

  switch (BM23.currentSymbol()) {
    case '/':
      currentOperation = '/';
      if (userValueRegA == 0) {
        userValueRegA = IV28.returnNumber();
      } else {
        userValueRegB = IV28.returnNumber();
      }
      break;

    case '*':
      currentOperation = '*';
      if (userValueRegA == 0) {
        userValueRegA = IV28.returnNumber();
      } else {
        userValueRegB = IV28.returnNumber();
      }
      break;

    case '-':
      currentOperation = '-';
      if (userValueRegA == 0) {
        userValueRegA = IV28.returnNumber();
      } else {
        userValueRegB = IV28.returnNumber();
      }
      break;

    case '+':
      currentOperation = '+';
      if (userValueRegA == 0) {
        userValueRegA = IV28.returnNumber();
      } else {
        userValueRegB = IV28.returnNumber();
      }
      break;

    case 's':
      currentOperation = 's';
      IV28.writeNumber(calc.Sqrt(IV28.returnNumber(), 50));
      break;

    case '%':
      if (userValueRegA != 0) {
        float tmpP = calc.division(userValueRegA, 10, 1, 50);
        userValueRegB = IV28.returnNumber();
        // userValueRegB = calc.multiplication(userValueRegB, tmpP, 50);
        IV28.writeNumber((float)userValueRegB * tmpP / 10);
      }
      break;

    case 'r':
      if (userValueRegA != 0) {
        uint16_t tmpR = userValueRegA;
        userValueRegA = IV28.returnNumber();
        userValueRegB = tmpR;
        IV28.writeNumber(userValueRegB);
      }
      break;

    case '=':
      if (userValueRegA != 0) {
        userValueRegB = IV28.returnNumber();
      }
      switch (currentOperation) {
        case '/':
          if (userValueRegA != 0 && userValueRegB != 0) {
            float templateValueCalculationFloat = calc.division(userValueRegA, userValueRegB, 1, 50);
            IV28.writeNumberF(templateValueCalculationFloat);
            userValueRegA = 0;
            userValueRegB = 0;
          } else {
            IV28.err();
          }
          break;
        case '*':
          templateValueCalculation = calc.multiplication(userValueRegA, userValueRegB, 50);
          IV28.writeNumber(templateValueCalculation);
          userValueRegA = 0;
          userValueRegB = 0;
          break;
        case '-':
          templateValueCalculation = calc.Subtraction(userValueRegA, userValueRegB, 50);
          IV28.writeNumber(templateValueCalculation);
          userValueRegA = 0;
          userValueRegB = 0;
          break;
        case '+':
          templateValueCalculation = calc.CalcSum(userValueRegA, userValueRegB, 50);
          IV28.writeNumber(templateValueCalculation);
          userValueRegA = 0;
          userValueRegB = 0;
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
#include <stdint.h>
#include "CalcRelay.h"
#include "HC595_4.h"

uint8_t RelayCalc::invert(uint8_t a) {
  return ~(uint8_t)(unsigned)a + (uint8_t)(unsigned)1;
}

uint8_t RelayCalc::Subtraction(uint8_t a, uint8_t b, uint8_t delayCalc) {
  return CalcSum(invert(b), a, delayCalc);
}

float RelayCalc::CalcSumFloat(float a, float b, uint8_t delayCalc = 30) {

  bool flagInteger = 1;
  bool flagFraction = 0;

  uint8_t integer;
  uint8_t fraction;
  float fractionA = modf(a, integer);
  float fractionB = modf(b, integer);

  if (fractionA > 0 || fractionB > 0) {
    flagFraction = 1;
  }

  do {

    if (flagInteger) {
      memoryA = (uint8_t)a;
      memoryB = (uint8_t)b;
    } else {
      memoryA = fractionA * 10;
      memoryB = fractionB * 10;
      flagFraction = 0;
    }

    for (int i = 7; i >= 0; i--) {
      uint8_t maskA = 1 << i;
      uint8_t tmpA = maskA & memoryA;
      HC595::reg.write(i, (bool)tmpA);
      HC595::reg.update();
    }
    delay(delayCalc);

    for (int i = 15; i >= 8; i--) {
      uint8_t maskB = 1 << i - 8;
      uint8_t tmpB = maskB & memoryB;
      HC595::reg.write(i, (bool)tmpB);
      HC595::reg.update();
    }
    delay(delayCalc);

    for (int i = 14; i <= 21; i++) {
      uint8_t maskC = 1 << i - 14;
      if (!digitalRead(i)) {
        Serial.print("Pin ");
        Serial.print(i);
        Serial.print(" = ");
        Serial.println(!digitalRead(i));

        memoryC |= maskC;  //| 00001000
      } else {
        memoryC &= ~maskC;  //& 11110111
      }
    }

    for (int i = 0; i <= 15; i++) {
      HC595::reg.write(i, 0);
      HC595::reg.update();
      delay(5);
    }
    flagInteger == 1 ? integer = memoryC : fraction = memoryC;
    flagInteger = 0;
  } while (flagFraction == 1);

  if ((memoryA + memoryB) != memoryC) {
    missCount++;
  }
  return integer + 1.0 * fraction / 10;
}

uint8_t RelayCalc::CalcSum(uint8_t a, uint8_t b, uint8_t delayCalc = 30) {

  memoryA = a;
  memoryB = b;

  for (int i = 7; i >= 0; i--) {
    uint8_t maskA = 1 << i;
    uint8_t tmpA = maskA & memoryA;
    HC595::reg.write(i, (bool)tmpA);
    HC595::reg.update();
  }
  //    delay(delayCalc);

  for (int i = 15; i >= 8; i--) {
    uint8_t maskB = 1 << i - 8;
    uint8_t tmpB = maskB & memoryB;
    HC595::reg.write(i, (bool)tmpB);
    HC595::reg.update();
  }
  delay(delayCalc);

  for (int i = 14; i <= 21; i++) {
    uint8_t maskC = 1 << i - 14;
    if (!digitalRead(i)) {
      memoryC |= maskC;  //| 00001000
    } else {
      memoryC &= ~maskC;  //& 11110111
    }
  }

  for (int i = 0; i <= 15; i++) {
    HC595::reg.write(i, 0);
    HC595::reg.update();
  }
  delay(5);


  if ((memoryA + memoryB) != memoryC) {
    missCount++;
  }
  return memoryC;
}

uint32_t RelayCalc::multiplication(uint8_t a, uint8_t b, uint8_t delayCalc = 30) {

  uint32_t tmp = 0;
  uint32_t maxTmp = 0;

  uint16_t count = 0;
  uint8_t arr[512] = {};

  uint16_t minTmp = 0;
  uint8_t thresholdNumber = 130;
  if (a > b) {
    minTmp = b;
    maxTmp = a;
  } else {
    minTmp = a;
    maxTmp = b;
  }
  tmp = maxTmp;

  const uint8_t constTmp = maxTmp;

  for (uint16_t i = minTmp; i > 1; i--) {
    maxTmp = constTmp;
    if (maxTmp > thresholdNumber) {
      maxTmp -= thresholdNumber;
      count = count + 1;
    }
    if (tmp > thresholdNumber) {
      tmp -= thresholdNumber;
      count = count + 1;
    }
    //        Serial.print("TMP ");
    //        Serial.println(tmp);
    //        Serial.print("maxTMP ");
    //        Serial.println(maxTmp);

    tmp = CalcSum(tmp, maxTmp, delayCalc);
  }

  uint32_t sum = 0;

  sum = count * thresholdNumber + tmp;

  //    cout << "Count: "  << (unsigned)count  << '\n';
  //    cout << "Tmp: "    << (unsigned)tmp    << '\n';
  //    cout << "Sum: "    << (unsigned)sum    << '\n';
  //    cout << "AllSum: " << (unsigned)AllSum << '\n';
  //    cout << "--------" << '\n';
  return sum;
}

float RelayCalc::division(uint8_t a, uint8_t b, uint8_t numberOfNumbers, uint8_t delayCalc) {

  uint8_t integer = 0;
  uint8_t fractional = 0;
  float result = 0;
  uint8_t count = 0;
  uint8_t arr[numberOfNumbers] = {};

  if (b != 1 && a != 1) {
    while (a >= b) {
      a = Subtraction(a, b, delayCalc * 1.3);
      integer++;
    }

    //    Serial.println();
    //    Serial.print(integer);
    //    Serial.print(",");

    for (uint8_t i = 0; i < numberOfNumbers; i++) {
      if (a < b) {
        if (a != 0) {
          a = multiplication(a, 10, delayCalc);
        }
      }
      while (a >= b) {
        a = Subtraction(a, b, delayCalc * 1.3);
        fractional++;
      }
      arr[count] = fractional;
      count++;

      //      Serial.print(fractional);
      //      Serial.println();

      fractional = 0;
    }
    result = integer;
    result = integer + 1.0 * arr[0] / 10;
    //    result = integer + 1.0 * arr[1]/100;
    //    result = integer + 1.0 * arr[2]/1000;
    return result;
  } else {
    Serial.println(a / b);
    return a / b;
  }
}

uint8_t RelayCalc::Sqrt(uint8_t a, uint8_t delayCalc) {

  for (uint8_t i = 1; i < a; i++) {
    if (multiplication(i, i, delayCalc) == a) {
      return i;
    }
  }
  return 0;

  //   float rslt = (unsigned)a; // По формуле Ньютона http://codenet.ru/progr/alg/sqrt.php
  //      float divF = a;
  //      float divF0 = a;
  //      if (a <= 0)
  //            return 0;
  //      while (1)
  //      {
  //          float tmp1 = (unsigned)a / (unsigned)divF;
  //          uint8_t tmp2 = CalcSum((unsigned)tmp1, (unsigned)divF, delayCalc);
  //          float tmp = (float)tmp2 / 2;
  //            divF =  tmp / 2;
  //
  //            if (rslt > divF)
  //                   rslt = (unsigned)divF;
  //            else
  //                   return rslt;
  //      }
  //
}

void RelayCalc::bencmark() {
  int number;
  for (number = 1; number < 20; number++) {

    for (int i = 2; i < 50; i += 2) {

      Serial.print("Числа(x * x): ");
      Serial.println(number);
      Serial.print("Результат: ");
      Serial.println(multiplication(number, number, i));
      Serial.print("Скорость мс: ");
      Serial.println(i);
      Serial.print("Колличество ошибок вычисления: ");
      Serial.println(missCount);
      missCount = 0;
    }
  }
}
uint8_t RelayCalc::GetMemoryValue(uint8_t memoryNumber) {

  switch (memoryNumber) {
    case 1:
      return memoryA;
    case 2:
      return memoryB;
    case 3:
      return memoryC;
    default:
      return 0;
  }
}

uint8_t& RelayCalc::GetMemoryAdress(uint8_t memoryNumber) {

  switch (memoryNumber) {
    case 1:
      return memoryA;
    case 2:
      return memoryB;
    case 3:
      return memoryC;
    default:
      return memoryA;
  }
}

void RelayCalc::coutMem(uint8_t number) {

  //    cout << '\n';

  for (int8_t i = bits - 1; i >= 0; i--) {
    //            cout << bitValue(i, number);
  }
}

void RelayCalc::TransferDecimalToTwo(uint8_t number, uint8_t addres) {

  uint8_t base = 2;

  for (uint8_t i = 0; i < bits; i++) {
    setBitValue(i, (number % base), addres);
    number = number / base;
    // cout << tmpArr[i];
  }
}

void RelayCalc::setBitValue(const uint8_t bitIndex, const bool value, uint8_t addres) {
  uint8_t& tmp = GetMemoryAdress(addres);

  uint8_t mask = 1 << bitIndex;
  if (value) {
    tmp |= mask;  //| 00001000
  } else {
    tmp &= ~mask;  //& 11110111
  }
}

bool RelayCalc::bitValue(const uint8_t bitIndex, uint8_t addres) {
  uint8_t mask = 1 << bitIndex;
  return (mask & GetMemoryValue(addres));
}
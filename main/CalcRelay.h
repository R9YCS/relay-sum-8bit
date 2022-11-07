#pragma once

#include <stdint.h>

class RelayCalc {

    public:
      
      RelayCalc() {};
      ~RelayCalc() {};

      uint8_t Subtraction(uint8_t a, uint8_t b, uint8_t delayCalc); // Вычитание
      
      float CalcSumFloat(float a, float b, uint8_t delayCalc); // Сумма с плавающей запятой
      uint8_t CalcSum(uint8_t a, uint8_t b, uint8_t delayCalc); // Сумма с целыми числами
      
      uint32_t multiplication(uint8_t a, uint8_t b, uint8_t delayCalc); // Умножение целых чисел
      
      float division(uint8_t a, uint8_t b, uint8_t numberOfNumbers, uint8_t delayCalc); // Деление целых чисел

      uint8_t Sqrt(uint8_t a, uint8_t delayCalc); // Корень (целочисленный)
      
      void bencmark(); // Тест всех реле на скорость и задержку

    private:

      void TransferDecimalToTwo(uint8_t number, uint8_t addres);

      uint8_t GetMemoryValue(uint8_t memoryNumber);
      uint8_t& GetMemoryAdress(uint8_t memoryNumber);
      void setBitValue(const uint8_t bitIndex, const bool value, uint8_t addres);
      bool bitValue(const uint8_t bitIndex, uint8_t addres);

      uint8_t invert(uint8_t a);

      void coutMem(uint8_t number);

      static const uint8_t bits = 8;
      
      uint16_t missCount = 0; // Счетчик ошибок при рассчетах(для bencmark())

      uint8_t memoryA = 0; // Значения регистра A
      uint8_t memoryB = 0; // Значения регистра B
      uint8_t memoryC = 0; // Значения регистра С(результат)

      uint64_t AllSum = 0;
    
};

#pragma once

#include <stdint.h>

class RelayCalc {

    public:
    
    RelayCalc() {};
    ~RelayCalc() {};

    void coutMem(uint8_t number);
    
    uint8_t invert(uint8_t a);

    uint8_t Subtraction(uint8_t a, uint8_t b, uint8_t delayCalc);
    
    float CalcSumFloat(float a, float b, uint8_t delayCalc);
    uint8_t CalcSum(uint8_t a, uint8_t b, uint8_t delayCalc);
    
    uint32_t multiplication(uint8_t a, uint8_t b, uint8_t delayCalc);
    
    float division(uint8_t a, uint8_t b, uint8_t numberOfNumbers, uint8_t delayCalc);

    uint8_t Sqrt(uint8_t a, uint8_t delayCalc);
    
    void bencmark();

    void TransferDecimalToTwo(uint8_t number, uint8_t addres);

    uint8_t GetMemoryValue(uint8_t memoryNumber);
    uint8_t& GetMemoryAdress(uint8_t memoryNumber);

    void setBitValue(const uint8_t bitIndex, const bool value, uint8_t addres);
    bool bitValue(const uint8_t bitIndex, uint8_t addres);

    uint16_t missCount = 0;
    private:

    static const uint8_t bits = 8; 

    uint8_t memoryA = 0;
    uint8_t memoryB = 0;
    uint8_t memoryC = 0;

    uint64_t AllSum = 0;
    
};

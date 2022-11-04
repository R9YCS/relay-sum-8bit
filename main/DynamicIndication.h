#pragma once

#include <stdint.h>
#include <Vector.h>

class DynamicIndication {

    public:
    
    DynamicIndication() {};
    ~DynamicIndication() {};

    void clear();
    void clearSymbol();
    int32_t returnNumber();
    void writeNumber(int32_t number);
    void err();
    void symbolOutput(uint8_t symbol, uint8_t index);
    void segmentOutput(int8_t segment);
    void screenPrint(int32_t symbol, uint8_t index);
    void refScreen();

    private:
    
    static const uint8_t countSegments = 8;
    int8_t currentScreenSymbol[8] = {};
    int8_t currentScreenSegment[8] = {};

    uint8_t leightCurrent = 0;

    
    
};

#include <stdint.h>
#include "DynamicIndication.h"
#include "HC595_4.h"

const int8_t ELEMENT_COUNT_MAX = 10;
int8_t storage_array[ELEMENT_COUNT_MAX];
typedef Vector<int8_t> symbols;
symbols vector(storage_array);


void DynamicIndication::clear() {
  vector.clear();
  segmentOutput(16);
}

void DynamicIndication::clearSymbol() {
  if(vector.size() == 1) {
    clear();
  } else {
    vector.pop_back();
  }
}

int32_t DynamicIndication::returnNumber() {
  int32_t tmp = 0;
  for(int i = 0; i < vector.size(); i++) {
    tmp = tmp * 10 + vector[i];
  }
  clear();
  return tmp;
}
void DynamicIndication::writeNumber(int32_t number) {
  clear();
  int32_t tmpN = number;
  uint8_t countNumber = 0;
  while(tmpN > 0) {
    countNumber++;
    tmpN /= 10;
  }
  tmpN = number;
  // Serial.print("Number = ");
  // Serial.println(tmpN);
  // Serial.print("countNumber = ");
  // Serial.println(countNumber);
  vector.assign(countNumber, 0);
  for(int i = countNumber - 1; i >= 0; i--) {
    vector[i] = tmpN % 10;
    tmpN /= 10;
  }
}

void DynamicIndication::writeNumberF(float number) {
  clear();
  float tmpN = ceil(number * 10) / 10;
  uint16_t tmpNumerator = (uint16_t)tmpN;
  uint16_t tmpDenumerator = ceil(((tmpN - tmpNumerator) * 100.0)) / 10;
  uint8_t countNumber = 0;
  
  // Serial.print("tmpNumerator = ");
  // Serial.println(tmpNumerator);
  // Serial.print("tmpDenumerator = ");
  // Serial.println(tmpDenumerator);

  uint8_t Numerator = tmpNumerator;
  while(tmpNumerator > 0) {
    countNumber++;
    tmpNumerator /= 10;
  }
  tmpNumerator = Numerator;

  uint8_t Denumerator = tmpDenumerator;
  
  while(tmpDenumerator > 0) {
    countNumber++;
    tmpDenumerator /= 10;
  }
  tmpDenumerator = Denumerator;
  vector.assign(countNumber, 0);

  Serial.print("countNumber = ");
  Serial.println(countNumber);

  for(int i = countNumber - 1; i >= 0; i--) {
    if(tmpNumerator > 0) {
      vector[i] = tmpNumerator % 10;
      tmpNumerator /= 10;
    } 
  }
  
  if (tmpDenumerator > 0) {
    vector[countNumber - 1] *= 100;
    vector.push_back(tmpDenumerator % 10);
    tmpDenumerator /= 10;
    vector.remove(0);
  }
}

void DynamicIndication::err() {
  clear();
  vector.push_back('E');
  vector.push_back('R');
  vector.push_back('R');
  refScreen();
}

void DynamicIndication::symbolOutput(uint16_t symbol, bool floatNumber) {
  
  for(int i = 7; i >= 0; i--) {
    HC595::reg.write(16 + i, 0); 
  }
  HC595::reg.update();
  switch(symbol) {

  case 0: 
    HC595::reg.write(23,1); 
    HC595::reg.write(19,1);
    break;
  case 1:
    HC595::reg.write(16,1);
    HC595::reg.write(19,1); 
    HC595::reg.write(20,1);  
    HC595::reg.write(21,1); 
    HC595::reg.write(22,1); 
    HC595::reg.write(23,1);    
    break;
  case 2:
    HC595::reg.write(18,1); 
    HC595::reg.write(19,1); 
    HC595::reg.write(22,1);  
    break;
  case 3: 
    HC595::reg.write(19,1); 
    HC595::reg.write(21,1); 
    HC595::reg.write(22,1); 
    break;
  case 4:
    HC595::reg.write(16,1);
    HC595::reg.write(19,1); 
    HC595::reg.write(20,1);  
    HC595::reg.write(21,1); 
    break;
  case 5:
    HC595::reg.write(17,1);
    HC595::reg.write(19,1);  
    HC595::reg.write(21,1);   
    break;
  case 6:
    HC595::reg.write(17,1);
    HC595::reg.write(19,1);  
    break;
  case 7:
    HC595::reg.write(19,1); 
    HC595::reg.write(20,1);  
    HC595::reg.write(21,1); 
    HC595::reg.write(22,1); 
    HC595::reg.write(23,1);   
    break;
  case 8:
    HC595::reg.write(19,1);   
    break;
  case 9:
    HC595::reg.write(19,1);   
    HC595::reg.write(21,1);    
    break;

  case 999: // костыль для запятых :3
    HC595::reg.write(23,1); 
    break;
  case 100:
    HC595::reg.write(16,1);
    HC595::reg.write(20,1);  
    HC595::reg.write(21,1); 
    HC595::reg.write(22,1); 
    HC595::reg.write(23,1);    
    break;
  case 200:
    HC595::reg.write(18,1); 
    HC595::reg.write(22,1);  
    break;
  case 300: 
    HC595::reg.write(21,1); 
    HC595::reg.write(22,1); 
    break;
  case 400:
    HC595::reg.write(16,1);
    HC595::reg.write(20,1);  
    HC595::reg.write(21,1); 
    break;
  case 500:
    HC595::reg.write(17,1);
    HC595::reg.write(21,1);   
    break;
  case 600:
    HC595::reg.write(17,1);
    break;
  case 700:
    HC595::reg.write(20,1);  
    HC595::reg.write(21,1); 
    HC595::reg.write(22,1); 
    HC595::reg.write(23,1);   
    break;
  case 800:
    break;
  case 900: 
    HC595::reg.write(21,1);    
    break;

    
  case 'A':
    HC595::reg.write(16,1);
    HC595::reg.write(17,1);
    HC595::reg.write(18,1);
    HC595::reg.write(19,1); 
    HC595::reg.write(21,1);  
    HC595::reg.write(22,1); 
    HC595::reg.write(23,1); 
    break;
  case 'B':
    HC595::reg.write(18,1);
    HC595::reg.write(19,1); 
    HC595::reg.write(20,1);  
    HC595::reg.write(21,1);  
    HC595::reg.write(22,1); 
    HC595::reg.write(23,1); 
    break;
  case 'C':
    HC595::reg.write(16,1);
    HC595::reg.write(19,1); 
    HC595::reg.write(20,1);  
    HC595::reg.write(21,1);  
    HC595::reg.write(22,1); 
    break;  
  case 'D':
    HC595::reg.write(17,1);
    HC595::reg.write(18,1);
    HC595::reg.write(19,1); 
    HC595::reg.write(20,1);  
    HC595::reg.write(21,1);  
    HC595::reg.write(23,1); 
    break;  
  case 'E':
    HC595::reg.write(19,1); 
    HC595::reg.write(17,1);
    HC595::reg.write(18,1);
    break;
  case 'F':
    HC595::reg.write(16,1);
    HC595::reg.write(19,1);  
    HC595::reg.write(21,1);  
    HC595::reg.write(22,1); 
    HC595::reg.write(23,1); 
    break;  
  case 'G':
    HC595::reg.write(16,1);
    HC595::reg.write(17,1);
    HC595::reg.write(18,1);
    HC595::reg.write(19,1); 
    HC595::reg.write(20,1);   
    HC595::reg.write(22,1); 
    HC595::reg.write(23,1); 
    break;  
  case 'H':
    HC595::reg.write(18,1);
    HC595::reg.write(19,1); 
    HC595::reg.write(21,1);  
    HC595::reg.write(22,1); 
    HC595::reg.write(23,1); 
    break;
  case 'I':
    HC595::reg.write(16,1);
    HC595::reg.write(17,1);
    HC595::reg.write(19,1); 
    HC595::reg.write(20,1);  
    HC595::reg.write(21,1);  
    HC595::reg.write(22,1); 
    HC595::reg.write(23,1); 
    break;
  case 'J':
    HC595::reg.write(17,1);
    HC595::reg.write(18,1);
    HC595::reg.write(19,1); 
    HC595::reg.write(20,1);  
    HC595::reg.write(21,1);  
    break;
  case 'K':
    HC595::reg.write(17,1);
    HC595::reg.write(18,1);
    HC595::reg.write(19,1);  
    HC595::reg.write(21,1);  
    HC595::reg.write(22,1); 
    HC595::reg.write(23,1); 
    break;
  case 'L':
    HC595::reg.write(16,1);
    HC595::reg.write(17,1);
    HC595::reg.write(18,1);
    HC595::reg.write(19,1); 
    HC595::reg.write(23,1); 
    break;
  case 'M':
    HC595::reg.write(17,1);
    HC595::reg.write(19,1); 
    HC595::reg.write(20,1);  
    HC595::reg.write(22,1); 
    HC595::reg.write(23,1); 
    break;
  case 'N':
    HC595::reg.write(16,1);
    HC595::reg.write(17,1);
    HC595::reg.write(19,1); 
    HC595::reg.write(20,1);    
    HC595::reg.write(22,1); 
    break;
  case 'O':
    HC595::reg.write(16,1);
    HC595::reg.write(17,1);
    HC595::reg.write(19,1);  
    HC595::reg.write(22,1); 
    break;
  case 'P':
    HC595::reg.write(18,1);
    HC595::reg.write(19,1); 
    HC595::reg.write(20,1);   
    break;
  case 'Q':
    HC595::reg.write(19,1);
    HC595::reg.write(20,1);  
    HC595::reg.write(21,1);  
    break;
  case 'R':
    HC595::reg.write(16,1);
    HC595::reg.write(17,1);
    HC595::reg.write(18,1);
    HC595::reg.write(19,1); 
    HC595::reg.write(20,1);  
    HC595::reg.write(22,1); 
    break;
  case 'S':
    HC595::reg.write(16,1);
    HC595::reg.write(18,1);
    HC595::reg.write(19,1); 
    HC595::reg.write(20,1);  
    HC595::reg.write(22,1); 
    HC595::reg.write(23,1); 
    break;
  case 'T':
    HC595::reg.write(16,1);
    HC595::reg.write(17,1);
    HC595::reg.write(18,1);
    HC595::reg.write(19,1); 
    break;
  case 'U':
    HC595::reg.write(16,1);
    HC595::reg.write(19,1); 
    HC595::reg.write(23,1); 
    break;
  case 'V':
    HC595::reg.write(16,1);
    HC595::reg.write(17,1);
    HC595::reg.write(19,1);  
    HC595::reg.write(22,1); 
    HC595::reg.write(23,1); 
    break;
  case 'W':
    HC595::reg.write(16,1);
    HC595::reg.write(18,1);
    HC595::reg.write(19,1); 
    HC595::reg.write(21,1);  
    HC595::reg.write(23,1); 
    break;
  case 'X':
    HC595::reg.write(16,1);
    HC595::reg.write(19,1); 
    HC595::reg.write(20,1);  
    break;
  case 'Y':
    HC595::reg.write(16,1);
    HC595::reg.write(19,1); 
    HC595::reg.write(21,1);  
    break;
  case 'Z':
    HC595::reg.write(18,1);
    HC595::reg.write(19,1); 
    HC595::reg.write(22,1); 
    break;
  }
  if(floatNumber == 1) {
    HC595::reg.write(19,0); 
  }
  HC595::reg.update();
}

void DynamicIndication::segmentOutput(int8_t segment) {
  
  for(int i = 0; i <= 7; i++) {
    HC595::reg.write(24 + i, 1); 
  }

  HC595::reg.update();
  switch(segment) {

  case 0: 
    HC595::reg.write(24,0); 
    break;
  case 1:
    HC595::reg.write(25,0);  
    break;
  case 2:
    HC595::reg.write(26,0); 
    break;
  case 3: 
    HC595::reg.write(27,0); 
    break;
  case 4:
    HC595::reg.write(28,0);
    break;
  case 5:
    HC595::reg.write(30,0);
    break;
  case 6:
    HC595::reg.write(29,0);
    break;
  case 7:
    HC595::reg.write(31,0);   
    break;
  case 8:
    HC595::reg.write(32,0);   
    break;
  case 16: 
    break;
  }
  HC595::reg.update();
}

void DynamicIndication::screenPrint(int32_t symbol, uint8_t index) {
  vector.push_back(symbol);
  refScreen();
}
void DynamicIndication::refScreen() {

  for(int i = 0; i < vector.size(); i++) {

    // Serial.print("Vector i = ");
    // Serial.println(vector[i]);
    // Serial.print("i = ");
    // Serial.println(i);
    // Serial.print("vector.size = ");
    // Serial.println(vector.size());
    
    symbolOutput(vector[i], 0);
    segmentOutput(vector.size() - i - 1);
    delay(2);
  }
  
 }

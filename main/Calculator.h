#include "KeyBoard.h" // Класс работы с клавиатурой 5х5 на сдвиговых регистрах паралельно - последовательного преобразования hc165
#include "DynamicIndication.h" // Класс работы с вакумным дисплеем IV28 на регистрах последовательно - паралельного преобразования hc595
#include "CalcRelay.h" // Ядро вычисления на реле

#include "HC165_2.h" // Объект класса для работы с hc165
#include "HC595_4.h" // Объект класса для работы с hc595
#include <Vector.h> // Класс костыль от "Peter", который имеет подобие std::vector только для ардуино(так как std нет в arduino), использует статическую память а не динамическую 

class Calculator: public Keyboard, public DynamicIndication, public RelayCalc {

  public:
  Calculator() {};
  ~Calculator() {};

  void tick() { // Метод который должен крутиться всегда в Loop, проверяет на нажатие и обновляет экран
    if (HC165::shift.update() && millis() - btnTimer > 100) {
      btnTimer = millis();
      mainLogic();
    }
    IV28.refScreen();
  }

  void mainLogic();

  private:

    uint8_t multA = 0;
    uint8_t multB = 0;
    uint8_t currentOperation = 0;

    uint32_t btnTimer = 0;
    uint32_t clearTimer = 0;

    DynamicIndication IV28;
    Keyboard BM23;
    RelayCalc calc;

};
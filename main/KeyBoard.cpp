#include "HC165_2.h"
#include "KeyBoard.h"


int8_t Keyboard::currentSymbol() {
  int8_t tmp = -1;
  if (!HC165::shift.state(6) && !HC165::shift.state(7) && !HC165::shift.state(5)) tmp = 0;
  if (!HC165::shift.state(4) && !HC165::shift.state(7)) tmp = 1;
  if (!HC165::shift.state(4) && !HC165::shift.state(12)) tmp = 2;
  if (!HC165::shift.state(4) && !HC165::shift.state(14)) tmp = 3;
  if (!HC165::shift.state(7) && !HC165::shift.state(15)) tmp = 4;
  if (!HC165::shift.state(12) && !HC165::shift.state(15)) tmp = 5;
  if (!HC165::shift.state(14) && !HC165::shift.state(15)) tmp = 6;
  if (!HC165::shift.state(7) && !HC165::shift.state(8)) tmp = 7;
  if (!HC165::shift.state(8) && !HC165::shift.state(12)) tmp = 8;
  if (!HC165::shift.state(8) && !HC165::shift.state(14)) tmp = 9;
  if (!HC165::shift.state(9) && !HC165::shift.state(10)) tmp = '=';                           //61 =
  if (!HC165::shift.state(6) && !HC165::shift.state(12) && !HC165::shift.state(5)) tmp = 46;  // .
  if (!HC165::shift.state(10) && !HC165::shift.state(15)) tmp = 42;                           // *
  if (!HC165::shift.state(10) && !HC165::shift.state(4)) tmp = 45;                            // -
  if (!HC165::shift.state(5) && !HC165::shift.state(10) && !HC165::shift.state(6)) tmp = 43;  // +
  if (!HC165::shift.state(10) && !HC165::shift.state(8)) tmp = 47;                            // /
  if (!HC165::shift.state(9) && !HC165::shift.state(7)) tmp = 99;                             // clear
  if (!HC165::shift.state(11) && !HC165::shift.state(14)) tmp = 's';                          // sqrt
  if (!HC165::shift.state(9) && !HC165::shift.state(14)) tmp = '%';                           // %
  if (!HC165::shift.state(9) && !HC165::shift.state(12)) tmp = 'r';                           // reg switch
  return tmp;
}
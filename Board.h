#ifndef CS_204_HW3_BOARD_H
#define CS_204_HW3_BOARD_H
#include "CharStack.h"

struct slot{
    slot * next;
    slot * prev;
    CharStack slotStack;
    slot()          //empty constructor
    { }
};

class Board{
private:
    slot * head;
    slot * tail;
    int xCount;
    int oCount;
public:
    Board();            //default constructor
    bool noMove(char player, int die);
    int validMove(char player, int startingIndex, int steps, int direction);
    void movePiece(int startingIndex, int targetIndex);
    void printBoard();
    int evaluateGame();
    bool targetSlotFull(int slotIndex);
    void destroySlot(int slotIndex);
    void createSlotBegin(char player, int num);
    void createSlotEnd(char player, int num);
    void createEmptySlotEnd();
    void clearBoard();
};

#endif //CS_204_HW3_BOARD_H

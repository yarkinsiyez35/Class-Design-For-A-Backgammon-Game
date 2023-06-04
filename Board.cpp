#include "Board.h"
#include <iostream>
using namespace std;

Board::Board()          //default constructor
{
    head = nullptr;
    tail = nullptr;
    xCount =0;
    oCount =0;
}

bool Board::noMove(char player, int die)            //returns true if there are no possible moves
{
    /* finding players slots*/
    //check each slot, if a slot has that piece, check for the die many to the left and to the right
    slot * temp = head;                     //a temporary slot * is created to traverse through the list
    int count = 0;                          //keeps the count to know which index we are at
    char slotPiece = ' ';                   //will find the if the piece on the current node is 'X' or 'O'
    bool boolForFunctions;              //necessary for pop and push functions
    while(temp != nullptr)          //starts the traversal
    {
        if (!temp->slotStack.isEmpty())         //if the slot is not empty
        {
            boolForFunctions = temp->slotStack.pop(slotPiece);              //pops one element to see if it is 'X' or 'O'
            boolForFunctions = temp->slotStack.push(slotPiece);                //pushes back the same element to the stack
            if (slotPiece == player)            //if that slot has the same piece
            {
                /*traversal to the right */
                slot * candidate = temp;            //creates a candidate pointer to traverse to the right and left
                bool inRange = true;                //creates a boolean variable to know if we are out of the list range
                for (int i =0; i< die; i++)             //traversal to the right
                {
                    if (candidate == nullptr)           //if there are no nodes remaining
                    {
                        inRange = false;                //sets it as false since we are out of the list range
                        break;                          //breaks the loop because it is unnecessary to continue
                    }
                    candidate = candidate->next;        //goes to the next node
                }
                if (candidate == nullptr)               //final check for the last iteration as it is not checked in the loop
                {
                    inRange = false;
                }
                if (inRange)        //if candidate is actually a node
                {
                    if(!candidate->slotStack.isFull())          //if the stack is not full
                    {
                        if (candidate->slotStack.isEmpty())         //if the node is empty, it is a valid move
                        {
                            return false;
                        }
                        boolForFunctions = candidate->slotStack.pop(slotPiece);              //pops one element to see if it is 'X' or 'O'
                        boolForFunctions = candidate->slotStack.push(slotPiece);                //pushes back the same element to the stack to keep it the same
                        if (slotPiece == player)            //if the pieces are the same, there is a valid move
                        {
                            return false;
                        }
                    }
                }
                /*traversal to the left */
                candidate = temp;               // returns candidate pointer back to the current node
                inRange = true;             //sets inRange to true because the same procedure will be carried again
                for (int i =0; i<die; i++)          //traversal to the left die many times
                {
                    if (candidate == nullptr)          //if the list is over
                    {
                        inRange = false;            //sets inRange to false because we are out of the index range
                        break;                      //breaks the loop because it is not necessary to go on
                    }
                    candidate = candidate->prev;          //shifts left by one
                }
                if (candidate == nullptr)              //check for the last iteration
                {
                    inRange = false;
                }
                if (inRange)            //if candidate is a node in the list
                {
                    if (!candidate->slotStack.isFull())         //if the stack is not full
                    {
                        if (candidate->slotStack.isEmpty())     //if the stack is empty, it is a valid move
                        {
                            return false;
                        }
                        boolForFunctions = candidate->slotStack.pop(slotPiece);          //pops one element to see if it is 'X' or 'O'
                        boolForFunctions = candidate->slotStack.push(slotPiece);             //pushes back the same element to the stack to keep it the same
                        if (slotPiece == player)            //if the pieces are the same, there is a valid move
                        {
                            return false;
                        }
                    }
                }

            }
        }
        temp = temp->next;              //goes to the next node
        count++;
    }
    return true;                   //program will only reach here if there is not a match, so it will return true
}

int Board::validMove(char player, int startingIndex, int steps, int direction)          //returns 0 if the move is valid, returns other numbers depending on type of error
{
    slot * temp = head;             //creates a temporary pointer to do operations

    /*Case 1: starting index is out of bounds */
    if (startingIndex <0)               //indexing starts from 0 so it cannot be negative
    {
        return 1;
    }
    for (int i =0; i< startingIndex; i++)           //shifts to reach the startingIndex
    {
        if (temp == nullptr)                        //if temp is not pointing to a node, meaning it is out of index
        {
            return 1;                               //returns 1 as requested
        }
        temp = temp->next;
    }
    if (temp == nullptr)                    //check for the final iteration
    {
        return 1;
    }

    /*Case 4: Starting index does not belong the player */          //this case is done before others because there is no need to do computations if the startingIndex does not belong to the player
    if (temp->slotStack.isEmpty())              //if the stack is empty, it does not belong to the player
    {
        return 4;                       // returns 4 as requested
    }
    bool boolForFunctions;              //necessary for functions to work
    char element = ' ';             //this will become 'X' or 'O' after pop function
    boolForFunctions = temp->slotStack.pop(element);                //pops one element and updates element to 'X' or 'O'
    boolForFunctions = temp->slotStack.push(element);                   //pushes the same element to keep the stack same
    if (player != element)              //if the player's piece is different from the piece in the slot
    {
        return 4;
    }

    /*Case 2: target index is out of bounds */
    if (direction == 0)         //traverse to the left
    {
        for (int i = 0; i<steps; i++)
        {
            if (temp == nullptr)                //if it is out of index
            {
                return 2;                       //returns 2 as requested
            }
            temp = temp->prev;              //goes to the left
        }
        if (temp == nullptr)                //check for the final iteration
        {
            return 2;
        }
    }
    else                        //traverse to the right
    {
        for (int i = 0; i<steps; i++)
        {
            if (temp == nullptr)                //if it is out of index
            {
                return 2;                       //returns 2 as requested
            }
            temp = temp->next;              //goes to the right
        }
        if (temp == nullptr)                //check for the final iteration
        {
            return 2;
        }
    }

    /*Case 3: target slot index is not available */
    if (temp->slotStack.isFull())                   //if the stack is full, it won't be available
    {
        return 3;                                   //returns 3 as requested
    }
    if (!temp->slotStack.isEmpty())                 //if the stack is not empty, checks for the stack's piece
    {
        boolForFunctions = temp->slotStack.pop(element);                //pops one element and updates element to 'X' or 'O'
        boolForFunctions = temp->slotStack.push(element);                   //pushes the same element to keep the stack same
        if (player != element)              //if the player's piece is different from the piece in the slot
        {
            return 3;
        }
    }

    /*Case 0 */
    return 0;                    //returns 0 if it is valid


}

void Board::movePiece(int startingIndex, int targetIndex)  //removes one piece from startingIndex, adds one piece to targetIndex
{
    slot * temp = head;     //declares a variable to traverse the list
    for (unsigned int i =0; i<startingIndex; i++)       //slides startingIndex many times to the right to find the slot
    {                                                   //since slotIndex is always valid, there will not be an error for any case
        temp = temp->next;
    }
    char element = ' ';         //declares an empty character
    bool boolForPop;            //necessary for pop function to work
    boolForPop = temp->slotStack.pop(element);       //removes one piece from the startingIndex and updates the element as 'X' or 'O'
    int difference = startingIndex - targetIndex;    //finds the relative distance of indices
    if (difference  > 0)                //if targetIndex is to the left of startingIndex
    {
        for (unsigned int i = 0; i<difference; i++)         //slides temp, difference many times to the left of the slot
        {
            temp = temp->prev;
        }
        bool boolForPush;                           //necessary for push function to work
        boolForPush = temp->slotStack.push(element);                  //adds one 'X' or 'O' to the targetIndex
    }
    else                                //if difference < 0
    {                                   //if targetIndex is to the right of the startingIndex
        difference *= -1;               //converts difference to a positive value to use in the for loop
        for (unsigned int i =0; i< difference; i++)                 //slides temp, difference many times to the right of the slot
        {
            temp = temp->next;
        }
        bool boolForPush;               //necessary for push function to work
        boolForPush = temp->slotStack.push(element);              //adds one 'X' or 'O' to the targetIndex
    }
}

void Board::printBoard()            //prints the board
{
    int columns = 0;            //columns will keep number of columns to use in the for loop
    slot * temp = head;         //creates a temporary pointer to traverse the list
    while (temp != nullptr)
    {
        temp = temp->next;          //goes to the next node
        columns++;                  //increments column by 1
    }
    cout << endl;               // this is first row

    for (int i =0; i<3; i++)    //there are three rows in a stack
    {
        string row = "";            //a string that will be printed for each row
        temp = head;                //sets temp to the beginning
        for (int j = 0 ; j<columns; j++)            //this will iterate through each stack
        {
            if (temp->slotStack.isEmpty())          //if the stack is empty, it will not print anything
            {
                row += " ";
            }
            else if (temp->slotStack.isFull())      //if the stack is full, it will print the piece for every row
            {
                char piece = ' ';               //this piece will be 'X' or 'O'
                bool boolForFunctions;          //necessary for pop and push functions to work
                boolForFunctions = temp->slotStack.pop(piece);          //pops one from the stack to update piece
                boolForFunctions = temp->slotStack.push(piece);             //pushes piece to keep the stack same
                row += piece;                       //adds the piece to the row
            }
            else                        //if the stack is not full or empty
            {
                //pop n many times, can be done with boolean
                bool boolForPop = true;             //sets boolForPop true as it will be the condition of the while loop
                int count = 0;                      //sets count to 0, will increment for each successful pop operation
                char piece = ' ';
                while (boolForPop)              //this loop will stop when the stack becomes empty
                {
                    boolForPop = temp->slotStack.pop(piece);            //pops a piece from the stack and returns true if popping is successful
                    count++;                                                //increments count since it is successful
                }
                count--;            //decrements count by one since we increment count one last time even though pop was not successful

                // push n many times to not modify the stack
                for (int k =0; k<count; k++)                //adds the pieces back to keep the stack same
                {
                    boolForPop = temp->slotStack.push(piece);
                }

                // find a relation between row number and number of pieces
                if (i+ count > 2)
                {
                    row += piece;
                }
                else
                {
                    row += " ";
                }
            }
            temp = temp->next;          //goes to the next node
        }
        cout << row << endl;
    }
    for (int i =0; i<columns; i++)          //prints the final row
    {
        cout << "^";
    }
    cout << endl;
}

int Board::evaluateGame()           //returns 1 for X, 2 for O , 3 for draw
{
    //returns 1 if x wins
    //returns 2 if o wins
    //returns 3 if draw
    if (xCount < oCount)                //x wins
    {
        return 1;
    }
    else if (oCount < xCount)           //o wins
    {
        return 2;
    }
    else                        //draw
    {
        return 3;
    }
}

bool Board::targetSlotFull(int slotIndex)           //returns true if the slot's stack is full
{
    slot * temp = head;         //declares a variable to traverse the list

    for (int i = 0; i<slotIndex; i++)           //slides slotIndex many times to the right to find the slot
    {                                           //Since slotIndex is assumed to be valid, there will not be an error for any case
        temp = temp->next;
    }
    return temp->slotStack.isFull();        //returns the condition of the stack
}

void Board::destroySlot(int slotIndex)      //destroys the slot with given index
{
    if(slotIndex == 0)      //if it is the first slot
    {
        slot * temp = head;             //creates a temporary slot *
        char element = ' ';             //necessary for pop function to work
        bool boolForPop;                //necessary for pop function to work
        for (unsigned int i= 0; i<4; i++)                   //removes every piece from the stack, this is necessary to update the xCount or oCount
        {
            boolForPop = temp->slotStack.pop(element);
        }
        if (element == 'x')                 //decreases the xCount if the popped element is X
        {
            xCount -= 4;
        }
        else                                //decreases the oCount if the popped element is O
        {
            oCount -= 4;
        }
        temp = temp->next;              //goes to the second element
        temp->prev = nullptr;           //connects the second element to the ground as it is the new head
        delete head;                    //deletes the first node
        head = temp;                    //sets head as the formerly second element
    }
    else            //if it is another slot
    {               //we need to hold previous slot as well
        slot * temp = head;
        for (unsigned int i = 0; i<slotIndex; i++)          //slides slotIndex many times to the right to find the targeted slot
        {
            temp = temp->next;
        }
        slot * previousNode = temp->prev;               //holds the previous node as it is necessary for operations
        slot * nextNode = temp->next;                   //holds the next node as it is necessary for operations
        if (nextNode != nullptr)            //if the desired slot is somewhere in the middle
        {
            previousNode->next = nextNode;          //connects the previousNode with the nextNode
            nextNode->prev = previousNode;          //connects the nextNode with the previousNode
            char element = ' ';             //necessary for pop function to work
            bool boolForPop;                //necessary for pop function to work
            for (unsigned int i = 0; i<4; i++)
            {
                boolForPop = temp->slotStack.pop(element);          //removes every piece from the stack, this is necessary to update the xCount or oCount
            }
            delete temp;                        //deallocates temp
            temp = nullptr;                     //sets temp as nullptr as good practice
            if (element == 'x')                 //decreases the xCount if the popped element is X
            {
                xCount -= 4;
            }
            else                                //decreases the oCount if the popped element is O
            {
                oCount -= 4;
            }
        }
        else                    //the desired slot is the tail
        {
            previousNode->next = nullptr;           //previousNode will become the tail as the current tail will be deleted
            char element = ' ';              //necessary for pop function to work
            bool boolForPop;                //necessary for pop function to work
            for (unsigned int i =0; i<4; i++)               //removes every piece from the stack, this is necessary to update the xCount or oCount
            {
                boolForPop = temp->slotStack.pop(element);
            }
            delete temp;                    //deallocates temp, thus deletes the tail node
            tail = previousNode;            //assigns tail to the previousNode
            if (element == 'x')                 //decreases the xCount if the popped element is X
            {
                xCount -= 4;
            }
            else                                //decreases the oCount if the popped element is O
            {
                oCount -= 4;
            }
        }
    }
}

void Board::createSlotEnd(char player, int num)     //creates a slot at the end of the list
{
    slot * newSlot = new slot;
    if (head == nullptr)        //if it is an empty list
    {
        newSlot->prev = nullptr;                //connects to ground
        newSlot->next = nullptr;                //connects to ground
        head = newSlot;                         //sets newSlot as head
        tail = newSlot;                         //sets newSlot as tail
        bool boolForPush;                       //necessary for push function to work
        for (unsigned int i =0; i<num; i++)     //adds num many 'X' or 'O' to the stack
        {
            boolForPush = newSlot->slotStack.push(player);
        }
        if (player == 'x')                  //increases the xCount by num
        {
            xCount += num;
        }
        else                                //increases the oCount by num
        {
            oCount += num;
        }
    }
    else        //if there is a tail
    {
        newSlot->next = nullptr;            //connects to ground
        newSlot->prev = tail;               //connects newSlot with the previous node
        tail->next = newSlot;               //connects the previous node with newSlot
        tail = newSlot;                     //sets newSlot as tail
        bool boolForPush;                   //necessary for push function to work
        for (unsigned int i =0; i<num; i++)
        {
            boolForPush = newSlot->slotStack.push(player);        //adds num many 'X' or 'O' to the stack
        }
        if (player == 'x')                      //increases the xCount by num
        {
            xCount += num;
        }
        else                                    //increases the oCount by num
        {
            oCount += num;
        }
    }
}

void Board::createSlotBegin(char player, int num)       //creates a slot at the beginning of the list
{
    slot * newSlot = new slot;
    if (head == nullptr)        //if it is an empty list
    {
        newSlot->prev = nullptr;                //connects to ground
        newSlot->next = nullptr;                //connects to ground
        head = newSlot;                         //sets newSlot as head
        tail = newSlot;                         //sets newSlot as tail
        bool boolForPush;                       //necessary for push function to work
        for (unsigned int i =0; i<num; i++)     //adds num many 'X' or 'O' to the stack
        {
            boolForPush = newSlot->slotStack.push(player);
        }
        if (player == 'x')              //increases the xCount by num
        {
            xCount += num;
        }
        else                            //increases the oCount by num
        {
            oCount += num;
        }
    }
    else        //if there is a head
    {
        newSlot->prev = nullptr;        //connects to ground
        newSlot->next = head;           //connects newSlot to the next node
        head->prev = newSlot;           //connects the next node to newSlot
        head = newSlot;                 //sets newSlot as head
        bool boolForPush;                       //necessary for push function to work
        for (unsigned int i =0; i<num; i++)     //adds num many 'X' or 'O' to the stack
        {
            boolForPush = newSlot->slotStack.push(player);
        }
        if (player == 'x')                  //increases the xCount by num
        {
            xCount += num;
        }
        else                                //increases the oCount by num
        {
            oCount += num;
        }
    }
}

void Board::createEmptySlotEnd()        //creates an empty slot at the end of the list
{
    slot * newSlot = new slot;
    if (head == nullptr)         //if it is an empty list
    {
        newSlot->prev = nullptr;        //connects to ground
        newSlot->next = nullptr;        //connects to ground
        head =newSlot;                  //sets newSlot as head
        tail = newSlot;                 //sets newSlot as head
    }
    else            //if there is tail
    {
        newSlot->next = nullptr;        //connects to ground
        newSlot->prev = tail;           //connects to previous node
        tail->next = newSlot;           //connects the previous node to newSlot
        tail = newSlot;                 //sets newSlot as tail
    }
}

void Board::clearBoard()    //deletes every slot in the list
{
    slot * temp = head;
    while (temp!= nullptr)          //for each node in the list
    {
        head = temp->next;          //head becomes the next node
        delete temp;                //deletes the first node
        temp = head;                //temp becomes the next node
    }
    head = nullptr;                 //sets head to nullptr as good practice
    tail = nullptr;                 //sets tail to nullptr as good practice

}


#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <limits>
using namespace std;

#include "Math.h"
#include "Box.h"

enum Direction {
    UP   ,
    DOWN ,
    LEFT ,
    RIGHT,
    ERROR
};

#include "BoxAry.h"

Direction C2D(char dir);
void check(char &dir, BoxAry &ary);
void check(char &choice);

int main()
{
    srand( (unsigned)time(NULL) );

    BoxAry ary;

    for ( ; true ; )
    {
      cout << ary << endl;

      if      ( ary.win() )
              { cout << "您贏了, 分數: " << ary.getScr() << "." << endl;
              }
      else if ( ary.lose() )
              { cout << "您輸了, 分數: " << ary.getScr() << "." << endl;
              }

      if ( ary.win() || ary.lose() )
         {
           char cho;
           cout << "是否再來一局 [Y/N]? ";
           cin >> cho;  check(cho);
           cout << endl;

           if ( cho == 'N' || cho == 'n' )
              { cout << "請按 Enter 鍵離開...";
                cin.ignore();
                cin.get();
                break;
              }

           if ( cho == 'Y' || cho == 'y' )
              { ary.reset();
                continue;
              }
         }

      char dir;
      cout << "[W/A/S/D]? ";
      cin >> dir;  check(dir, ary);
      cout << endl;

      ary.moveNrmal(C2D(dir));
    }

    return 0;
}

Direction C2D(char dir)
{
    if ( dir == 'W' || dir == 'w' )
       { return UP;
       }
    if ( dir == 'S' || dir == 's' )
       { return DOWN;
       }
    if ( dir == 'A' || dir == 'a' )
       { return LEFT;
       }
    if ( dir == 'D' || dir == 'd' )
       { return RIGHT;
       }
    return ERROR;
}

void check(char &dir, BoxAry &ary)
{
    if ( !cin.fail() )
    if ( C2D(dir) != ERROR )
    if ( ary.movePrChk(C2D(dir)) )
       return;

    cout << "不允許的操作, 請再次輸入: ";
    cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin >> dir;

    return check(dir, ary);
}

void check(char &choice)
{
    if ( !cin.fail() )
    if ( choice=='Y' || choice=='y' || choice=='N' || choice=='n' )
       return;

    cout << "不允許的操作, 請再次輸入: ";
    cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin >> choice;

    return check(choice);
}

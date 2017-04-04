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

char D2C(Direction dir);
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

      if ( false )
         {
           cout << "請按 Enter 鍵繼續...";
           cin.get();
         }

      Direction dir = ary.moveAuto();
      cout << "[W/A/S/D]? " << D2C(dir) << endl << endl;

      ary.moveNrmal(dir);
    }

    return 0;
}

char D2C(Direction dir)
{
    if ( dir == UP )
       { return 'W';
       }
    if ( dir == DOWN )
       { return 'S';
       }
    if ( dir == LEFT )
       { return 'A';
       }
    if ( dir == RIGHT )
       { return 'D';
       }
    return '*';
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

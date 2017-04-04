#ifndef BOXARY_H_INCLUDED
#define BOXARY_H_INCLUDED

class BoxAry {
private:
    Box  **ary;
    Box ***pry;
    int  score;

    static const int high = 2048;

public:
    BoxAry();
   ~BoxAry();
    BoxAry(const BoxAry &src);

     int getScr();
    bool win();
    bool lose();

private:
    void aryReset0();
    void aryDeploy();

    void prySetAsA();
    void pryRotate();
    void pryRotate(const int t);
    void pryRotate(Direction dir);

public:
    void reset();

private:
    void moveNoChk(Direction dir);

public:
    bool movePrChk(Direction dir);
    void moveNrmal(Direction dir);
    Direction moveAuto();

    BoxAry& operator=(const BoxAry &src);

    bool operator==(const BoxAry &src);
    bool operator!=(const BoxAry &src);

    friend ostream& operator<<(ostream &out, BoxAry &src);
};

BoxAry::BoxAry() {
    score = 0;


    ary = new Box*[4];
    for ( int i=0 ; i<4 ; ++i )
        { ary[i] = new Box[4];
        }

    aryDeploy();


    pry = new Box**[4];
    for ( int i=0 ; i<4 ; ++i )
        { pry[i] = new Box*[4];
        }

    prySetAsA();
}

BoxAry::~BoxAry() {
    for ( int i=0 ; i<4 ; ++i )
        { delete [] ary[i];
          delete [] pry[i];
        }
    delete [] ary;
    delete [] pry;
}

BoxAry::BoxAry(const BoxAry &src) {
    score = src.score;

    ary = new Box*[4];
    pry = new Box**[4];
    for ( int i=0 ; i<4 ; ++i )
        { ary[i] = new Box[4];
          pry[i] = new Box*[4];
        }

    for ( int i=0 ; i<4 ; ++i )
        { for ( int j=0 ; j<4 ; ++j )
              { ary[i][j] = src.ary[i][j];
                pry[i][j] = &ary[i][j];
              }
        }
}

int BoxAry::getScr() {
    return score;
}

bool BoxAry::win() {
    if ( score >= high )
       { return true;
       }
    return false;
}

bool BoxAry::lose() {
    if ( movePrChk(UP) )
       { return false;
       }
    if ( movePrChk(DOWN) )
       { return false;
       }
    if ( movePrChk(LEFT) )
       { return false;
       }
    if ( movePrChk(RIGHT) )
       { return false;
       }
    return true;
}

void BoxAry::aryReset0() {
    for ( int i=0 ; i<4 ; ++i )
        { for ( int j=0 ; j<4 ; ++j )
              { ary[i][j].reset();
              }
        }
    return;
}

void BoxAry::aryDeploy() {
    int x[2];

    x[0] = rand()%16;
    x[1] = rand()%16;

    for ( ; x[0] == x[1] ; )
        { x[1] = rand()%16;
        }

    ary[ x[0]/4 ][ x[0]%4 ].setBas(1);
    ary[ x[1]/4 ][ x[1]%4 ].setBas(1);

    return;
}

void BoxAry::prySetAsA() {
    for ( int i=0 ; i<4 ; ++i )
        { for ( int j=0 ; j<4 ; ++j )
              { pry[i][j] = &ary[i][j];
              }
        }
    return;
}

void BoxAry::pryRotate() {
    Box ***tmp = new Box**[4];
    for ( int i=0 ; i<4 ; ++i )
        { tmp[i] = new Box*[4];
        }

    for ( int i=0, x=0 ; i<4 ; ++i, ++x )
        { for ( int j=0, y=3 ; j<4 ; ++j, --y )
              { tmp[i][j] = pry[y][x];
              }
        }

    for ( int i=0 ; i<4 ; ++i )
        { delete [] pry[i];
        }
    delete [] pry;

    pry = tmp;

    return;
}

void BoxAry::pryRotate(const int t) {
    for ( int i=0 ; i<t ; ++i )
        { pryRotate();
        }
    return;
}

void BoxAry::pryRotate(Direction dir) {
    if ( dir == UP )
       { return;
       }
    if ( dir == DOWN )
       { pryRotate(2);
         return;
       }
    if ( dir == LEFT )
       { pryRotate(1);
         return;
       }
    if ( dir == RIGHT )
       { pryRotate(3);
         return;
       }
    return;
}

void BoxAry::reset() {
    aryReset0();
    aryDeploy();
    prySetAsA();
    score = 0;
    return;
}

void BoxAry::moveNoChk(Direction dir) {
    pryRotate(dir);

    for ( int j=0 ; j<4 ; ++j )
        {
          for ( int i=1 ; i<4 ; ++i )
              {
                int t = i;

                for ( ; true ; --t )
                    {
                      if ( t == 0 )
                         { break;
                         }
                      if ( !pry[t-1][j]->empty() )
                         { break;
                         }
                    }

                if ( t == i )
                   { continue;
                   }

                *pry[t][j] = *pry[i][j];
                pry[i][j]->reset();
              }
        }

    prySetAsA();

    return;
}

bool BoxAry::movePrChk(Direction dir) {
    BoxAry tmp(*this);


    tmp.moveNoChk(dir);


    tmp.pryRotate(dir);

    for ( int j=0 ; j<4 ; ++j )
        {
          for ( int i=0 ; i<3 ; ++i )
              {
                if ( tmp.pry[i+1][j]->empty() )
                   { continue;
                   }
                if ( *tmp.pry[i][j] != *tmp.pry[i+1][j] )
                   { continue;
                   }

                *tmp.pry[i][j] += *tmp.pry[i+1][j];
              }
        }

    tmp.prySetAsA();


    tmp.moveNoChk(dir);


    if ( tmp == *this )
       { return false;
       }
    return true;
}

void BoxAry::moveNrmal(Direction dir) {
    if ( !movePrChk(dir) )
       { return;
       }

    moveNoChk(dir);


    pryRotate(dir);

    for ( int j=0 ; j<4 ; ++j )
        {
          for ( int i=0 ; i<3 ; ++i )
              {
                if ( pry[i+1][j]->empty() )
                   { continue;
                   }
                if ( *pry[i][j] != *pry[i+1][j] )
                   { continue;
                   }

                *pry[i][j] += *pry[i+1][j];

                if ( pry[i][j]->getNum() > score )
                   { score = pry[i][j]->getNum();
                   }
              }
        }

    prySetAsA();


    moveNoChk(dir);


    pryRotate(dir);

    for ( ; true ; )
        {
          int x = rand()%4;

          if ( pry[3][x]->empty() )
             { pry[3][x]->setBas(3);
               break;
             }
        }

    prySetAsA();

    return;
}

Direction BoxAry::moveAuto() {
          int cnh =     0;
          int cnt =    -1;
    Direction ans = ERROR;

    for ( Direction d1=UP ; d1<ERROR ; d1=(Direction)(d1+1) )
        { if ( !movePrChk(d1) )
             { continue;
             }

          BoxAry t1(*this);
          t1.moveNrmal(d1);

          int c = 0;
          for ( int i=0 ; i<4 ; ++i )
          for ( int j=0 ; j<4 ; ++j )
           if ( t1.ary[i][j].empty() )
              { ++c;
              }

          if ( ( c > cnt ) || ( c == cnt && 1 > cnh ) )
             {
               cnh =  1;
               cnt =  c;
               ans = d1;
             }

          for ( Direction d2=UP ; d2<ERROR ; d2=(Direction)(d2+1) )
              { if ( !movePrChk(d2) )
                   { continue;
                   }

                BoxAry t2(t1);
                t2.moveNrmal(d2);

                int c = 0;
                for ( int i=0 ; i<4 ; ++i )
                for ( int j=0 ; j<4 ; ++j )
                 if ( t2.ary[i][j].empty() )
                    { ++c;
                    }

                if ( ( c+1 > cnt ) || ( c+1 == cnt && 2 > cnh ) )
                   {
                     cnh =   2;
                     cnt = c+1;
                     ans =  d1;
                   }

                for ( Direction d3=UP ; d3<ERROR ; d3=(Direction)(d3+1) )
                    { if ( !movePrChk(d3) )
                         { continue;
                         }

                      BoxAry t3(t2);
                      t3.moveNrmal(d3);

                      int c = 0;
                      for ( int i=0 ; i<4 ; ++i )
                      for ( int j=0 ; j<4 ; ++j )
                       if ( t3.ary[i][j].empty() )
                          { ++c;
                          }

                      if ( ( c+2 > cnt ) || ( c+2 == cnt && 3 > cnh ) )
                         {
                           cnh =   3;
                           cnt = c+2;
                           ans =  d1;
                         }

                      for ( Direction d4=UP ; d4<ERROR ; d4=(Direction)(d4+1) )
                          { if ( !movePrChk(d4) )
                               { continue;
                               }

                            BoxAry t4(t3);
                            t4.moveNrmal(d4);

                            int c = 0;
                            for ( int i=0 ; i<4 ; ++i )
                            for ( int j=0 ; j<4 ; ++j )
                             if ( t4.ary[i][j].empty() )
                                { ++c;
                                }

                            if ( ( c+3 > cnt ) || ( c+3 == cnt && 4 > cnh ) )
                               {
                                 cnh =   4;
                                 cnt = c+3;
                                 ans =  d1;
                               }

                            for ( Direction d5=UP ; d5<ERROR ; d5=(Direction)(d5+1) )
                                { if ( !movePrChk(d5) )
                                     { continue;
                                     }

                                  BoxAry t5(t4);
                                  t5.moveNrmal(d5);

                                  int c = 0;
                                  for ( int i=0 ; i<4 ; ++i )
                                  for ( int j=0 ; j<4 ; ++j )
                                   if ( t5.ary[i][j].empty() )
                                      { ++c;
                                      }

                                  if ( ( c+4 > cnt ) || ( c+4 == cnt && 5 > cnh ) )
                                     {
                                       cnh =   5;
                                       cnt = c+4;
                                       ans =  d1;
                                     }
                                }
                          }
                    }
              }
        }
    return ans;
}

BoxAry& BoxAry::operator=(const BoxAry &src) {
    for ( int i=0 ; i<4 ; ++i )
        { for ( int j=0 ; j<4 ; ++j )
              { ary[i][j] = src.ary[i][j];
                pry[i][j] = &ary[i][j];
              }
        }

    score = src.score;
    return *this;
}

bool BoxAry::operator==(const BoxAry &src) {
    for ( int i=0 ; i<4 ; ++i )
        { for ( int j=0 ; j<4 ; ++j )
              { if ( ary[i][j] != src.ary[i][j] )
                   { return false;
                   }
              }
        }
    return true;
}

bool BoxAry::operator!=(const BoxAry &src) {
    return !( operator==(src) );
}

ostream& operator<<(ostream &out, BoxAry &src) {
    for ( int i=0 ; i<4 ; ++i )
        { for ( int j=0 ; j<4 ; ++j )
              { out << src.ary[i][j];

                if ( j != 3 )
                   { out << "|";
                   }
              }
          out << endl;

          if ( i != 3 )
             { out << "---------------------------"
                   << endl;
             }
        }
    return out;
}

#endif // BOXARY_H_INCLUDED

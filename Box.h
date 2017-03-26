#ifndef BOX_H_INCLUDED
#define BOX_H_INCLUDED

class Box {
private:
     int base;
     int numb;
    bool flag;

    static const int ProbabilityOf2 = 85;

public:
    Box();
    Box(const Box &src);

     int getNum();
    bool fail();
    bool empty();

    void setBas(const int src);
    void reset();

    void rise();

    Box& operator=(const Box &src);
    Box& operator+=(Box &src);

    bool operator==(const Box &src);
    bool operator!=(const Box &src);
    bool operator>=(const Box &src);
    bool operator<=(const Box &src);
    bool operator>(const Box &src);
    bool operator<(const Box &src);

    friend ostream& operator<<(ostream &out, Box &src);
};

Box::Box() {
    base = 0;
    numb = 1;
    flag = false;
}

Box::Box(const Box &src) {
    base = src.base;
    numb = src.numb;
    flag = false;
}

int Box::getNum() {
    return numb;
}

bool Box::fail() {
    return flag;
}

bool Box::empty() {
    if ( base == 0 )
       { return true;
       }
    return false;
}

void Box::setBas(const int src) {
    if ( !empty() )
       { flag = true;
         return;
       }

    if ( !( src == 1 || src == 2 || src == 3 ) )
       { flag = true;
         return;
       }

    int tar = src;

    if ( src == 3 )
       { int x = rand()%100 + 1;

         if   ( x <= ProbabilityOf2 )
              { tar = 1;
              }
         else { tar = 2;
              }
       }

    base = tar;
    numb = pow(base);

    return;
}

void Box::reset() {
    base = 0;
    numb = 1;
    return;
}

void Box::rise() {
    ++base;
    numb *= 2;
    return;
}

Box& Box::operator=(const Box &src) {
    base = src.base;
    numb = src.numb;
    return *this;
}

Box& Box::operator+=(Box &src) {
    if ( *this != src )
       { flag = true;
         return *this;
       }

    rise();
    src.reset();
    return *this;
}

bool Box::operator==(const Box &src) {
    if ( base == src.base )
       { return true;
       }
    return false;
}

bool Box::operator!=(const Box &src) {
    return !( operator==(src) );
}

bool Box::operator>=(const Box &src) {
    return operator==(src) || operator>(src);
}

bool Box::operator<=(const Box &src) {
    return !( operator>(src) );
}

bool Box::operator>(const Box &src) {
    if ( base > src.base )
       { return true;
       }
    return false;
}

bool Box::operator<(const Box &src) {
    return !( operator>=(src) );
}

ostream& operator<<(ostream &out, Box &src) {
    out << " ";

    if   ( src.empty() )
         { out << string(4, ' ');
         }
    else { out << setw(4) << src.getNum();
         }

    out << " ";

    return out;
}

#endif // BOX_H_INCLUDED

#ifndef MATH_H_INCLUDED
#define MATH_H_INCLUDED

int pow(const unsigned n)
{
    int ans = 1;

    for ( unsigned i=0 ; i<n ; ++i )
        { ans *= 2;
        }

    return ans;
}

#endif // MATH_H_INCLUDED

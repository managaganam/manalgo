#ifndef UTILS
#define UTILS


inline int random(int min, int max) // both included
{
    qsrand(qrand());
    return min + (qrand() % (max - min + 1));
}


#endif // UTILS


#ifndef UTILS
#define UTILS

#include <QtMath>

inline int random(int min, int max) // both included
{
    qsrand(qrand());
    return min + (qrand() % (max - min + 1));
}

inline float distanceBetweenTwoPoint(float x1, float y1, float x2, float y2)
{
    float sum = ((x2-x1)*(x2-x1)) + ((y2-y1)*(y2-y1));
    float distance = qSqrt(sum);
    return distance;
}

#endif // UTILS


#ifndef SQUARETIME_H
#define SQUARETIME_H

#define NB_ELEMENTS 40
#define NB_ITERATION 100

#include <QPainter>
#include <QList>
#include <QRect>

class SquareTime
{
public:
    SquareTime(QPainter *painter, QImage *img);
    ~SquareTime();

    void evolve();

private:
    QList<QRect*> rects;
    QPainter *p;
};

#endif // SQUARETIME_H

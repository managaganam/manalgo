#include "squaretime.h"
#include "utils.h"

SquareTime::SquareTime(QPainter *painter, QImage *img)
{
    QPen pen;
    pen.setWidth(1);
    painter->setPen(pen);

    for(int i=0; i<NB_ELEMENTS; ++i)
    {
        rects.append(new QRect(random(20, img->width()), random(20, img->height()), random(40, 200), random(40, 200)));
        painter->drawRect(*rects.at(i));
    }

    p = painter;

    evolve();
}

void SquareTime::evolve()
{
   for(int i=0; i<NB_ITERATION; ++i)
   {
       for(int j=0; j<NB_ELEMENTS; ++j)
       {
           int x, y, width, height;
           rects.at(j)->getRect(&x, &y, &width, &height);
           x += random(5, 50);
           y += random(5, 50);
           width += random(2, 70);
           height += random(5, 80);

           rects.at(j)->setRect(x, y, width, height);
           p->drawRect(*rects.at(j));
       }
   }
}

SquareTime::~SquareTime()
{

}


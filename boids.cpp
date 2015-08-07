#include "boids.h"
#include "utils.h"

Boids::Boids(QPainter *painter, QImage *img)
{
    p = painter;
    i = img;

    QPen pen;
    pen.setWidth(2);
    painter->setPen(pen);

    // Init
    for(int i=0; i<NB_BIRDS; ++i)
    {
        birds.append(new Bird(random(5, img->width() / 4), random(5, img->height() / 4), random(35, 115)));
        painter->drawPoint(birds.at(i)->x, birds.at(i)->y);
        drawBird(birds.at(i));
    }

    // Advance
    advance();
}

void Boids::drawBird(Bird *b)
{
    /*p->drawPoint(b->x, b->y);*/

      p->drawEllipse(b->x, b->y, random(2,50), random(2,50));

    /*p->setBrush(QColor(100,20, 150));
    p->drawEllipse(b->x, b->y, 10, 10);*/
}

QList<Bird*> Boids::returnNeighbours(int x, int y)
{
    QList<Bird*> n;

    for(int i=0; i<NB_BIRDS; ++i)
    {
        if(distanceBetweenTwoPoint(x, y, birds.at(i)->x, birds.at(i)->y) < NEIGHBOUR_RADIUS)
        {
            n.append(birds.at(i));
        }
    }

    return n;
}

int Boids::returnAverageNeighboursDirection(QList<Bird*> neigh)
{
    int sum = 0;
    for(int i=0; i<neigh.size(); ++i)
    {
        sum += neigh.at(i)->direction;
    }
    if(sum == 0)
        return 0;
    else
        return sum / neigh.size();
}

void Boids::drawNextBirdStep(Bird *b)
{
    // Calculate next coordinate
    // new x = step size * cos direction
    float newx = b->x + STEP_SIZE * qCos(qDegreesToRadians((float)b->direction));


    // new y = step size * cos (180 - 45 - direction)
    float newy = b->y + STEP_SIZE * qCos(qDegreesToRadians((float)(180 - 45 - b->direction)));

    b->x = newx;
    b->y = newy;

    drawBird(b);
}

void Boids::advance()
{
    for(int j=0; j<NB_STEP; ++j)
    {
        for(int i=0; i<NB_BIRDS; ++i)
        {
            // Detecting neighbours
            QList<Bird*> neigh = returnNeighbours(birds.at(i)->x, birds.at(i)->y);

            // Adjusting direction according to it
            int newDirection = returnAverageNeighboursDirection(neigh);
            if(newDirection != 0)
                birds.at(i)->direction = newDirection;

            // Drawing according to the direction
            drawNextBirdStep(birds.at(i));
        }
    }
}

Boids::~Boids()
{

}


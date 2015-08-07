#ifndef BOIDS_H
#define BOIDS_H

#define NB_BIRDS 200
#define NB_STEP 1500
#define NEIGHBOUR_RADIUS 50
#define STEP_SIZE 10

#include <QPainter>
#include <QList>
#include <QRect>
#include <QtMath>

class Bird
{
public:
    int x;
    int y;
    float direction;
    Bird(int xp, int yp, int directionp) { x = xp; y =yp; direction = directionp; }
};

class Boids
{
public:
    Boids(QPainter *painter, QImage *img);
    ~Boids();

    void advance();
    QList<Bird*> returnNeighbours(int x, int y);
    int returnAverageNeighboursDirection(QList<Bird*> neigh);
    void drawNextBirdStep(Bird* b);
    void drawBird(Bird *b);

private:
    QList<Bird*> birds;
    QPainter *p;
    QImage *i;
};

#endif // BOIDS_H

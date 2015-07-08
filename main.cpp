/*
 * Manalgo: Generative art renderer
 *
 * Copyright © 2015 Managa <managa@riseup.net>
 *
 * This program is free software. It comes without any warranty, to
 * the extent permitted by applicable law. You can redistribute it
 * and/or modify it under the terms of the Do What The Fuck You Want
 * To Public License, Version 2, as published by Sam Hocevar. See
 * the COPYING file for more details.
 */

#include <iostream>
#include <QCoreApplication>
#include <QImage>
#include <QColor>
#include <QPainter>
#include <QDebug>
#include <QLine>
#include <QCommandLineParser>
#include <QtMath>
#include <QRgb>
#include <QFile>

#include "utils.h"
#include "squaretime.h"

// Default parameter for the app
#define WIDTH "6000"
#define HEIGHT "6000"
#define QUALITY_OUTPUT "80"
#define OUTPUT "./output.png"

// Paintings
#define STRATES "strates"
#define FRONTIERES "frontieres"
#define DETERMINISME "determinisme"
#define AUGEN_0 "augen0"
#define AUGEN_1 "augen1"
#define AUGEN_2 "augen2"
#define MOSAIQUE_0 "mosaique0"
#define MOSAIQUE_1 "mosaique1"
#define CARIBOU_XOR_125 "caribouxor125"
#define NOUS "nous"
#define BOITES "boites"
#define SQUARE_TIME "squaretime"

int widthParam;
int heightParam;
int qualityOutputParam;
QString outputParam;
QString paintingParam;
bool signParam;

// Paintings
void strates(QPainter *painter);
void frontieres(QPainter *painter);
void determinisme(QPainter *painter);
void augen(QPainter *painter, int serie);
void mosaique(QPainter *painter, int serie);
void caribouXor125(QPainter *painter);
void nous(QPainter *painter);
void boites(QPainter *painter, QImage *img);

// Global purpose functions
void addSignature(QPainter *painter);

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QCoreApplication::setApplicationName("manalgo");
    QCoreApplication::setApplicationVersion("0.1");

    // List of paintings available
    QStringList paintings;
    paintings << STRATES << FRONTIERES << DETERMINISME << AUGEN_0 << AUGEN_1 << AUGEN_2 << MOSAIQUE_0 << MOSAIQUE_1 << NOUS;

    // Parsing arguments
    QCommandLineParser parser;
    parser.setApplicationDescription("Digital and algorithmical art renderer");
    parser.addHelpOption();
    parser.addVersionOption();

    QCommandLineOption listOption(QStringList() << "l" << "list-paintings", "list available paintings");
    parser.addOption(listOption);
    QCommandLineOption outputOption("output", "output path", "output", OUTPUT);
    parser.addOption(outputOption);
    QCommandLineOption widthOption("width", "width of the output", "width", WIDTH);
    parser.addOption(widthOption);
    QCommandLineOption heightOption("height", "height of the output", "height", HEIGHT);
    parser.addOption(heightOption);
    QCommandLineOption qualityOutputOption("quality", "quality of the output", "quality", QUALITY_OUTPUT);
    parser.addOption(qualityOutputOption);
    QCommandLineOption paintingOption("painting", "painting to use", "painting", paintings.first());
    parser.addOption(paintingOption);
    QCommandLineOption signOption("sign", "add a Managa signature to the painting");
    parser.addOption(signOption);

    parser.process(a);

    if(parser.isSet(listOption))
    {
        for(int i=0; i<paintings.count(); ++i)
        {
            std::cout << paintings.at(i).toStdString() << std::endl;
        }
        return 0;
    }

    if(parser.isSet(signOption))
    {
        signParam = true;
    }
    else
    {
        signParam = false;
    }

    outputParam = parser.value(outputOption);
    widthParam = parser.value(widthOption).toInt();
    heightParam = parser.value(heightOption).toInt();
    qualityOutputParam = parser.value(qualityOutputOption).toInt();
    paintingParam = parser.value(paintingOption);

    // Creating the canvas
    QImage *img = new QImage(widthParam, heightParam, QImage::Format_RGB32);
    QColor color(255, 255, 255);
    img->fill(color);
    QPainter *painter = new QPainter(img);

    // Painting the canvas
    if(paintingParam == STRATES)
    {
        strates(painter);
    }
    else if(paintingParam == FRONTIERES)
    {
        frontieres(painter);
    }
    else if(paintingParam == DETERMINISME)
    {
        determinisme(painter);
    }
    else if(paintingParam == AUGEN_0)
    {
        augen(painter, 0);
    }
    else if(paintingParam == AUGEN_1)
    {
        augen(painter, 1);
    }
    else if(paintingParam == AUGEN_2)
    {
        augen(painter, 2);
    }
    else if(paintingParam == MOSAIQUE_0)
    {
        mosaique(painter, 0);
    }
    else if(paintingParam == MOSAIQUE_1)
    {
        mosaique(painter, 1);
    }
    else if(paintingParam == CARIBOU_XOR_125)
    {
        caribouXor125(painter);
    }
    else if(paintingParam == NOUS)
    {
        nous(painter);
    }
    else if(paintingParam == BOITES)
    {
        boites(painter, img);
    }
    else if(paintingParam == SQUARE_TIME)
    {
        SquareTime(painter, img);
    }
    else
    {
        qWarning() << "Could not find the painting: " << paintingParam << ", aborting.";
        return -1;
    }

    if(signParam)
    {
        addSignature(painter);
    }

    delete painter;

    // Saving the output
    img->save(outputParam, 0, qualityOutputParam);

    delete img;

    return 0;
}

void addSignature(QPainter *painter)
{
    QString pathToImg = QString::fromLatin1("./material/managa-sign.svg");
    if(!QFile(pathToImg).exists())
    {
        qWarning() << "Error: could not find the file " << pathToImg;
        qWarning() << "No signature";
        return;
    }

    QImage sign(pathToImg);
    int width = widthParam / 25;
    float ratio = float(sign.height()) / float(sign.width());
    int height = int(ratio * float(width));

    painter->drawImage(QRect(widthParam - width, heightParam - height, width, height), sign);
}

void strates(QPainter *painter)
{
    int yPen = 0;
    while(yPen < heightParam)
    {
        // Height of line
        int lineHeight = random(heightParam / 1000, heightParam / 200);

        // Color of line
        QColor color(random(0, 255), random(0, 255), random(0, 255));
        painter->setPen(color);

        // Line
        for(int i=0; i<lineHeight; ++i)
        {
            QLine line(0, yPen, widthParam, yPen);
            painter->drawLine(line);
            ++yPen;
        }
    }
}

void frontieres(QPainter *painter)
{
   for(int i=0; i<10000; ++i)
   {
       QColor color(random(20, 140), random(60, 255), random(100, 255));
       painter->setPen((color));

       QRect rect(QPoint(random(-30, widthParam), random(-100, heightParam)), QSize(random(150, widthParam / 50), random(200, heightParam / 60)));

       QBrush br(color);
       painter->setBrush(br);

       painter->drawRect(rect);
   }
}

void determinisme(QPainter *painter)
{
    painter->fillRect(0, 0, widthParam, heightParam, QColor(80, 15, 200));

    // We divide in 100 column
    const int nbCol = 60;
    for(int i=0; i<nbCol; ++i)
    {
        int xPerson = i*(widthParam / (nbCol + 1));

        // We always need salt
        int salt;
        if(i % 2)
        {
            salt = -1;
        }
        else
        {
            salt = 1;
        }

        int r = random(0,255);
        int v = random(0, 255);
        int b = random(0, 255);
        // Which is the smallest ?
        int smallest;
        if(r < v && r < b)
            smallest = 0;
        if(v < b && v < r)
            smallest = 1;
        else
            smallest = 2;

        for(int yAdvanceInLife = 100; yAdvanceInLife<heightParam-100; yAdvanceInLife += 50)
        {

            QPointF points[3] =
            {
                QPointF(90 + xPerson + random(50, 150), yAdvanceInLife + salt * random(50, 150)),
                QPointF(80 + xPerson - salt * random(50, 150), yAdvanceInLife + random(50, 150)),
                QPointF(100 + xPerson + salt * random(50, 150), yAdvanceInLife - random(50, 150))
            };

            // Then make people follows what they are supposed to do
            if(smallest == 0)
            {
                if(r<255) ++r;
                if(v>0) --v;
            }
            if(smallest == 1)
            {
                if(v<255) ++v;
                if(b>0) --b;
            }

            if(smallest == 2)
            {
                if(b<255) ++b;
                if(r>0) --r;
            }

            //qDebug() << "i: " << i << "yAdvance: " << yAdvanceInLife << " " << r << v << b;
            QColor newColor(r, v, b);
            painter->setBrush(newColor);
            painter->drawPolygon(points, 3);
        }
    }
}

void augen(QPainter *painter, int serie)
{
    // Fill the background
    painter->fillRect(0,0, widthParam, heightParam, QColor(100, 100, 180));

    if(serie == 1 || serie == 2) // Other background for serie 1
    {
        int y=0;
        while(y < heightParam)
        {
            if(serie == 2)
            {
                painter->setPen(QColor(random(0,200), random(0,220), random(0,255)));
            }
            else
            {
                painter->setPen(QColor(random(90,110), random(90,110), random(180, 255)));
            }

            int widthLine = random (5,15);
            for(int i=0; i<widthLine; ++i)
            {
                QLine line(0, y, widthParam, y);
                painter->drawLine(line);
                ++y;
            }
        }
    }


    int pos = 0;
    while(pos < (heightParam / 2))
    {
        QColor color(random(0,255), random(0,255), random(0,255));
        painter->setPen(color);

        int nb;
        if(serie == 2)
            nb = random(15, 45);
        else
            nb = random(20,100);

        for(int i=0; i<nb; ++i)
        {
            QLine line1(pos,0,0,pos);
            QLine line2;
            //QLine line2(0, heightParam - pos,pos,0); // interesting effect
            if(serie == 0)
            {
                 line2 = QLine(widthParam / 2, heightParam - pos,widthParam / 2 - pos,heightParam);
            }
            else if(serie == 1)
            {
                 line2 = QLine(widthParam / 2 - pos, heightParam - pos,widthParam / 2 - pos,heightParam);
            }
            else if(serie == 2)
            {
                 line2 = QLine(0, heightParam - pos, pos, heightParam);
            }
            QLine line3(widthParam - pos,0,widthParam,pos);
            QLine line4;
            if(serie != 2)
            {
                line4 = QLine(widthParam - pos, heightParam,widthParam - pos,heightParam- pos);
            }
            else
            {
                line4 = QLine(widthParam, heightParam - pos, widthParam - pos, heightParam);
            }
            painter->drawLine(line1);
            painter->drawLine(line2);
            painter->drawLine(line3);
            painter->drawLine(line4);
            ++pos;
        }

    }
}

void mosaique(QPainter *painter, int serie)
{
    // Splitting the painting in a matrix
    const int nbSquare = 50;
    int squareSize = widthParam / nbSquare;

    for(int i=0; i<nbSquare; ++i)
    {
        for(int j=0; j<nbSquare; ++j)
        {
            QColor color;
            if(serie == 0)
            {
                color = QColor(random(0, 50), random(0, 255), random(0, 255));

                if(((i+j) % 5) > 3)
                {
                    color = color.lighter(200);
                }

                // Are we into the circle
                int xCircle = nbSquare / 2;
                int yCircle = nbSquare / 2;
                int radius = nbSquare / 3;

                // Distance between current point and x y from the circle
                int distance = qSqrt((xCircle - i) * (xCircle - i) + (yCircle - j)*(yCircle -j));
                if(distance == radius)
                {
                    color.setRed(random(100,200));
                }
            }
            else if(serie == 1) // Only random square
            {
                color = QColor(random(0, 255), random(0, 255), random(0, 255));
            }
            painter->setPen(color);
            painter->setBrush(color);
            painter->drawRect(i*squareSize, j*squareSize, squareSize, squareSize);
        }
    }
}

void caribouXor125(QPainter *painter)
{
    QString pathToImg = QString::fromLatin1("../manalgo/material/caribou.jpg");
    if(!QFile(pathToImg).exists())
    {
        qWarning() << "Error: could not find the file " << pathToImg;
        qWarning() << "Result will be a blank painting";
        return;
    }

    QImage caribou(pathToImg);
    int width = caribou.width();
    int height = caribou.height();

    for(int x=0; x<width; ++x)
    {
        for(int y=0; y<height; ++y)
        {
            QColor pix(caribou.pixel(x, y));
            pix.setRed(pix.red() ^ 125);
            pix.setBlue(pix.blue() ^ 125);
            pix.setGreen(pix.green() ^ 125);
            caribou.setPixel(x, y, pix.rgb());
        }
    }

    painter->drawImage(QRect(0, 0, widthParam, heightParam), caribou);
}

float fitnessNous(QList<QColor> pop)
{
    // The higher the note is the better it is

    // Test sum of green
    float note = 0;
    for(int i=0; i<pop.count(); ++i)
    {
        note += pop.at(i).green();
        note -= pop.at(i).blue() / 3; // and we still want to have some blue
        note -= pop.at(i).red() / 5;  // and green but not too much
    }

    return note;
}

void nous(QPainter *painter)
{
    const int populationSize = 200;
    const int nbIteration = populationSize; // This make something quadratic
    // Sorting a line thanks to a genetic algorithm, each iteration with a better result will be displayed

    // Creating the initial population
    QList<QColor> initialPopulation;
    for(int i=0; i<populationSize; ++i)
    {
        initialPopulation.append(QColor(random(0,100), random(0,255), random(0,255)));
    }

    float bestNote = fitnessNous(initialPopulation);

    // Draw the initial population
    int currentY = 0;
    int squareHeight = heightParam / nbIteration;
    int squareWidth = widthParam / populationSize;
    for(int i=0; i<populationSize; ++i)
    {
        painter->setPen(initialPopulation.at(i));
        painter->setBrush(initialPopulation.at(i));
        painter->drawRect(i*squareWidth, currentY, squareWidth, squareHeight);
    }
    currentY += squareHeight;

    // Iterate
    QList<QColor> currentPopulation(initialPopulation);
    for(int i=0; i<nbIteration; ++i)
    {
        bool betterSolution = false;
        while(!betterSolution)
        {
            QList<QColor> selectedPopulation(currentPopulation);
            // Crossing or not
            if(i%2 == 0) // Crossing one out of 2
            {
                int ind = random(1, populationSize);
                QList<QColor> temp;
                for(int j=ind; j<populationSize; ++j)
                {
                    temp.append(selectedPopulation.at(j));
                }
                for(int j=0; j<ind; j++)
                {
                    temp.append(selectedPopulation.at(j));
                }
                selectedPopulation.swap(temp);
            }

            // Mutation
            int nbMutation = random(1, 10);
            for(int i=0; i<nbMutation; ++i)
            {
                int ind = random(0, populationSize - 1);
                selectedPopulation.replace(ind, QColor(random(0, 255), random(0, 255), random(0, 255)));
            }

            // Calculate note of the selected population
            float selectedNote = fitnessNous(selectedPopulation);

            if(bestNote < selectedNote)
            {
                currentPopulation = selectedPopulation;
                bestNote = selectedNote;
                betterSolution = true;
            }
        }

        // Draw the better solution
        for(int i=0; i<populationSize; ++i)
        {
            painter->setPen(currentPopulation.at(i));
            painter->setBrush(currentPopulation.at(i));
            painter->drawRect(i*squareWidth, currentY, squareWidth, squareHeight);
        }
        currentY += squareHeight;

    }
}

int nextFreeY(int x, QImage *img)
{
    for(int i=0; i<heightParam; ++i)
    {

        QColor c(img->pixel(x, i));
        // as soon as we find a white one we draw it
        if(c.red() == 50 && c.green() == 100 && c.blue() == 180)
        {
            return i;
        }
    }

    return -1;
}

int nextFreeX(int y, QImage *img)
{
    for(int i=0; i<widthParam; ++i)
    {

        QColor c(img->pixel(i, y));
        if(c.red() == 50 && c.green() == 100 && c.blue() == 180)
        {
            return i;
        }
    }

    return -1;
}

void boites(QPainter *painter, QImage *img)
{
    // Fill the background with a nice color
    painter->fillRect(0,0, widthParam, heightParam, QColor(50, 100, 180));

    bool full = false;
    QPen pen;
    pen.setWidth(10);

    painter->setPen(pen);

    int currentYTopLeft = 0;

    while(!full)
    {
        int currentXTopLeft = 0;
        int width = random(200, widthParam / 4);
        int height = random(100, widthParam / 5);
        bool lineComplete = false;

        while(!lineComplete)
        {
            painter->setBrush(QColor(random(0, 255), random(0, 255), random(0, 255)));
            QRect rect(currentXTopLeft, currentYTopLeft, width, height);
            painter->drawRect(rect);

            // Go to next one
            width = random(300, widthParam / 7);
            height = random(200, widthParam / 3);
            currentXTopLeft = nextFreeX(currentYTopLeft, img);

            if(currentXTopLeft == -1 || currentXTopLeft > widthParam)
                lineComplete = true;
        }

        currentYTopLeft = nextFreeY(0, img);

        if(currentYTopLeft == -1 || currentYTopLeft > heightParam)
        {
            full = true;
        }
    }
}

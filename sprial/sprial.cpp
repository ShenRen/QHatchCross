#include "sprial.h"

Sprial::Sprial(QObject *parent) :
    QObject(parent)
{
    liner = new QPainterPath();
}

void Sprial::setString(QString s)
{
    sourceImg = QImage(s);
}

double Sprial::Radians(double a)
{

    return a*M_PI/180.0;
}

void Sprial::drawFillLine()
{
    double angle = 315;
    double majorX = cos(Radians(angle));
    double majorY = sin(Radians(angle));

    double steps = 4;
    int i = 0;
    int passes = 4;
    double level = 255.0/(passes+1);

    double dx = sourceImg.width();
    double dy = sourceImg.height();
    double radius = sqrt(dx*dx+dy*dy);
    double r2 = radius*2;
    int i_radius = (int)radius;
    liner->moveTo(0,0);

    for(int a =-i_radius;a<i_radius;a+=steps)
    {
        double majorPX = majorX*a;
        double majorPY = majorY*a;
        double startPX = majorPX - majorY*radius;
        double startPY = majorPY + majorX*radius;

        double endPX = majorPX + majorY*radius;
        double endPY = majorPY - majorX*radius;

         qDebug()<<tr("along line,sx=%1,sy=%2,ex=%3,ey=%4").arg(startPX).arg(startPY).arg(endPX).arg(endPY);
        double l2 = 128;
        if((i%2)==0)
        {
            convertAlongLine(startPX,startPY,endPX,endPY,steps,r2,l2);
        }
        else
        {
            convertAlongLine(endPX,endPY,startPX,startPY,steps,r2,l2);
        }
        i++;
    }

}

void Sprial::convertAlongLine(double x0,double y0,double x1,double y1,double stepSize,double r2,double level)
{
    double b;
    double dx=x1-x0;
    double dy=y1-y0;

    double steps = r2 / stepSize;
    if(steps<1) steps=1;
    QRgb *grays = (QRgb *)sourceImg.scanLine(0);
    double n,x,y,v;

    for (b = 0; b <= steps; ++b)
    {
        n = b / steps;
        x = dx * n + x0;
        y = dy * n + y0;

        if((x<sourceImg.width())&&(y<sourceImg.height())&&(x>=0)&&(y>=0))
            v = qGray(grays[((int)x)+((int)y)*(sourceImg.width())]);
        else
            v = 255;
        if(v<=level)
        {
            liner->lineTo(x,y);
        }
        else
        {
            liner->moveTo(x,y);
        }
//        qDebug()<<tr("along line,x=%1,y=%2").arg(x).arg(y);
    }

}

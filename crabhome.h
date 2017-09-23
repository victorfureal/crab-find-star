#ifndef CRABHOME_H
#define CRABHOME_H
#include<QGraphicsPixmapItem>
#include "star.h"

class CrabHome : public QGraphicsPixmapItem
{
public:
    explicit CrabHome(QGraphicsItem *parent = Q_NULLPTR);
    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void addStar(Star *star);
private:
    int star_num;
};

#endif // CRABHOME_H

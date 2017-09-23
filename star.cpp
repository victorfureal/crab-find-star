#include "star.h"
#include<QPixmap>
#include<QTime>
#include<QDebug>
#include"constval.h"

Star::Star(QGraphicsItem *parent):QGraphicsPixmapItem(parent)
{
    setOffset(-STAR_SIZE/2,-STAR_SIZE/2);
    setPixmap(QPixmap(":/res/icon/point.png"));
    setData(ITEM_TYPE,star);
    setData(STAR_IS_HOME,false);
//    setZValue(3);
}



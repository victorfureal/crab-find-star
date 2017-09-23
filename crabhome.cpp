#include "crabhome.h"
#include "constval.h"
#include<QDebug>

CrabHome::CrabHome(QGraphicsItem *parent):QGraphicsPixmapItem(parent),star_num(0)
{
    setOffset(-CRAB_HOME_SIZE/2,-CRAB_HOME_SIZE/2);
    setPixmap(QPixmap(":/res/icon/house.png"));
    setPos(-SCENE_WIDTH/2+CRAB_HOME_SIZE/2,0);
    setOpacity(0.5);
    setData(ITEM_TYPE,home);
//    setZValue(1);
}

QRectF CrabHome::boundingRect() const
{
    return QRectF(-CRAB_HOME_SIZE/2,-CRAB_HOME_SIZE/2,CRAB_HOME_SIZE,CRAB_HOME_SIZE);
}

QPainterPath CrabHome::shape() const
{
    QPainterPath path;
    path.addRect(-CRAB_HOME_SIZE/2,-CRAB_HOME_SIZE/2,CRAB_HOME_SIZE,CRAB_HOME_SIZE);
    return path;
}

void CrabHome::addStar(Star *star)
{
    QPointF p = mapToParent(boundingRect().topLeft());
    int x = (star_num%5)*STAR_SIZE;
    int y = (star_num/5)*STAR_SIZE;
    x+=STAR_SIZE/2;
    p.setX(p.x()+x);
    p.setY(p.y()+y);
    star->setPos(p);
    star->setData(STAR_IS_HOME,true);
    star_num++;
}



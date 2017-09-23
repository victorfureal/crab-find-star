#include "crab.h"
#include<QPainter>
#include "star.h"
#include<QTime>
#include<QGraphicsScene>
#include<QDebug>

Crab::Crab(CrabHome* cHome,QGraphicsItem *parent):QGraphicsPixmapItem(parent),speed(2),index(0),state(exploring),home(cHome),deliver_star(Q_NULLPTR)
{
    setOffset(-CRAB_SIZE/2,-CRAB_SIZE/2);
    setPixmap(QPixmap(":/res/icon/ant.png"));
    qsrand(QTime::currentTime().msec());
    setData(ITEM_TYPE,crab);
//    setZValue(2);
}

QRectF Crab::boundingRect() const
{
    return QRectF(-CRAB_SIZE/2,-CRAB_SIZE/2,CRAB_SIZE,CRAB_SIZE);
}

QPainterPath Crab::shape() const
{
    QPainterPath path;
    path.addRect(-CRAB_SIZE/2,-CRAB_SIZE/2,CRAB_SIZE,CRAB_SIZE);
    return path;
}

void Crab::do_exploring()
{
    if(check_near_star())return;
    QLineF lineToDest(pos(),destination);
    if(lineToDest.length()>speed-1)
    {
        lineToDest = lineToDest.unitVector();
        setPos(mapToParent(lineToDest.dx()*speed,lineToDest.dy()*speed));
    }
    else
    {
        destination.setX(qrand()%(SCENE_WIDTH-CRAB_SIZE)-SCENE_WIDTH/2);
        destination.setY(qrand()%(SCENE_HEIGHT-CRAB_SIZE)-SCENE_HEIGHT/2);
    }
}

void Crab::do_finding()
{
    QLineF lineToDest(pos(),destination);
    if(lineToDest.length()>speed-1){
        lineToDest = lineToDest.unitVector();
        setPos(mapToParent(lineToDest.dx()*speed,lineToDest.dy()*speed));
    }
    else{
        QList<QGraphicsItem *> list = scene()->items();
        foreach (QGraphicsItem * item,list) {
            if(item->data(ITEM_TYPE).toInt()==star&&(!(item->data(STAR_IS_HOME).toBool()))){
                bool isCollides = item->mapRectToParent(item->boundingRect()).intersects(mapRectToParent(boundingRect()));
                if(isCollides){
                    deliver_star = (Star*)item;
                }
            }
        }
        if(deliver_star!=Q_NULLPTR){
            destination.setX(home->x());
            destination.setY(home->y());
            state = delivering;
        }
        else{
            state = exploring;
        }
    }
}

void Crab::do_delivering()
{
    QLineF lineToDest(pos(),destination);
    if(lineToDest.length()>speed-1){
        lineToDest = lineToDest.unitVector();
        setPos(mapToParent(lineToDest.dx()*speed,lineToDest.dy()*speed));
        deliver_star->setPos(deliver_star->mapToParent(lineToDest.dx()*speed,lineToDest.dy()*speed));
    }
    else{
        home->addStar(deliver_star);
        deliver_star = Q_NULLPTR;
        state = exploring;
    }
}

bool Crab::check_near_star()
{
    QRectF detectRigion(-CRAB_SIZE/2-CRAB_DETECT_SIZE,-CRAB_SIZE/2-CRAB_DETECT_SIZE,
                        CRAB_SIZE+2*CRAB_DETECT_SIZE,CRAB_SIZE+2*CRAB_DETECT_SIZE);
    QList<QGraphicsItem *> list = scene()->items();
    foreach (QGraphicsItem * item,list) {
        if(item->data(ITEM_TYPE).toInt()==star&&(!(item->data(STAR_IS_HOME).toBool()))){
            bool isCollides = item->mapRectToParent(item->boundingRect()).intersects(mapRectToParent(detectRigion));
            if(isCollides){
                destination.setX(item->x());
                destination.setY(item->y());
                state = finding;
                return true;
            }
        }
    }
    return false;
}

void Crab::advance(int step)
{
    if(!step)return;
//    qDebug()<<state<<destination;
    switch (state) {
    case exploring:
    {
        do_exploring();
        break;
    }
    case finding:
    {
        do_finding();
        break;
    }
    case delivering:
    {
        do_delivering();
        break;
    }
    default:
        break;
    }
}

void Crab::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    if(index<7)index++;
    else index = 0;
    QRectF target(-32,-32,64,64);
    QRectF source(index * 64,0.0,64,64);
    painter->drawPixmap(target,pixmap(),source);
}

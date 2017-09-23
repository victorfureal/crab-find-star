#ifndef CRAB_H
#define CRAB_H
#include<QGraphicsPixmapItem>
#include "constval.h"
#include "crabhome.h"

class Crab : public QGraphicsPixmapItem
{
public:
    explicit Crab(CrabHome* cHome,QGraphicsItem *parent = Q_NULLPTR);
    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void do_exploring();
    void do_finding();
    void do_delivering();
    bool check_near_star();

protected:
    void advance(int step) override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                     QWidget *widget) override;

private:
    qreal speed;
    int index;
    QPointF destination;
    crab_state state;
    CrabHome* home;
    Star* deliver_star;
};

#endif // CRAB_H

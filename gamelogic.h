#ifndef GAMELOGIC_H
#define GAMELOGIC_H
#include <QGraphicsScene>
#include "constval.h"
#include "star.h"

class GameLogic:public QObject
{
    Q_OBJECT
public:
    GameLogic();
    static void randomStar(QGraphicsScene&);
};

#endif // GAMELOGIC_H

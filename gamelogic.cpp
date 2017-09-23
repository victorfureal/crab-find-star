#include "gamelogic.h"
#include<QTime>
#include<QDebug>

GameLogic::GameLogic()
{

}

void GameLogic::randomStar(QGraphicsScene& scene)
{
    qsrand(QTime::currentTime().msec());
    for(int i=0;i<STAR_NUM;i++)
    {
        Star * star = new Star;
        qreal x = qrand()%(SCENE_WIDTH-CRAB_SIZE)-SCENE_WIDTH/2;
        qreal y = qrand()%(SCENE_HEIGHT-CRAB_SIZE)-SCENE_HEIGHT/2;
        star->setPos(x,y);
        scene.addItem(star);
    }
}




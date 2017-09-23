# crab-find-star
a simple demo for study
# 螃蟹搬星星——Qt图形视图框架学习 #
Qt的图形视图框架(Graphics View Framework)可以用来做简单的小游戏，该框架提供了一套处理大量2D元素的方案，主要通过提供场景(the Scene)，视图(the View)和图形对象(the Item)这三种类来实现相关功能。本文通过实现一个小demo来学习该框架的基本用法和理念，demo非常简单，就是螃蟹将星星搬回自己的家。


首先，我们这里有螃蟹、星星和螃蟹的家这三种图形对象(the Item)，在Qt的图形视图框架中提供了QGraphicsItem类表示图形对象，该类还有一些子类分别表示不同类型的图形对象，例如QGraphicsRectItem表示一个矩形图形对象、QGraphicsPixmapItem表示一个Pixmap图形对象，由于这里的螃蟹、星星和家都用图片表示，我们取QGraphicsPixmapItem作为这三种类的父类，我们创建Crab、Star、CrabHome这三个类并分别继承QGraphicsPixmapItem类。

为了实现Crab类，首先我们需要重写父类中的boundingRect()、shape()、advance(int step)和paint(QPainter *painter, const QStyleOptionGraphicsItem *option,QWidget *widget)这四个方法。

其中，boundingRect()方法返回一个矩形区域，该区域表示当前对象的重绘区域，场景Scene通过这个值来决定是否图形对象需要进行重绘；

	QRectF Crab::boundingRect() const
	{
		 return QRectF(-CRAB_SIZE/2,-CRAB_SIZE/2,CRAB_SIZE,CRAB_SIZE);
	}		
shape()方法决定图形对象的范围，可用于碰撞检测；

	QPainterPath Crab::shape() const
	{
	    QPainterPath path;
	    path.addRect(-CRAB_SIZE/2,-CRAB_SIZE/2,CRAB_SIZE,CRAB_SIZE);
	    return path;
	}

advance(int step)方法是在Scene的同名方法调用时，Scene会调用所有图形对象的该方法进行更新操作，该方法传入step参数，当step为0时不做任何操作，这是因为advance()被调用两次: 第一次step == 0,表示图形对象将要进行advance,之后step == 1才是真正进行advance，这里我们给螃蟹定义了三种状态，分别是exploring探索状态、finding寻找状态和delivering搬运状态，螃蟹一开始进行探索，只是随机的在地图上行进，当期发现有星星时即切换到寻找状态，直奔星星而去，到达星星位置后，螃蟹进入搬运状态，即将星星搬回家的位置；

	void Crab::advance(int step)
	{
	    if(!step)return;
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

paint()方法是在重绘时调用的，这里我们需要更新不同的螃蟹图片，因此重写该方法，这里我们有7张螃蟹的图片，连起来变成一个动态的螃蟹，当然也可以用一张图片包含所有的螃蟹状态，每次显示图片的不同区域，效果是一样的：

	void Crab::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
	{
	    if(index<7)index++;
	    else index = 0;
	    QRectF target(-32,-32,64,64);
	    QRectF source(index * 64,0.0,64,64);
	    painter->drawPixmap(target,pixmap(),source);
	}

接下来的星星类Star和家类CrabHome比较简单，仅仅设置一下图片即可，因为它们不需要移动。当设置好三种图形对象后，要将其放入场景中：

	QGraphicsScene scene;
    scene.setSceneRect(-512, -256, 1024, 512);
    CrabHome home;
    scene.addItem(&home);
    Crab crab(&home);
    scene.addItem(&crab);
    GameLogic::randomStar(scene);

这里我们使用QGraphicsScene这个类，该类是图形视图框架中的场景类，表示一个场景，其中setSceneRect（）方法设置了场景的范围，如果不设置该范围，当图形对象移动时，场景范围将不断扩大，这里设置的范围是场景的坐标系，我们将其设置为(-512, -256, 1024, 512)，这样场景的(0,0)原点就在场景的中心位置，接下来我们将对象分别加入场景，GameLogic::randomStar(scene)方法产生随机位置的多个星星。最后，我们需要设置场景的视图View：

 	QGraphicsView view(&scene);
    view.setRenderHint(QPainter::Antialiasing);
    view.setBackgroundBrush(QPixmap(":/res/icon/background.jpg"));
    view.setCacheMode(QGraphicsView::CacheBackground);
    view.setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    view.setWindowTitle(QT_TRANSLATE_NOOP(QGraphicsView, "Crab Find Star"));
    view.show();

这一步，我们使用QGraphicsView这个类，其是图形视图框架中的视图类，表示一个视图，视图是用来绘制场景的一个类，在图形视图框架中，场景只是提供了管理图形对象的接口，绘制场景是视图来实现的。最后，我们以一个QTimer来定时刷新场景中的对象，我们将时间间隔设置为1000 / 24，这样就可以实现24FPS的效果：

    QTimer timer;
    QObject::connect(&timer, SIGNAL(timeout()), &scene, SLOT(advance()));
    timer.start(1000 / 24);

通过这个例子，简单介绍了Qt的图形视图框架。

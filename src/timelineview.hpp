#ifndef TIMELINEVIEW_HPP
#define TIMELINEVIEW_HPP

#include <QGraphicsView>
#include "timelinescene.hpp"

class TimeLineView : public QGraphicsView
{
    Q_OBJECT

public:
    TimeLineView(TimeLineScene *scene, QWidget *parent = nullptr);
};

#endif

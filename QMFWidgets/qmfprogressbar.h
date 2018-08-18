#ifndef QMFPROGRESSBAR_H
#define QMFPROGRESSBAR_H
/****************************************************************************
**
** Copyright (C) 2018 Mehdi Farhadi <mfarhadi.ece.iut.ac.ir>
** Contact: 09134223351
**
** Download URL : https://github.com/mfarhadi92/QMFWidgets
**
** Widgets:
**  MessageBox ==> (QMFMessageBox)
**  ProgressBar ==> (QMFProgressBar)
**
** Licensed for distribution under the GPL version3
****************************************************************************/
#include <QWidget>
#include <QBrush>
#include <QPen>

namespace Ui {
class QMFProgressBar;
}
class QPropertyAnimation;
class QGraphicsScene;
class QGraphicsRectItem;
class QGraphicsTextItem;
class QTimer;

class QMFProgressBar : public QWidget
{
    Q_OBJECT

    QTimer          *timer;
    quint8          currentStep = 0;
    quint8          min=0,max=100,value=0;
    QPen            penChunk;
    QBrush          evenBrushChunk,oddBrushChunk;
    QString         title="{{value}}%";
    int             chunkWidth = 15;
    QColor          bgColor,textColor;

    QGraphicsScene  *chunkScene;
    QList<QGraphicsRectItem*>   chunks;
    QGraphicsTextItem   *titleItem = nullptr;
    QPropertyAnimation  *propertyAnimation;

public:
    explicit QMFProgressBar(QWidget *parent = 0);
    ~QMFProgressBar();
    void setMinimun(quint8 min_);
    void setMaximum(quint8 max_);
    void setValue(quint8 value_);
    quint8 getValue(){ return value; }
    void setTitle(QString title_);
    void setThemeColor(QColor bgColor_, QColor textColor_=QColor("black"));
    QColor getBGColor(){ return bgColor; }
    void resizeEvent(QResizeEvent *event);

private slots:
    void updateAnim();
    void updateSize();

private:
    Ui::QMFProgressBar *ui;
};

#endif // QMFPROGRESSBAR_H

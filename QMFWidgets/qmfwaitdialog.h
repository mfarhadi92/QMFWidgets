#ifndef QMFWAITDIALOG_H
#define QMFWAITDIALOG_H

#include <QWidget>
#include <QPen>
#include <QList>

class QGraphicsScene;
class QGraphicsItem;
class QTimer;

namespace Ui {
class QMFWaitDialog;
}

class QMFWaitDialog : public QWidget
{
    Q_OBJECT
    Ui::QMFWaitDialog   *ui;
    QList<QGraphicsItem *>bars;
    QGraphicsScene *scene;
    const int   minWidgetSize   = 200;
    const int   minBarCount     = 10;
    const float heightDxAnim    = .1;
    const float minHeightAnimPercent = .2;
    const int   animDuration    = 60;
    const QColor    defaultBGColor = QColor("#05d0ea");
    quint8  barCount    = minBarCount;
    QSize   barSize     = QSize(10,50);
    quint8  barSpace    = 5;
    float   currentStep = 0;
    float   leftMargin  = 0;
    QString title       = "Please wait";
    QTimer  *timer;
    QBrush  brush;
    QPen    pen;
    QMargins    barMargin;


public:
    explicit QMFWaitDialog(QWidget *parent = 0);
    void setBarCount(quint8 barCount_ );
    void showEvent(QShowEvent *event);
    void setBackgroundBar(QColor backgroundBar);
    void setTitle(QString title_);
    void initWindowFlag();
    void stop();
    void start();
    inline void setBarSize(QSize barSize_ , quint8 barSpace_ ){ barSize = barSize_ ;  barSpace = barSpace_ ; initWaitBar(); }
    void initWaitBar();
    ~QMFWaitDialog();

private slots:
    void doAnim();
};

#endif // QMFWAITDIALOG_H

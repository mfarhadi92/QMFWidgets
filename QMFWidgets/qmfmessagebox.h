#ifndef QMFMESSAGEBOX_H
#define QMFMESSAGEBOX_H
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
#include "structer.h"

class QTimer;
namespace Ui {
class QMFMessageBox;
}

class QMFMessageBox : public QWidget
{
    Q_OBJECT

    Ui::QMFMessageBox *ui;
    enum Step { LEFT_TOP_TO_RIGHT_TOP_STEP = 0 ,RIGHT_TOP_TO_RIGHT_BOTTOM_STEP , WAIT_WIDGET_STEP , CLOSE_WIDGET_STEP };

    Step    step = LEFT_TOP_TO_RIGHT_TOP_STEP;
    float   x1,x2,y1,y2;
    float   colorStop1=0.414773 , colorStop2 = .619318;
    float   waitWidgetIdx = 0;
    float   colorPoxDX = .05;
    QColor  borderColor , centerColor;
    QTimer  *timer;
    QString     animWidgetStyle = "#widget {border-radius:10px;background-color: qlineargradient(spread:reflect, x1:%1, y1:%2, x2:%3, y2:%4, stop:%5 %8, stop:0.5 %7, stop:%6 %8);}";
    QtMFW::AlertInfo    info;

public:
    explicit QMFMessageBox(QWidget *parent = 0);
    void setInfo(QtMFW::AlertInfo *info_);
    ~QMFMessageBox();

private slots:
    void doAnim();

private:
    void start();
    QString colorToString(QColor color);
    void init();

};

#endif // QMFMESSAGEBOX_H

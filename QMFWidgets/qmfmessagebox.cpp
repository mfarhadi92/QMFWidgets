#include "qmfmessagebox.h"
#include "ui_qmfmessagebox.h"
#include <QTimer>
#include <QDebug>

using namespace QtMFW;

QMFMessageBox::QMFMessageBox(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QMFMessageBox)
{
    ui->setupUi(this);
    init();
}

void QMFMessageBox::init()
{
    setWindowFlags(Qt::Widget | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    setParent(0);
    setAttribute(Qt::WA_NoSystemBackground, true);
    setAttribute(Qt::WA_TranslucentBackground, true);
    setAttribute(Qt::WA_PaintOnScreen);

    timer   = new QTimer(this);
    connect(timer , SIGNAL(timeout()) , this ,SLOT(doAnim()));
}

QMFMessageBox::~QMFMessageBox()
{
    delete ui;
}

void QMFMessageBox::setInfo(AlertInfo *info_)
{
    info    = *info_;
    step    = LEFT_TOP_TO_RIGHT_TOP_STEP;
    y1      = 1;
    y2      = 0;
    x1      = 0;
    x2      = 1;

    waitWidgetIdx   = 0;
    ui->lbl_title->setText(info.text);
    ui->lbl_icon->setPixmap(QPixmap(QtMFW::alertIcon[info.status]));

    switch( info.status )
    {
    case processing:
        centerColor = QColor("#976fe6");
        borderColor = QColor("#7129ff");
        break;
    case successed:
        centerColor = QColor("#59c9ea");
        borderColor = QColor("#1792fb");
        break;
    case warning:
        centerColor = QColor("#ffc061");
        borderColor = QColor("#ff8100");
        break;
    case failed:
        centerColor = QColor("#ff6e29");
        borderColor = QColor("#fd0000");
        break;
    default:
        centerColor = QColor("#976fe6");
        borderColor = QColor("#7129ff");
        break;
    }
    borderColor.setAlpha(0);
    start();
}

void QMFMessageBox::start(){
    timer->stop();
    timer->setSingleShot(false);
    timer->setInterval(50);
    timer->start();
    show();
}

void QMFMessageBox::doAnim()
{
    switch( step )
    {
    case LEFT_TOP_TO_RIGHT_TOP_STEP:
        y1 -= colorPoxDX;
        y2 += colorPoxDX;
        x1 = 0;
        x2 = 1;
        if( y1 <= 0 )
        {
            step = RIGHT_TOP_TO_RIGHT_BOTTOM_STEP;
            y1 = 0;
            y2 = 1;
        }
        ui->widget->setStyleSheet(animWidgetStyle.arg(x1).arg(y1).arg(x2).arg(y2).arg(colorStop1).arg(colorStop2).arg(centerColor.name()).arg(colorToString(borderColor)));
        break;
    case RIGHT_TOP_TO_RIGHT_BOTTOM_STEP:
        x1 += colorPoxDX;
        x2 -= colorPoxDX;
        y1 = 0;
        y2 = 1;
        waitWidgetIdx = 0;
        if( x1 > 1 )
        {
            step = WAIT_WIDGET_STEP;
            x1 = 1;
            x2 = 0;
            y1 = 0;
            y2 = 1;
        }
        ui->widget->setStyleSheet(animWidgetStyle.arg(x1).arg(y1).arg(x2).arg(y2).arg(colorStop1).arg(colorStop2).arg(centerColor.name()).arg(colorToString(borderColor)));
        break;
    case WAIT_WIDGET_STEP:
    {
        QColor currentBorderColor;
        int tickCount = ((1.0 - colorStop2)/(colorPoxDX*.5))+1;
        float stopT1 , stopT2;
        stopT1  = colorStop1 - waitWidgetIdx*(colorPoxDX*.5);
        stopT2  = colorStop2 + waitWidgetIdx*(colorPoxDX*.5);
        centerColor.setBlue(((waitWidgetIdx+.0)/tickCount)*255.0);
        borderColor.setAlpha(((waitWidgetIdx+.0)/tickCount)*255.0);
        currentBorderColor.setRed(centerColor.red() + ((borderColor.red() - centerColor.red()+.0)/tickCount)*waitWidgetIdx);
        currentBorderColor.setGreen(centerColor.green() + ((borderColor.green() - centerColor.green()+.0)/tickCount)*waitWidgetIdx);
        currentBorderColor.setBlue(centerColor.blue() + ((borderColor.blue() - centerColor.blue()+.0)/tickCount)*waitWidgetIdx);
        if( stopT1 < 0 )
            stopT1  = 0;
        if( stopT2 >= 1 )
            stopT2  = 1;
        ui->widget->setStyleSheet(animWidgetStyle.arg(x1).arg(y1).arg(x2).arg(y2).arg(stopT1).arg(stopT2).arg(currentBorderColor.name()).arg(colorToString(borderColor)));
        waitWidgetIdx ++;
        if( stopT1 == 0 || stopT2 == 1 )
        {
            step    = CLOSE_WIDGET_STEP;
            timer->setSingleShot(true);
            timer->setInterval(2000);
        }
        break;
    }
    case CLOSE_WIDGET_STEP:
        step    = LEFT_TOP_TO_RIGHT_TOP_STEP;
        timer->stop();
        close();
        return ;
    }
}

QString QMFMessageBox::colorToString(QColor color)
{
    return QString("rgba(%1,%2,%3,%4)").arg(color.red()).arg(color.green()).arg(color.blue()).arg(color.alpha());
}

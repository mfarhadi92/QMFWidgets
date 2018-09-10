#include "ui_qmfwaitdialog.h"
#include "qmfwaitdialog.h"
#include <QGraphicsItemAnimation>
#include <QDesktopWidget>
#include <QGraphicsItem>
#include <QGraphicsView>
#include <QTimeLine>
#include <QTimer>
#include <QDebug>

QMFWaitDialog::QMFWaitDialog(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QMFWaitDialog)
{
    ui->setupUi(this);
    scene   = new QGraphicsScene(ui->graphicsView);
    timer   = new QTimer(this);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);
    connect(timer,SIGNAL(timeout()),this,SLOT(doAnim()));
    timer->setInterval(animDuration);
    setBackgroundBar(defaultBGColor);
    initWindowFlag();
}

QMFWaitDialog::~QMFWaitDialog()
{
    delete ui;
}


void QMFWaitDialog::setBarCount(quint8 barCount_)
{
    if( barCount_ < minBarCount )
        barCount = minBarCount;
    else
        barCount = barCount_;
    initWaitBar();
}

void QMFWaitDialog::showEvent(QShowEvent *event)
{
    initWaitBar();
    QWidget::showEvent(event);
}

void QMFWaitDialog::setBackgroundBar(QColor backgroundBar)
{
    brush.setColor(backgroundBar);
    brush.setStyle(Qt::SolidPattern);
    pen.setWidth(0);
    pen.setBrush(QBrush(backgroundBar));
    ui->lbl_title->setStyleSheet(QString("color:%1").arg(backgroundBar.name()));
    ui->container->setStyleSheet(QString("border-color:%1").arg(backgroundBar.name()));
}

void QMFWaitDialog::setTitle(QString title_)
{
    title   = title_;
    ui->lbl_title->setText(title);
}

void QMFWaitDialog::initWindowFlag()
{
    setWindowFlags(Qt::Widget | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    setParent(0);
    setAttribute(Qt::WA_NoSystemBackground, true);
    setAttribute(Qt::WA_TranslucentBackground, true);
    setAttribute(Qt::WA_PaintOnScreen);
}

void QMFWaitDialog::initWaitBar()
{
    int windowWidth = barCount*(barSize.width()+barSpace)+20;
    setMinimumWidth(windowWidth<minWidgetSize?minWidgetSize:windowWidth);
    setMaximumWidth(windowWidth<minWidgetSize?minWidgetSize:windowWidth);
    scene->setSceneRect(0,0,ui->graphicsView->width()-2,ui->graphicsView->height()-2);
    barMargin.setLeft(( ui->graphicsView->width() - barCount*barSize.width() - barSpace*(barCount-1) ) / 2);
    barMargin.setRight(barMargin.left());
    barMargin.setTop(5);
    barMargin.setBottom(5);
    setMaximumHeight(barSize.height()+barMargin.top()+barMargin.bottom()+ui->lbl_title->height()+25);
    setMinimumHeight(barSize.height()+barMargin.top()+barMargin.bottom()+ui->lbl_title->height()+25);
    scene->setSceneRect(0,0,ui->graphicsView->width(),ui->graphicsView->height());
    setGeometry(QStyle::alignedRect(Qt::LeftToRight, Qt::AlignCenter, size(), qApp->desktop()->availableGeometry()));
    currentStep = 0;
}

void QMFWaitDialog::start()
{
    initWaitBar();
    timer->start();
}

void QMFWaitDialog::doAnim()
{
    scene->clear();
    for( qint8 barIdx = 0 ; barIdx < barCount ; barIdx++ )
    {
        float bHeight = barSize.height() - (1.0-minHeightAnimPercent)*barSize.height()*fabs(sin(currentStep-(barIdx*2)*.1));
        scene->addRect(barIdx*barSize.width()+barSpace*barIdx+barMargin.left(),( ui->graphicsView->height() - bHeight ) / 2,barSize.width(),bHeight,pen,brush);
    }
    currentStep += heightDxAnim;
    if( sin(currentStep) == 0 )
        currentStep = 0;
}

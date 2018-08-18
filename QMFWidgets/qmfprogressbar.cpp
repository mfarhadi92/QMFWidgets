#include "qmfprogressbar.h"
#include "ui_qmfprogressbar.h"
#include <QGraphicsRectItem>
#include <QPropertyAnimation>
#include <QTextBlockFormat>
#include <QGraphicsScene>
#include <QTextDocument>
#include <QTextCursor>
#include <QTimer>
#include <QDebug>

QMFProgressBar::QMFProgressBar(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QMFProgressBar)
{
    ui->setupUi(this);
    propertyAnimation   = new QPropertyAnimation(ui->graphicsView,"size",this);
    chunkScene  = new QGraphicsScene(ui->graphicsView);
    ui->graphicsView->setScene(chunkScene);

    penChunk.setColor(Qt::transparent);
    penChunk.setWidth(0);

    evenBrushChunk.setColor(QColor("#337ab7"));
    evenBrushChunk.setStyle(Qt::SolidPattern);
    oddBrushChunk.setColor(QColor("#719fc7"));
    oddBrushChunk.setStyle(Qt::SolidPattern);
    timer   = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(updateAnim()));
    timer->setInterval(30);
    timer->start();
}

QMFProgressBar::~QMFProgressBar()
{
    delete ui;
}

void QMFProgressBar::setMinimun(quint8 min_)
{
    min = min_;
    updateSize();
}

void QMFProgressBar::setMaximum(quint8 max_)
{
    max = max_;
    updateSize();
}

void QMFProgressBar::setValue(quint8 value_)
{
    value = value_;
    if( value < min )
        value = min;
    else if( value > max )
        value = max;
    updateSize();
}

void QMFProgressBar::setTitle(QString title_)
{
    title   = title_;
}

void QMFProgressBar::setThemeColor(QColor bgColor_,QColor textColor_)
{
    if( bgColor != bgColor_ || textColor_ != textColor )
    {
        bgColor = bgColor_;
        evenBrushChunk.setColor(bgColor);
        quint8 r , g , b;
        if( bgColor.red() < 15 )
            r = bgColor.red() + 30;
        else
            r = bgColor.red() - 15;

        if( bgColor.green() < 15 )
            g = bgColor.green() + 30;
        else
            g = bgColor.green() - 15;

        if( bgColor.blue() < 15 )
            b = bgColor.blue() + 30;
        else
            b = bgColor.blue() - 15;

        oddBrushChunk.setColor(QColor(r,g,b));
        textColor   = textColor_;
        resizeEvent(nullptr);
    }
}

void QMFProgressBar::resizeEvent(QResizeEvent *event)
{
    chunkWidth = ui->graphicsView->height() > 50 ? 50 : ui->graphicsView->height();
    chunkScene->setSceneRect(QRectF(0,0,ui->container->width(),ui->container->height()));
    chunks.clear();
    chunkScene->clear();
    QPen pen(Qt::transparent);
    pen.setWidth(0);
    chunkScene->addRect(-30,0,ui->container->width()+60,ui->container->height(),pen,evenBrushChunk);
    for( int i= -10 ; i< ui->container->width()/(chunkWidth*2) ; i++ )
    {
        QGraphicsRectItem *rect = chunkScene->addRect(i*(chunkWidth*2)+currentStep,(chunkWidth*2)*i+currentStep,chunkWidth,ui->graphicsView->height()*3,pen,oddBrushChunk);
        rect->setRotation(-45);
        chunks.append(rect);
    }

    float dx;
    if( max > min && ( value <= max || value >= min) )
    {
        dx = (ui->container->width()-6) / (max-min+0.0);
        ui->graphicsView->setMaximumWidth(dx*(value));
        ui->graphicsView->setMinimumWidth(dx*(value));
    }

    updateSize();
    QWidget::resizeEvent(event);
}

void QMFProgressBar::updateAnim()
{
    for( int i=0 ; i<chunks.count() ; i++ )
        chunks.at(i)->setRect(QRectF((i-10)*(chunkWidth*2)+currentStep,(chunkWidth*2)*(i-10)+currentStep,chunkWidth,ui->graphicsView->height()*3));
    currentStep += 1;
    if( currentStep >= (chunkWidth*2) )
        currentStep = 0;
}

void QMFProgressBar::updateSize()
{
    float dx;
    if( max > min && ( value <= max && value >= min ) )
    {
        dx = (ui->container->width()-4) / (max-min+0.0);
        int gWidth = dx*(value);
        if( gWidth >= ui->container->width() - 6 )
            gWidth = ui->container->width() - 8;

        QPropertyAnimation *animation = new QPropertyAnimation(ui->graphicsView,"minimumWidth");
        animation->setEndValue(gWidth);
        animation->setDuration(100);
        animation->start();
    }

    if( dx > 0)
    {
        if( titleItem && chunkScene->items().contains(titleItem) )
            chunkScene->removeItem(titleItem);

        titleItem   = chunkScene->addText(QString(title).replace("{{value}}",QString::number(value)),font());
        titleItem->setZValue(100);

        titleItem->setTextWidth(dx*(value));
        titleItem->setPos(0,(ui->graphicsView->height()-titleItem->document()->size().height())/2 );
        QTextBlockFormat format;
        format.setAlignment(Qt::AlignCenter);
        QTextCursor cursor = titleItem->textCursor();
        int position = titleItem->textCursor().position();
        cursor.select(QTextCursor::Document);
        cursor.mergeBlockFormat(format);
        cursor.clearSelection();
        cursor.setPosition(position);

        titleItem->setTextCursor(cursor);
        titleItem->setDefaultTextColor(textColor);
    }
}

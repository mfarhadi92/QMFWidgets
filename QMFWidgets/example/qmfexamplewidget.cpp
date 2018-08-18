#include "qmfexamplewidget.h"
#include "ui_qmfexamplewidget.h"
#include "../qmfmessagebox.h"
#include "../structer.h"

QMFExampleWidget::QMFExampleWidget(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::QMFExampleWidget)
{
    ui->setupUi(this);
    messageBox = new QMFMessageBox(0);
    ui->progressBar->setTitle(QString("%1 {{value}}%").arg("test title"));
    connect(&timer,SIGNAL(timeout()),this,SLOT(timeout_event()));
    timer.start(1000);
}

QMFExampleWidget::~QMFExampleWidget()
{
    delete ui;
}

void QMFExampleWidget::on_btn_successAlert_clicked()
{
    QtMFW::AlertInfo alertInfo;
    alertInfo.text = "success alert";
    alertInfo.status = QtMFW::successed;
    messageBox->setInfo(&alertInfo);
}

void QMFExampleWidget::on_btn_failedAlert_clicked()
{
    QtMFW::AlertInfo alertInfo;
    alertInfo.text = "failed alert";
    alertInfo.status = QtMFW::failed;
    messageBox->setInfo(&alertInfo);
}

void QMFExampleWidget::on_btn_warningAlert_clicked()
{
    QtMFW::AlertInfo alertInfo;
    alertInfo.text = "warning alert";
    alertInfo.status = QtMFW::warning;
    messageBox->setInfo(&alertInfo);
}

void QMFExampleWidget::on_btn_processingAlert_clicked()
{
    QtMFW::AlertInfo alertInfo;
    alertInfo.text = "processing alert";
    alertInfo.status = QtMFW::processing;
    messageBox->setInfo(&alertInfo);
}

void QMFExampleWidget::timeout_event()
{
    quint8 value = ui->progressBar->getValue();
    value +=5;
    if( value > 100 )
        value = 0;
    if( value >= 75 )
        ui->progressBar->setThemeColor(QColor("#ef3232"),QColor("white"));
    else if( value >= 50 )
        ui->progressBar->setThemeColor(QColor("#e2840f"),QColor("white"));
    else if( value >= 25 )
        ui->progressBar->setThemeColor(QColor("#2c63ff"),QColor("white"));
    else
        ui->progressBar->setThemeColor(QColor("#5fd026"),QColor("white"));
    ui->progressBar->setValue(value);
}

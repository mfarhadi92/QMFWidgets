#ifndef QMFEXAMPLEWIDGET_H
#define QMFEXAMPLEWIDGET_H

#include <QMainWindow>
#include <QTimer>

class QMFMessageBox;
class QMFWaitDialog;

namespace Ui {
class QMFExampleWidget;
}

class QMFExampleWidget : public QMainWindow
{
    Q_OBJECT
    QMFMessageBox   *messageBox;
    QMFWaitDialog   *waitDialog;
    QTimer          timer;

public:
    explicit QMFExampleWidget(QWidget *parent = 0);
    ~QMFExampleWidget();

private slots:
    void on_btn_successAlert_clicked();
    void on_btn_failedAlert_clicked();
    void on_btn_warningAlert_clicked();
    void on_btn_processingAlert_clicked();
    void timeout_event();

    void on_btn_waitDialog_clicked();

private:
    Ui::QMFExampleWidget *ui;
};

#endif // QMFEXAMPLEWIDGET_H

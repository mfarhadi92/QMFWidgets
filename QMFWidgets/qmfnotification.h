#ifndef QMFNOTIFICATION_H
#define QMFNOTIFICATION_H
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
**  Notification ==> (QMFNotification)
**
** Licensed for distribution under the GPL version3
****************************************************************************/
#include <QWidget>
#include "structer.h"

namespace Ui {
class QMFNotification;
}
class QTimer;
class QPropertyAnimation;

class QMFNotification : public QWidget
{
    Q_OBJECT

    Ui::QMFNotification *ui;
    QTimer  *fadeOutTimer  = nullptr;
    QPropertyAnimation *animation = nullptr;

public:
    explicit QMFNotification(QWidget *parent = 0);
    ~QMFNotification();
    void setNotification(const QString headerTitle , const QString notification , const QPixmap &nifiicationPixmap ,
                         const QtMFW::Status status, const quint16 duration = 5000);

public slots:
    void stop(quint16 ms=0);

private:
    void init();

private slots:
    void fadeIn();
    void fadeOut();
};

#endif // QMFNOTIFICATION_H

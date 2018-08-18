#ifndef QMFW_STRUCTER_H
#define QMFW_STRUCTER_H

#include <QStringList>

namespace QtMFW {

static const QStringList alertIcon = QStringList()<<":/image/res/images/status/success.png"<<":/image/res/images/status/success.png"<<
                                                   ":/image/res/images/status/warning.png"<<":/image/res/images/status/error.png"<<"";
enum Status{processing,successed,warning,failed,empty};
struct AlertInfo {
    QString text;
    Status status = successed;
    bool autoHide = true;
};

}

#endif // QMFW_STRUCTER_H

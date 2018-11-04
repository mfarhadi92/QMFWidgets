#ifndef QMFW_STRUCTER_H
#define QMFW_STRUCTER_H

#include <QStringList>

namespace QtMFW {

static const QStringList alertIcon = QStringList()<<":/image/res/images/status/success.png"<<":/image/res/images/status/success.png"<<
                                                   ":/image/res/images/status/warning.png"<<":/image/res/images/status/error.png"<<"";
enum Status{processing,successed,warning,failed,empty};
static const QStringList StatusColor = QStringList() << "#2196f3" << "#4cb74c" << "#f9a937" << "#ff4c4c" << "#4c4c4c";
  
struct AlertInfo {
    QString text;
    Status status = successed;
    bool autoHide = true;
};

}

#endif // QMFW_STRUCTER_H

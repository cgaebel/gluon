#ifndef KCLCODE_H
#define KCLCODE_H

#include <QString>
#include <QEvent>
#include "kcl.h"

class KCLCode
{
public:
    static QString buttonName(int code);
    static QString eventName(int code);
    static QString relAxisName(int code);
    static QString absAxisName(int code);


};

#endif // KCLCODE_H

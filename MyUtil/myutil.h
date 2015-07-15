#ifndef MYUTIL_H
#define MYUTIL_H

#include <QString>
#include "myutil_global.h"

class MYUTILSHARED_EXPORT MyUtil
{

public:
    MyUtil();

    static QString getName() {return "MyUtil";}
};

#endif // MYUTIL_H

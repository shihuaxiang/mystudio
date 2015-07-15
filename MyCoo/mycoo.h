#ifndef MYCOO_H
#define MYCOO_H

#include <QString>
#include "mycoo_global.h"

class MYCOOSHARED_EXPORT MyCoo
{

public:
    MyCoo();

    static QString getName() {return "MyCoo";}
};

#endif // MYCOO_H

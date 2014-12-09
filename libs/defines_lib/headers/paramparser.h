#ifndef PARAMPARSER_H
#define PARAMPARSER_H
#include "defineslib_global.h"
#include <QHash>
#include <QList>
#include <QStringList>

class DEFINESLIBSHARED_EXPORT paramParser
{
public:
    paramParser(){;}
    paramParser(QStringList list){parse(list);}
    virtual ~paramParser();
    struct dataParse
    {
        QStringList data;
        QString name;
    };
    virtual void parse(QStringList list);

    bool exists(QString str);
    QStringList get(QString item);

protected:
    QHash<QString, QStringList> hash;
    dataParse parse(QString str);
};


#endif // PARAMPARSER_H

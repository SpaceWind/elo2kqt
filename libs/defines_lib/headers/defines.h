#ifndef DEFINES_H
#define DEFINES_H

#include "defineslib_global.h"
#include <QObject>
#include <QStringList>
#include <QFile>
#include <QTextStream>

class DEFINESLIBSHARED_EXPORT Defines
{
public:
        Defines();
        Defines(QString filename);
        ~Defines();
        QString       Get(QString key, QString prefix="", QString postfix="");
        void          Set(QString key, QString value);

        QStringList   GetList(QString key);
        void          SetList(QString key, QStringList &data);

        void          RemoveList(QString key);
        void          ClearList(QString key);
        bool          AddToList(QString key, QString data);
        void          RemoveFromList(QString keyList, QString data);

        bool          IsDefined(QString key);
        void          Define(QString key);
        void          Undef(QString key);

        void   Load(QString filename);
        void   LoadFromString(QString txt);
        void   Save(QString filename);
        void   Save(){Save(_filename);}
        QString toString();
        QString _filename;
private:
        QStringList l;
};

#endif // DEFINES_H

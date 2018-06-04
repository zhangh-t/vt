#ifndef VTINIOPERATION_H
#define VTINIOPERATION_H

#include <QObject>
#include <QString>
#include <QVariant>
#include <QSettings>
#include "vehicleterminalcommunicationtools_global.h"

class VEHICLETERMINALCOMMUNICATIONTOOLS_EXPORT VTIniOperation : public QObject
{
    Q_OBJECT
public:
    VTIniOperation(const QString& path);
    ~VTIniOperation(); 
public:
    void set(const QString& sectionName, const QString& keyName, const QVariant& value);
    QVariant read(const QString& sectionName, const QString& keyName);
private:
    QSettings* m_Ini;
};

#endif // VTINIOPERATION_H

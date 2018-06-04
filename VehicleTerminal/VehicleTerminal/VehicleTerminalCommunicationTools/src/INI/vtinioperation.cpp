#include "INI/vtinioperation.h"
#include <QFile>
VTIniOperation::VTIniOperation(const QString& path)
    : QObject(0), m_Ini(nullptr)
{
    if (!QFile::exists(path))
    {
        throw QString("%1 not exsits").arg(path);
    }
    m_Ini = new QSettings(path, QSettings::IniFormat);
}

VTIniOperation::~VTIniOperation()
{
    if (m_Ini)
    {
        delete m_Ini; 
    }
}

void VTIniOperation::set(const QString& sectionName, const QString& keyName, const QVariant& value)
{
    if (m_Ini->contains(sectionName + "/" + keyName))
    {
        m_Ini->beginGroup(sectionName);
        m_Ini->setValue(keyName, value);
        m_Ini->endGroup();
    }
}

QVariant VTIniOperation::read(const QString& sectionName, const QString& keyName)
{
    QVariant res;
    if (m_Ini->contains(sectionName + "/" + keyName))
    {
        m_Ini->beginGroup(sectionName);
        res = m_Ini->value(keyName);
        m_Ini->endGroup();
    }
    return res;
}

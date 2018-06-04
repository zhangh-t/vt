#include "vtcommon.h"
#include <QColor>
#include <QString>
VEHICLETERMINALCONTROLS_EXPORT QString vt::colorToString(QColor& color)
{
    int r = color.red();
    int g = color.green();
    int b = color.blue();
    QString sr = QString("%1").arg(r,2,16,QLatin1Char('0'));
    QString sg = QString("%1").arg(g,2,16,QLatin1Char('0'));
    QString sb = QString("%1").arg(b,2,16,QLatin1Char('0'));
    return QString("#")+sr+sg+sb;
}

#ifndef __VTCOMMON_H
#define __VTCOMMON_H
#include "vehicleterminalcontrols_global.h"
#include <QMap>
#include <QVariant>
class QColor;
class QString;
typedef QMap<int, QVariant> VTOptions;    //Õº±Ì—°œÓ
typedef VTOptions::Iterator VTOptionsIter;
namespace vt
{
    VEHICLETERMINALCONTROLS_EXPORT QString colorToString(QColor& color);
    template <typename T> QVariant getOption(VTOptions& option, int key, T defaultIfNotExsits)
    {
        VTOptionsIter iter = option.find(key);
        if (iter == option.end())
        {
            return QVariant(defaultIfNotExsits);
        }
        else {
            return iter.value();
        }
    }
}
#endif

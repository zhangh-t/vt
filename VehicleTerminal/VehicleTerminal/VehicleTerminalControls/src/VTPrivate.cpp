#include "VTPrivate.h"
#include "vtexception.h"
#include <QString>
#include <QByteArray>

VTPrivate::VTPrivate(void)
{
}


VTPrivate::~VTPrivate(void)
{
}

bool VTPrivate::checkValidity(VTOptions& options)
{
    return true;
}

void VTPrivate::raiseException(QString& strExceptionDetails)
{
    int nLength = strExceptionDetails.length();
    QByteArray arr = strExceptionDetails.toLatin1();
    char* pWhat = arr.data();
    VT_RAISEEXCEPTION(pWhat);
}

#pragma once
#include "vtcommon.h"

class VTPrivate
{
public:
    VTPrivate(void);
    ~VTPrivate(void);
public:
    virtual bool checkValidity(VTOptions& options);
    virtual void raiseException(QString& strExceptionDetails);
};


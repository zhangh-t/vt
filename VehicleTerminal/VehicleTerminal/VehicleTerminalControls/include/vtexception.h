#ifndef VTEXCEPTION_H
#define VTEXCEPTION_H
#include <QException>
class VTException : public QException
{
public:
    VTException(char* what);
    ~VTException();
private:
};

#ifdef WINDOWS
#define VT_RAISEEXCEPTION(what) throw VTException(what)
#endif


#endif // VTEXCEPTION_H

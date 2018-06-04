#ifndef VTLOG_H
#define VTLOG_H
#include "log4cplus\logger.h"
#include "log4cplus\consoleappender.h"
#include "log4cplus\fileappender.h"
#include "vehicleterminalcommunicationtools_global.h"
#include <QString>
#include <QMap>
using namespace log4cplus;
enum VTLogMode
{
    lmConsole,
    lmFile,
};

class VTLog;
class VEHICLETERMINALCOMMUNICATIONTOOLS_EXPORT VTLogs
{
public:
    VTLogs* globalInstance();
public:
    VTLog* log(const QString& name);
    VTLog* newLogInstance(const QString& name,
        VTLogMode oMode);
private:
    VTLogs(){}
    ~VTLogs();
private:
    QMap<QString, VTLog*> m_logs;
    static VTLogs* m_pInstance;
};

class VEHICLETERMINALCOMMUNICATIONTOOLS_EXPORT VTLog
{
public:
    void trace(const QString& infomations);
    void debug(const QString& infomations);
    void info(const QString& infomations);
    void warn(const QString& infomations);
    void error(const QString& infomations);
    void fatal(const QString& infomations);
private:
    Logger logger;
    VTLog(const QString& name,
        VTLogMode oMode);
    ~VTLog();
    friend class VTLogs;
};

//demo:
/*
    VTLog* pTestingLog = VTLogs::globalInstance()->newLogInstance(QString("testing"), lmFile);
    //...
    VTLog* pTestingLog = VTLogs::globalInstance()->log(QString("testing"));
    if (pTestingLog)
    {
        pTestingLog->error(QString("error happend"));
    }
*/

#endif // VTLOG_H

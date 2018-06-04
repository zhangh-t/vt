#include "LOG/vtlog.h"
#include "log4cplus/loggingmacros.h"
using namespace log4cplus::helpers;
void VTLog::trace(const QString& infomations)
{
    LOG4CPLUS_TRACE(logger, infomations.toStdWString());
}

void VTLog::debug(const QString& infomations)
{
    LOG4CPLUS_DEBUG(logger, infomations.toStdWString());
}

void VTLog::info(const QString& infomations)
{
    LOG4CPLUS_INFO(logger, infomations.toStdWString());
}

void VTLog::warn(const QString& infomations)
{
    LOG4CPLUS_WARN(logger, infomations.toStdWString());
}

void VTLog::error(const QString& infomations)
{
    LOG4CPLUS_ERROR(logger, infomations.toStdWString());
}

void VTLog::fatal(const QString& infomations)
{
    LOG4CPLUS_FATAL(logger, infomations.toStdWString());
}

VTLog::VTLog(const QString& name,
    VTLogMode oMode)
{
    SharedAppenderPtr pAppender;
    if (oMode == lmConsole)
    {
        pAppender = new ConsoleAppender();
    }
    else if (oMode == lmFile)
    {
        QString strFileName = name + ".log";
        pAppender = new FileAppender(strFileName.toStdWString());
    }

    log4cplus::tstring pattern = L"%d{%m/%d/%y %H:%M:%S}  - %m [%l]%n";
    std::auto_ptr<Layout> pLayout(new PatternLayout(pattern));
     pAppender->setLayout(pLayout);
    logger = Logger::getInstance(name.toStdWString());
    logger.addAppender(pAppender);
}

VTLog::~VTLog()
{

}

VTLogs* VTLogs::m_pInstance = nullptr;
VTLogs* VTLogs::globalInstance()
{
    if (m_pInstance == nullptr)
    {
        m_pInstance = new VTLogs;
    }
    return m_pInstance;
}

VTLog* VTLogs::log(const QString& name)
{
    if (m_logs.contains(name))
    {
        return m_logs[name];
    }
    return nullptr;
}

VTLog* VTLogs::newLogInstance(const QString& name, VTLogMode oMode)
{
    if (m_logs.contains(name))
    {
        delete m_logs[name];
    }
    VTLog* pRes = new VTLog(name, oMode);
    m_logs[name] = pRes;
    return pRes;
}

VTLogs::~VTLogs()
{
    for (auto iter = m_logs.begin(); iter != m_logs.end(); ++iter)
    {
        delete iter.value();
    }
    m_logs.clear();
}

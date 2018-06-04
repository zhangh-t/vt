#include "SOCKET\vtsocket.h"
#include "SOCKET\vtsocket_p.h"


VTSocket::VTSocket(VTSocketType oType, QObject *parent)
    : QObject(parent)
{
    m_private = new VTSocketPrivate;
    m_private->m_pMaster = this;
    m_private->m_oType = oType;
    m_private->m_oState = ssUnInited;
}

VTSocket::~VTSocket()
{
    delete m_private;
}

void VTSocket::start(int nPort)
{
    m_private->initializeSocket(nPort);
}

void VTSocket::stop()
{
    m_private->finalizeSocket();
}

QAbstractSocket::SocketError VTSocket::lastRrror()
{
    return m_private->m_oLastError;
}

VTSocketState VTSocket::state()
{
    return m_private->m_oState;
}

void VTSocket::send(QHostAddress& addr, int nPort, QByteArray& data)
{
    this->doBeforeSend(addr, nPort, data);
    m_private->send(addr, nPort, data);
    this->doAfterSend(addr, nPort, data);
}

void VTSocket::recv(QHostAddress& addr, QByteArray& data)
{
    this->doBeforeRecv(addr, data);
    this->doAfterRecv(addr, data);
}

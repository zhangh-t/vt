#include "SOCKET/vtsocket_p.h"
void VTSocketPrivate::initializeSocket(int nPort)
{
    if (state() == ssUnInited)
    {
        if (m_oType == stTcp)
        {
            m_pSocket = new QTcpSocket(this);
            initForTCPMode();
        }
        else if (m_oType == stUdp)
        {
            m_pSocket = new QUdpSocket(this);
            initForUDPMode();
        }
        m_pSocket->bind(QHostAddress::Any, nPort);
        setState(ssRunning);
    }
}

void VTSocketPrivate::finalizeSocket()
{
    if (state() == ssRunning)
    {
        m_pSocket->close();
        setState(ssUnInited);
    }
    else
    {
        throw "socket is busy now!";
    }
}

void VTSocketPrivate::initForTCPMode()
{
    initBasicly();
}

void VTSocketPrivate::initForUDPMode()
{
    initBasicly();
}

void VTSocketPrivate::initBasicly()
{
    connect(m_pSocket, SIGNAL(readyRead()), this, SLOT(onRecv()));
    connect(m_pSocket, SIGNAL(error(QAbstractSocket::SocketError)), SLOT(onErr(QAbstractSocket::SocketError)));
}

void VTSocketPrivate::setState(VTSocketState oState)
{
    m_oLock.lockForWrite();
    m_oState = oState;
    m_oLock.unlock();
}

VTSocketState VTSocketPrivate::state()
{
    VTSocketState oRes;
    m_oLock.lockForRead();
    oRes = m_oState;
    m_oLock.unlock();
    return oRes;
}

void VTSocketPrivate::connectTo(QHostAddress& addr, int nPort)
{
    if (m_oType == stTcp)
    {
        m_pSocket->connectToHost(addr, nPort);
    }
}

void VTSocketPrivate::broadCast(int nPort, QByteArray& data)
{
    if (m_oType == stUdp)
    {
        setState(ssSendding);
        QUdpSocket* pUdpSocket = dynamic_cast<QUdpSocket*>(m_pSocket);
        if (pUdpSocket)
        {
            pUdpSocket->writeDatagram(data,
                QHostAddress::Broadcast, nPort);
        }
        setState(ssRunning);
    }
}

void VTSocketPrivate::send(QHostAddress& addr, int nPort, QByteArray& data)
{
    setState(ssSendding);
    if (m_oType == stUdp)
    {
        udpSend(addr, nPort, data);
    }
    else if (m_oType == stTcp)
    {
        tcpSend(addr, nPort, data);
    }
    setState(ssRunning);
}

void VTSocketPrivate::onRecv()
{
    setState(ssReciving);
    if (m_oType == stTcp)
    {
        tcpRecv();
    }
    else if (m_oType == stUdp)
    {
        udpRecv();
    }
    setState(ssRunning);
}

void VTSocketPrivate::onErr(QAbstractSocket::SocketError err)
{
    m_oLastError = err;
}

void VTSocketPrivate::udpRecv()
{
    QUdpSocket* pUdpSocket = dynamic_cast<QUdpSocket*>(m_pSocket);
    if (pUdpSocket)
    {
        QByteArray data;
        QHostAddress addr = pUdpSocket->peerAddress();
        while (pUdpSocket->hasPendingDatagrams())
        {
            QByteArray innerData;
            innerData.resize(pUdpSocket->pendingDatagramSize());
            pUdpSocket->readDatagram(data.data(), innerData.size());
            data += innerData;
        }
        m_pMaster->recv(addr, data);
    }
}

void VTSocketPrivate::tcpRecv()
{
    QTcpSocket* pTcpSocket = dynamic_cast<QTcpSocket*>(m_pSocket);
    if (pTcpSocket)
    {
        QHostAddress addr = pTcpSocket->peerAddress();
        QByteArray data = pTcpSocket->readAll();
        m_pMaster->recv(addr, data);
    }
}

void VTSocketPrivate::udpSend(QHostAddress& addr, int nPort, QByteArray& data)
{
    QUdpSocket* pUdpSocket = dynamic_cast<QUdpSocket*>(m_pSocket);
    if (pUdpSocket)
    {
        pUdpSocket->writeDatagram(data, addr, nPort);
    }
}

void VTSocketPrivate::tcpSend(QHostAddress& addr, int nPort, QByteArray& data)
{
    QTcpSocket* pTcpSocket = dynamic_cast<QTcpSocket*>(m_pSocket);
    if (pTcpSocket)
    {
        pTcpSocket->write(data);
    }
}

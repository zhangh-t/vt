#ifndef VTSOCKET_P_H
#define VTSOCKET_P_H

#include <QObject>
#include <QTcpSocket>
#include <QUdpSocket>
#include <QMutex>
#include <QReadWriteLock>
#include "SOCKET/vtsocket.h"

class VTSocketPrivate : public QObject
{
    Q_OBJECT
public:
    VTSocketPrivate() {}
    ~VTSocketPrivate() {}
private:
    void initializeSocket(int nPort);
    void finalizeSocket();
private:
    void initForTCPMode();
    void initForUDPMode();
    void initBasicly();
public:
    void setState(VTSocketState oState);
    VTSocketState state();
public:
    void connectTo(QHostAddress& addr, int nPort);    //定向连接
    void broadCast(int nPort, QByteArray& data);    //UDP广播
    void send(QHostAddress& addr, int nPort, QByteArray& data);
    private slots:
        void onRecv();
        void onErr(QAbstractSocket::SocketError err);
private:
    void udpRecv();
    void tcpRecv();
    void udpSend(QHostAddress& addr, int nPort, QByteArray& data);
    void tcpSend(QHostAddress& addr, int nPort, QByteArray& data);
private:
    QAbstractSocket* m_pSocket;
    VTSocket* m_pMaster;;
private:
    VTSocketType m_oType;
    friend VTSocket;
private:
    VTSocketState m_oState;
    QReadWriteLock m_oLock;
    QAbstractSocket::SocketError m_oLastError;
};

#endif // VTSOCKET_P_H

#ifndef VTSOCKET_H
#define VTSOCKET_H

#include <QObject>
#include <QHostAddress>
#include <QAbstractSocket>
#include "vehicleterminalcommunicationtools_global.h"

enum VTSocketType
{
    stTcp,
    stUdp,
};

enum VTSocketState
{
    ssUnInited,
    ssRunning,
    ssReciving,
    ssSendding,
};

class VTSocketPrivate;
class VEHICLETERMINALCOMMUNICATIONTOOLS_EXPORT VTSocket : public QObject
{
    Q_OBJECT
public:
    VTSocket(VTSocketType oType, 
        QObject *parent = nullptr);
    ~VTSocket();
public:
    void start(int nPort);
    void stop();
public:
    QAbstractSocket::SocketError lastRrror();
    VTSocketState state();
public:
    //如果是tcp，则无视前两个参数
    void send(QHostAddress& addr, int nPort, QByteArray& data);
    void recv(QHostAddress& addr, QByteArray& data);
protected:
    virtual void doBeforeSend(QHostAddress& addr, int nPort, QByteArray& data) {}
    virtual void doAfterSend(QHostAddress& addr, int nPort, QByteArray& data) {}
    virtual void doBeforeRecv(QHostAddress& addr, QByteArray& data) {}
    virtual void doAfterRecv(QHostAddress& addr, QByteArray& data) {}
private:
    VTSocketPrivate* m_private;
};

#endif // VTSOCKET_H

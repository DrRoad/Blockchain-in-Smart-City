#ifndef PEERSTER_NETSOCKET_HH
#define PEERSTER_NETSOCKET_HH

#include <unistd.h>
#include <QUdpSocket>
#include <QDebug>

#include "Block.hh"
#include "Peer.hh"

class NetSocket : public QUdpSocket
{
	Q_OBJECT
        
public:
  NetSocket(QVector<Peer*> *peerList);

	// Bind this socket to a Peerster-specific default port.
	int bind();
  quint16 getPortNum();
  QString getPortString();

  void sendMsg(QString text, QString origin, quint32 seq, const QHostAddress addr, quint16 port, quint32 lastIP = 0, quint16 lastPort = 0);
  void sendRouteRumor(QString origin, quint32 seq, const QHostAddress addr, quint16 port, quint32 lastIP = 0, quint16 lastPort = 0);
  void sendBlockRequest(QString, QString, quint32, QByteArray, const QHostAddress, quint16);
  void sendBlockReply(QString, QString, quint32, QByteArray, QByteArray, const QHostAddress,quint16);
  void sendNewBLOCK(Block block, const QHostAddress addr, quint16 port);
  void sendNewBLOCKToNeighbors(Block block, QHostAddress exSender = QHostAddress::Null, quint16 exSenderPort = 0);
  void sendWantBLOCKMsg(const QHostAddress addr, quint16 port, quint16 seq);
  void sendPrivateMsg(QString dest, QString origin, QString text, quint32 ttl, const QHostAddress addr,quint16 port);

private:
  QVector<Peer*> *peerList;
	int myPortMin, myPortMax;
  quint16 portNum;
};


#endif

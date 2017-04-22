#include "tlo/qtnetcatmodel.hpp"

namespace tlo {
void QtNetcatModel::receiveFromRemote() {
  if (!tcpSocket->atEnd()) {
    emit dataFromRemote(tcpSocket->readAll());
  }
}

void QtNetcatModel::emitDisconnectedStatusMessage() {
  emit statusMessage("disconnected\n");
}

QtNetcatModel::QtNetcatModel(const QString &remoteHostName_,
                             quint16 remotePort_, QObject *parent)
    : QObject(parent),
      remoteHostName(remoteHostName_),
      remotePort(remotePort_) {}

void QtNetcatModel::run() {
  // allocate tcpSocket in run() rather than in constructor so that tcpSocket
  // will be in the same thread where run() is called
  tcpSocket = new QTcpSocket(this);

  emit statusMessage("connecting\n");
  tcpSocket->connectToHost(remoteHostName, remotePort);
  if (tcpSocket->waitForConnected()) {
    emit statusMessage(
        QString("connected to %1|%2\n").arg(remoteHostName).arg(remotePort));
  } else {
    emit statusMessage(QString("failed to connect to %1|%2\n")
                           .arg(remoteHostName)
                           .arg(remotePort));
    emit disconnected();
  }

  connect(tcpSocket, SIGNAL(readyRead()), this, SLOT(receiveFromRemote()));
  connect(tcpSocket, SIGNAL(disconnected()), this,
          SLOT(emitDisconnectedStatusMessage()));
  connect(tcpSocket, SIGNAL(disconnected()), this, SIGNAL(disconnected()));
}

void QtNetcatModel::sendToRemote(const QByteArray &data) {
  if (tcpSocket->state() == QAbstractSocket::ConnectedState &&
      tcpSocket->isValid()) {
    tcpSocket->write(data);
    tcpSocket->flush();
  }
}
}  // namespace tlo

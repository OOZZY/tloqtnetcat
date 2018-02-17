#ifndef TLO_QTNETCATMODEL_HPP
#define TLO_QTNETCATMODEL_HPP

#include <QTcpSocket>

namespace tlo {
class QtNetcatModel : public QObject {
  Q_OBJECT

 private:
  QString remoteHostName;
  quint16 remotePort;
  QTcpSocket *tcpSocket;

 private slots:
  void receiveFromRemote();
  void emitDisconnectedStatusMessage();

 public:
  QtNetcatModel(const QString &remoteHostName_, quint16 remotePort_,
                QObject *parent = nullptr);

 public slots:
  void run();
  void sendToRemote(const QByteArray &data);

 signals:
  void statusMessage(const QString &message);
  void dataFromRemote(const QByteArray &data);
  void disconnected();
};
}  // namespace tlo

#endif  // TLO_QTNETCATMODEL_HPP

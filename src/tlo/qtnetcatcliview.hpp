#ifndef TLO_QTNETCATCLIVIEW_HPP
#define TLO_QTNETCATCLIVIEW_HPP

#include "tlo/qtnetcatmodel.hpp"

namespace tlo {
class QtNetcatCLIViewReceiver : public QObject {
  Q_OBJECT

 private:
  QtNetcatModel *netcatModel;

 private slots:
  void displayStatusMessage(const QString &message);
  void displayDataFromRemote(const QByteArray &data);
  void handleDisconnect();

 public:
  explicit QtNetcatCLIViewReceiver(QtNetcatModel &model_,
                                   QObject *parent = nullptr);
};

class QtNetcatCLIViewSender : public QObject {
  Q_OBJECT

 private:
  QtNetcatModel *netcatModel;

 public:
  explicit QtNetcatCLIViewSender(QtNetcatModel &model_,
                                 QObject *parent = nullptr);

 public slots:
  void run();

 signals:
  void dataEntered(const QByteArray &data);
  void finished();
};
}  // namespace tlo

#endif  // TLO_QTNETCATCLIVIEW_HPP

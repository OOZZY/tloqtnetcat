#include "tlo/qtnetcatcliview.hpp"

namespace tlo {
void QtNetcatCLIViewReceiver::displayStatusMessage(const QString &message) {
  QTextStream out(stdout);
  out << "tloqtnetcat: " << message << flush;
}

void QtNetcatCLIViewReceiver::displayDataFromRemote(const QByteArray &data) {
  QTextStream out(stdout);
  out << data << flush;
}

namespace {
const char *const EXIT_COMMAND = "exit";
}  // namespace

void QtNetcatCLIViewReceiver::handleDisconnect() {
  QTextStream out(stdout);
  out << "tloqtnetcatcli: please enter \"" << EXIT_COMMAND << "\" to exit"
      << endl;
}

QtNetcatCLIViewReceiver::QtNetcatCLIViewReceiver(QtNetcatModel &model_,
                                                 QObject *parent)
    : QObject(parent), netcatModel(&model_) {
  connect(netcatModel, SIGNAL(statusMessage(QString)), this,
          SLOT(displayStatusMessage(QString)));
  connect(netcatModel, SIGNAL(dataFromRemote(QByteArray)), this,
          SLOT(displayDataFromRemote(QByteArray)));
  connect(netcatModel, SIGNAL(disconnected()), this, SLOT(handleDisconnect()));
}

QtNetcatCLIViewSender::QtNetcatCLIViewSender(QtNetcatModel &model_,
                                             QObject *parent)
    : QObject(parent), netcatModel(&model_) {
  connect(this, SIGNAL(dataEntered(QByteArray)), netcatModel,
          SLOT(sendToRemote(QByteArray)));
}

void QtNetcatCLIViewSender::run() {
  QTextStream out(stdout);
  QTextStream in(stdin);

  out << "tloqtnetcatcli: running" << endl;
  out << "tloqtnetcatcli: enter \"" << EXIT_COMMAND << "\" to exit" << endl;

  while (!in.atEnd()) {
    QString line = in.readLine();
    if (line == EXIT_COMMAND) {
      out << "tloqtnetcatcli: exit command received" << endl;
      break;
    }
    line.append('\n');
    emit dataEntered(line.toUtf8());
  }

  out << "tloqtnetcatcli: exiting" << endl;
  emit finished();
}
}  // namespace tlo

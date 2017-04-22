#include <QApplication>
#include <QThread>
#include <QTimer>
#include <tlo/qtnetcatcliview.hpp>
#include <tlo/qtnetcatmodel.hpp>

namespace {
const int PROGRAM_INDEX = 0;
const int HOST_INDEX = 1;
const int PORT_INDEX = 2;
const int NUM_ARGS_NEEDED = 3;
}  // namespace

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);

  QStringList arguments = QCoreApplication::arguments();
  if (arguments.size() < NUM_ARGS_NEEDED) {
    QTextStream out(stdout);
    out << "usage: " << arguments.at(PROGRAM_INDEX) << " <host> <port>" << endl;
    return 0;
  }
  const QString host = arguments.at(HOST_INDEX);
  const quint16 port = arguments.at(PORT_INDEX).toUShort();

  try {
    QThread *netcatModelThread = new QThread;
    QThread *netcatCLIViewReceiverThread = new QThread;

    tlo::QtNetcatModel netcatModel(host, port);
    tlo::QtNetcatCLIViewReceiver netcatCLIViewReceiver(netcatModel);
    tlo::QtNetcatCLIViewSender netcatCLIViewSender(netcatModel);

    /*
     * from http://doc.qt.io/qt-5/signalsandslots.html#signals:
     * If several slots are connected to one signal, the slots will be executed
     * one after the other, in the order they have been connected, when the
     * signal is emitted.
     */

    // execute netcatModel.run() when netcatModelThread->start()
    QObject::connect(netcatModelThread, SIGNAL(started()), &netcatModel,
                     SLOT(run()));

    // execute netcatCLIViewSender.run() in event loop after event loop starts
    QTimer::singleShot(0, &netcatCLIViewSender, SLOT(run()));

    // thread will emit finished() after it quit()
    QObject::connect(&netcatCLIViewSender, SIGNAL(finished()),
                     netcatCLIViewReceiverThread, SLOT(quit()));
    QObject::connect(netcatCLIViewReceiverThread, SIGNAL(finished()),
                     netcatModelThread, SLOT(quit()));

    // allocating QThread using new and using deleteLater() prevents
    // "QThread: Destroyed while thread is still running"
    QObject::connect(netcatCLIViewReceiverThread, SIGNAL(finished()),
                     netcatCLIViewReceiverThread, SLOT(deleteLater()));
    QObject::connect(netcatModelThread, SIGNAL(finished()), netcatModelThread,
                     SLOT(deleteLater()));

    QObject::connect(netcatModelThread, SIGNAL(finished()),
                     QCoreApplication::instance(), SLOT(quit()));

    netcatModel.moveToThread(netcatModelThread);
    netcatCLIViewReceiver.moveToThread(netcatCLIViewReceiverThread);

    netcatModelThread->start();
    netcatCLIViewReceiverThread->start();

    return app.exec();
  } catch (const std::exception &e) {
    QTextStream err(stderr);
    err << e.what() << endl;
  }
}

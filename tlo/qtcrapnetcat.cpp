#include "tlo/qtcrapnetcat.hpp"
#include <thread>

namespace tlo {
QtCrapNetcatError::QtCrapNetcatError(const std::string &what)
    : std::runtime_error(what) {}
void QtCrapNetcatError::outoflinevirtualmethod() {}

namespace {
QTextStream out(stdout);
}  // namespace

QtCrapNetcat::QtCrapNetcat(const QString &hostName, quint16 port) {
  out << "connecting" << endl;
  tcpSocket.connectToHost(hostName, port);
  if (tcpSocket.waitForConnected()) {
    out << "connected to " << hostName << "|" << port << endl;
  } else {
    throw QtCrapNetcatError(
        "QtCrapNetcat::QtCrapNetcat: failed to connect to host");
  }
}

namespace {
const int MSECS_TIMEOUT = 125;

void backgroundTask(bool &running, QTcpSocket &tcpSocket) {
  while (running) {
    if (tcpSocket.waitForReadyRead(MSECS_TIMEOUT)) {
      QByteArray data = tcpSocket.readAll();
      out << data << flush;
    }

    if (tcpSocket.state() == QAbstractSocket::UnconnectedState ||
        tcpSocket.waitForDisconnected(MSECS_TIMEOUT)) {
      out << "server closed connection. please exit" << endl;
      running = false;
    }
  }
}

const char *const EXIT_COMMAND = "exit";
}  // namespace

void QtCrapNetcat::run() {
  out << "running" << endl;
  out << "enter \"exit\" to exit" << endl;

  // use std::ref so thread actually uses references and not copies
  std::thread thread =
      std::thread(backgroundTask, std::ref(running), std::ref(tcpSocket));

  QTextStream in(stdin);
  while (!in.atEnd()) {
    QString line = in.readLine();
    if (line == EXIT_COMMAND) {
      out << "exit command received" << endl;
      running = false;
      break;
    }
    line.append('\n');
    tcpSocket.write(line.toUtf8());
    tcpSocket.flush();
  }

  thread.join();

  out << "exiting" << endl;
}
}  // namespace tlo

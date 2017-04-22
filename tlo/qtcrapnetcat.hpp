#ifndef TLO_QTCRAPNETCAT_HPP
#define TLO_QTCRAPNETCAT_HPP

#include <QTcpSocket>

namespace tlo {
class QtCrapNetcatError : public std::runtime_error {
 public:
  explicit QtCrapNetcatError(const std::string &what);
  virtual void outoflinevirtualmethod();
};

class QtCrapNetcat {
 private:
  QTcpSocket tcpSocket;
  bool running = true;

 public:
  QtCrapNetcat(const QString &hostName, quint16 port);
  void run();
};
}  // namespace tlo

#endif  // TLO_QTCRAPNETCAT_HPP

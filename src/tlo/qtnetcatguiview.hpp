#ifndef TLO_QTNETCATGUIVIEW_HPP
#define TLO_QTNETCATGUIVIEW_HPP

#include <QMainWindow>
#include "tlo/qtnetcatmodel.hpp"

namespace tlo {
namespace Ui {
class QtNetcatGUIView;
}

class QtNetcatGUIView : public QMainWindow {
  Q_OBJECT

 private:
  Ui::QtNetcatGUIView *ui;
  QtNetcatModel *netcatModel;

 private slots:
  void displayStatusMessage(const QString &message);
  void displayDataFromRemote(const QByteArray &data);
  void handleDisconnect();
  void on_messageToSend_returnPressed();

 public:
  explicit QtNetcatGUIView(QtNetcatModel &model_, QWidget *parent = nullptr);
  ~QtNetcatGUIView();

 signals:
  void dataEntered(const QByteArray &data);
};
}  // namespace tlo

#endif  // TLO_QTNETCATGUIVIEW_HPP

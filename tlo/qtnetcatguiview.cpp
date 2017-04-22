#include "tlo/qtnetcatguiview.hpp"
#include "tlo/ui_qtnetcatguiview.h"

namespace tlo {
namespace {
QString removeNewline(QString string) {
  if (string.endsWith("\r\n")) {
    string.remove(string.size() - 2, 2);
  } else if (string.endsWith("\n")) {
    string.remove(string.size() - 1, 1);
  }
  return string;
}
}  // namespace

void QtNetcatGUIView::displayStatusMessage(const QString &message) {
  ui->messages->appendPlainText(
      QString("tloqtnetcat: %1").arg(removeNewline(message)));
}

void QtNetcatGUIView::displayDataFromRemote(const QByteArray &data) {
  ui->messages->appendPlainText(removeNewline(QString::fromUtf8(data)));
}

void QtNetcatGUIView::handleDisconnect() {
  ui->messages->appendPlainText("tloqtnetcatgui: please exit");
}

void QtNetcatGUIView::on_messageToSend_returnPressed() {
  emit dataEntered(ui->messageToSend->text().append('\n').toUtf8());
  ui->messages->appendPlainText(
      QString("tloqtnetcatgui: sent: %1").arg(ui->messageToSend->text()));
  ui->messageToSend->clear();
}

QtNetcatGUIView::QtNetcatGUIView(QtNetcatModel &model_, QWidget *parent)
    : QMainWindow(parent), ui(new Ui::QtNetcatGUIView), netcatModel(&model_) {
  ui->setupUi(this);
  connect(netcatModel, SIGNAL(statusMessage(QString)), this,
          SLOT(displayStatusMessage(QString)));
  connect(netcatModel, SIGNAL(dataFromRemote(QByteArray)), this,
          SLOT(displayDataFromRemote(QByteArray)));
  connect(netcatModel, SIGNAL(disconnected()), this, SLOT(handleDisconnect()));
  connect(this, SIGNAL(dataEntered(QByteArray)), netcatModel,
          SLOT(sendToRemote(QByteArray)));
}

QtNetcatGUIView::~QtNetcatGUIView() { delete ui; }
}  // namespace tlo

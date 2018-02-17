#include <QApplication>
#include <tlo/qtnetcatguiview.hpp>
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
    tlo::QtNetcatModel netcatModel(host, port);
    tlo::QtNetcatGUIView netcatGUIView(netcatModel);
    netcatGUIView.show();
    netcatModel.run();
    return app.exec();
  } catch (const std::exception &e) {
    QTextStream err(stderr);
    err << e.what() << endl;
  }
}

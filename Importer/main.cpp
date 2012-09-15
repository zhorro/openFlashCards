#include <QApplication>
#include "importerwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    importerWindow w;
    w.show();
    
    return a.exec();

	delete manager;
}

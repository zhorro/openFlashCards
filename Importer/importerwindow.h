#ifndef IMPORTERWINDOW_H
#define IMPORTERWINDOW_H

#include <QByteArray>
#include <QMainWindow>
#include <QWebPage>

#include "wordsimporter.h"

namespace Ui {
class importerWindow;
}

class importerWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit importerWindow(QWidget *parent = 0);
    ~importerWindow();

public slots:
    void onGo();
    void weVeGotTranslation(QString);

private:
    Ui::importerWindow *ui;
    wordsImporter impa;
};

#endif // IMPORTERWINDOW_H

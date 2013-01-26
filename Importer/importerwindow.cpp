#include "importerwindow.h"
#include "wordsbuilder.h"
#include "ui_importerwindow.h"

#include <QDebug>

#include <QDir>

#include <QThreadPool>
#include <QTextStream>

#include <QWebElementCollection>
#include <QWebFrame>

importerWindow::importerWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::importerWindow),
    impa(false, "it", "ru", this)
{
    ui->setupUi(this);

    connect (ui->pushButton, SIGNAL(clicked()), this,  SLOT(onGo()));
    connect (&impa, SIGNAL(wordTranslated(QString)), this, SLOT(weVeGotTranslation(QString)), Qt::QueuedConnection);
}

importerWindow::~importerWindow()
{
    delete ui;
}

void importerWindow::onGo()
{
    QString txt = ui->textEdit->toPlainText();
    impa.useBackTranslation(ui->tansBack->isChecked());
    impa.onGo(txt);
}

void importerWindow::weVeGotTranslation(QString word)
{
    ui->translatedWords->addItem(word);
}


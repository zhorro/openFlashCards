#include "importerwindow.h"
#include "wordsbuilder.h"
#include "ui_importerwindow.h"

#include <QDebug>

#include <QThreadPool>
#include <QTextStream>

#include <QWebElementCollection>
#include <QWebFrame>

importerWindow::importerWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::importerWindow)
{
    ui->setupUi(this);

	words      = new wordsBuilder ("es-ru-es");
	cleanWords = new wordsBuilder ("es-ru-es");
	backtransl = new wordsBuilder ("es-ru-es");

	connect (ui->pushButton, SIGNAL(clicked()), this,  SLOT(onGo()));
	connect (this, SIGNAL(wowNewWord(QString)), words, SLOT(add(QString)), Qt::QueuedConnection);
	connect (words, SIGNAL(cleanWord(QString)), cleanWords, SLOT(add(QString)), Qt::QueuedConnection);
	connect (cleanWords, SIGNAL(cleanWord(QString, QByteArray)), this, SLOT(returnWord(QString, QByteArray)), Qt::QueuedConnection);
	connect (this, SIGNAL(translateItBack(QString)), backtransl, SLOT(add(QString)), Qt::QueuedConnection);
	connect (backtransl, SIGNAL(cleanWord(QString, QByteArray)), this, SLOT(saveCard(QString, QByteArray)), Qt::QueuedConnection);
}

importerWindow::~importerWindow()
{
    delete ui;
}

void importerWindow::onGo()
{
    QString plainText = ui->textEdit->toPlainText();
    QTextStream stream (&plainText);

    while ( !stream.atEnd () )
    {
        QString candi;
        stream >> candi;
		emit wowNewWord(candi);
    }
}

void importerWindow::returnWord(QString word, QByteArray translation)
{
	saveCard(word, translation); // Но туточки нужно не просто сохранить слово, но и запузырить обратный поиск!
	QWebFrame * frame = page.mainFrame();
	frame->setContent (translation);
	if (ui->tansBack->isChecked())
	{
		QWebElementCollection transl = frame->findAllElements(".b-translate a");
		foreach (QWebElement h, transl) {
			qDebug() << "translate back" << h.toPlainText();
			emit translateItBack(h.toPlainText());
		}
	}
}

void importerWindow::saveCard   (QString word, QByteArray translation)
{
	ui->plainTextEdit->appendPlainText (word);

	QFile file ("replays/"+word+".html");
	file.open (QIODevice::WriteOnly);
	file.write(translation);
	file.close();

	QWebFrame * frame = page.mainFrame();
	frame->setContent (translation);

	QWebElement header = frame->findFirstElement(".b-title");
	
	QWebElementCollection perevod = frame->findAllElements(".b-translate p");

	QFile transFile (QString("translations/%1.txt").arg(header.toPlainText()));
	transFile.open(QIODevice::WriteOnly);
	QTextStream io (&transFile);

	io << header.toPlainText() << endl << endl;

	foreach (QWebElement h, perevod) {
		qDebug() << h.toOuterXml();
		if (h.hasClass("l0"))
			io << h.toPlainText() << endl;
		else if (h.hasClass("l1"))
			io << "    " << h.toPlainText() << endl;
		else if (h.hasClass("l2"))
			io << "    " << "    " << h.toPlainText() << endl;
		else
			qDebug() << "unknown classes: " << h.classes();
	}
}


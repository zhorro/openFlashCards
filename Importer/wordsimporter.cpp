#include <QDebug>
#include <QDir>
#include <QThreadPool>
#include <QTextStream>
#include <QWebElementCollection>
#include <QWebFrame>

#include "wordsimporter.h"
#include "wordsbuilder.h"


wordsImporter::wordsImporter(bool backTrans, QString src, QString dst, QObject * parent)
	 : QObject(parent)
	 , backTranslation(backTrans)
{
	words      = new wordsBuilder (QString("%1-%2-%2").arg(src).arg(dst));
	cleanWords = new wordsBuilder (QString("%1-%2-%2").arg(src).arg(dst));
	backtransl = new wordsBuilder (QString("%1-%2-%2").arg(src).arg(dst));
	pica	   = new picturesDownloader();
	sndUrl     = new soundUrlExtractor(QString("%1-%2").arg(src).arg(dst));
	sndDownloader = new urlDownloader ();

	connect (this, SIGNAL(wowNewWord(QString)), words, SLOT(add(QString)), Qt::QueuedConnection);
	connect (words, SIGNAL(cleanWord(QString)), cleanWords, SLOT(add(QString)), Qt::QueuedConnection);
	connect (cleanWords, SIGNAL(cleanWord(QString, QByteArray)), this, SLOT(returnWord(QString, QByteArray)), Qt::QueuedConnection);
	connect (this, SIGNAL(translateItBack(QString)), backtransl, SLOT(add(QString)), Qt::QueuedConnection);

	connect (this, SIGNAL(picturize(QString)), pica, SLOT(add(QString)), Qt::QueuedConnection);
	connect (this, SIGNAL(soundize(QString)), sndUrl, SLOT(add(QString)), Qt::QueuedConnection);
	connect (sndUrl, SIGNAL(downloadUrl(QString, QUrl)), sndDownloader, SLOT(add(QString, QUrl)), Qt::QueuedConnection);
	
	connect (sndDownloader, SIGNAL(downloadDone(QString, QByteArray)), this, SLOT(saveSnd(QString, QByteArray)), Qt::QueuedConnection);
	connect (backtransl, SIGNAL(cleanWord(QString, QByteArray)), this, SLOT(saveCard(QString, QByteArray)), Qt::QueuedConnection);
}

wordsImporter::~wordsImporter()
{
	delete words;
	delete cleanWords;
	delete backtransl;
	delete pica;
	delete sndUrl;
	delete sndDownloader;
}

void wordsImporter::onGo(QString & text)
{
    QTextStream stream (&text);

    while ( !stream.atEnd () )
    {
        QString candi;
        stream >> candi;
		emit wowNewWord(candi);
    }
}

void wordsImporter::returnWord(QString word, QByteArray translation)
{
	saveCard(word, translation); // Но туточки нужно не просто сохранить слово, но и запузырить обратный поиск!
	QWebFrame * frame = page.mainFrame();
	frame->setContent (translation);
	if (backTranslation)
	{
		QWebElementCollection transl = frame->findAllElements(".b-translate a");
		foreach (QWebElement h, transl) {
			qDebug() << "translate back" << h.toPlainText();
			emit translateItBack(h.toPlainText());
		}
	}
	emit picturize(word);
	emit soundize (word);
	emit wordTranslated(word);
}

void wordsImporter::saveCard   (QString word, QByteArray translation)
{
    QDir::current().mkpath("replays/");
	QFile file ("replays/"+word+".html");
	file.open (QIODevice::WriteOnly);
	file.write(translation);
	file.close();

	QWebFrame * frame = page.mainFrame();
	frame->setContent (translation);

	QWebElement header = frame->findFirstElement(".b-title");
	
	QWebElementCollection perevod = frame->findAllElements(".b-translate p");

    QDir::current().mkpath("translations/");
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

void wordsImporter::saveSnd (QString word, QByteArray sound)
{
    QDir::current().mkpath("translations/");
	QFile soundFile (QString("translations/%1.mp3").arg(word));
	soundFile.open(QIODevice::WriteOnly);
	soundFile.write(sound);
	soundFile.close();
}


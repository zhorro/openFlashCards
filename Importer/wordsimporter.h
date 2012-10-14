#ifndef WORDS_IMPORTERWINDOW_H
#define WORDS_IMPORTERWINDOW_H

#include <QByteArray>
#include <QMainWindow>
#include <QWebPage>

#include "wordsbuilder.h"
#include "picturesdownloader.h"
#include "soundUrlExtractor.h"
#include "urldownloader.h"

class wordsImporter : public QObject
{
    Q_OBJECT

public:
    explicit wordsImporter(bool backTrans, QString src, QString dst = "ru", QObject * parent = NULL);
    ~wordsImporter();

public slots:
    void useBackTranslation(bool backTranslationState = true) { backTranslation = backTranslationState; }

    void returnWord (QString word, QByteArray translation = QByteArray ());
	void saveCard   (QString word, QByteArray card);
	void saveSnd    (QString word, QByteArray snd);

	void onGo(QString & text);

private:
    bool backTranslation;

    QWebPage page;

	wordsBuilder * words;
	wordsBuilder * cleanWords;
	wordsBuilder * backtransl;

	picturesDownloader * pica;
	soundUrlExtractor  * sndUrl;
	urlDownloader	   * sndDownloader;

signals:
	void wowNewWord (QString word);
	void translateItBack (QString word);
	void picturize (QString work);
	void soundize  (QString work);
	void downloadSnd (QString, QUrl);

	void wordTranslated (QString);
};

#endif // WORDS_IMPORTERWINDOW_H

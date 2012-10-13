#ifndef IMPORTERWINDOW_H
#define IMPORTERWINDOW_H

#include <QByteArray>
#include <QMainWindow>
#include <QWebPage>

#include "wordsbuilder.h"
#include "picturesdownloader.h"

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
	void returnWord (QString word, QByteArray translation = QByteArray ());
	void saveCard   (QString word, QByteArray card);

	void onGo();

private:
    Ui::importerWindow *ui;
	
	QWebPage page;
	
	wordsBuilder * words;
	wordsBuilder * cleanWords;
	wordsBuilder * backtransl;

	picturesDownloader * pica;

signals:
	void wowNewWord (QString word);
	void translateItBack (QString word);
	void picturize (QString work);
};

#endif // IMPORTERWINDOW_H

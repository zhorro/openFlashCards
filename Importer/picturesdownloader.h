#ifndef PICTURESDOWNLOADER_H
#define PICTURESDOWNLOADER_H

#include <QObject>
#include <QThread>
#include <QStringList>
#include <QNetworkAccessManager>
#include <QWebPage>

class picturesDownloader : public QThread
{
    Q_OBJECT

	QWebPage page;

    bool active;
    void next();
public:
    QStringList words;
	explicit picturesDownloader();

public slots:
	void pageLoaded (bool ok);
    void add (QString);

signals:
    void cleanWord(QString str, QByteArray translation = QByteArray ());
};


#endif // PICTURESDOWNLOADER_H

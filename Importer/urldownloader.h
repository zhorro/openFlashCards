#ifndef urlDownloader_H
#define urlDownloader_H

#include <QObject>
#include <QRunnable>
#include <QString>
#include <QStringList>

#include <QNetworkAccessManager>
#include <QNetworkReply>

#include <QThread>
#include <QList>
#include <QPair>

class downloadPair : public QPair<QString, QUrl> 
{
public:
downloadPair (QString f, QUrl s) : QPair<QString, QUrl>(f,s) {};
bool operator== (const downloadPair&b) 
{ 
	return this->first.compare(b.first, Qt::CaseInsensitive) == 0; 
}
};

class urlDownloader : public QThread
{
	Q_OBJECT

	QNetworkAccessManager * manager;
	bool active;
	void next();
public:
	QList <downloadPair> words;
	explicit urlDownloader();

public slots:
	void replyFinished (QNetworkReply*);
	void add (QString, QUrl);

signals:
	void downloadDone(QString str, QByteArray data = QByteArray ());
};

#endif // urlDownloader_H

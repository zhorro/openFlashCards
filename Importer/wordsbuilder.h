#ifndef WORDSBUILDER_H
#define WORDSBUILDER_H

#include <QObject>
#include <QRunnable>
#include <QString>
#include <QStringList>

#include <QNetworkAccessManager>
#include <QNetworkReply>

#include <QThread>

class wordsBuilder : public QThread
{
	Q_OBJECT

	QNetworkAccessManager * manager;
	bool active;
	void next();
	QString request;
public:
	QStringList words;
	explicit wordsBuilder(QString lang);

public slots:
	void replyFinished (QNetworkReply*);
	void add (QString);

signals:
	void cleanWord(QString str, QByteArray translation = QByteArray ());
};

#endif // WORDSBUILDER_H

#include <QTextStream>
#include <QDebug>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QFile>

#include "urldownloader.h"

urlDownloader::urlDownloader()
{
	manager = new QNetworkAccessManager(this);
	connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyFinished(QNetworkReply*)));
	active = false;
	words.clear();
}

void urlDownloader::next()
{
	if (!words.count() || active)
		return;

	active = true;
    manager->get(QNetworkRequest(words[0].second));
}

void urlDownloader::replyFinished (QNetworkReply * reply)
{
	active = false;
	QByteArray R = reply->readAll();
	emit downloadDone(words[0].first, R);

	words.removeFirst();
	next();
}

void urlDownloader::add(QString newWord, QUrl newUrl)
{	
	downloadPair pair (newWord, newUrl);
	if (words.contains(pair))
		return;

	words.append(pair);
	next();
}


#include <QTextStream>
#include <QDebug>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QFile>

#include "picturesdownloader.h"

picturesDownloader::picturesDownloader(QString lang) :
    request(lang)
{
    manager = new QNetworkAccessManager(this);
    connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyFinished(QNetworkReply*)));
    active = false;
}

void picturesDownloader::next()
{
    if (!words.count() || active)
        return;

    active = true;
    manager->get(QNetworkRequest(QUrl(QString("http://%1.jpg.to").arg(words[0]))));
}

void picturesDownloader::replyFinished (QNetworkReply * reply)
{
    active = false;
    QByteArray R = reply->readAll();



    next();
}

void picturesDownloader::add(QString newWord)
{
    if (words.contains(newWord, Qt::CaseInsensitive))
        return;

    words.append(newWord);
    next();
}


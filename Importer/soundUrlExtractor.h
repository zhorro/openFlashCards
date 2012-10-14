#ifndef soundDownloader_H
#define soundDownloader_H

#include <QObject>
#include <QThread>
#include <QStringList>
#include <QNetworkAccessManager>
#include <QWebPage>

class soundUrlExtractor : public QThread
{
    Q_OBJECT

    QWebPage page;

    bool active;
    QString request;
    void next();

public:
    QStringList words;
    explicit soundUrlExtractor(QString req);

public slots:
    void pageLoaded (bool ok);
    void add (QString);

signals:
    void downloadUrl(QString, QUrl);
};


#endif // soundDownloader_H

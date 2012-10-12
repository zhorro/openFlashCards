#ifndef PICTURESDOWNLOADER_H
#define PICTURESDOWNLOADER_H

#include <QObject>
#include <QThread>
#include <QStringList>
#include <QNetworkAccessManager>

extern QNetworkAccessManager *manager;

class picturesDownloader : public QThread
{
    Q_OBJECT

    QNetworkAccessManager * manager;
    bool active;
    void next();
    QString request;
public:
    QStringList words;
    explicit picturesDownloader(QString lang);

public slots:
    void replyFinished (QNetworkReply*);
    void add (QString);

signals:
    void cleanWord(QString str, QByteArray translation = QByteArray ());
};


#endif // PICTURESDOWNLOADER_H
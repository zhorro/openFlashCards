#include <QDebug>
#include <QDir>
#include <QFile>
#include <QImage>
#include <QPainter>
#include <QPicture>

#include <QWebFrame>
#include <QWebElement>
#include <QWebElementCollection>

#include "picturesdownloader.h"

QSize picSizes (640, 480);

picturesDownloader::picturesDownloader()
{
	page.setViewportSize(picSizes);
    connect(page.mainFrame(), SIGNAL(loadFinished (bool)), this, SLOT(pageLoaded(bool)));
    active = false;
}

void picturesDownloader::next()
{
    if (!words.count() || active)
        return;

    active = true;
    page.mainFrame()->load(QUrl(QString("http://%1.jpg.to").arg(words[0])));
}

void picturesDownloader::pageLoaded( bool ok )
{
    active = false;
	if (!ok)
		next();

	QWebElement imgs = page.mainFrame()->findFirstElement("img");
	QImage   img (imgs.geometry().size(), QImage::Format_ARGB32);
	// QImage   img (page.mainFrame()->contentsSize(), QImage::Format_ARGB32);
	QPainter painter;
	painter.begin(&img);
	page.mainFrame()->render(&painter);

	painter.end();
	QDir::current().mkdir("images");
	img.save(QString("images/%1.jpeg").arg(words[0]), "JPEG");

	words.removeFirst();
    next();
	
}

void picturesDownloader::add(QString newWord)
{
    if (words.contains(newWord, Qt::CaseInsensitive))
        return;

    words.append(newWord);
    next();
}


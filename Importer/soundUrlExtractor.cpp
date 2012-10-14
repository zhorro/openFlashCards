#include <QDebug>
#include <QDir>
#include <QFile>
#include <QImage>
#include <QPainter>
#include <QPicture>

#include <QWebFrame>
#include <QWebElement>
#include <QWebElementCollection>

#include "soundUrlExtractor.h"

soundUrlExtractor::soundUrlExtractor(QString req) : request(req), active(false)
{
    connect(page.mainFrame(), SIGNAL(loadFinished (bool)), this, SLOT(pageLoaded(bool)));
}

void soundUrlExtractor::next()
{
    if (!words.count() || active)
        return;

    active = true;
    page.mainFrame()->load(QUrl(QString("http://lingvopro.abbyyonline.com/ru/Translate/%2/%1").arg(words[0]).arg(request)));
}

void soundUrlExtractor::pageLoaded( bool ok )
{
    active = false;
	if (!ok)
		next();

	QDir::current().mkdir("./lingvo_replays");
	QFile rep (QString("./lingvo_replays/%1.html").arg(words[0]));
	rep.open(QIODevice::WriteOnly);
	QTextStream st (&rep);
	st << page.mainFrame()->toHtml();

	QWebElement snd = page.mainFrame()->findFirstElement(".soundJS");
	QString link = snd.attribute("data-flash-url");
	QString castratedLink = link.mid(26);
	if (!castratedLink.isEmpty())
	{
		castratedLink.replace("%26", "&");
		QUrl url (QString("http://lingvopro.abbyyonline.com%1").arg(castratedLink));
		qDebug() << url.toString();
		emit downloadUrl(words[0], url);
	}
	else
		qDebug () << link << " : " << castratedLink;

	words.removeFirst();
    next();
	
}

void soundUrlExtractor::add(QString newWord)
{
    if (words.contains(newWord, Qt::CaseInsensitive))
        return;

    words.append(newWord);
    next();
}


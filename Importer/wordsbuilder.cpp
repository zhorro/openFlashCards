#include <QTextStream>
#include <QDebug>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QFile>

#include "wordsbuilder.h"

wordsBuilder::wordsBuilder(QString lang) :
	request(lang)	
{
	manager = new QNetworkAccessManager(this);
	connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyFinished(QNetworkReply*)));
	active = false;
	words.clear();
}

void wordsBuilder::next()
{
	if (!words.count() || active)
		return;

	active = true;
	QNetworkRequest request (QUrl("http://m.slovari.yandex.ru/translate.xml?text="+words[0]+"&lang="+request));
	manager->get(request);
}

void wordsBuilder::replyFinished (QNetworkReply * reply)
{
	active = false;
	QByteArray R = reply->readAll();
	QString answer = QString::fromUtf8(R, R.size());

	const QString startString = "<h1 class=\"b-title\">";
	const QString endString   = "<";

	QString trueWord = answer.mid(answer.indexOf(startString)+startString.length());
	trueWord.truncate(trueWord.indexOf(endString));

	words.removeFirst();

	emit cleanWord(trueWord, R);

	next();
}

void wordsBuilder::add(QString newWord)
{	
	if (words.contains(newWord, Qt::CaseInsensitive))
		return;

	words.append(newWord);
	next();
}


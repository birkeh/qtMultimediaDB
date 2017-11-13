#include "common.h"

#include "cfanartimage.h"

#include <QDir>
#include <QFile>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QEventLoop>
#include <QUrl>


cFanartImage::cFanartImage()
{
}

QPixmap cFanartImage::getImage(const QString& szFileName)
{
	QPixmap	pixmap;

	QString	szPath	= rootPath() + QDir::separator() + szFileName.mid(25);
	szPath.replace("/", QDir::separator());

	if(szFileName.isEmpty())
		pixmap.load(rootPath() + QDir::separator() + QDir::separator() + "empty.jpg");
	else
		pixmap.load(szPath);

	if(!pixmap.width())
		return(downloadFile(szFileName));

	return(pixmap);
}

QPixmap cFanartImage::downloadFile(const QString& szFileName)
{
	QPixmap					pixmap;

	QString	szPath	= rootPath() + QDir::separator() + szFileName.mid(25);
	szPath.replace("/", QDir::separator());
	QString	szURL	= szFileName;

	QNetworkAccessManager	networkManager;
	QUrl					url(szURL);
	QNetworkRequest			request(url);
	request.setHeader(QNetworkRequest::ContentTypeHeader, "application/xml");

	QNetworkReply*			reply   = networkManager.get(request);
	QEventLoop				loop;

	QObject::connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
	loop.exec();

	QByteArray				szData  = reply->readAll();
	delete reply;

	pixmap.loadFromData(szData);

	QDir		dir(szPath);
	QFileInfo	fileInfo(szPath);
	dir.mkpath(dir.filePath(fileInfo.absolutePath()));
	pixmap.save(szPath);

	return(pixmap);
}

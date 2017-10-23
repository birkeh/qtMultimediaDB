#include "common.h"

#include "cimage.h"

#include <QDir>
#include <QFile>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QEventLoop>
#include <QUrl>


cImage::cImage()
{
}

QPixmap cImage::getImage(const QString& szFileName)
{
	QPixmap	pixmap;

	QString	szPath	= rootPath() + QDir::separator() + szFileName;

	if(szFileName.isEmpty())
		pixmap.load(rootPath() + QDir::separator() + QDir::separator() + "empty.jpg");
	else
		pixmap.load(szPath);

	if(!pixmap.width())
		return(downloadFile(szFileName));

	return(pixmap);
}

QPixmap cImage::downloadFile(const QString& szFileName)
{
	QPixmap					pixmap;

	QString	szPath	= rootPath() + QDir::separator() + szFileName;
//	QString	szURL	= "http://thetvdb.com/banners/" + szFileName;
	QString	szURL	= "https://www.thetvdb.com/banners/" + szFileName;

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

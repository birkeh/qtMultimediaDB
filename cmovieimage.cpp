#include "common.h"

#include "cmovieimage.h"

#include <QDir>
#include <QFile>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QEventLoop>
#include <QUrl>


cMovieImage::cMovieImage()
{
}

QPixmap cMovieImage::getImage(const QString& szFileName)
{
	QPixmap	pixmap;

	QString	szPath	= rootPath() + QDir::separator() + "t" + QDir::separator() + "p" + QDir::separator() + "w300" + QDir::separator() + szFileName.right(szFileName.length()-1);

	if(szFileName.isEmpty())
		pixmap.load(rootPath() + QDir::separator() + QDir::separator() + "empty.jpg");
	else
		pixmap.load(szPath);

	if(!pixmap.width())
		return(downloadFile(szFileName));

	return(pixmap);
}

QPixmap cMovieImage::downloadFile(const QString& szFileName)
{
	QPixmap					pixmap;

	QString	szPath	= rootPath() + QDir::separator() + "t" + QDir::separator() + "p" + QDir::separator() + "w300" + QDir::separator() + szFileName.right(szFileName.length()-1);
	QString	szURL	= "http://image.tmdb.org/t/p/w300" + szFileName;

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

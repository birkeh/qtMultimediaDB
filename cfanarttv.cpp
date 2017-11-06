#include "cfanarttv.h"


#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QEventLoop>
#include <QByteArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>


cFanartTV::cFanartTV() :
	m_szAPIKey("5c31661038de56f110b5f2fc4d49a7d1")
{
}

void cFanartTV::processArray(const QJsonArray& array, cFanartList& fanartList, cFanart::Type type)
{
	cFanart*		lpFanart;

	for(int x = 0;x < array.count();x++)
	{
		QJsonObject	obj	= array.at(x).toObject();
		lpFanart	= fanartList.add(type);

		switch(type)
		{
		case cFanart::TypeHDTVLogo:
		case cFanart::TypeClearLogo:
		case cFanart::TypeTVPoster:
		case cFanart::TypeClearArt:
		case cFanart::TypeHDClearArt:
		case cFanart::TypeTVThumb:
		case cFanart::TypeCharacterArt:
		case cFanart::TypeTVBanner:
			lpFanart->setID(obj["id"].toString().toInt());
			lpFanart->setLanguage(obj["lang"].toString());
			lpFanart->setLikes(obj["likes"].toString().toInt());
			lpFanart->setURL(obj["url"].toString());
			break;
		case cFanart::TypeShowBackground:
		case cFanart::TypeSeasonPoster:
		case cFanart::TypeSeasonBanner:
		case cFanart::TypeSeasonThumb:
			lpFanart->setID(obj["id"].toString().toInt());
			lpFanart->setLanguage(obj["lang"].toString());
			lpFanart->setLikes(obj["likes"].toString().toInt());
			lpFanart->setURL(obj["url"].toString());
			if(!obj["season"].toString().compare("all"))
				lpFanart->setSeason(-1);
			else
				lpFanart->setSeason(obj["season"].toString().toInt());
			break;
		case cFanart::TypeHDMovieLogo:
		case cFanart::TypeMovieLogo:
		case cFanart::TypeMoviePoster:
		case cFanart::TypeHDMovieClearArt:
		case cFanart::TypeMovieArt:
		case cFanart::TypeMovieBackground:
		case cFanart::TypeMovieBanner:
		case cFanart::TypeMovieThumb:
			lpFanart->setID(obj["id"].toString().toInt());
			lpFanart->setLanguage(obj["lang"].toString());
			lpFanart->setLikes(obj["likes"].toString().toInt());
			lpFanart->setURL(obj["url"].toString());
			break;
		case cFanart::TypeMovieDisc:
			lpFanart->setID(obj["id"].toString().toInt());
			lpFanart->setLanguage(obj["lang"].toString());
			lpFanart->setLikes(obj["likes"].toString().toInt());
			lpFanart->setURL(obj["url"].toString());
			lpFanart->setDisc(obj["disc"].toString());
			lpFanart->setDiscType(obj["disc_type"].toString());
			break;
		default:
			break;
		}
	}
}

cFanartList cFanartTV::loadFanartSerie(const qint32 &iID)
{
	cFanartList				fanartList;
	QNetworkAccessManager	networkManager;
	QNetworkRequest			request(QUrl(QString("http://webservice.fanart.tv/v3/tv/%1?api_key=%2").arg(iID).arg(m_szAPIKey)));

	request.setRawHeader("Content-Type", "application/json");

	QNetworkReply*			reply   = networkManager.get(request);
	QEventLoop				loop;

	QObject::connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
	loop.exec();

	if (reply->error() == QNetworkReply::NoError)
	{
		QString			strReply		= (QString)reply->readAll();
		QJsonDocument	jsonResponse	= QJsonDocument::fromJson(strReply.toUtf8());
		QJsonObject		jsonObj			= jsonResponse.object();

		delete reply;

		processArray(jsonObj["hdtvlogo"].toArray(), fanartList, cFanart::TypeHDTVLogo);
		processArray(jsonObj["clearlogo"].toArray(), fanartList, cFanart::TypeClearLogo);
		processArray(jsonObj["tvposter"].toArray(), fanartList, cFanart::TypeTVPoster);
		processArray(jsonObj["clearart"].toArray(), fanartList, cFanart::TypeClearArt);
		processArray(jsonObj["hdclearart"].toArray(), fanartList, cFanart::TypeHDClearArt);
		processArray(jsonObj["showbackground"].toArray(), fanartList, cFanart::TypeShowBackground);
		processArray(jsonObj["seasonposter"].toArray(), fanartList, cFanart::TypeSeasonPoster);
		processArray(jsonObj["tvthumb"].toArray(), fanartList, cFanart::TypeTVThumb);
		processArray(jsonObj["seasonbanner"].toArray(), fanartList, cFanart::TypeSeasonBanner);
		processArray(jsonObj["characterart"].toArray(), fanartList, cFanart::TypeCharacterArt);
		processArray(jsonObj["seasonthumb"].toArray(), fanartList, cFanart::TypeSeasonThumb);
		processArray(jsonObj["tvbanner"].toArray(), fanartList, cFanart::TypeTVBanner);
	}
	else
	{
		qDebug() << reply->errorString();
		delete reply;
	}
	return(fanartList);
}

cFanartList cFanartTV::loadFanartMovie(const QString &szIMDBID)
{
	cFanartList				fanartList;
	QNetworkAccessManager	networkManager;
	QNetworkRequest			request(QUrl(QString("http://webservice.fanart.tv/v3/movies/%1?api_key=%2").arg(szIMDBID).arg(m_szAPIKey)));

	request.setRawHeader("Content-Type", "application/json");

	QNetworkReply*			reply   = networkManager.get(request);
	QEventLoop				loop;

	QObject::connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
	loop.exec();

	if (reply->error() == QNetworkReply::NoError)
	{
		QString			strReply		= (QString)reply->readAll();
		QJsonDocument	jsonResponse	= QJsonDocument::fromJson(strReply.toUtf8());
		QJsonObject		jsonObj			= jsonResponse.object();

		delete reply;

		processArray(jsonObj["hdmovielogo"].toArray(), fanartList, cFanart::TypeHDMovieLogo);
		processArray(jsonObj["movielogo"].toArray(), fanartList, cFanart::TypeMovieLogo);
		processArray(jsonObj["movieposter"].toArray(), fanartList, cFanart::TypeMoviePoster);
		processArray(jsonObj["hdmovieclearart"].toArray(), fanartList, cFanart::TypeHDMovieClearArt);
		processArray(jsonObj["movieart"].toArray(), fanartList, cFanart::TypeMovieArt);
		processArray(jsonObj["moviebackground"].toArray(), fanartList, cFanart::TypeMovieBackground);
		processArray(jsonObj["moviebanner"].toArray(), fanartList, cFanart::TypeMovieBanner);
		processArray(jsonObj["moviethumb"].toArray(), fanartList, cFanart::TypeMovieThumb);
	}
	else
	{
		qDebug() << reply->errorString();
		delete reply;
	}
	return(fanartList);
}

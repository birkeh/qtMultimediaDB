#include "ctheaudiodbv1.h"


#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QEventLoop>
#include <QByteArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

#include <QApplication>


cTheAudioDBV1::cTheAudioDBV1()
{
	m_szToken	= "1";
}

cTheAudioDBV1::~cTheAudioDBV1()
{
}

QList<cArtist*> cTheAudioDBV1::searchArtist(const QString& szArtist)
{
	QList<cArtist*>			artistList;
	QNetworkAccessManager	networkManager;
//	QString					szRequest	= QString("theaudiodb.com/api/v1/json/%1/search.php?s=%2").arg(m_szToken).arg(szArtist);

	QNetworkRequest			request(QUrl(QString("https://www.theaudiodb.com/api/v1/json/%1/search.php?s=%2").arg(m_szToken).arg(szArtist)));

	QNetworkReply*			reply   = networkManager.get(request);
	QEventLoop				loop;

	QObject::connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
	loop.exec();

	if (reply->error() == QNetworkReply::NoError)
	{
		QString			strReply		= (QString)reply->readAll();
		QJsonDocument	jsonResponse	= QJsonDocument::fromJson(strReply.toUtf8());
		QJsonObject		jsonObj			= jsonResponse.object();
		QJsonArray		jsonArray		= jsonObj["artists"].toArray();

		for(int z = 0;z < jsonArray.count();z++)
		{
			QJsonObject	artist			= jsonArray[z].toObject();
			cArtist*	lpArtist		= new cArtist;

			lpArtist->setArtistID(artist["idArtist"].toInt());
			lpArtist->setArtist(artist["strArtist"].toString());
			lpArtist->setArtistStripped(artist["strArtistStripped"].toString());
			lpArtist->setArtistAlernate(artist["strArtistAlternate"].toString());
			lpArtist->setLabel(artist["strLabel"].toString());
			lpArtist->setLabelID(artist["idLabel"].toInt());
			lpArtist->setFormedYear(artist["intFormedYear"].toInt());
			lpArtist->setBornYear(artist["intBornYear"].toInt());
			lpArtist->setDiedYear(artist["intDiedYear"].toInt());
			lpArtist->setDisbanded(artist["strDisbanded"].toString());
			lpArtist->setStyle(artist["strStyle"].toString());
			lpArtist->setGenre(artist["strGenre"].toString());
			lpArtist->setMood(artist["strMood"].toString());
			lpArtist->setWebsite(artist["strWebsite"].toString());
			lpArtist->setFacebook(artist["strFacebook"].toString());
			lpArtist->setTwitter(artist["strTwitter"].toString());
			lpArtist->setBiography(artist["strBiographyDE"].toString());
			if(lpArtist->biography().isEmpty())
				lpArtist->setBiography(artist["strBiographyEN"].toString());
			lpArtist->setGender(artist["strGender"].toString());
			lpArtist->setMembers(artist["intMembers"].toInt());
			lpArtist->setCountry(artist["strCountry"].toString());
			lpArtist->setCountryCode(artist["strCountryCode"].toString());
			lpArtist->setArtistThumb(artist["strArtistThumb"].toString());
			lpArtist->setArtistLogo(artist["strArtistLogo"].toString());
			lpArtist->setArtistClearart(artist["strArtistClearart"].toString());
			lpArtist->setArtistWideThumb(artist["strArtistWideThumb"].toString());
			lpArtist->setArtistFanart(artist["strArtistFanart"].toString());
			lpArtist->setArtistFanart2(artist["strArtistFanart2"].toString());
			lpArtist->setArtistFanart3(artist["strArtistFanart3"].toString());
			lpArtist->setArtistBanner(artist["strArtistBanner"].toString());
			lpArtist->setMusicBrainzID(artist["strMusicBrainzID"].toString());
			lpArtist->setLastFMChart(artist["strLastFMChart"].toString());

			artistList.append(lpArtist);
		}
		delete reply;
	}
	else
	{
		qDebug() << reply->errorString();
		delete reply;
	}

	return(artistList);
}

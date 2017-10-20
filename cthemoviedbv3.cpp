#include "cthemoviedbv3.h"


#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QEventLoop>
#include <QByteArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

using std::pair;


cTheMovieDBV3::cTheMovieDBV3()
{
	m_szToken	= "a33271b9e54cdcb9a80680eaf5522f1b";
}

QList<cMovie*> cTheMovieDBV3::search(const QString& szMovie, const qint16& year, const QString& szLanguage)
{
	QList<cMovie*>			movieList;
	QNetworkAccessManager	networkManager;
	QString					szRequest	= QString("https://api.themoviedb.org/3/search/movie?api_key=%1").arg(m_szToken);
	qint16					page		= 1;

	if(!szLanguage.contains("all"))
		szRequest.append(QString("&language=%1").arg(szLanguage));

	szRequest.append(QString("&query=%1").arg(szMovie));

	if(year != -1)
		szRequest.append(QString("&year=%1").arg(year));

	szRequest.append("&include_adult=false");

	for(;;)
	{
		QNetworkRequest			request(QUrl(QString("%1&page=%2").arg(szRequest).arg(page)));

		QNetworkReply*			reply   = networkManager.get(request);
		QEventLoop				loop;

		QObject::connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
		loop.exec();

		if (reply->error() == QNetworkReply::NoError)
		{
			QString			strReply		= (QString)reply->readAll();
			QJsonDocument	jsonResponse	= QJsonDocument::fromJson(strReply.toUtf8());
			QJsonObject		jsonObj			= jsonResponse.object();
			QJsonArray		jsonArray		= jsonObj["results"].toArray();

			for(int z = 0;z < jsonArray.count();z++)
			{
				QJsonObject	movie			= jsonArray[z].toObject();
				cMovie*		lpMovie			= new cMovie;
				lpMovie->setMovieTitle(movie["title"].toString());
				lpMovie->setMovieID(movie["id"].toInt());
				lpMovie->setOriginalTitle(movie["original_title"].toString());
				lpMovie->setReleaseDate(movie["release_date"].toString());
				movieList.append(lpMovie);
			}
			if(jsonObj["total_pages"].toInt() == page)
				break;

			page++;
			if(page > 20)
				break;

			delete reply;
		}
		else
		{
			qDebug() << reply->errorString();
			delete reply;
		}
	}
	return(movieList);
}

cMovie* cTheMovieDBV3::load(const qint32 &iID, const QString &szLanguage)
{
	cMovie*					lpMovie	= 0;
	QNetworkAccessManager	networkManager;
	QNetworkRequest			request(QUrl(QString("https://api.themoviedb.org/3/movie/%1?api_key=%2&language=%3").arg(iID).arg(m_szToken).arg(szLanguage)));

	request.setRawHeader("Content-Type", "application/json");
	request.setRawHeader("Authorization", QString("Bearer %1").arg(m_szToken).toUtf8());
	if(!szLanguage.contains("all"))
		request.setRawHeader("Accept-Language", szLanguage.toUtf8());
	else
		request.setRawHeader("Accept-Language", "en");

	QNetworkReply*			reply   = networkManager.get(request);
	QEventLoop				loop;

	QObject::connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
	loop.exec();

	if (reply->error() == QNetworkReply::NoError)
	{
		QString			strReply		= (QString)reply->readAll();
		QJsonDocument	jsonResponse	= QJsonDocument::fromJson(strReply.toUtf8());
		QJsonObject		jsonObj			= jsonResponse.object();

		QJsonArray		genreArray		= jsonObj["genres"].toArray();
		QStringList		genreList;

		QJsonArray		productionCompaniesArray	= jsonObj["production_companies"].toArray();
		QStringList		productionCompaniesList;

		QJsonArray		productionCountriesArray	= jsonObj["production_countries"].toArray();
		QStringList		productionCountriesList;

		QJsonArray		spokenLanguagesArray		= jsonObj["spoken_languages"].toArray();
		QStringList		spokenLanguagesList;

		QJsonObject		tmpObj;

		delete reply;

		lpMovie	= new cMovie;

		lpMovie->setMovieTitle(jsonObj["title"].toString());
		lpMovie->setMovieID(jsonObj["id"].toInt());
		lpMovie->setOriginalTitle(jsonObj["original_title"].toString());
		lpMovie->setReleaseDate(jsonObj["release_date"].toString());
		lpMovie->setAdult(jsonObj["adult"].toBool());
		lpMovie->setBackdropPath(jsonObj["backdrop_path"].toString());
		tmpObj	= jsonObj["belongs_to_collection"].toObject();
		lpMovie->setBelongsToCollection(tmpObj["name"].toString());
		lpMovie->setBudget(jsonObj["budget"].toDouble());
		for(int z = 0;z < genreArray.count();z++)
		{
			tmpObj	= genreArray[z].toObject();
			genreList.append(tmpObj["name"].toString());
		}
		lpMovie->setGenres(genreList);
		lpMovie->setHomepage(jsonObj["homepage"].toString());
		lpMovie->setIMDBID(jsonObj["imdb_id"].toString());
		lpMovie->setOriginalLanguage(jsonObj["original_language"].toString());
		lpMovie->setOverview(jsonObj["overview"].toString());
		lpMovie->setPopularity(jsonObj["popularity"].toDouble());
		lpMovie->setPosterPath(jsonObj["poster_path"].toString());
		for(int z = 0;z < productionCompaniesArray.count();z++)
		{
			tmpObj	= productionCompaniesArray[z].toObject();
			productionCompaniesList.append(tmpObj["name"].toString());
		}
		lpMovie->setProductionCompanies(productionCompaniesList);
		for(int z = 0;z < productionCountriesArray.count();z++)
		{
			tmpObj	= productionCountriesArray[z].toObject();
			productionCountriesList.append(tmpObj["name"].toString());
		}
		lpMovie->setProductionCountries(productionCountriesList);
		lpMovie->setRevenue(jsonObj["revenue"].toDouble());
		lpMovie->setRuntime(jsonObj["runtime"].toInt());
		for(int z = 0;z < spokenLanguagesArray.count();z++)
		{
			tmpObj	= spokenLanguagesArray[z].toObject();
			spokenLanguagesList.append(tmpObj["name"].toString());
		}
		lpMovie->setSpokenLanguages(spokenLanguagesList);
		lpMovie->setStatus(jsonObj["status"].toString());
		lpMovie->setTagline(jsonObj["tagline"].toString());
		lpMovie->setVideo(jsonObj["video"].toBool());
		lpMovie->setVoteAverage(jsonObj["vote_average"].toDouble());
		lpMovie->setVoteCount(jsonObj["vote_count"].toInt());
		lpMovie->setState(cMovie::StateInit);

		request.setUrl(QUrl(QString("https://api.themoviedb.org/3/movie/%1/credits?api_key=%2").arg(iID).arg(m_szToken)));

		request.setRawHeader("Content-Type", "application/json");
		if(!szLanguage.contains("all"))
			request.setRawHeader("Accept-Language", szLanguage.toUtf8());
		else
			request.setRawHeader("Accept-Language", "en");

		reply   = networkManager.get(request);

		QObject::connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
		loop.exec();

		if (reply->error() == QNetworkReply::NoError)
		{
			strReply		= (QString)reply->readAll();
			jsonResponse	= QJsonDocument::fromJson(strReply.toUtf8());
			QJsonObject		jsonCast		= jsonResponse.object();
			QJsonArray		jsonArrayCast	= jsonCast["cast"].toArray();
			QJsonArray		jsonArrayCrew	= jsonCast["crew"].toArray();

			QStringList		szCast;
			QStringList		szCrew;

			delete reply;

			for(int x = 0;x < jsonArrayCast.count();x++)
			{
				tmpObj	= jsonArrayCast.at(x).toObject();
				szCast.append(QString("%1,%2").arg(tmpObj["name"].toString()).arg(tmpObj["character"].toString()));
			}
			if(szCast.count())
				lpMovie->setCast(szCast);

			for(int x = 0;x < jsonArrayCrew.count();x++)
			{
				tmpObj	= jsonArrayCrew.at(x).toObject();
				szCrew.append(QString("%1,%2").arg(tmpObj["name"].toString()).arg(tmpObj["job"].toString()));
			}
			if(szCrew.count())
				lpMovie->setCrew(szCrew);
		}
	}
	else
	{
		qDebug() << reply->errorString();
		delete reply;
	}
	return(lpMovie);
}

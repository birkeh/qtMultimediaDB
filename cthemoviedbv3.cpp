#include "cthemoviedbv3.h"


#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QEventLoop>
#include <QByteArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

//using std::pair;


cTheMovieDBV3::cTheMovieDBV3()
{
	m_szToken	= "a33271b9e54cdcb9a80680eaf5522f1b";
}

QList<cMovie*> cTheMovieDBV3::searchMovie(const QString& szMovie, const qint16& year, const QString& szLanguage)
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

QList<cSerie*> cTheMovieDBV3::searchSerie(const QString& szSerie, const qint16& year, const QString& szLanguage)
{
	QList<cSerie*>			serieList;
	QNetworkAccessManager	networkManager;
	QString					szRequest	= QString("https://api.themoviedb.org/3/search/tv?api_key=%1").arg(m_szToken);
	qint16					page		= 1;

	if(!szLanguage.contains("all"))
		szRequest.append(QString("&language=%1").arg(szLanguage));

	szRequest.append(QString("&query=%1").arg(szSerie));

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
				QJsonObject	serie			= jsonArray[z].toObject();
				cSerie*		lpSerie			= new cSerie;
				lpSerie->setSeriesName(serie["name"].toString());
				lpSerie->setSeriesID(serie["id"].toInt());
				lpSerie->setOriginalName(serie["original_name"].toString());
				lpSerie->setFirstAired(serie["first_air_date"].toString());
				serieList.append(lpSerie);
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
	return(serieList);
}

cMovie* cTheMovieDBV3::loadMovie(const qint32 &iID, const QString &szLanguage)
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

cSerie* cTheMovieDBV3::loadSerie(const QString& szIMDBID)
{
	qint32					iID;
	QNetworkAccessManager	networkManager;
	QNetworkRequest			request(QUrl(QString("https://api.themoviedb.org/3/find/%1?api_key=%2&external_source=imdb_id").arg(szIMDBID).arg(m_szToken)));

	request.setRawHeader("Content-Type", "application/json");
	request.setRawHeader("Authorization", QString("Bearer %1").arg(m_szToken).toUtf8());

	QNetworkReply*			reply   = networkManager.get(request);
	QEventLoop				loop;

	QObject::connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
	loop.exec();

	if (reply->error() == QNetworkReply::NoError)
	{
		QString			strReply		= (QString)reply->readAll();
		QJsonDocument	jsonResponse	= QJsonDocument::fromJson(strReply.toUtf8());
		QJsonObject		jsonObj			= jsonResponse.object();

		QJsonArray		tmpArray;
		QJsonObject		tmpObj;

		delete reply;

		tmpArray	= jsonObj["tv_results"].toArray();
		tmpObj		= tmpArray.at(0).toObject();
		iID			= tmpObj["id"].toInt();

		return(loadSerie(iID, "de-DE"));
	}
	else
		qDebug() << reply->errorString();
	return(0);
}

cSerie* cTheMovieDBV3::loadSerie(const qint32 &iID, const QString& szLanguage)
{
	cSerie*					lpSerie	= 0;
	QNetworkAccessManager	networkManager;
	QNetworkRequest			request(QUrl(QString("https://api.themoviedb.org/3/tv/%1?api_key=%2&language=%3&append_to_response=credits,external_ids").arg(iID).arg(m_szToken).arg(szLanguage)));

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

		QJsonArray		tmpArray;
		QStringList		tmpList;

		QJsonObject		tmpObj;

		delete reply;

		lpSerie	= new cSerie;

		lpSerie->setSeriesID(iID);
		lpSerie->setBackdropPath(jsonObj["backdrop_path"].toString());
		tmpArray	= jsonObj["created_by"].toArray();
		for(int x = 0;x < tmpArray.count();x++)
			tmpList.append(tmpArray.at(x).toObject()["name"].toString());
		lpSerie->setCreatedBy(tmpList);
		tmpList.clear();
		lpSerie->setFirstAired(jsonObj["first_air_date"].toString());
		tmpArray	= jsonObj["genres"].toArray();
		for(int x = 0;x < tmpArray.count();x++)
			tmpList.append(tmpArray.at(x).toObject()["name"].toString());
		lpSerie->setGenre(tmpList);
		tmpList.clear();
		lpSerie->setHomepage(jsonObj["homepage"].toString());
		lpSerie->setLastAired(jsonObj["last_air_date"].toString());
		tmpArray	= jsonObj["languages"].toArray();
		for(int x = 0;x < tmpArray.count();x++)
			tmpList.append(tmpArray.at(x).toString());
		lpSerie->setLanguages(tmpList);
		tmpList.clear();
		lpSerie->setSeriesName(jsonObj["name"].toString());
		tmpArray	= jsonObj["networks"].toArray();
		for(int x = 0;x < tmpArray.count();x++)
			tmpList.append(tmpArray.at(x).toObject()["name"].toString());
		lpSerie->setNetworks(tmpList);
		tmpList.clear();
		lpSerie->setEpisodes(jsonObj["number_of_episodes"].toInt());
		lpSerie->setSeasons(jsonObj["number_of_seasons"].toInt());
		tmpArray	= jsonObj["origin_country"].toArray();
		for(int x = 0;x < tmpArray.count();x++)
			tmpList.append(tmpArray.at(x).toString());
		lpSerie->setOriginCountries(tmpList);
		tmpList.clear();
		lpSerie->setOriginalLanguage(jsonObj["original_language"].toString());
		lpSerie->setOriginalName(jsonObj["original_name"].toString());
		lpSerie->setOverview(jsonObj["overview"].toString());
		lpSerie->setPopularity(jsonObj["popularity"].toDouble());
		lpSerie->setPosterPath(jsonObj["poster_path"].toString());
		tmpArray	= jsonObj["production_companies"].toArray();
		for(int x = 0;x < tmpArray.count();x++)
			tmpList.append(tmpArray.at(x).toObject()["name"].toString());
		lpSerie->setProductionCompanies(tmpList);
		tmpList.clear();
		lpSerie->setStatus(jsonObj["status"].toString());
		lpSerie->setType(jsonObj["type"].toString());
		lpSerie->setVoteAverage(jsonObj["vote_average"].toDouble());
		lpSerie->setVoteCount(jsonObj["vote_count"].toInt());

		QJsonObject	idsObj			= jsonObj["external_ids"].toObject();
		if(!idsObj.isEmpty())
		{
			lpSerie->setIMDBID(idsObj["imdb_id"].toString());
			lpSerie->setFreebaseMID(idsObj["freebase_mid"].toString());
			lpSerie->setFreebaseID(idsObj["freebase_id"].toString());
			lpSerie->setTVDBID(idsObj["tvdb_id"].toInt());
			lpSerie->setTVRageID(idsObj["tvrage_id"].toInt());
		}

		QJsonObject	creditsObj		= jsonObj["credits"].toObject();
		if(!creditsObj.isEmpty())
		{
			QJsonArray		jsonArrayCast	= creditsObj["cast"].toArray();
			QJsonArray		jsonArrayCrew	= creditsObj["crew"].toArray();

			QStringList		szCast;
			QStringList		szCrew;

			for(int x = 0;x < jsonArrayCast.count();x++)
			{
				tmpObj	= jsonArrayCast.at(x).toObject();
				szCast.append(QString("%1,%2").arg(tmpObj["name"].toString()).arg(tmpObj["character"].toString()));
			}
			if(szCast.count())
				lpSerie->setCast(szCast);

			for(int x = 0;x < jsonArrayCrew.count();x++)
			{
				tmpObj	= jsonArrayCrew.at(x).toObject();
				szCrew.append(QString("%1,%2").arg(tmpObj["name"].toString()).arg(tmpObj["job"].toString()));
			}
			if(szCrew.count())
				lpSerie->setCrew(szCrew);
		}

		tmpArray	= jsonObj["seasons"].toArray();

		for(int x = 0; x < tmpArray.count();x++)
		{
			QJsonObject	seasonObj		= tmpArray.at(x).toObject();
			qint16		seasonNumber	= seasonObj["season_number"].toInt();
			cSeason*	lpSeason		= lpSerie->addSeason(seasonNumber);

			request.setUrl(QUrl(QString("https://api.themoviedb.org/3/tv/%1/season/%2?api_key=%3&language=%4").arg(iID).arg(seasonNumber).arg(m_szToken).arg(szLanguage)));

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
				QJsonObject		jsonEpisodes		= jsonResponse.object();
				QJsonArray		jsonArrayEpisodes	= jsonEpisodes["episodes"].toArray();

				delete reply;

				lpSeason->set_ID(jsonEpisodes["_id"].toInt());
				lpSeason->setAirDate(jsonEpisodes["air_date"].toString());
				lpSeason->setName(jsonEpisodes["name"].toString());
				lpSeason->setOverview(jsonEpisodes["overview"].toString());
				lpSeason->setID(jsonEpisodes["id"].toInt());
				lpSeason->setPosterPath(jsonEpisodes["poster_path"].toString());

				for(int x = 0;x < jsonArrayEpisodes.count();x++)
				{
					tmpObj	= jsonArrayEpisodes.at(x).toObject();

					cEpisode*	lpEpisode	= lpSeason->addEpisode(tmpObj["episode_number"].toInt());
					lpEpisode->setAirDate(tmpObj["air_date"].toString());
					lpEpisode->setName(tmpObj["name"].toString());
					lpEpisode->setOverview(tmpObj["overview"].toString());
					lpEpisode->setID(tmpObj["id"].toInt());
					lpEpisode->setProductionCode(tmpObj["production_code"].toString());
					lpEpisode->setSeasonNumber(tmpObj["season_number"].toInt());
					lpEpisode->setStillPath(tmpObj["still_path"].toString());
					lpEpisode->setVoteAverage(tmpObj["vote_average"].toDouble());
					lpEpisode->setVoteCount(tmpObj["vote_count"].toInt());
					lpEpisode->setSeriesID(lpSerie->seriesID());

					QJsonArray	jsonArrayCrew		= tmpObj["crew"].toArray();
					QJsonArray	jsonArrayGuestStars	= tmpObj["guest_stars"].toArray();

					QStringList	szCrew;
					QStringList	szGuestStars;

					for(int x = 0;x < jsonArrayCrew.count();x++)
					{
						tmpObj	= jsonArrayCrew.at(x).toObject();
						szCrew.append(QString("%1,%2").arg(tmpObj["name"].toString()).arg(tmpObj["job"].toString()));
					}
					if(szCrew.count())
						lpEpisode->setCrew(szCrew);

					for(int x = 0;x < jsonArrayGuestStars.count();x++)
					{
						tmpObj	= jsonArrayGuestStars.at(x).toObject();
						szGuestStars.append(QString("%1,%2").arg(tmpObj["name"].toString()).arg(tmpObj["character"].toString()));
					}
					if(szGuestStars.count())
						lpEpisode->setGuestStars(szGuestStars);
				}
			}
		}
	}
	else
	{
		qDebug() << reply->errorString();
		delete reply;
	}
	return(lpSerie);
}

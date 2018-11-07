#ifndef CEPISODEDETAILS_H
#define CEPISODEDETAILS_H

#include <QWidget>
#include <QStandardItemModel>

#include "cepisode.h"


namespace Ui {
class cEpisodeDetails;
}

/*!
 \brief

 \class cEpisodeDetails cepisodedetails.h "cepisodedetails.h"
*/
class cEpisodeDetails : public QWidget
{
	Q_OBJECT

public:
	/*!
	 \brief

	 \fn cEpisodeDetails
	 \param parent
	*/
	explicit cEpisodeDetails(QWidget *parent = 0);
	/*!
	 \brief

	 \fn ~cEpisodeDetails
	*/
	~cEpisodeDetails();

	/*!
	 \brief

	 \fn setEpisode
	 \param lpEpisode
	*/
	void					setEpisode(cEpisode* lpEpisode);
	/*!
	 \brief

	 \fn loadImages
	*/
	void					loadImages();
private:
	Ui::cEpisodeDetails*	ui; /*!< TODO: describe */
	QStandardItemModel*		m_lpDetailsActorsModel;
	cEpisode*				m_lpEpisode; /*!< TODO: describe */
	bool					m_bLoaded; /*!< TODO: describe */
};

#endif // CEPISODEDETAILS_H

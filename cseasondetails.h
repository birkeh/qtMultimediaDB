#ifndef CSEASONDETAILS_H
#define CSEASONDETAILS_H


#include "cseason.h"

#include <QWidget>


namespace Ui {
class cSeasonDetails;
}

/*!
 \brief

 \class cSeasonDetails cseasondetails.h "cseasondetails.h"
*/
class cSeasonDetails : public QWidget
{
	Q_OBJECT

public:
	/*!
	 \brief

	 \fn cSeasonDetails
	 \param parent
	*/
	explicit cSeasonDetails(QWidget *parent = 0);
	/*!
	 \brief

	 \fn ~cSeasonDetails
	*/
	~cSeasonDetails();

	/*!
	 \brief

	 \fn setSeason
	 \param lpSeason
	*/
	void				setSeason(cSeason* lpSeason);

private slots:
	/*!
	 \brief

	 \fn on_m_lpDetailsEpisodeTab_tabBarClicked
	 \param index
	*/
	void				on_m_lpDetailsEpisodeTab_tabBarClicked(int index);

private:
	Ui::cSeasonDetails*	ui; /*!< TODO: describe */
};

#endif // CSEASONDETAILS_H

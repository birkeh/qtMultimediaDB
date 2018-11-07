#ifndef CEDIT_H
#define CEDIT_H


#include "cserie.h"

#include <QDialog>


namespace Ui {
class cEdit;
}

/*!
 \brief

 \class cEdit cedit.h "cedit.h"
*/
class cEdit : public QDialog
{
	Q_OBJECT

public:
	/*!
	 \brief

	 \fn cEdit
	 \param parent
	*/
	explicit cEdit(QWidget *parent = 0);
	/*!
	 \brief

	 \fn ~cEdit
	*/
	~cEdit();

	/*!
	 \brief

	 \fn setSerie
	 \param lpSerie
	*/
	void		setSerie(cSerie* lpSerie);
	/*!
	 \brief

	 \fn download
	 \return QString
	*/
	QString		download();
private slots:
	/*!
	 \brief

	 \fn lpAllInit_clicked
	*/
	void		lpAllInit_clicked();
	/*!
	 \brief

	 \fn lpAllProgress_clicked
	*/
	void		lpAllProgress_clicked();
	/*!
	 \brief

	 \fn lpAllDone_clicked
	*/
	void		lpAllDone_clicked();

	/*!
	 \brief

	 \fn allInit_clicked
	*/
	void		allInit_clicked();
	/*!
	 \brief

	 \fn allProgress_clicked
	*/
	void		allProgress_clicked();
	/*!
	 \brief

	 \fn allDone_clicked
	*/
	void		allDone_clicked();

	/*!
	 \brief

	 \fn on_m_lpTabWidget_tabBarClicked
	 \param index
	*/
	void		on_m_lpTabWidget_tabBarClicked(int index);

	/*!
	 \brief

	 \fn on_m_lpCliffhanger_clicked
	*/
	void		on_m_lpCliffhanger_clicked();

	/*!
	 \brief

	 \fn on_m_lpFirstAired_dateChanged
	 \param date
	*/
	void		on_m_lpFirstAired_dateChanged(const QDate &date);

private:
	Ui::cEdit*			ui; /*!< TODO: describe */
	bool				m_bLoaded; /*!< TODO: describe */
	QRadioButton*		m_lpButton1; /*!< TODO: describe */
	QRadioButton*		m_lpButton2; /*!< TODO: describe */
	QRadioButton*		m_lpButton3; /*!< TODO: describe */
	QPushButton*		m_lpInit; /*!< TODO: describe */
	QPushButton*		m_lpProgress; /*!< TODO: describe */
	QPushButton*		m_lpDone; /*!< TODO: describe */

	QGroupBox*			m_lpGroupBox; /*!< TODO: describe */
	QGridLayout*		m_lpGridLayout; /*!< TODO: describe */
	QGridLayout*		m_lpGrid; /*!< TODO: describe */
	QLabel*				m_lpLabel; /*!< TODO: describe */
	QLabel*				m_lpLabel1; /*!< TODO: describe */
	QSpacerItem*		m_lpSpacer; /*!< TODO: describe */
	QButtonGroup*		m_lpGroup; /*!< TODO: describe */
	QPushButton*		m_lpAllInit; /*!< TODO: describe */
	QPushButton*		m_lpAllProgress; /*!< TODO: describe */
	QPushButton*		m_lpAllDone; /*!< TODO: describe */

	QSpacerItem*		m_lpVerticalSpacer; /*!< TODO: describe */

	cSerie*				m_lpSerie; /*!< TODO: describe */
};

#endif // CEDIT_H

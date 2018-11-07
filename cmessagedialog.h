#ifndef CMESSAGEDIALOG_H
#define CMESSAGEDIALOG_H

#include <QDialog>

namespace Ui {
class cMessageDialog;
}

/*!
 \brief

 \class cMessageDialog cmessagedialog.h "cmessagedialog.h"
*/
class cMessageDialog : public QDialog
{
	Q_OBJECT

public:
	/*!
	 \brief

	 \fn cMessageDialog
	 \param parent
	*/
	explicit cMessageDialog(QWidget *parent = 0);
	/*!
	 \brief

	 \fn ~cMessageDialog
	*/
	~cMessageDialog();

	/*!
	 \brief

	 \fn setMessage
	 \param szMessage
	*/
	void			setMessage(const QString& szMessage);
	/*!
	 \brief

	 \fn addMessage
	 \param szMessage
	*/
	void			addMessage(const QString& szMessage);
	/*!
	 \brief

	 \fn setProgress
	 \param iMin
	 \param iMax
	*/
	void			setProgress(qint32 iMin, qint32 iMax);
	/*!
	 \brief

	 \fn setProgress
	 \param iValue
	*/
	void			setProgress(qint32 iValue);

	/*!
	 \brief

	 \fn cancelButton
	 \return QPushButton
	*/
	QPushButton*	cancelButton();
private:
	Ui::cMessageDialog *ui; /*!< TODO: describe */
};

#endif // CMESSAGEDIALOG_H

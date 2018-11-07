#ifndef QXTSPANSLIDER_H
/****************************************************************************
** Copyright (c) 2006 - 2011, the LibQxt project.
** See the Qxt AUTHORS file for a list of authors and copyright holders.
** All rights reserved.
**
** Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are met:
**     * Redistributions of source code must retain the above copyright
**       notice, this list of conditions and the following disclaimer.
**     * Redistributions in binary form must reproduce the above copyright
**       notice, this list of conditions and the following disclaimer in the
**       documentation and/or other materials provided with the distribution.
**     * Neither the name of the LibQxt project nor the
**       names of its contributors may be used to endorse or promote products
**       derived from this software without specific prior written permission.
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
** ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
** WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
** DISCLAIMED. IN NO EVENT SHALL <COPYRIGHT HOLDER> BE LIABLE FOR ANY
** DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
** (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
** LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
** ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
** SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
**
** <http://libqxt.org>  <foundation@libqxt.org>
*****************************************************************************/

#define QXTSPANSLIDER_H

#include <QSlider>
//#include "qxtnamespace.h"
//#include "qxtglobal.h"

class QxtSpanSliderPrivate;

/*!
 \brief

 \class QxtSpanSlider qxtspanslider.h "qxtspanslider.h"
*/
class QxtSpanSlider : public QSlider {
    Q_OBJECT

    //QXT_DECLARE_PRIVATE(QxtSpanSlider)
    Q_PROPERTY(int lowerValue READ lowerValue WRITE setLowerValue)
    Q_PROPERTY(int upperValue READ upperValue WRITE setUpperValue)
    Q_PROPERTY(int lowerPosition READ lowerPosition WRITE setLowerPosition)
    Q_PROPERTY(int upperPosition READ upperPosition WRITE setUpperPosition)
    Q_PROPERTY(HandleMovementMode handleMovementMode READ handleMovementMode WRITE setHandleMovementMode)
    Q_ENUMS(HandleMovementMode)

public:
	/*!
	 \brief

	 \fn QxtSpanSlider
	 \param parent
	*/
	explicit QxtSpanSlider(QWidget* parent = 0);
	/*!
	 \brief

	 \fn QxtSpanSlider
	 \param orientation
	 \param parent
	*/
	explicit QxtSpanSlider(Qt::Orientation orientation, QWidget* parent = 0);
	/*!
	 \brief

	 \fn ~QxtSpanSlider
	*/
	virtual ~QxtSpanSlider();

	/*!
	 \brief

	 \enum HandleMovementMode
	*/
	enum HandleMovementMode
    {
        FreeMovement,
        NoCrossing,
        NoOverlapping
    };

	/*!
	 \brief

	 \enum SpanHandle
	*/
	enum SpanHandle
    {
        NoHandle,
        LowerHandle,
        UpperHandle
    };

	/*!
	 \brief

	 \fn handleMovementMode
	 \return HandleMovementMode
	*/
	HandleMovementMode handleMovementMode() const;
	/*!
	 \brief

	 \fn setHandleMovementMode
	 \param mode
	*/
	void setHandleMovementMode(HandleMovementMode mode);

	/*!
	 \brief

	 \fn lowerValue
	 \return int
	*/
	int lowerValue() const;
	/*!
	 \brief

	 \fn upperValue
	 \return int
	*/
	int upperValue() const;

	/*!
	 \brief

	 \fn lowerPosition
	 \return int
	*/
	int lowerPosition() const;
	/*!
	 \brief

	 \fn upperPosition
	 \return int
	*/
	int upperPosition() const;

public Q_SLOTS:
	/*!
	 \brief

	 \fn setLowerValue
	 \param lower
	*/
	void setLowerValue(int lower);
	/*!
	 \brief

	 \fn setUpperValue
	 \param upper
	*/
	void setUpperValue(int upper);
	/*!
	 \brief

	 \fn setSpan
	 \param lower
	 \param upper
	*/
	void setSpan(int lower, int upper);

	/*!
	 \brief

	 \fn setLowerPosition
	 \param lower
	*/
	void setLowerPosition(int lower);
	/*!
	 \brief

	 \fn setUpperPosition
	 \param upper
	*/
	void setUpperPosition(int upper);

Q_SIGNALS:
	/*!
	 \brief

	 \fn spanChanged
	 \param lower
	 \param upper
	*/
	void spanChanged(int lower, int upper);
	/*!
	 \brief

	 \fn lowerValueChanged
	 \param lower
	*/
	void lowerValueChanged(int lower);
	/*!
	 \brief

	 \fn upperValueChanged
	 \param upper
	*/
	void upperValueChanged(int upper);

	/*!
	 \brief

	 \fn lowerPositionChanged
	 \param lower
	*/
	void lowerPositionChanged(int lower);
	/*!
	 \brief

	 \fn upperPositionChanged
	 \param upper
	*/
	void upperPositionChanged(int upper);

	/*!
	 \brief

	 \fn sliderPressed
	 \param handle
	*/
	void sliderPressed(SpanHandle handle);

protected:
	/*!
	 \brief

	 \fn keyPressEvent
	 \param event
	*/
	virtual void keyPressEvent(QKeyEvent* event);
	/*!
	 \brief

	 \fn mousePressEvent
	 \param event
	*/
	virtual void mousePressEvent(QMouseEvent* event);
	/*!
	 \brief

	 \fn mouseMoveEvent
	 \param event
	*/
	virtual void mouseMoveEvent(QMouseEvent* event);
	/*!
	 \brief

	 \fn mouseReleaseEvent
	 \param event
	*/
	virtual void mouseReleaseEvent(QMouseEvent* event);
	/*!
	 \brief

	 \fn paintEvent
	 \param event
	*/
	virtual void paintEvent(QPaintEvent* event);

private:
	QxtSpanSliderPrivate* d_ptr; /*!< TODO: describe */
    friend class QxtSpanSliderPrivate;
};

#endif // QXTSPANSLIDER_H

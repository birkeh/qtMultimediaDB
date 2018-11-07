#ifndef QXTSPANSLIDER_P_H
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

#define QXTSPANSLIDER_P_H

#include <QStyle>
#include <QObject>
#include "qxtspanslider.h"

QT_FORWARD_DECLARE_CLASS(QStylePainter)
QT_FORWARD_DECLARE_CLASS(QStyleOptionSlider)

/*!
 \brief

 \class QxtSpanSliderPrivate qxtspanslider_p.h "qxtspanslider_p.h"
*/
class QxtSpanSliderPrivate : public QObject {
    Q_OBJECT
public:
	/*!
	 \brief

	 \fn QxtSpanSliderPrivate
	*/
	QxtSpanSliderPrivate();
	/*!
	 \brief

	 \fn initStyleOption
	 \param option
	 \param handle
	*/
	void initStyleOption(QStyleOptionSlider* option, QxtSpanSlider::SpanHandle handle = QxtSpanSlider::UpperHandle) const;
	/*!
	 \brief

	 \fn pick
	 \param pt
	 \return int
	*/
	int pick(const QPoint& pt) const
    {
        return q_ptr->orientation() == Qt::Horizontal ? pt.x() : pt.y();
    }
	/*!
	 \brief

	 \fn pixelPosToRangeValue
	 \param pos
	 \return int
	*/
	int pixelPosToRangeValue(int pos) const;
	/*!
	 \brief

	 \fn handleMousePress
	 \param pos
	 \param control
	 \param value
	 \param handle
	*/
	void handleMousePress(const QPoint& pos, QStyle::SubControl& control, int value, QxtSpanSlider::SpanHandle handle);
	/*!
	 \brief

	 \fn drawHandle
	 \param painter
	 \param handle
	*/
	void drawHandle(QStylePainter* painter, QxtSpanSlider::SpanHandle handle) const;
	/*!
	 \brief

	 \fn setupPainter
	 \param painter
	 \param orientation
	 \param x1
	 \param y1
	 \param x2
	 \param y2
	*/
	void setupPainter(QPainter* painter, Qt::Orientation orientation, qreal x1, qreal y1, qreal x2, qreal y2) const;
	/*!
	 \brief

	 \fn drawSpan
	 \param painter
	 \param rect
	*/
	void drawSpan(QStylePainter* painter, const QRect& rect) const;
	/*!
	 \brief

	 \fn triggerAction
	 \param action
	 \param main
	*/
	void triggerAction(QAbstractSlider::SliderAction action, bool main);
	/*!
	 \brief

	 \fn swapControls
	*/
	void swapControls();

	int lower; /*!< TODO: describe */
	int upper; /*!< TODO: describe */
	int lowerPos; /*!< TODO: describe */
	int upperPos; /*!< TODO: describe */
	int offset; /*!< TODO: describe */
	int position; /*!< TODO: describe */
	QxtSpanSlider::SpanHandle lastPressed; /*!< TODO: describe */
	QxtSpanSlider::SpanHandle mainControl; /*!< TODO: describe */
	QStyle::SubControl lowerPressed; /*!< TODO: describe */
	QStyle::SubControl upperPressed; /*!< TODO: describe */
	QxtSpanSlider::HandleMovementMode movement; /*!< TODO: describe */
	bool firstMovement; /*!< TODO: describe */
	bool blockTracking; /*!< TODO: describe */


public Q_SLOTS:
	/*!
	 \brief

	 \fn updateRange
	 \param min
	 \param max
	*/
	void updateRange(int min, int max);
	/*!
	 \brief

	 \fn movePressedHandle
	*/
	void movePressedHandle();

private:
	QxtSpanSlider* q_ptr; /*!< TODO: describe */
    friend class QxtSpanSlider;


};

#endif // QXTSPANSLIDER_P_H

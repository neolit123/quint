/*
quint: quintview.cpp

Copyright (C) 2012 Andrew Baldwin

Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the "Software"), to deal in
the Software without restriction, including without limitation the rights to
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
of the Software, and to permit persons to whom the Software is furnished to do
so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include <quintview.h>
#include <QDebug>

QuintView::QuintView() : QQuickView(),m_framecount(0)
   {
       setResizeMode(QQuickView::SizeRootObjectToView);
       QObject::connect(this, SIGNAL(frameSwapped()), this, SLOT(fpscounter()));
   }

void QuintView::mouseMoveEvent(QMouseEvent* event)
{
    m_cursorpos = event->pos();
    emit cursormovedsignal();
}

void QuintView::fpscounter(void)
{
    // Called from a frame swapped
    // Keep an average FPS count
    if (m_framecount==0) {
        m_fpscounter.start();
    } else if (m_framecount%100==0) {
        m_fps = QString::number(100000.0/qreal(m_fpscounter.restart()),'g',2);
        emit fpsupdated();
    }
    m_framecount++;
    //qDebug() << "fpscounter" << m_fps;
}

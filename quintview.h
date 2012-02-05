/*
quint: quintview.h

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

#ifndef QUINTVIEW_H
#define QUINTVIEW_H

#ifdef NO_QUICKVIEW
   #include <qsgitem.h>
   #include <qsgview.h>
   #define QQuickView QSGView
#else
   #include <QtQuick/qquickitem.h>
   #include <QtQuick/qquickview.h>
#endif

#include <QtCore/QTime>

class QuintView : public QQuickView
{
    Q_OBJECT
    Q_PROPERTY(QPoint cursorpos READ cursorpos NOTIFY cursormovedsignal)
    Q_PROPERTY(QString fps READ fps NOTIFY fpsupdated)
    QPoint cursorpos() {return m_cursorpos;}
    QString fps() {return m_fps;}
public:
    QuintView();
    void mouseMoveEvent(QMouseEvent *);
public Q_SLOTS:
    void fpscounter();
Q_SIGNALS:
    void cursormovedsignal();
    void fpsupdated();
private:
    QPoint m_cursorpos;
    QTime m_fpscounter;
    QString m_fps;
    int m_framecount;
};

#endif // QUINTVIEW_H

#ifndef QUINTVIEW_H
#define QUINTVIEW_H

#ifdef NO_QUICKVIEW
   #include <qsgitem.h>
   #include <qsgview.h>
   #define QQuickView QSGView
#else
   #include <qquickitem.h>
   #include <qquickview.h>
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

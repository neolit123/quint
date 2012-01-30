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

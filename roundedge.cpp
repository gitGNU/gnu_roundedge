/*
 * Copyright (C) 2009 Christoph Fritz <chris_honschu(at)gmx.de>
 *
 * This file is part of roundedge.
 *
 *  roundedge is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  roundedge is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with roundedge.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include <QtGui>
#include "roundedge.h"

RoundEdge::RoundEdge(QWidget *parent, Qt::WindowFlags f, Orientation orient)
        : QWidget(parent, f)
{
    /* set size policy */
    setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed));

    /* set window position */
    QDesktopWidget* desktopWidget = QApplication::desktop();
    QRect r = desktopWidget->screenGeometry();
    r.adjust(0, 0, -24, -24);
    if (orient == UpLeft)
        move(r.topLeft());
    else if (orient == DownLeft)
        move(r.bottomLeft());
    else if (orient == UpRight)
        move(r.topRight());
    else if (orient == DownRight)
        move(r.bottomRight());

    /* allow mouse move events */
    setMouseTracking(true);

    /* set background */
    QPalette palette;
    palette.setColor(QPalette::Background, Qt::black);
    this->setPalette(palette);

    /* create path rounded corner */
    QPainterPath path;
    path.moveTo(25.0, 25.0);
    path.arcTo(0.0, 0.0, 50.0, 50.0, 270.0, 90.0);
    path.moveTo(25.0, 25.0);
    path.lineTo(50.0, 25.0);
    path.lineTo(50.0, 50.0);
    path.lineTo(25.0, 50.0);
    path.closeSubpath();

    /* draw path into bmp */
    QBitmap bmp(25,25);
    QPainter painter( &bmp );
    painter.setRenderHint(QPainter::Antialiasing);
    painter.eraseRect(0,0,25,25);
    painter.setPen(Qt::NoPen);
    painter.setBrush(Qt::black);
    switch (orient)
    {
    case UpLeft:
        painter.rotate(180);
        painter.translate(-50.0, -50.0);
        break;
    case DownLeft:
        painter.rotate(90);
        painter.translate(-25.0, -50.0);
        break;
    case UpRight:
        painter.rotate(-90);
        painter.translate(-50.0, -25.0);
        break;
    case DownRight:
        painter.translate(-25.0, -25.0);
        break;
    }
    painter.drawPath(path);
    painter.end();

    /* set the masked region */
    mask = new QRegion(bmp);
    setMask(*mask);

    /* init timer but don't start it */
    timer = new QTimer(this);
    timer->setInterval(200);
    connect(timer, SIGNAL(timeout()), this, SLOT(cleanupMask()));
}

/* so the window below will get focus */
void RoundEdge::shootHoleInMask(const QPoint *point)
{
    QRegion mouseRegion(point->x(), point->y(), 1, 1);
    QRegion hole = mask->subtracted(mouseRegion);
    setMask(hole);
}

void RoundEdge::mouseMoveEvent(QMouseEvent *event)
{
    shootHoleInMask(&event->pos());
    event->accept();
}

void RoundEdge::leaveEvent(QEvent *event)
{
    if (!timer->isActive())
        timer->start();
    event->accept();
}

void RoundEdge::cleanupMask()
{
    QRegion tmp = mask->translated(geometry().topLeft());
    if (!tmp.contains(QCursor::pos())) {
        setMask(*mask);
        timer->stop();
    }
}

QSize RoundEdge::sizeHint() const
{
    return QSize(25, 25);
}

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

#ifndef ROUNDEDGE_H
#define ROUNDEDGE_H

#include <QWidget>

/* FIXME WM_*: don't know if it will work on all WindowManagers */
#define WM_UNMANAGED (Qt::X11BypassWindowManagerHint | Qt::FramelessWindowHint)
#define WM_SPLASH (Qt::WindowStaysOnTopHint | Qt::SplashScreen )
#define WM_MANAGED 0

enum Orientation { UpLeft, DownLeft, UpRight, DownRight };

class RoundEdge : public QWidget
{
    Q_OBJECT

public:
    RoundEdge(QWidget *parent=0, Qt::WindowFlags f=0, Orientation orient=UpLeft);

protected:
    void mouseMoveEvent(QMouseEvent *event);
    void leaveEvent(QEvent * event);
    QSize sizeHint() const;
    void shootHoleInMask(const QPoint *point);
    QRegion *mask;
    QTimer *timer;

private slots:
    void cleanupMask();
};

#endif // ROUNDEDGE_H

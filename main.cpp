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

#include <QApplication>
#include <QTextStream>
#include "roundedge.h"

#define NO_PARENT 0

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QStringList args = QCoreApplication::arguments();
    Qt::WindowFlags wf = WM_UNMANAGED;
    int start = 0x00;
    RoundEdge *redge;

    for (int i = 1; i < args.size(); ++i)
    {
        if (args.at(i) == "managed" || args.at(i) == "-managed")
            wf = WM_MANAGED;
        if (args.at(i) == "splash" || args.at(i) == "-splash")
            wf = WM_SPLASH;
        else if (args.at(i).contains("all", Qt::CaseInsensitive))
            start = 0x0F;
        else if (args.at(i).contains("UpL", Qt::CaseInsensitive))
            start |= 0x01;
        else if (args.at(i).contains("DownL", Qt::CaseInsensitive))
            start |= 0x02;
        else if (args.at(i).contains("UpR", Qt::CaseInsensitive))
            start |= 0x04;
        else if (args.at(i).contains("DownR", Qt::CaseInsensitive))
            start |= 0x08;
        else if (args.at(i).contains("h", Qt::CaseInsensitive)) {
            QTextStream out(stdout);
            out.setFieldAlignment(QTextStream::AlignLeft);
            out << endl << "WM-Options:" << endl;
            out << "\t-unmanaged\tbypass X11 window manager (default)" << endl;
            out << "\t-managed\twindow manager keeps full track" << endl;
            out << "\t-splash\t\tsplash-window that stays on top" << endl;
            out << "Options:" << endl;
            out << "\t-all\t\tshows roundedge in all edges (default)" << endl;
            out << "\t-UpLeft\t\tshow roundedge in up left corner" << endl;
            out << "\t-DownLeft\tshow roundedge in down left corner" << endl;
            out << "\t-UpRight\tshow roundedge in up right corner" << endl;
            out << "\t-DownRight\tshow roundedge in down right corner" << endl;
            out << "\t-help\t\tshow this helptext" << endl << endl;
            out.flush();
            return 0;
        }
    }

    if ( start & 0x01 || start == 0x00 ) {
        redge = new RoundEdge(NO_PARENT, wf, UpLeft);
        redge->show();
    }
    if ( start & 0x02 || start == 0x00 ) {
        redge = new RoundEdge(NO_PARENT, wf, DownLeft);
        redge->show();
    }
    if ( start & 0x04 || start == 0x00 ) {
        redge = new RoundEdge(NO_PARENT, wf, UpRight);
        redge->show();
    }
    if ( start & 0x08 || start == 0x00 ) {
        redge = new RoundEdge(NO_PARENT, wf, DownRight);
        redge->show();
    }
    return app.exec();
}

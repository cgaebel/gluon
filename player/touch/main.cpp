/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (c) 2010 Laszlo Papp <djszapi@archlinux.us>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */

#include <player/lib/authentication.h>

#include <QtGui/QApplication>
#include <QtDeclarative/QDeclarativeView>
#include <QtDeclarative/QDeclarativeContext>
#include <QtGui/QGraphicsObject>

int main( int argc, char** argv )
{
    QApplication app( argc, argv );
    app.setOrganizationName( "KDE Gluon" );
    app.setApplicationName( "Gluon QML Player" );

    QDeclarativeView view;
    GluonPlayer::Authentication *auth = GluonPlayer::Authentication::instance();
    view.rootContext()->setContextProperty("authentication", auth);
    view.setSource(QUrl("qrc:/main.qml"));
    view.show();

    QObject *obj = view.rootObject();
    QObject *login = obj->findChild<QObject *>("login");
    QObject::connect(auth, SIGNAL(initialized()), login, SLOT(providerSet()));

    return app.exec();
}

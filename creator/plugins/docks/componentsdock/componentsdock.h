/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (c) 2010 Arjen Hiemstra <ahiemstra@heimr.nl>
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

#ifndef GLUON_CREATOR_COMPONENTSDOCK_H
#define GLUON_CREATOR_COMPONENTSDOCK_H

#include "widgets/dock.h"

namespace GluonCreator
{

    class ComponentsDock : public Dock
    {
        public:
            explicit ComponentsDock(const QString& title, QWidget* parent = 0, Qt::WindowFlags flags = 0);
            ~ComponentsDock();

            void setSelection(GluonCore::GluonObject* obj = 0);
            QAbstractItemView* view();
            QAbstractItemModel* model();

        private:
            class ComponentsDockPrivate;
            ComponentsDockPrivate* d;
    };

}

#endif // GLUON_CREATOR_COMPONENTSDOCK_H

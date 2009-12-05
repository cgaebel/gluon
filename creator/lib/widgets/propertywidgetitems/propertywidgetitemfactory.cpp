/*
   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Library General Public
   License version 2 as published by the Free Software Foundation.

   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Library General Public License for more details.

   You should have received a copy of the GNU Library General Public License
   along with this library; see the file COPYING.LIB.  If not, write to
   the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.
*/

#include "propertywidgetitemfactory.h"

#include "textpropertywidgetitem.h"
#include "vectorpropertywidgetitem.h"
#include "nullpropertywidgetitem.h"

using namespace Gluon::Creator;

template<> PropertyWidgetItemFactory* KSingleton<PropertyWidgetItemFactory>::m_instance = 0;

PropertyWidgetItem* PropertyWidgetItemFactory::create(const QString& type, QWidget* parent)
{
    if(type == "QString") return new TextPropertyWidgetItem(parent);
    if(type == "Eigen::Vector3f") return new VectorPropertyWidgetItem(parent);

    return new NullPropertyWidgetItem(parent);
}


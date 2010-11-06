/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (C) 2010 Dan Leinir Turthra Jensen <admin@leinir.dk>
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

#include "scriptingcomponentprivate.h"

using namespace GluonEngine;

ScriptingComponent::ScriptingComponentPrivate::ScriptingComponentPrivate()
    : scriptingAsset( 0 )
{
}

ScriptingComponent::ScriptingComponentPrivate::ScriptingComponentPrivate( const GluonEngine::ScriptingComponent::ScriptingComponentPrivate& other )
    : QSharedData( other )
    , scriptingAsset( other.scriptingAsset )
    , initializeFunction( other.initializeFunction )
    , startFunction( other.startFunction )
    , updateFunction( other.updateFunction )
    , drawFunction( other.drawFunction )
    , stopFunction( other.stopFunction )
    , cleanupFunction( other.cleanupFunction )
{
}

ScriptingComponent::ScriptingComponentPrivate::~ScriptingComponentPrivate()
{
}

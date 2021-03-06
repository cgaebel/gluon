/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (C) 2009 Guillaume Martres <smarter@ubuntu.com>
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

#ifndef GLUON_AUDIO_DEVICE_P_H
#define GLUON_AUDIO_DEVICE_P_H

#include <QtCore/QStringList>

#ifdef Q_WS_X11
#include <AL/alc.h>
#endif
#ifdef Q_WS_MAC
#include <OpenAL/alc.h>
#endif
#ifdef Q_WS_WIN
#include <AL/alc.h>
#endif


namespace GluonAudio
{

    class Device
    {
        public:
            Device( ALCdevice* device = 0 );
            virtual ~Device();

            static bool isExtensionPresent( const QString& extension );

            static QStringList contextOption( int option );

        protected:
            ALCdevice* m_device;
    };
}

#endif // GLUON_AUDIO_DEVICE_P_H

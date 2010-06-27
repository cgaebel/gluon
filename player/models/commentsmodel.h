/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (C) 2010 Shantanu Tushar Jha <jhahoneyk@gmail.com>
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

#ifndef GLUONPLAYER_COMMENTSMODEL_H
#define GLUONPLAYER_COMMENTSMODEL_H

#include <QAbstractItemModel>
#include <QStringList>

#include "gluon_player_export.h"

namespace GluonCore
{
    class GluonObject;
};

namespace GluonPlayer
{

    class GLUON_PLAYER_EXPORT CommentsModel : public QAbstractItemModel
    {

    public:
        enum Column { AuthorColumn, TitleColumn, BodyColumn, DateTimeColumn, RatingColumn };

        CommentsModel(QObject* parent = 0);
        virtual ~CommentsModel();
        virtual QVariant data (const QModelIndex& index, int role = Qt::DisplayRole) const;
        virtual int columnCount (const QModelIndex& parent = QModelIndex()) const;
        virtual int rowCount (const QModelIndex& parent = QModelIndex()) const;
        virtual QModelIndex parent (const QModelIndex& child) const;
        virtual QModelIndex index (int row, int column, const QModelIndex& parent = QModelIndex()) const;
        virtual QVariant headerData (int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;

        QString columnName(const Column col) const;

    private:
        GluonCore::GluonObject *rootNode;
        QStringList m_columnNames;
    };

}

#endif // GLUONPLAYER_COMMENTSMODEL_H
/*
    <one line to give the program's name and a brief idea of what it does.>
    Copyright (C) <year>  <name of author>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/

#include <QStringList>
#include <QDebug>
#include "gdlhandler.h"
#include "gluonobject.h"
#include "gluonobjectfactory.h"

using namespace Gluon;

template<> GDLHandler* KSingleton<GDLHandler>::m_instance = 0;

GDLHandler::GDLHandler()
{
}

GDLHandler::~GDLHandler()
{
}

GluonObject *
GDLHandler::instantiateObject(QString className)
{
    GluonObject * newObject = GluonObjectFactory::instance()->instantiateObjectByName(className);
    if(!newObject)
        newObject = new GluonObject();
    
    return newObject;
}

GluonObject *
GDLHandler::createObject(QStringList objectStringList, QObject * parent)
{
    GluonObject * createdObject = 0;
    int index = 0;
    QString currentPropertyName;
    foreach(const QString &item, objectStringList)
    {
        switch(index)
        {
            case 0:
                // Object type
                createdObject = instantiateObject(item);
                createdObject->setParent(parent);
                break;
            case 1:
                // Object name
                createdObject->setName(item);
                break;
            default:
                // Everything else
                if(currentPropertyName.isEmpty())
                {
                    if(item.startsWith('{'))
                    {
                        // Items are parented automatically - see case 0 above
                        QList<GluonObject *> childList = parseGDL(item, createdObject);
                    }
                    else
                    {
                        currentPropertyName = item;
                    }
                }
                else
                {
                    // Set the property with the current string as the value, and finally clear the property name
                    createdObject->setPropertyFromString(currentPropertyName, item);
                    currentPropertyName.clear();
                }
                break;
        }
        ++index;
    }
    return createdObject;
}

QList<QStringList>
GDLHandler::tokenizeObject(QString objectString)
{
    QList<QStringList> tokenizedObject;
    
    bool inItem = false;
    bool inName = false;
    bool inValue = false;
    bool inChild = false;
    bool inObjectDefinition = false;
    bool beingEscaped = false;
    int extraBracketCounter = 0;
    QString currentString;
    QStringList currentItem;
    
    QString::const_iterator i;
    for(i = objectString.begin(); i != objectString.end(); ++i)
    {
        if(!inItem)
        {
            if(i->isSpace())
            {
                // Just do nothing - whitespace should be ignored outside of items
            }
            else if(i->toLower() == '{')
            {
                qDebug() << "Found opening bracket";
                inItem = true;
            }
        }
        else
        {
            if(!inValue && !inName && !inChild && !inObjectDefinition)
            {
                if(!currentString.isEmpty())
                {
                    currentItem.append(currentString.trimmed());
                    currentString.clear();
                }
                
                // Ignore whitespace as instructed, rar!
                if(!i->isSpace())
                {
                    if(i->toLower() == '}')
                    {
                        // Once we hit an end, we should stop looking at this item
                        // In other words - add the item to the list of items and make a new stringlist to work on...
                        qDebug() << "Found closing bracket";
                        QStringList theItem(currentItem);
                        tokenizedObject.append(theItem);
                        currentItem.clear();
                    }
                    else if(i->toLower() == '{')
                    {
                        // If we hit a start while already inside an item, we should simply start adding stuff
                        // until we hit the correct ending again
                        qDebug() << "Found child object";
                        inChild = true;
                    }
                    else
                    {
                        // Once you hit something, start reading the object definition
                        inObjectDefinition = true;
                    }
                }
            }
            
            if(inObjectDefinition)
            {
                if(!inName && !inValue)
                {
                    // Ignore spaces between the start { and the object type
                    if(!i->isSpace())
                        inName = true;
                }
                else if(inName)
                {
                    if(i->toLower() == '(')
                    {
                        currentItem.append(currentString.trimmed());
                        qDebug() << "Name:" << currentString;
                        currentString.clear();
                        inName = false;
                        inValue = true;
                    }
                    else
                        currentString += i->unicode();
                }
                else // meaning inValue
                {
                    if(i->toLower() == ')')
                    {
                        currentItem.append(currentString.trimmed());
                        currentString.clear();
                        qDebug() << "Value:" << currentString;
                        inValue = false;
                        inObjectDefinition = false;
                    }
                    else
                        currentString += i->unicode();
                }
            }
            else if(inChild)
            {
                if(i->toLower() == '\\' && !beingEscaped)
                    beingEscaped = true;
                else
                {
                    currentString += i->unicode();
                    if(!beingEscaped)
                    {
                        if(i->toLower() == '{')
                        {
                            ++extraBracketCounter;
                        }
                        if(i->toLower() == '}')
                        {
                            --extraBracketCounter;
                            if(extraBracketCounter == -1)
                            {
                                // Now we're ready to look for more values, yay! ;)
                                extraBracketCounter = 0;
                                inChild = false;
                                qDebug() << "End child" << currentString;
                            }
                        }
                    }
                    else
                        beingEscaped = false;
                }
            }
            else if(inName)
            {
                // Read name until we hit a space, and after that, start reading the value...
                if(!i->isSpace())
                {
                    currentString += i->unicode();
                    qDebug() << "Name:" << i->unicode();
                }
                else
                {
                    inName = false;
                    inValue = true;
                }
            }
            else if(inValue)
            {
                if(i->toLower() == '\\' && !beingEscaped)
                    beingEscaped = true;
                else
                {
                    // Read the value until the value ends, wooh! ;)
                    currentString += i->unicode();
                    if(!beingEscaped && i->toLower() == ')')
                    {
                        inValue = false;
                        qDebug() << currentString;
                    }
                    beingEscaped = false;
                }
            }
        }
    }
    
    return tokenizedObject;
}

QList<GluonObject *>
GDLHandler::parseGDL(const QString parseThis, QObject * parent)
{
    qDebug() << "Begin parsing data";
    
    QList<GluonObject *> thisObjectList;
    
    QList<QStringList> tokenizedObject = tokenizeObject(parseThis);

    qDebug() << tokenizedObject;
    
    foreach(const QStringList &item, tokenizedObject)
    {
        GluonObject * currentObject = createObject(item, parent);
        thisObjectList.append(currentObject);
    }

    qDebug() << "End parsing data";
    return thisObjectList;
}

QString
serializeGDL(QList<GluonObject *> serializeThis)
{
    QString serializedData;
    return serializedData;
}

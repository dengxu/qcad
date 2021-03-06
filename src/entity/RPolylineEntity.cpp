/**
 * Copyright (c) 2011-2018 by Andrew Mustun. All rights reserved.
 * 
 * This file is part of the QCAD project.
 *
 * QCAD is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * QCAD is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with QCAD.
 */
#include "RPolylineEntity.h"
#include "RMetaTypes.h"
#include "RExporter.h"
#include "RLine.h"

RPropertyTypeId RPolylineEntity::PropertyCustom;
RPropertyTypeId RPolylineEntity::PropertyHandle;
RPropertyTypeId RPolylineEntity::PropertyProtected;
RPropertyTypeId RPolylineEntity::PropertyType;
RPropertyTypeId RPolylineEntity::PropertyBlock;
RPropertyTypeId RPolylineEntity::PropertyLayer;
RPropertyTypeId RPolylineEntity::PropertyLinetype;
RPropertyTypeId RPolylineEntity::PropertyLinetypeScale;
RPropertyTypeId RPolylineEntity::PropertyLineweight;
RPropertyTypeId RPolylineEntity::PropertyColor;
RPropertyTypeId RPolylineEntity::PropertyDisplayedColor;
RPropertyTypeId RPolylineEntity::PropertyDrawOrder;

RPropertyTypeId RPolylineEntity::PropertyPolylineGen;
RPropertyTypeId RPolylineEntity::PropertyClosed;
RPropertyTypeId RPolylineEntity::PropertyVertexNX;
RPropertyTypeId RPolylineEntity::PropertyVertexNY;
RPropertyTypeId RPolylineEntity::PropertyVertexNZ;
RPropertyTypeId RPolylineEntity::PropertyBulgeN;
RPropertyTypeId RPolylineEntity::PropertyAngleN;
RPropertyTypeId RPolylineEntity::PropertyStartWidthN;
RPropertyTypeId RPolylineEntity::PropertyEndWidthN;

RPropertyTypeId RPolylineEntity::PropertyGlobalWidth;

RPropertyTypeId RPolylineEntity::PropertyOrientation;
RPropertyTypeId RPolylineEntity::PropertyLength;
RPropertyTypeId RPolylineEntity::PropertyTotalLength;
RPropertyTypeId RPolylineEntity::PropertyArea;
RPropertyTypeId RPolylineEntity::PropertyTotalArea;

QString RPolylineEntity::TrClockwise = QString("↻ ") + QT_TRANSLATE_NOOP("REntity", "Clockwise");
QString RPolylineEntity::TrCounterclockwise = QString("↺ ") + QT_TRANSLATE_NOOP("REntity", "Counterclockwise");

RPolylineEntity::RPolylineEntity(RDocument* document, const RPolylineData& data) :
    REntity(document), data(document, data) {
    RDebug::incCounter("RPolylineEntity");
}

RPolylineEntity::RPolylineEntity(const RPolylineEntity& other) : REntity(other) {
    RDebug::incCounter("RPolylineEntity");
    data = other.data;
}

RPolylineEntity::~RPolylineEntity() {
    RDebug::decCounter("RPolylineEntity");
}

void RPolylineEntity::setShape(const RPolyline& l) {
    data.setVertices(l.getVertices());
    data.setBulges(l.getBulges());
    data.setClosed(l.isClosed());
    data.setStartWidths(l.getStartWidths());
    data.setEndWidths(l.getEndWidths());
}

void RPolylineEntity::init() {
    RPolylineEntity::PropertyCustom.generateId(typeid(RPolylineEntity), RObject::PropertyCustom);
    RPolylineEntity::PropertyHandle.generateId(typeid(RPolylineEntity), RObject::PropertyHandle);
    RPolylineEntity::PropertyProtected.generateId(typeid(RPolylineEntity), RObject::PropertyProtected);
    RPolylineEntity::PropertyType.generateId(typeid(RPolylineEntity), REntity::PropertyType);
    RPolylineEntity::PropertyBlock.generateId(typeid(RPolylineEntity), REntity::PropertyBlock);
    RPolylineEntity::PropertyLayer.generateId(typeid(RPolylineEntity), REntity::PropertyLayer);
    RPolylineEntity::PropertyLinetype.generateId(typeid(RPolylineEntity), REntity::PropertyLinetype);
    RPolylineEntity::PropertyLinetypeScale.generateId(typeid(RPolylineEntity), REntity::PropertyLinetypeScale);
    RPolylineEntity::PropertyLineweight.generateId(typeid(RPolylineEntity), REntity::PropertyLineweight);
    RPolylineEntity::PropertyColor.generateId(typeid(RPolylineEntity), REntity::PropertyColor);
    RPolylineEntity::PropertyDisplayedColor.generateId(typeid(RPolylineEntity), REntity::PropertyDisplayedColor);
    RPolylineEntity::PropertyDrawOrder.generateId(typeid(RPolylineEntity), REntity::PropertyDrawOrder);

    RPolylineEntity::PropertyPolylineGen.generateId(typeid(RPolylineEntity), "", QT_TRANSLATE_NOOP("REntity", "Polyline Pattern"));
    RPolylineEntity::PropertyClosed.generateId(typeid(RPolylineEntity), "", QT_TRANSLATE_NOOP("REntity", "Closed"));
    RPolylineEntity::PropertyVertexNX.generateId(typeid(RPolylineEntity), QT_TRANSLATE_NOOP("REntity", "Vertex"), QT_TRANSLATE_NOOP("REntity", "X"));
    RPolylineEntity::PropertyVertexNY.generateId(typeid(RPolylineEntity), QT_TRANSLATE_NOOP("REntity", "Vertex"), QT_TRANSLATE_NOOP("REntity", "Y"));
    RPolylineEntity::PropertyVertexNZ.generateId(typeid(RPolylineEntity), QT_TRANSLATE_NOOP("REntity", "Vertex"), QT_TRANSLATE_NOOP("REntity", "Z"));
    RPolylineEntity::PropertyBulgeN.generateId(typeid(RPolylineEntity), QT_TRANSLATE_NOOP("REntity", "Vertex"), QT_TRANSLATE_NOOP("REntity", "Bulge"));
    RPolylineEntity::PropertyAngleN.generateId(typeid(RPolylineEntity), QT_TRANSLATE_NOOP("REntity", "Vertex"), QT_TRANSLATE_NOOP("REntity", "Angle"));

    RPolylineEntity::PropertyStartWidthN.generateId(typeid(RPolylineEntity), QT_TRANSLATE_NOOP("REntity", "Vertex"), QT_TRANSLATE_NOOP("REntity", "Start Width"));
    RPolylineEntity::PropertyEndWidthN.generateId(typeid(RPolylineEntity), QT_TRANSLATE_NOOP("REntity", "Vertex"), QT_TRANSLATE_NOOP("REntity", "End Width"));

    RPolylineEntity::PropertyGlobalWidth.generateId(typeid(RPolylineEntity), "", QT_TRANSLATE_NOOP("REntity", "Global Width"));

    RPolylineEntity::PropertyOrientation.generateId(typeid(RPolylineEntity), "", QT_TRANSLATE_NOOP("REntity", "Orientation"));
    RPolylineEntity::PropertyLength.generateId(typeid(RPolylineEntity), "", QT_TRANSLATE_NOOP("REntity", "Length"));
    RPolylineEntity::PropertyTotalLength.generateId(typeid(RPolylineEntity), "", QT_TRANSLATE_NOOP("REntity", "Total Length"));
    RPolylineEntity::PropertyArea.generateId(typeid(RPolylineEntity), "", QT_TRANSLATE_NOOP("REntity", "Area"));
    RPolylineEntity::PropertyTotalArea.generateId(typeid(RPolylineEntity), "", QT_TRANSLATE_NOOP("REntity", "Total Area"));
}

bool RPolylineEntity::setProperty(RPropertyTypeId propertyTypeId,
        const QVariant& value, RTransaction* transaction) {

    bool ret = REntity::setProperty(propertyTypeId, value, transaction);
    ret = ret || RObject::setMember(data.polylineGen, value, PropertyPolylineGen == propertyTypeId);
    ret = ret || RObject::setMember(data.closed, value, PropertyClosed == propertyTypeId);
    ret = ret || RObject::setMemberX(data.vertices, value, PropertyVertexNX == propertyTypeId);
    ret = ret || RObject::setMemberY(data.vertices, value, PropertyVertexNY == propertyTypeId);
    ret = ret || RObject::setMemberZ(data.vertices, value, PropertyVertexNZ == propertyTypeId);
    ret = ret || RObject::setMember(data.bulges, value, PropertyBulgeN == propertyTypeId);

    if (RPolyline::hasProxy()) {
        ret = ret || RObject::setMember(data.startWidths, value, PropertyStartWidthN == propertyTypeId);
        ret = ret || RObject::setMember(data.endWidths, value, PropertyEndWidthN == propertyTypeId);

        if (PropertyGlobalWidth==propertyTypeId) {
            data.setGlobalWidth(value.toDouble());
            ret = true;
        }

        if (PropertyOrientation==propertyTypeId) {
            if (value.type()==QVariant::String) {
                if (value.toString()==RPolylineEntity::TrClockwise) {
                    ret = ret || data.setOrientation(RS::CW);
                }
                else {
                    ret = ret || data.setOrientation(RS::CCW);
                }
            }
            else {
                ret = ret || data.setOrientation((RS::Orientation)value.toInt());
            }
        }
    }

    return ret;
}

QPair<QVariant, RPropertyAttributes> RPolylineEntity::getProperty(
        RPropertyTypeId& propertyTypeId, bool humanReadable,
        bool noAttributes) {
    if (propertyTypeId == PropertyClosed) {
        QVariant v;
        v.setValue(data.closed);
        return qMakePair(v, RPropertyAttributes());
    } else if (propertyTypeId == PropertyPolylineGen) {
        QVariant v;
        v.setValue(data.polylineGen);
        return qMakePair(v, RPropertyAttributes());
    } else if (propertyTypeId == PropertyVertexNX) {
        QVariant v;
        v.setValue(RVector::getXList(data.vertices));
        return qMakePair(v, RPropertyAttributes(RPropertyAttributes::List));
    } else if (propertyTypeId == PropertyVertexNY) {
        QVariant v;
        v.setValue(RVector::getYList(data.vertices));
        return qMakePair(v, RPropertyAttributes(RPropertyAttributes::List));
    } else if (propertyTypeId == PropertyVertexNZ) {
        QVariant v;
        v.setValue(RVector::getZList(data.vertices));
        return qMakePair(v, RPropertyAttributes(RPropertyAttributes::List));
    } else if (propertyTypeId == PropertyBulgeN) {
        QVariant v;
        v.setValue(data.bulges);
        return qMakePair(v, RPropertyAttributes(RPropertyAttributes::List));
    } else if (propertyTypeId == PropertyAngleN) {
        QVariant v;
        v.setValue(data.getVertexAngles());
        return qMakePair(v, RPropertyAttributes(RPropertyAttributes::List|RPropertyAttributes::Angle));
    } else if (RPolyline::hasProxy() && propertyTypeId == PropertyStartWidthN) {
        QVariant v;
        v.setValue(data.startWidths);
        return qMakePair(v, RPropertyAttributes(RPropertyAttributes::List));
    } else if (RPolyline::hasProxy() && propertyTypeId == PropertyEndWidthN) {
        QVariant v;
        v.setValue(data.endWidths);
        return qMakePair(v, RPropertyAttributes(RPropertyAttributes::List));
    } else if (RPolyline::hasProxy() && propertyTypeId == PropertyGlobalWidth) {
        QVariant v;
        double val = -1.0;
        for (int i=0; i<data.startWidths.length() && i<data.endWidths.length(); i++) {
            if (val<0.0) {
                val = data.startWidths[i];
                v.setValue(val);
            }

            if (!RMath::fuzzyCompare(data.startWidths[i], val) || !RMath::fuzzyCompare(data.endWidths[i], val)) {
                v.setValue(QString());
                break;
            }
        }
        return qMakePair(v, RPropertyAttributes(RPropertyAttributes::Redundant));
    }

    // human readable properties (not relevant for transactions):
    if (humanReadable) {
        if (propertyTypeId == PropertyLength) {
            QVariant v;
            v.setValue(data.getLength());
            return qMakePair(v, RPropertyAttributes(RPropertyAttributes::ReadOnly));
        } else if (propertyTypeId == PropertyTotalLength) {
            QVariant v;
            v.setValue(data.getLength());
            return qMakePair(v, RPropertyAttributes(RPropertyAttributes::Sum));
        } else if (propertyTypeId == PropertyArea) {
            QVariant v;
            v.setValue(data.getArea());
            return qMakePair(v, RPropertyAttributes(RPropertyAttributes::ReadOnly));
        } else if (propertyTypeId == PropertyTotalArea) {
            QVariant v;
            v.setValue(data.getArea());
            return qMakePair(v, RPropertyAttributes(RPropertyAttributes::Sum));
        }
    }

    if (RPolyline::hasProxy()) {
        if (propertyTypeId == PropertyOrientation) {
            RPropertyAttributes attr;
            if (!noAttributes && humanReadable) {
                attr.setChoices(QSet<QString>() << RPolylineEntity::TrClockwise << RPolylineEntity::TrCounterclockwise);
            }
            attr.setRedundant(true);
            RS::Orientation ori = data.getOrientation(true);
            if (humanReadable) {
                QString oriStr = (ori==RS::CCW ? RPolylineEntity::TrCounterclockwise : RPolylineEntity::TrClockwise);
                return qMakePair(oriStr, attr);
            }
            return qMakePair(ori, attr);
        }
    }

    return REntity::getProperty(propertyTypeId, humanReadable, noAttributes);
}


void RPolylineEntity::exportEntity(RExporter& e, bool preview, bool forceSelected) const {
    Q_UNUSED(preview);
    Q_UNUSED(forceSelected);

    e.setBrush(Qt::NoBrush);

    e.exportPolyline(data, data.getPolylineGen());
}

void RPolylineEntity::print(QDebug dbg) const {
    dbg.nospace() << "RPolylineEntity(";
    REntity::print(dbg);
    data.print(dbg);
    dbg.nospace()  << ")";
}

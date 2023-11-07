/*
 * Copyright (C) 2023 The Layers Project
 *
 * This file is part of QLayers.
 *
 * QLayers is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * QLayers is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with QLayers. If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef QLATTRIBUTEMAPITEM_H
#define QLATTRIBUTEMAPITEM_H

#include <QVariant>
#include <QList>

#include <Layers/lattribute.h>

#include "qlayers_global.h"
#include "qlayers_export.h"

QLAYERS_NAMESPACE_BEGIN
class QLAttributeMapItem : public QObject
{
	Q_OBJECT

public:
	QLAttributeMapItem(Layers::LAttribute* attribute,
		QLAttributeMapItem* parent = nullptr);

	void append_child(QLAttributeMapItem* child);

	Layers::LAttribute* attribute() const;

	QLAttributeMapItem* child(int index) const;

	int child_count() const;

	QMap<QString, QLAttributeMapItem*>& children();

	int index() const;

private:
	QMap<QString, QLAttributeMapItem*> m_child_attr_items;
	Layers::LAttribute* m_attribute{ nullptr };
};
QLAYERS_NAMESPACE_END

#endif // QLATTRIBUTEMAPITEM_H

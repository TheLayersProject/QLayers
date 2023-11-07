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

#include <QLayers/qlattributemapitem.h>

using Layers::LAttribute;

using QLayers::QLAttributeMapItem;

QLAttributeMapItem::QLAttributeMapItem(
	LAttribute* attribute, QLAttributeMapItem* parent) :
	m_attribute{ attribute }, QObject(parent) {}

void QLAttributeMapItem::append_child(QLAttributeMapItem* child)
{
	m_child_attr_items[
		QString::fromStdString(child->m_attribute->object_name().c_str())
	] = child;
}

LAttribute* QLAttributeMapItem::attribute() const
{
	return m_attribute;
}

QLAttributeMapItem* QLAttributeMapItem::child(int index) const
{
	if (index < 0 || index >= m_child_attr_items.size())
		return nullptr;
	return m_child_attr_items[m_child_attr_items.keys().at(index)];
}

int QLAttributeMapItem::child_count() const
{
	return m_child_attr_items.count();
}

QMap<QString, QLAttributeMapItem*>& QLAttributeMapItem::children()
{
	return m_child_attr_items;
}

int QLAttributeMapItem::index() const
{
	if (QLAttributeMapItem* parent_item =
		dynamic_cast<QLAttributeMapItem*>(parent()))
	{
		QStringList keys = parent_item->m_child_attr_items.keys();

		for (int i = 0; i < keys.size(); i++)
		{
			QLAttributeMapItem* parent_child_attr_item =
				parent_item->m_child_attr_items[keys.at(i)];

			if (parent_child_attr_item == this)
				return i;
		}
	}

	return 0;
}

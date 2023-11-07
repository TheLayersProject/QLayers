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

#include <QLayers/qlattributemapmodel.h>

using Layers::LAttribute;
using Layers::LAttributeMap;

using QLayers::QLAttributeMapItem;
using QLayers::QLAttributeMapModel;

QLAttributeMapModel::QLAttributeMapModel(QObject* parent) :
	QAbstractItemModel(parent)
{
}

QLAttributeMapModel::~QLAttributeMapModel()
{
	delete m_root_item;
}

int QLAttributeMapModel::columnCount(const QModelIndex& parent) const
{
	Q_UNUSED(parent);
	return 1;
}

QVariant QLAttributeMapModel::data(const QModelIndex& index, int role) const
{
	if (!index.isValid())
	{
		return QVariant();
	}
	else if (role == Qt::DisplayRole)
	{
		return QString::fromStdString(
			get_item(index)->attribute()->object_name().c_str());
	}
	else if (role == Qt::UserRole)
	{
		return QVariant::fromValue(get_item(index)->attribute());
	}

	return QVariant();
}

QModelIndex QLAttributeMapModel::index(
	int row, int column, const QModelIndex& parent) const
{
	if (parent.isValid() && parent.column() != 0)
		return QModelIndex();

	QLAttributeMapItem* parent_item = get_item(parent);
	if (!parent_item)
		return QModelIndex();

	QLAttributeMapItem* child_item = parent_item->child(row);
	if (child_item)
		return createIndex(row, column, child_item);

	return QModelIndex();
}

QModelIndex QLAttributeMapModel::parent(const QModelIndex& index) const
{
	if (!index.isValid())
		return QModelIndex();

	QLAttributeMapItem* child_item = get_item(index);
	QLAttributeMapItem* parent_item = child_item ?
		dynamic_cast<QLAttributeMapItem*>(child_item->parent()) : nullptr;

	if (parent_item == m_root_item || !parent_item)
		return QModelIndex();

	return createIndex(parent_item->index(), 0, parent_item);
}

int QLAttributeMapModel::rowCount(const QModelIndex& parent) const
{
	if (parent.isValid() && parent.column() > 0)
		return 0;

	const QLAttributeMapItem* parent_item = get_item(parent);

	return parent_item ?
		parent_item->child_count() : 0;
}

void QLAttributeMapModel::set_attributes(
	LAttributeMap attributes, const QStringList& filter_paths)
{
	beginResetModel();

	delete m_root_item;

	m_root_item = new QLAttributeMapItem(nullptr);

	for (const auto& [key, attr] : attributes)
		if (!filter_paths.contains(QString::fromStdString(attr->path().c_str())))
			m_root_item->append_child(
				init_item(attr, filter_paths, m_root_item));

	endResetModel();
}

QLAttributeMapItem* QLAttributeMapModel::init_item(
	LAttribute* attribute, const QStringList& filter_paths,
	QLAttributeMapItem* parent)
{
	QLAttributeMapItem* item = new QLAttributeMapItem(attribute, parent);

	for (const auto& [key, override_attr] : attribute->overrides())
		item->append_child(init_item(override_attr, filter_paths, item));

	return item;
}

QLAttributeMapItem* QLAttributeMapModel::get_item(const QModelIndex& index) const
{
	if (index.isValid())
		if (QLAttributeMapItem* item =
			static_cast<QLAttributeMapItem*>(index.internalPointer()))
		{
			return item;
		}

	if (m_root_item)
		return m_root_item;

	return nullptr;
}

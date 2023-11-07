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

#include <QLayers/qlthemelineagemodel.h>

using QLayers::QLThemeLineageModel;

QLThemeLineageModel::QLThemeLineageModel(QObject* parent) :
	QAbstractTableModel(parent) {}

void QLThemeLineageModel::append(const QLThemeLineageData& lineage_data)
{
	beginInsertRows({}, m_lineage_data.count(), m_lineage_data.count());
	m_lineage_data.append(lineage_data);
	endInsertRows();
}

void QLThemeLineageModel::clear()
{
	if (!m_lineage_data.isEmpty())
	{
		beginResetModel();
		m_lineage_data.clear();
		endResetModel();
	}
}

int QLThemeLineageModel::columnCount(const QModelIndex& parent) const
{
	return 2;
}

QVariant QLThemeLineageModel::data(const QModelIndex& index, int role) const
{
	if (role == Qt::DisplayRole || role == Qt::EditRole)
	{
		auto theme_name = m_lineage_data[index.row()].name;
		auto theme_uuid = m_lineage_data[index.row()].uuid;

		switch (index.column()) {
		case 0:
			if (!theme_uuid.isEmpty())
				return theme_name + " (" + theme_uuid + ")";
			else
				return theme_name;
		default:
			return {};
		}
	}
	else if (role == Qt::DecorationRole)
	{
		const bool& theme_has_app_implementation_available =
			m_lineage_data[index.row()].has_app_implementation_available;

		switch (index.column()) {
		case 1:
			return theme_has_app_implementation_available;
		default:
			return {};
		}
	}
	else
		return {};
}

QVariant QLThemeLineageModel::headerData(int section, Qt::Orientation orientation, int role) const
{
	if (orientation != Qt::Horizontal || role != Qt::DisplayRole)
		return {};

	switch (section) {
	case 0:
		return "Theme";
	case 1:
		return "Compatible";
	default:
		return {};
	}
}

int QLThemeLineageModel::rowCount(const QModelIndex& parent) const
{
	if (!parent.isValid())
		return m_lineage_data.count();
	else
		return 0;
}


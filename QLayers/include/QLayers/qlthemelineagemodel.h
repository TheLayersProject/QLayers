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

#ifndef QLTHEMELINEAGEMODEL_H
#define QLTHEMELINEAGEMODEL_H

#include <QAbstractTableModel>

#include "qlayers_global.h"
#include "qlayers_export.h"

QLAYERS_NAMESPACE_BEGIN
struct QLAYERS_EXPORT QLThemeLineageData
{
	QString name;
	QString uuid;
	bool has_app_implementation_available = false;
};

class QLAYERS_EXPORT QLThemeLineageModel : public QAbstractTableModel
{
	Q_OBJECT

public:
	QLThemeLineageModel(QObject* parent = nullptr);

	void append(const QLThemeLineageData& lineage_data);

	void clear();

	virtual int columnCount(const QModelIndex& parent = QModelIndex()) const override;

	virtual QVariant data(
		const QModelIndex& index, int role) const override;

	virtual QVariant headerData(
		int section, Qt::Orientation orientation, int role) const override;

	virtual int rowCount(const QModelIndex& parent = QModelIndex()) const override;

private:
	QList<QLThemeLineageData> m_lineage_data{ QList<QLThemeLineageData>() };
};
QLAYERS_NAMESPACE_END

#endif // QLTHEMELINEAGEMODEL_H  

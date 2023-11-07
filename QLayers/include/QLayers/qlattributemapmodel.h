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

#ifndef QLATTRIBUTEMAPMODEL_H
#define QLATTRIBUTEMAPMODEL_H

#include <QAbstractItemModel>
#include <QModelIndex>
#include <QVariant>

#include <Layers/lattribute.h>

#include "qlayers_global.h"
#include "qlayers_export.h"

#include "qlattributemapitem.h"

QLAYERS_NAMESPACE_BEGIN
class QLAttributeMapModel : public QAbstractItemModel
{
	Q_OBJECT

public:
	QLAttributeMapModel(QObject* parent = nullptr);

	~QLAttributeMapModel();

	virtual int columnCount(const QModelIndex& parent = QModelIndex()) const override;

	virtual QVariant data(const QModelIndex& index, int role) const override;

	virtual QModelIndex index(int row, int column,
		const QModelIndex& parent = QModelIndex()) const override;

	virtual QModelIndex parent(const QModelIndex& index) const override;

	virtual int rowCount(const QModelIndex& parent = QModelIndex()) const override;

	void set_attributes(
		Layers::LAttributeMap attributes, const QStringList& filter_paths);

private:
	QLAttributeMapItem* init_item(
		Layers::LAttribute* attribute, const QStringList& filter_paths,
		QLAttributeMapItem* parent = nullptr);

	QLAttributeMapItem* get_item(const QModelIndex& index) const;

	QLAttributeMapItem* m_root_item{ nullptr };
};
QLAYERS_NAMESPACE_END

#endif // QLATTRIBUTEMAPMODEL_H

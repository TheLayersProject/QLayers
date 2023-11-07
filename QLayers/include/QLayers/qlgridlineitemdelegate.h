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

#ifndef QLGRIDLINEITEMDELEGATE_H
#define QLGRIDLINEITEMDELEGATE_H

#include <QStyledItemDelegate>

#include <Layers/lattribute.h>

#include "qlayers_global.h"
#include "qlayers_export.h"

#include "qlthemeable.h"

QLAYERS_NAMESPACE_BEGIN
class QLAYERS_EXPORT QLGridlineItemDelegate :
	public QStyledItemDelegate, public QLThemeable
{
	Q_OBJECT

signals:
	void changed();

public:
	QLGridlineItemDelegate(QObject* parent = nullptr);

	Layers::LAttribute* grid_fill() const;

	Layers::LAttribute* grid_thickness() const;

	virtual void paint(QPainter* painter,
		const QStyleOptionViewItem& option,
		const QModelIndex& index) const override;

	using QStyledItemDelegate::sizeHint;
	using QStyledItemDelegate::createEditor;
	using QStyledItemDelegate::setEditorData;
	using QStyledItemDelegate::setModelData;
	using QStyledItemDelegate::updateEditorGeometry;

private:
	Layers::LAttribute* m_grid_fill{
		new Layers::LAttribute("Grid.Fill", "#808080", this) };

	Layers::LAttribute* m_grid_thickness{
		new Layers::LAttribute("Grid.Thickness", 3.0, this) };
};
QLAYERS_NAMESPACE_END

#endif // QLGRIDLINEITEMDELEGATE_H  

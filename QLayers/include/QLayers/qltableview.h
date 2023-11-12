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

#ifndef QLTABLEVIEW_H
#define QLTABLEVIEW_H

#include <QHeaderView>
#include <QTableView>
#include <QStyledItemDelegate>

#include <Layers/lattribute.h>

#include "qlayers_global.h"
#include "qlayers_export.h"

#include "qlsvgrenderer.h"
#include "qlthemeable.h"

QLAYERS_NAMESPACE_BEGIN
class QLAYERS_EXPORT QLTableView : public QTableView, public QLThemeable
{
	Q_OBJECT

public:
	QLTableView(QWidget* parent = nullptr);

	virtual QList<QLThemeable*> child_qlthemeables(
		Qt::FindChildOptions options = Qt::FindDirectChildrenOnly) override;

	void setItemDelegate(QAbstractItemDelegate* item_delegate);

	virtual void update() override;

	void update_height();

private:
	//void init_attributes();

	Layers::LAttribute* m_border_fill
		{ new Layers::LAttribute("Border.Fill", "#a0a0a4", this) };

	Layers::LAttribute* m_border_thickness
		{ new Layers::LAttribute("Border.Thickness", 3.0, this) };

	Layers::LAttribute* m_corner_radii_bottom_left
		{ new Layers::LAttribute("Corner Radii.Bottom Left", 5.0, this) };

	Layers::LAttribute* m_corner_radii_bottom_right
		{ new Layers::LAttribute("Corner Radii.Bottom Right", 5.0, this) };

	Layers::LAttribute* m_corner_radii_top_left
		{ new Layers::LAttribute("Corner Radii.Top Left", 5.0, this) };

	Layers::LAttribute* m_corner_radii_top_right
		{ new Layers::LAttribute("Corner Radii.Top Right", 5.0, this) };

	Layers::LAttribute* m_fill
		{ new Layers::LAttribute("Fill", "#ffffff", this) };

	Layers::LAttribute* m_item_fill
		{ new Layers::LAttribute("Item Fill", "#ffffff", this) };

	QAbstractItemDelegate* m_table_delegate{ nullptr };

	Layers::LAttribute* m_text_color
		{ new Layers::LAttribute("Text Color", "#000000", this) };

	int m_visible_row_limit{ 3 };
};
QLAYERS_NAMESPACE_END

#endif // QLTABLEVIEW_H

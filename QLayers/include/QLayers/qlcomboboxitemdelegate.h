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

#ifndef QLCOMBOBOXITEMDELEGATE_H
#define QLCOMBOBOXITEMDELEGATE_H

#include <QPainterPath>
#include <QStyledItemDelegate>

#include <Layers/lattribute.h>

#include "qlayers_global.h"
#include "qlayers_export.h"

#include "qlthemeable.h"
#include "qlstatepool.h"

QLAYERS_NAMESPACE_BEGIN
class QLAYERS_EXPORT QLComboBoxItemDelegate :
	public QStyledItemDelegate, public QLThemeable
{
	Q_OBJECT

public:
	QLComboBoxItemDelegate(QObject* parent = nullptr);

	QPainterPath background_path(
		const QStyleOptionViewItem& option,
		const QModelIndex& index) const;

	Layers::LAttribute* corner_radius() const;

	Layers::LAttribute* fill() const;

	virtual void paint(QPainter* painter,
		const QStyleOptionViewItem& option,
		const QModelIndex& index) const override;

	void set_is_above_control(bool condition = true);

	Layers::LAttribute* text_color() const;

protected:
	Layers::LAttribute* m_corner_radius
		{ new Layers::LAttribute("Corner Radius", 4.0, this) };

	Layers::LAttribute* m_fill
		{ new Layers::LAttribute("Fill", "#27272e", this)};

	Layers::LAttribute* m_text_color
		{ new Layers::LAttribute("Text Color", "#e1e1e1", this) };

private:
	void init_attributes();

	bool m_is_above_control{ false };

	QLStatePool* m_select_states{
		new QLStatePool("Status", { "Selected", "Unselected" }) };
};
QLAYERS_NAMESPACE_END

#endif // QLCOMBOBOXITEMDELEGATE_H  

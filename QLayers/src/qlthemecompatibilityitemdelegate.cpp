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

#include <QLayers/qlthemecompatibilityitemdelegate.h>

#include <QPainter>

using QLayers::QLSvgRenderer;
using QLayers::QLThemeCompatibilityItemDelegate;

QLThemeCompatibilityItemDelegate::QLThemeCompatibilityItemDelegate(QObject* parent) :
	QLGridlineItemDelegate(parent)
{
	m_check_svg->set_object_name("Checkmark Svg");
}

void QLThemeCompatibilityItemDelegate::paint(
	QPainter* painter,
	const QStyleOptionViewItem& option,
	const QModelIndex& index) const
{
	QLGridlineItemDelegate::paint(painter, option, index);

	if (index.column() == index.model()->columnCount() - 1)
	{
		if (index.data(Qt::DecorationRole).toBool())
		{
			int centered_x = option.rect.x() + (option.rect.width() / 2) - 10;
			int centered_y = option.rect.y() + (option.rect.height() / 2) - 10;

			m_check_svg->render(painter,
				QRectF(centered_x, centered_y, 20, 15));
		}
	}
}

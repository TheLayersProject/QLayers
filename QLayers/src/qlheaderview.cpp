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

#include <QLayers/qlheaderview.h>

#include <QPainter>

#include <Layers/lstring.h>

using Layers::LString;

using QLayers::QLHeaderView;

QLHeaderView::QLHeaderView(Qt::Orientation orientation, QWidget* parent) :
	QHeaderView(orientation, parent)
{
	update();

	if (orientation == Qt::Horizontal)
		set_object_name("Horizontal Header");
	else
		set_object_name("Vertical Header");
}

void QLHeaderView::update()
{
	setStyleSheet(
		"QHeaderView {"
		"background: " +
			QString::fromStdString(m_fill->as<LString>().c_str()) + ";"
		"border-top-left-radius: "
			+ QString::number(m_corner_radii_top_left->as<double>()) + "px;"
		"border-top-right-radius: "
			+ QString::number(m_corner_radii_top_right->as<double>()) + "px;"
		"border-bottom-left-radius: "
			+ QString::number(m_corner_radii_bottom_left->as<double>()) + "px;"
		"border-bottom-right-radius: "
			+ QString::number(m_corner_radii_bottom_right->as<double>()) + "px;"
		"color: " +
			QString::fromStdString(m_text_color->as<LString>().c_str()) + ";"
		"}"

		"QHeaderView::section {"
		"background: transparent;"
		"}"
	);

	QWidget::update();
}

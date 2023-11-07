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

#include <QLayers/qlattributemapview.h>

#include <Layers/lstring.h>

using Layers::LAttribute;
using Layers::LAttributeMap;
using Layers::LString;

using QLayers::QLAttributeMapView;
using QLayers::QLThemeable;

QLAttributeMapView::QLAttributeMapView(QWidget* parent) :
	QTreeView(parent)
{
	set_object_name("Attribute Map View");

	setHeaderHidden(true);
	setHorizontalScrollBar(m_horizontal_scrollbar);
	setModel(m_model);
	setVerticalScrollBar(m_vertical_scrollbar);

	m_horizontal_scrollbar->set_object_name("Horizontal ScrollBar");

	m_vertical_scrollbar->set_object_name("Vertical ScrollBar");

	update();
}

QList<QLThemeable*> QLAttributeMapView::q_child_themeables(Qt::FindChildOptions options)
{
	QList<QLThemeable*> q_child_themeables = QLThemeable::q_child_themeables(options);

	q_child_themeables.append(m_horizontal_scrollbar);
	q_child_themeables.append(m_vertical_scrollbar);

	return q_child_themeables;
}

void QLAttributeMapView::set_attributes(
	LAttributeMap attributes, const QStringList& filter_paths)
{
	m_model->set_attributes(attributes, filter_paths);
}

void QLAttributeMapView::update()
{
	QString style_sheet =
		"QAbstractItemView {"
		"background: " +
			QString::fromStdString(m_fill->as<LString>().c_str()) + ";"
		"border: none;"
		"}"

		"QAbstractItemView::item {"
		"height: 40px;"
		"color: " +
			QString::fromStdString(m_text_color->as<LString>().c_str()) + ";"
		"}";

	setStyleSheet(
		style_sheet
	);

	QWidget::update();
}

void QLAttributeMapView::selectionChanged(
	const QItemSelection& selected, const QItemSelection& deselected)
{
	QModelIndexList indexes = selected.indexes();

	if (!indexes.isEmpty())
		emit selected_map_item_changed(
			indexes.first().data(Qt::UserRole).value<LAttribute*>());
}

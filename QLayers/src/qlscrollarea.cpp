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

#include <QLayers/qlscrollarea.h>

#include <QEvent>

using QLayers::QLScrollArea;
using QLayers::QLScrollBar;
using QLayers::QLThemeable;

QLScrollArea::QLScrollArea(QWidget* parent) : QScrollArea(parent)
{
	installEventFilter(this);
	setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	
	setWidgetResizable(true);
	setStyleSheet(
		"QScrollArea { background-color:transparent; border:none; }");
	setHorizontalScrollBar(m_horizontal_scrollbar);
	setVerticalScrollBar(m_vertical_scrollbar);

	m_horizontal_scrollbar->set_object_name("Horizontal ScrollBar");

	m_vertical_scrollbar->set_object_name("Vertical ScrollBar");
}

QList<QLThemeable*> QLScrollArea::q_child_themeables(
	Qt::FindChildOptions options)
{
	QList<QLThemeable*> q_child_themeables =
		QLThemeable::q_child_themeables(options);

	q_child_themeables.append(m_horizontal_scrollbar);
	q_child_themeables.append(m_vertical_scrollbar);

	if (QLThemeable* themeable_widget = dynamic_cast<QLThemeable*>(widget()))
	{
		q_child_themeables.append(themeable_widget);

		if (options == Qt::FindChildrenRecursively)
		{
			QList<QObject*> widget_child_objects =
				widget()->findChildren<QObject*>(options);

			for (QObject* widget_child_object : widget_child_objects)
				if (QLThemeable* child_themeable =
					dynamic_cast<QLThemeable*>(widget_child_object))
				{
					q_child_themeables.append(child_themeable);
				}
		}
	}

	return q_child_themeables;
}

void QLScrollArea::setWidget(QWidget* widget)
{
	QScrollArea::setWidget(widget);

	widget->setStyleSheet("background-color:transparent;");
}

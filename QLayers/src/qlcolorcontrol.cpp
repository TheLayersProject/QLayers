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

#include <QLayers/qlcolorcontrol.h>

#include <QMouseEvent>

#include <Layers/lstring.h>

#include <QLayers/qlapplication.h>
#include <QLayers/qlcolordialog.h>

using Layers::LString;

using QLayers::QLColorControl;

QLColorControl::QLColorControl(QWidget* parent) : QLWidget(parent)
{
	init_attributes();

	setFixedSize(40, 40);
	installEventFilter(this);
}

QLColorControl::~QLColorControl()
{
	delete m_fill;
}

void QLColorControl::click()
{
	QLColorDialog color_dialog;
	color_dialog.apply_theme_item(
		activeTheme()->find_item(color_dialog.path()));
	color_dialog.color()->set_value(fill()->as<LString>());

	center(&color_dialog, window());

	if (color_dialog.exec())
	{
		fill()->set_value(color_dialog.color()->as<LString>());

		emit color_changed();
	}

	open_on_release = false;
}

void QLColorControl::disable_clicking(bool cond)
{
	clicking_disabled = cond;
}

bool QLColorControl::eventFilter(QObject* object, QEvent* event)
{
	if (event->type() == QEvent::MouseButtonPress)
	{
		QMouseEvent* mouse_event = static_cast<QMouseEvent*>(event);

		if (mouse_event->button() & Qt::LeftButton)
		{
			open_on_release = true;
		}
	}
	else if (event->type() == QEvent::MouseButtonRelease &&
		open_on_release && !clicking_disabled)
	{
		QMouseEvent* mouse_event = static_cast<QMouseEvent*>(event);

		if (mouse_event->button() & Qt::LeftButton)
		{
			click();
		}
	}
	else if (open_on_release && event->type() == QEvent::MouseMove)
	{
		open_on_release = false;
	}

	return false;
}

void QLColorControl::init_attributes()
{
	// Remove control attribute
	m_fill->set_parent(nullptr);

	m_border_fill->set_value("#D6D6D6");
	m_border_thickness->set_value(2.0);
	m_corner_radii_top_left->set_value(5.0);
	m_corner_radii_top_right->set_value(5.0);
	m_corner_radii_bottom_left->set_value(5.0);
	m_corner_radii_bottom_right->set_value(5.0);
	m_margins_left->set_value(8.0);
	m_margins_top->set_value(8.0);
	m_margins_right->set_value(8.0);
	m_margins_bottom->set_value(8.0);
}

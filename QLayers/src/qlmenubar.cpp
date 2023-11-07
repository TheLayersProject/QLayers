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

#include <QLayers/qlmenubar.h>

#include <QStyleOptionMenuItem>

#include <Layers/lstring.h>

using Layers::LAttribute;
using Layers::LString;

using QLayers::QLMenuBar;

QLMenuBar::QLMenuBar(QWidget* parent) : QMenuBar(parent)
{
	update();

	QFont f = font();
	f.setPointSize(12);
	setFont(f);
}

LAttribute* QLMenuBar::selected_text_color() const
{
	return m_selected_text_color;
}

LAttribute* QLMenuBar::text_color() const
{
	return m_text_color;
}

void QLMenuBar::update()
{
	setStyleSheet(build_stylesheet());
}

QString QLMenuBar::build_stylesheet()
{
	return
		"QMenuBar {"
		"background: transparent;"
		"color: " +
			QString::fromStdString(m_text_color->as<LString>().c_str()) + ";"
		"}"

		"QMenuBar::item {"
		"spacing: 3px;"
		"padding: 1px 4px;"
		"background: transparent;"
		"color: " +
			QString::fromStdString(m_text_color->as<LString>().c_str()) + ";"
		"}"

		"QMenuBar::item:selected {"
		"background: transparent;"
		"color: " +
			QString::fromStdString(
				m_selected_text_color->as<LString>().c_str()) + ";"
		"}"

		"QMenuBar::item:pressed {"
		"background: transparent;"
		"}";
}

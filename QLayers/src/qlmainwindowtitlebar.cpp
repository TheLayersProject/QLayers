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

#include "qlmainwindowtitlebar.h"

using QLayers::QLButton;
using QLayers::QLTab;
using QLayers::QLTabBar;
using QLayers::LMainWindowTitlebar;

LMainWindowTitlebar::LMainWindowTitlebar(QWidget* parent) :
	QLWidget(parent)
{
	setFixedHeight(40);

	set_object_name("Titlebar");

	m_menu_tab_bar->set_object_name("Menu Tab Bar");

	m_settings_button->set_object_name("Settings Button");

	m_minimize_button->set_object_name("Minimize Button");

	m_maximize_button->set_object_name("Maximize Button");

	m_exit_button->set_object_name("Exit Button");

	init_layout();
}

QLTabBar* LMainWindowTitlebar::menu_tab_bar() const
{
	return m_menu_tab_bar;
}

QLButton* LMainWindowTitlebar::settings_button() const
{
	return m_settings_button;
}

QLButton* LMainWindowTitlebar::minimize_button() const
{
	return m_minimize_button;
}

QLButton* LMainWindowTitlebar::maximize_button() const
{
	return m_maximize_button;
}

QLButton* LMainWindowTitlebar::exit_button() const
{
	return m_exit_button;
}

void LMainWindowTitlebar::init_layout()
{
	// Main Layout
	main_layout->setContentsMargins(0, 0, 0, 0);
	main_layout->setSpacing(0);
	main_layout->addWidget(m_menu_tab_bar);
	main_layout->addStretch();
	main_layout->addWidget(m_settings_button);
	main_layout->addWidget(m_minimize_button);
	main_layout->addWidget(m_maximize_button);
	main_layout->addWidget(m_exit_button);

	setLayout(main_layout);
}

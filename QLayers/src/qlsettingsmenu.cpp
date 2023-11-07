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

#include "qlsettingsmenu.h"

#include <QMouseEvent>

#include "qlsettingstab.h"
#include "qlthemeswidget.h"

using QLayers::QLGraphic;
using QLayers::QLSettingsMenu;
using QLayers::QLThemesWidget;

QLSettingsMenu::QLSettingsMenu(QWidget* parent) :
	m_themes_widget{ new QLThemesWidget },
	QLWidget(parent)
{
	init_layout();
	setMouseTracking(true);
	set_object_name("Settings Menu");

	//m_themes_settings_panel->hide();
	m_themes_widget->setMouseTracking(true);
	
	// Add Themes Settings Tab
	add_settings_tab(QLGraphic(":/images/themes_icon.svg", QSize(25, 25)), "Themes");
	m_settings_tabs.last()->set_object_name("Themes Settings Tab");
	//connect(m_settings_tabs.last(), &QLSettingsTab::clicked, [this] { m_app_preferences_settings_panel->hide(); m_themes_settings_panel->show(); });

	m_settings_tabs.first()->select_states()->set_state("Selected");

	m_sidebar->setFixedWidth(recommended_minimum_tab_width());
	m_sidebar->setMouseTracking(true);
	m_sidebar->set_object_name("Sidebar");
	m_sidebar->fill()->set_value("#c0c0c0");
}

void QLSettingsMenu::add_settings_tab(const QLGraphic& icon, const QString& label_text)
{
	QLSettingsTab* settings_tab = new QLSettingsTab(icon, label_text);

	for (QLSettingsTab* st : m_settings_tabs)
	{
		connect(st, &QLSettingsTab::clicked, [settings_tab]
		{
			settings_tab->select_states()->set_state("Unselected");
			settings_tab->QLThemeable::update();
		});
		connect(settings_tab, &QLSettingsTab::clicked, [st]
		{
			st->select_states()->set_state("Unselected");
			st->QLThemeable::update();
		});
	}

	m_settings_tabs.append(settings_tab);

	int active_tab_index = m_settings_tabs.indexOf(settings_tab);

	m_sidebar_layout->insertWidget(m_sidebar_layout->count() - 1, settings_tab);
}

int QLSettingsMenu::largest_tab_index() const
{
	int tab_index = -1;

	for (QLSettingsTab* st : m_settings_tabs)
	{
		int tab_rec_min_width = st->recommended_minimum_width();
		if (tab_rec_min_width > tab_index)
		{
			tab_index = m_settings_tabs.indexOf(st);
		}
	}

	return tab_index;
}

int QLSettingsMenu::recommended_minimum_tab_width() const
{
	int tab_width = 0;

	for (QLSettingsTab* st : m_settings_tabs)
	{
		int tab_rec_min_width = st->recommended_minimum_width();
		if (tab_rec_min_width > tab_width)
		{
			tab_width = tab_rec_min_width;
		}
	}

	return tab_width;
}

QLThemesWidget* QLSettingsMenu::themes_widget() const
{
	return m_themes_widget;
}

void QLSettingsMenu::init_layout()
{
	// Sidebar

	m_sidebar_layout->setContentsMargins(0, 0, 0, 0);
	m_sidebar_layout->setSpacing(0);
	m_sidebar_layout->addStretch();

	m_sidebar->setLayout(m_sidebar_layout);

	// Main Layout

	QHBoxLayout* main_layout = new QHBoxLayout;

	main_layout->setContentsMargins(0, 0, 0, 0);
	main_layout->setSpacing(0);
	main_layout->addWidget(m_sidebar);
	main_layout->addWidget(m_themes_widget);

	setLayout(main_layout);
}

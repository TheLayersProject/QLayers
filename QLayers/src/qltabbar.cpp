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

#include <QLayers/qltabbar.h>

#include <QEvent>
#include <QResizeEvent>

using QLayers::QLTab;
using QLayers::QLTabBar;

QLTabBar::QLTabBar(QWidget* parent) : QLWidget(parent)
{
	init_layout();
}

void QLTabBar::add_tab(const QLGraphic& icon, const QString& text)
{
	_add_tab(new QLTab(icon, text));
}

void QLTabBar::add_tab(const QString& text)
{
	_add_tab(new QLTab(text));
}

int QLTabBar::current_index() const
{
	return m_current_index;
}

void QLTabBar::set_current_index(int index)
{
	if (index != m_current_index)
	{
		int old_index = m_current_index;
		m_current_index = index;
		emit index_changed(old_index, index);

		if (old_index != -1)
			m_tabs[old_index]->status_states()->set_state("Inactive");

		if (index != -1)
			m_tabs[index]->status_states()->set_state("Active");
	}
}

QList<QLTab*> QLTabBar::tabs() const
{
	return m_tabs;
}

void QLTabBar::_add_tab(QLTab* tab)
{
	tab->set_object_name("Tabs");

	if (current_theme_item())
		tab->apply_theme_item(
			current_theme_item()->find_item(
				tab->objectName().toStdString().c_str()));

	m_tabs.append(tab);
	m_tab_layout->addWidget(tab);

	connect(tab, &QLTab::clicked, [this, tab]
		{ set_current_index(m_tabs.indexOf(tab)); });

	connect(tab, &QLTab::closed, [this, tab]
		{
			int remove_index = m_tabs.indexOf(tab);

			if (m_current_index == remove_index)
			{
				if (remove_index < m_tabs.count() - 1)
					set_current_index(remove_index + 1);
				else
					set_current_index(remove_index - 1);
			}

			m_tabs.takeAt(remove_index)->deleteLater();

			if (m_current_index > remove_index)
				m_current_index--;

			emit tab_closed(remove_index);
		});
}


void QLTabBar::init_layout()
{
	m_tab_layout->setContentsMargins(0, 0, 0, 0);
	m_tab_layout->setSpacing(0);

	setLayout(m_tab_layout);
}

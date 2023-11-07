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

#ifndef QLSETTINGSMENU_H
#define QLSETTINGSMENU_H

#include <QHBoxLayout>
#include <QVBoxLayout>

#include <QLayers/qlayers_global.h>

#include <QLayers/qlgraphic.h>
#include <QLayers/qlwidget.h>

QLAYERS_NAMESPACE_BEGIN

class QLLabel;
class QLSettingsTab;
class QLThemesWidget;

class QLSettingsMenu : public QLWidget
{
	Q_OBJECT

public:
	QLSettingsMenu(QWidget* parent = nullptr);

	void add_settings_tab(const QLGraphic& icon, const QString& label_text);

	int largest_tab_index() const;

	int recommended_minimum_tab_width() const;

	QLThemesWidget* themes_widget() const;

private:
	void init_layout();

	QVBoxLayout* m_sidebar_layout = new QVBoxLayout;

	QList<QLSettingsTab*> m_settings_tabs;

	QLWidget* m_sidebar{ new QLWidget };

	QLThemesWidget* m_themes_widget;
};
QLAYERS_NAMESPACE_END

#endif // QLSETTINGSMENU_H

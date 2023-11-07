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

#ifndef QLMAINWINDOWTITLEBAR_H
#define QLMAINWINDOWTITLEBAR_H

#include <QLayers/qlayers_global.h>

#include <QLayers/qltabbar.h>

QLAYERS_NAMESPACE_BEGIN
class LMainWindowTitlebar : public QLWidget
{
	Q_OBJECT

public:
	LMainWindowTitlebar(QWidget* parent = nullptr);

	QLTabBar* menu_tab_bar() const;

	QLButton* settings_button() const;
	QLButton* minimize_button() const;
	QLButton* maximize_button() const;
	QLButton* exit_button() const;

protected:
	void init_layout();

private:
	QHBoxLayout* main_layout = new QHBoxLayout;

	QLButton* m_settings_button{
		new QLButton(QLGraphic(":/images/settings.svg", QSize(20, 20))) };

	QLButton* m_minimize_button{
		new QLButton(QLGraphic(":/images/minimize.svg", QSize(20, 20))) };

	QLButton* m_maximize_button{
		new QLButton(QLGraphic(":/images/maximize.svg", QSize(20, 20))) };

	QLButton* m_exit_button{
		new QLButton(QLGraphic(":/images/exit.svg", QSize(20, 20))) };

	QLTabBar* m_menu_tab_bar{ new QLTabBar };
};
QLAYERS_NAMESPACE_END

#endif // QLMAINWINDOWTITLEBAR_H

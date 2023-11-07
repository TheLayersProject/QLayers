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

#ifndef QLTHEMESWIDGET_H
#define QLTHEMESWIDGET_H

#include <QLayers/qlayers_global.h>

#include <QLayers/qlbutton.h>
#include <QLayers/qlthemecombobox.h>

QLAYERS_NAMESPACE_BEGIN
class QLThemeEditorDialog;

class QLThemesWidget : public QLWidget
{
	Q_OBJECT

public:
	QLThemesWidget(QWidget* parent = nullptr);
	~QLThemesWidget();

	void handle_theme_buttons_visibility();

	QLButton* customize_theme_button() const;

	QLButton* new_theme_button() const;

	QLThemeComboBox* theme_combobox() const;

	void show_custom_theme_buttons(bool cond = true);

private:
	void init_layout();

	QLLabel* m_theme_label{ new QLLabel("Theme") };

	QLThemeComboBox* m_theme_combobox{ new QLThemeComboBox };

	QLButton* m_new_theme_button{
		new QLButton(QLGraphic(":/images/new_theme.svg", QSize(20, 20))) };
		
	QLButton* m_customize_theme_button{
		new QLButton(QLGraphic(":/images/customize_theme.svg", QSize(20, 20))) };
		
	QLButton* m_delete_theme_button{
		new QLButton(QLGraphic(":/images/delete_theme.svg", QSize(17, 20))) };
		
	QLButton* m_theme_info_button{
		new QLButton(QLGraphic(":/images/info_theme.svg", QSize(20, 20))) };

	QLWidget* m_separator_1{ new QLWidget };
	QLWidget* m_separator_2{ new QLWidget };
	QLWidget* m_spacer_1{ new QLWidget };
	QLWidget* m_spacer_2{ new QLWidget };

	QMetaObject::Connection m_theme_buttons_handler_connection;

	QLThemeEditorDialog* m_theme_editor_dialog{ nullptr };
};
QLAYERS_NAMESPACE_END

#endif // QLTHEMESWIDGET_H

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

#include "qlthemeswidget.h"

#include <QLayers/qlapplication.h>
#include <QLayers/qlthemeeditordialog.h>

using Layers::LTheme;

using QLayers::QLButton;
using QLayers::QLThemeComboBox;
using QLayers::QLThemesWidget;

QLThemesWidget::QLThemesWidget(QWidget* parent) : QLWidget(parent)
{
	set_object_name("Themes Widget");

	m_theme_label->set_object_name("Theme Label");
	m_theme_label->set_font_size(15);

	m_theme_combobox->set_object_name("Theme Combobox");

	for (LTheme* theme : qLayersApp->themes())
		m_theme_combobox->add_theme(theme);

	for (int i = 0; i < m_theme_combobox->count(); i++)
		if (m_theme_combobox->itemData(i).value<LTheme*>() == activeTheme())
		{
			m_theme_combobox->setCurrentIndex(i);
			break;
		}

	connect(qLayersApp, &QLApplication::theme_added,
		[this](LTheme* theme)
		{
			m_theme_combobox->add_theme(theme, true);
		});

	connect(m_theme_combobox, &QLThemeComboBox::currentIndexChanged, [this]
	{
		qLayersApp->apply_theme(
			m_theme_combobox->currentData().value<LTheme*>());
	});

	m_theme_buttons_handler_connection =
		connect(qLayersApp, &QLApplication::active_theme_changed, [this]
			{
				handle_theme_buttons_visibility();
			});

	if (!activeTheme()->editable())
		show_custom_theme_buttons(false);

	m_new_theme_button->set_object_name("New Theme Button");

	m_customize_theme_button->set_object_name("Customize Theme Button");

	connect(m_customize_theme_button, &QLButton::clicked,
		[this]
		{
			if (!m_theme_editor_dialog)
			{
				m_theme_editor_dialog = new QLThemeEditorDialog;

				center(m_theme_editor_dialog, window());

				m_theme_editor_dialog->apply_theme_item(
					activeTheme()->find_item(
						m_theme_editor_dialog->path()));

				connect(m_theme_editor_dialog, &QDialog::finished,
					[this]
					{
						m_theme_editor_dialog->deleteLater();
						m_theme_editor_dialog = nullptr;
					});
			}

			m_theme_editor_dialog->show();
			m_theme_editor_dialog->raise();
		});

	m_delete_theme_button->set_object_name("Delete Theme Button");

	m_theme_info_button->set_object_name("Theme Info Button");

	m_separator_1->set_object_name("Separators");
	m_separator_1->setFixedSize(1, 30);

	m_separator_2->set_object_name("Separators");
	m_separator_2->setFixedSize(1, 30);

	m_spacer_1->setFixedWidth(12);
	m_spacer_1->fill()->set_link_attribute(this->fill());

	m_spacer_2->setFixedWidth(12);
	m_spacer_2->fill()->set_link_attribute(this->fill());

	init_layout();
}

QLThemesWidget::~QLThemesWidget()
{
	QObject::disconnect(m_theme_buttons_handler_connection);
}

void QLThemesWidget::handle_theme_buttons_visibility()
{
	if (activeTheme()->editable())
		show_custom_theme_buttons();
	else
		show_custom_theme_buttons(false);
}

QLButton* QLThemesWidget::customize_theme_button() const
{
	return m_customize_theme_button;
}

QLButton* QLThemesWidget::new_theme_button() const
{
	return m_new_theme_button;
}

QLThemeComboBox* QLThemesWidget::theme_combobox() const
{
	return m_theme_combobox;
}

void QLThemesWidget::show_custom_theme_buttons(bool cond)
{
	if (cond)
	{
		m_customize_theme_button->show();
		m_delete_theme_button->show();
		m_separator_2->show();
		m_spacer_1->show();
		m_spacer_2->show();
	}
	else
	{
		m_customize_theme_button->hide();
		m_delete_theme_button->hide();
		m_separator_2->hide();
		m_spacer_1->hide();
		m_spacer_2->hide();
	}
}

void QLThemesWidget::init_layout()
{
	QHBoxLayout* theme_buttons_hbox = new QHBoxLayout;

	theme_buttons_hbox->setContentsMargins(0, 5, 0, 0);
	theme_buttons_hbox->setSpacing(0);
	theme_buttons_hbox->addWidget(m_new_theme_button);
	theme_buttons_hbox->addSpacing(12);
	theme_buttons_hbox->addWidget(m_separator_1);
	theme_buttons_hbox->addSpacing(12);
	theme_buttons_hbox->addWidget(m_customize_theme_button);
	theme_buttons_hbox->addWidget(m_delete_theme_button);
	theme_buttons_hbox->addWidget(m_spacer_1);
	theme_buttons_hbox->addWidget(m_separator_2);
	theme_buttons_hbox->addWidget(m_spacer_2);
	theme_buttons_hbox->addWidget(m_theme_info_button);
	theme_buttons_hbox->addStretch();

	QVBoxLayout* main_layout = new QVBoxLayout;

	main_layout->setContentsMargins(32, 32, 0, 0);
	main_layout->addWidget(m_theme_label);
	main_layout->addWidget(m_theme_combobox);
	main_layout->addLayout(theme_buttons_hbox);
	main_layout->addStretch();

	setLayout(main_layout);

	main_layout->activate();
}

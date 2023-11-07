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

#include "qlnewlinkwidget.h"

#include <Layers/lstring.h>
#include <Layers/lthemeitem.h>

using Layers::LAttribute;
using Layers::LString;
using Layers::LThemeItem;

using QLayers::QLNewLinkWidget;

QLNewLinkWidget::QLNewLinkWidget(LAttribute* attr, QWidget* parent) :
	m_attr{ attr },
	QLWidget(parent)
{
	init_layout();
	set_object_name("New Link Widget");
	setFixedHeight(357);

	connect(m_theme_view, &QLThemeView::selected_theme_item_changed,
		[this](LThemeItem* theme_item)
		{
			QStringList filter_paths = { QString::fromStdString(m_attr->path().c_str()) };
			for (LAttribute* dependent_attr : m_attr->dependent_attributes(true))
				filter_paths.append(QString::fromStdString(dependent_attr->path().c_str()));

			m_attr_map_view->set_attributes(
				theme_item->attributes(m_attr->type_index()), filter_paths);

			m_selected_link_attr = nullptr;

			m_path_editor->set_text(QString::fromStdString(theme_item->path().c_str()) + "/");
			m_apply_link_button->set_disabled();
		});

	connect(m_attr_map_view, &QLAttributeMapView::selected_map_item_changed,
		[this](LAttribute* attr)
		{
			m_selected_link_attr = attr;

			m_path_editor->set_text(QString::fromStdString(attr->path().c_str()));
			m_apply_link_button->set_disabled(false);
		});

	m_splitter->addWidget(m_theme_view);
	m_splitter->addWidget(m_attr_map_view);

	m_path_editor->set_object_name("Path Editor");
	m_path_editor->set_font_size_f(10.5);
	m_path_editor->setFixedHeight(30);
	m_path_editor->setSizePolicy(
		QSizePolicy::Minimum, QSizePolicy::Fixed);

	connect(m_path_editor, &QLLineEditor::text_edited,
		[this](const QString& text)
		{
			m_apply_link_button->set_disabled();
		});

	m_apply_link_button->set_object_name("Apply Link Button");
	m_apply_link_button->set_font_size_f(10.5);
	m_apply_link_button->set_padding(6);
	m_apply_link_button->setFixedHeight(30);
	m_apply_link_button->setSizePolicy(
		QSizePolicy::Maximum, QSizePolicy::Fixed);
	m_apply_link_button->set_disabled();

	connect(m_apply_link_button, &QLButton::clicked,
		[this]
		{
			m_attr->set_link_path(m_path_editor->text()->as<LString>());
			m_attr->set_link_attribute(m_selected_link_attr);

			deleteLater();
		});

	m_cancel_button->set_object_name("Cancel Button");
	m_cancel_button->set_font_size_f(10.5);
	m_cancel_button->set_padding(6);
	m_cancel_button->setFixedHeight(30);
	m_cancel_button->setSizePolicy(
		QSizePolicy::Maximum, QSizePolicy::Fixed);

	connect(m_cancel_button, &QLButton::clicked,
		[this] { deleteLater(); });

	m_resizer->set_widget(this, 180, 1000);
}

void QLNewLinkWidget::init_layout()
{
	QHBoxLayout* m_controls_layout = new QHBoxLayout;
	m_controls_layout->addWidget(m_path_editor);
	m_controls_layout->addWidget(m_apply_link_button);
	m_controls_layout->addWidget(m_cancel_button);
	m_controls_layout->setContentsMargins(0, 5, 0, 5);
	m_controls_layout->setSpacing(5);

	m_main_layout->addWidget(m_splitter);
	m_main_layout->addLayout(m_controls_layout);
	m_main_layout->addWidget(m_resizer);
	m_main_layout->setContentsMargins(5, 5, 5, 0);
	m_main_layout->setSpacing(0);

	setLayout(m_main_layout);
}

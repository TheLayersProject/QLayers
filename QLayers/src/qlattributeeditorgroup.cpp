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

#include <QLayers/qlattributeeditorgroup.h>

#include <QLayers/qlcalculate.h>

using QLayers::QLAttributeEditorGroup;

QLAttributeEditorGroup::QLAttributeEditorGroup(
	const QString& name, QWidget* parent
) :
	QLWidget(parent)
{
	init_attributes();

	m_label->setText(name);
	m_label->set_object_name("Label");
	m_label->set_font_size(12);

	m_collapse_button->set_object_name("Collapse Button");

	connect(m_collapse_button, &QLButton::clicked, [this] {
		if (m_collapsed)
			set_collapsed(false);
		else
			set_collapsed();
	});

	init_layout();
}

void QLAttributeEditorGroup::add_attribute_editor(
	QLAttributeEditor* attribute_editor)
{
	m_widgets_vbox->addWidget(attribute_editor);

	m_attribute_editors.append(attribute_editor);

	if (m_collapsed)
		attribute_editor->hide();
}

void QLAttributeEditorGroup::init_layout()
{
	QHBoxLayout* top_hbox = new QHBoxLayout;

	top_hbox->setContentsMargins(0, 0, 0, 0);
	top_hbox->setSpacing(0);
	top_hbox->addWidget(m_collapse_button);
	top_hbox->addWidget(m_label);
	top_hbox->addStretch();

	m_widgets_vbox->setContentsMargins(0, 0, 0, 0);
	m_widgets_vbox->setSpacing(3);

	QVBoxLayout* main_layout = new QVBoxLayout;

	main_layout->setContentsMargins(0, 0, 0, 0);
	main_layout->setSpacing(0);
	main_layout->addLayout(top_hbox);
	main_layout->addLayout(m_widgets_vbox);

	setLayout(main_layout);
}

void QLAttributeEditorGroup::set_collapsed(bool collapsed)
{
	if (collapsed)
	{
		m_widgets_vbox->setContentsMargins(0, 0, 0, 0);

		for (QLAttributeEditor* attribute_editor : m_attribute_editors)
			attribute_editor->hide();

		m_collapsed = true;
	}
	else
	{
		m_widgets_vbox->setContentsMargins(10, 0, 0, 10);

		for (QLAttributeEditor* attribute_editor : m_attribute_editors)
			attribute_editor->show();

		m_collapsed = false;
	}
}

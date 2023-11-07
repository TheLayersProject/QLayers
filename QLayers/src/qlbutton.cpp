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

#include <QLayers/qlbutton.h>

#include <QMouseEvent>

#include <QLayers/qlgraphic.h>

using QLayers::QLLabel;
using QLayers::QLButton;

QLButton::QLButton(const QLGraphic& graphic, const QString& text, QWidget* parent) :
	m_graphic_label{ new QLLabel(graphic) },
	m_text_label{ new QLLabel(text) },
	QLWidget(parent)
{
	init();
	
	m_corner_radii_top_left->set_value(7.0);
	m_corner_radii_top_right->set_value(7.0);
	m_corner_radii_bottom_left->set_value(7.0);
	m_corner_radii_bottom_right->set_value(7.0);
}

QLButton::QLButton(const QLGraphic& graphic, QWidget* parent) :
	m_graphic_label{ new QLLabel(graphic) },
	QLWidget(parent)
{
	init();
}

QLButton::QLButton(const QString& text, QWidget* parent) :
	m_text_label{ new QLLabel(text) },
	QLWidget(parent)
{
	init();

	m_corner_radii_top_left->set_value(7.0);
	m_corner_radii_top_right->set_value(7.0);
	m_corner_radii_bottom_left->set_value(7.0);
	m_corner_radii_bottom_right->set_value(7.0);
}

QLButton::QLButton(const QLGraphic& graphic, const QLGraphic& graphic_after, QWidget* parent) :
	m_graphic_label{ new QLLabel(graphic) },
	m_graphic_after_label{ new QLLabel(graphic_after) },
	QLWidget(parent)
{
	init();
}

bool QLButton::disabled() const
{
	return m_disabled;
}

QLLabel* QLButton::graphic_label() const
{
	return m_graphic_label;
}

void QLButton::set_disabled(bool cond)
{
	m_disabled = cond;

	if (m_disabled)
	{
		if (m_button_opacity->opacity() != 0.25)
			m_button_opacity->setOpacity(0.25);
	}
	else if (!m_disabled)
	{
		if (m_button_opacity->opacity() != 1.0)
			m_button_opacity->setOpacity(1.0);
	}
}

void QLButton::set_font_size(int size)
{
	if (m_text_label)
		m_text_label->set_font_size(size);
}

void QLButton::set_font_size_f(qreal size)
{
	if (m_text_label)
		m_text_label->set_font_size_f(size);
}

void QLButton::set_padding(int padding)
{
	main_layout->setContentsMargins(padding, padding, padding, padding);
}

void QLButton::set_padding(int left, int top, int right, int bottom)
{
	main_layout->setContentsMargins(left, top, right, bottom);
}

void QLButton::toggle_graphics()
{
	if (m_graphic_after_label)
	{
		if (m_graphic_label->isVisible())
		{
			m_graphic_label->hide();
			m_graphic_after_label->show();
		}
		else
		{
			m_graphic_label->show();
			m_graphic_after_label->hide();
		}
	}
}

bool QLButton::eventFilter(QObject* object, QEvent* event)
{
	if (event->type() == QEvent::MouseButtonPress || event->type() == QEvent::MouseButtonDblClick)
	{
		QMouseEvent* mouse_event = static_cast<QMouseEvent*>(event);

		if (mouse_event->button() & Qt::LeftButton)
		{
			if (!m_disabled)
				emit clicked();

			toggle_graphics();
		}
	}
	else if (event->type() == QEvent::Enter)
	{
		if (!m_disabled)
			m_select_states->set_state("Selected");
	}
	else if (event->type() == QEvent::Leave)
	{
		if (!m_disabled)
			m_select_states->set_state("Unselected");
	}

	QLWidget::eventFilter(object, event);

	return false;
}

void QLButton::init()
{
	init_layout();
	setMinimumSize(40, 40);
	installEventFilter(this);
	add_state_pool(m_select_states);

	m_select_states->set_state("Unselected");

	m_button_opacity->setOpacity(1.0);
	setGraphicsEffect(m_button_opacity);

	if (m_graphic_label)
	{
		m_graphic_label->setAlignment(Qt::AlignCenter);
		m_graphic_label->set_object_name("Graphic");

		m_graphic_label->graphic()->svg_renderer()->color()->set_value(
			"#808080");
		m_graphic_label->graphic()->svg_renderer()->color()->create_override(
			"Selected", "#c0c0c0");
	}

	if (m_graphic_after_label)
	{
		m_graphic_after_label->setAlignment(Qt::AlignCenter);
		m_graphic_after_label->set_object_name("Graphic After");
		m_graphic_after_label->hide();

		m_graphic_after_label->graphic()->svg_renderer()->color()->set_value(
			"#808080");
		m_graphic_after_label->graphic()->svg_renderer()->color()->create_override(
			"Selected", "#c0c0c0");
	}

	if (m_text_label)
		m_text_label->set_object_name("Text Label");
}

void QLButton::init_layout()
{
	if (m_graphic_label)
		main_layout->addWidget(m_graphic_label);

	if (m_graphic_after_label)
		main_layout->addWidget(m_graphic_after_label);

	if (m_text_label)
		main_layout->addWidget(m_text_label);

	setLayout(main_layout);
}

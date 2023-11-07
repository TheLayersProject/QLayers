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

#include <QLayers/qltab.h>

#include <QEvent>
#include <QMouseEvent>

#include <Layers/lstring.h>

using Layers::LString;

using QLayers::QLButton;
using QLayers::QLLabel;
using QLayers::QLStatePool;
using QLayers::QLTab;

QLTab::QLTab(const QLGraphic& icon, const QString& text, QWidget* parent) :
	m_icon_label{ new QLLabel(icon) },
	m_text_label{ new QLLabel(text) },
	QLWidget(parent)
{
	init();
}

QLTab::QLTab(const QString& text, QWidget* parent) :
	m_text_label{ new QLLabel(text) },
	QLWidget(parent)
{
	init();
}

QLButton* QLTab::close_button() const
{
	return m_close_button;
}

QLLabel* QLTab::icon_label() const
{
	return m_icon_label;
}

QLStatePool* QLTab::status_states() const
{
	return m_status_states;
}

QLLabel* QLTab::text_label() const
{
	return m_text_label;
}

bool QLTab::eventFilter(QObject* object, QEvent* event)
{
	if (event->type() == QEvent::MouseButtonPress &&
		!m_close_button->underMouse())
	{
		QMouseEvent* mouse_event = static_cast<QMouseEvent*>(event);

		if (mouse_event->button() & Qt::LeftButton)
		{
			emit clicked();
		}
	}

	QLWidget::eventFilter(object, event);

	return false;
}

void QLTab::init()
{
	add_state_pool(m_status_states);
	init_attributes();
	init_layout();
	installEventFilter(this);

	m_status_states->set_state("Inactive");

	if (m_icon_label)
	{
		m_icon_label->setAlignment(Qt::AlignCenter);
		m_icon_label->setMinimumWidth(42);
		m_icon_label->set_object_name("Icon");
	}

	m_text_label->setAttribute(Qt::WA_TransparentForMouseEvents);
	m_text_label->set_object_name("Text Label");
	m_text_label->set_font_size(12);

	m_close_button->set_object_name("Close Button");

	connect(m_close_button, &QLButton::clicked,
		[this] { emit closed(); });
}

void QLTab::init_attributes()
{
	m_fill->set_value("#36393f");
	m_fill->create_override("Active", LString("#25272b"));

	corner_radii_top_left()->set_value(5.0);
	corner_radii_top_right()->set_value(5.0);

	m_text_label->text_color()->set_value("#e3e3e3");

	if (m_icon_label)
		if (QLSvgRenderer* renderer = m_icon_label->graphic()->svg_renderer())
			renderer->color()->set_value("#e3e3e3");

	m_close_button->
		graphic_label()->
			graphic()->svg_renderer()->color()->set_value("#5f5f5f");
}

void QLTab::init_layout()
{
	main_layout->setContentsMargins(2, 0, 4, 0);
	main_layout->setSpacing(0);
	main_layout->addWidget(m_icon_label);
	main_layout->addWidget(m_text_label);
	main_layout->addWidget(m_close_button);

	setLayout(main_layout);
}

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

#include <QLayers/qlslider.h>

#include <QMouseEvent>
#include <QVBoxLayout>

using Layers::LAttribute;

using QLayers::QLSlider;

QLSlider::QLSlider(QWidget* parent) :
	m_is_decimal_slider{ true }, QLWidget(parent)
{
	init();
}

QLSlider::QLSlider(int limit, QWidget* parent) :
	m_is_decimal_slider{ false }, m_limit{ limit }, QLWidget(parent)
{
	init();
}

void QLSlider::set_limit(int limit)
{
	m_limit = limit;

	update_handle_pos();
}

LAttribute* QLSlider::value()
{
	return m_value;
}

bool QLSlider::eventFilter(QObject* object, QEvent* event)
{
	if (event->type() == QEvent::MouseButtonPress && m_handle->underMouse())
	{
		QMouseEvent* mouse_event = static_cast<QMouseEvent*>(event);

		if (mouse_event->button() & Qt::LeftButton)
		{
			m_dragging_handle = true;

			m_mouse_click_position = mouse_event->pos();
			m_value_on_click = m_value->as<double>();
		}
	}
	else if (event->type() == QEvent::MouseButtonRelease &&
		m_handle->underMouse())
	{
		QMouseEvent* mouse_event = static_cast<QMouseEvent*>(event);

		if (mouse_event->button() & Qt::LeftButton)
		{
			m_dragging_handle = false;
		}
	}

	if (event->type() == QEvent::MouseMove && m_dragging_handle == true)
	{
		QMouseEvent* mouse_event = static_cast<QMouseEvent*>(event);

		QPoint delta = mouse_event->pos() - m_mouse_click_position;

		if (m_is_decimal_slider)
		{
			float range = float(width() - m_handle->width());

			float ratio = 1 / range;

			double new_value =
				float(m_value_on_click) + (float(delta.x()) * ratio);

			if (new_value < 0.0)
			{
				if (m_value->as<double>() != 0.0)
				{
					m_value->set_value(0.0);
				}
			}
			else if (new_value > 1.0)
			{
				if (m_value->as<double>() != 1.0)
				{
					m_value->set_value(1.0);
				}
			}
			else
			{
				m_value->set_value(new_value);
			}
		}
		else
		{
			double drag_increment =
				double(m_bar->width() - m_handle->width()) / double(m_limit);

			double new_value =
				m_value_on_click + float(delta.x() / drag_increment);

			if (new_value < 0.0)
				m_value->set_value(0.0);

			else if (new_value > m_limit)
				m_value->set_value(double(m_limit));

			else
				m_value->set_value(new_value);
		}
	}

	return false;
}

void QLSlider::init()
{
	init_attributes();

	installEventFilter(this);
	setFixedHeight(40);

	m_bar->setFixedHeight(5);
	m_bar->set_object_name("Bar");

	m_handle->setFixedSize(40, 40);
	m_handle->set_object_name("Handle");

	init_layout();
}

void QLSlider::init_attributes()
{
	m_value->on_change(
		[this] {
			update_handle_pos();
		}
	);

	m_corner_radii_top_left->set_value(10.0);
	m_corner_radii_top_right->set_value(10.0);
	m_corner_radii_bottom_left->set_value(10.0);
	m_corner_radii_bottom_right->set_value(10.0);

	m_bar->fill()->set_value("#c0c0c0");
	m_bar->corner_radii_top_left()->set_value(2.0);
	m_bar->corner_radii_top_right()->set_value(2.0);
	m_bar->corner_radii_bottom_left()->set_value(2.0);
	m_bar->corner_radii_bottom_right()->set_value(2.0);
	m_bar->set_margin(20, 0, 20, 0);

	m_handle->fill()->set_value("#808080");
	m_handle->corner_radii_top_left()->set_value(3.0);
	m_handle->corner_radii_top_right()->set_value(3.0);
	m_handle->corner_radii_bottom_left()->set_value(3.0);
	m_handle->corner_radii_bottom_right()->set_value(3.0);
	m_handle->set_margin(15, 5, 15, 5);
}

void QLSlider::init_layout()
{
	QVBoxLayout* main_layout = new QVBoxLayout;

	main_layout->setContentsMargins(0, 0, 0, 0);
	main_layout->setSpacing(0);
	main_layout->addWidget(m_bar);

	setLayout(main_layout);

	m_handle->raise();
}

void QLSlider::update_handle_pos()
{
	if (m_is_decimal_slider)
	{
		float range = float(width() - m_handle->width());

		float ratio = 1 / range;

		m_handle->move(m_value->as<double>() / ratio, m_handle->y());
	}
	else
	{
		double drag_increment =
			double(width() - m_handle->width()) / double(m_limit);

		m_handle->move(drag_increment * m_value->as<double>(), m_handle->y());
	}
}

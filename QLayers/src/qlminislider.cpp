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

#include <QLayers/qlminislider.h>

#include <QApplication>
#include <QMouseEvent>
#include <QVBoxLayout>

using Layers::LAttribute;

using QLayers::QLMiniSlider;

QLMiniSlider::QLMiniSlider(double limit, QWidget* parent) :
	m_limit{ limit },
	QLWidget(parent)
{
	init_attributes();

	installEventFilter(this);
	setFixedSize(40, 40);

	m_bar->setFixedHeight(3);
	m_bar->set_object_name("Bar");

	m_handle->move(5, 13);
	m_handle->setFixedSize(5, 13);
	m_handle->set_object_name("Handle");

	m_value->on_change(
		[this] {
			update_handle_pos();
		}
	);

	init_layout();
}

void QLMiniSlider::set_limit(double limit)
{
	m_limit = limit;

	update_handle_pos();
}

LAttribute* QLMiniSlider::value()
{
	return m_value;
}

void QLMiniSlider::init_attributes()
{
	m_corner_radii_top_left->set_value(5.0);
	m_corner_radii_top_right->set_value(5.0);
	m_corner_radii_bottom_left->set_value(5.0);
	m_corner_radii_bottom_right->set_value(5.0);

	m_bar->set_margin(5, 0, 5, 0);
	m_bar->corner_radii_top_left()->set_value(2.0);
	m_bar->corner_radii_top_right()->set_value(2.0);
	m_bar->corner_radii_bottom_left()->set_value(2.0);
	m_bar->corner_radii_bottom_right()->set_value(2.0);

	m_handle->corner_radii_top_left()->set_value(2.0);
	m_handle->corner_radii_top_right()->set_value(2.0);
	m_handle->corner_radii_bottom_left()->set_value(2.0);
	m_handle->corner_radii_bottom_right()->set_value(2.0);

	// TODO: TEMP!
	m_fill->set_value("#c0c0c0");

	m_bar->fill()->set_value("#0000ff");

	m_handle->fill()->set_value("#ff0000");
}

void QLMiniSlider::update_handle_pos()
{
	m_handle->move(
		drag_increment() * m_value->as<double>() +
			m_bar->margins_left()->as<double>(),
		m_handle->y());
}

bool QLMiniSlider::eventFilter(QObject* object, QEvent* event)
{
	if (event->type() == QEvent::MouseButtonPress)
	{
		QMouseEvent* mouse_event = static_cast<QMouseEvent*>(event);

		if (mouse_event->button() & Qt::LeftButton)
		{
			QApplication::setOverrideCursor(Qt::BlankCursor);

			m_dragging_handle = true;

			m_mouse_click_position = mouse_event->pos();
			m_value_on_click = m_value->as<double>();
		}
	}
	else if (event->type() == QEvent::MouseButtonRelease)
	{
		QMouseEvent* mouse_event = static_cast<QMouseEvent*>(event);

		if (mouse_event->button() & Qt::LeftButton)
		{
			QApplication::restoreOverrideCursor();

			m_dragging_handle = false;

			QCursor::setPos(mapToGlobal(QPoint(width() / 2, height() / 2)));
		}
	}

	if (event->type() == QEvent::MouseMove && m_dragging_handle == true)
	{
		QMouseEvent* mouse_event = static_cast<QMouseEvent*>(event);

		QPoint delta = mouse_event->pos() - m_mouse_click_position;

		if (delta.x() % m_mouse_move_scale == 0)
		{
			double new_value = int(
				m_value_on_click + delta.x() /
					m_mouse_move_scale /
						drag_increment());

			if (new_value < 0.0)
				m_value->set_value(0.0);

			else if (new_value > m_limit)
				m_value->set_value(m_limit);

			else
				m_value->set_value(new_value);
		}
	}

	return false;
}

double QLMiniSlider::drag_increment() const
{
	int bar_margins =
		m_bar->margins_left()->as<double>() +
		m_bar->margins_right()->as<double>();

	return
		double(width() - m_handle->width() - bar_margins) /
			double(m_limit);
}

void QLMiniSlider::init_layout()
{
	QVBoxLayout* main_layout = new QVBoxLayout;

	main_layout->setContentsMargins(0, 0, 0, 0);
	main_layout->setSpacing(0);
	main_layout->addWidget(m_bar);

	setLayout(main_layout);

	m_handle->raise();
}

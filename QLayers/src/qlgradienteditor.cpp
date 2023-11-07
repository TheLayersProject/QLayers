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

#include <QLayers/qlgradienteditor.h>

#include <QMouseEvent>

#include <Layers/lalgorithms.h>

#include "qlgradienteditoritem.h"

using Layers::LString;

using QLayers::QLGradientEditor;
using QLayers::QLGradientEditorItem;

QLGradientEditor::QLGradientEditor(
	std::vector<LString> stops, QWidget* parent) :
	QLWidget(parent)
{
	init_attributes(stops);
	init_items(stops);
	init_add_stop_buttons();
	set_object_name("Gradient Editor");
	installEventFilter(this);
	setMinimumHeight(80);
	setMouseTracking(true);
	setSizePolicy(QSizePolicy::Minimum, QSizePolicy::MinimumExpanding);
	update_positions();
}

QLGradientEditor::~QLGradientEditor()
{
	for (QLGradientEditorItem* item : m_items)
		delete item;
}

std::vector<LString> QLGradientEditor::stops() const
{
	std::vector<LString> gradient_stops;

	for (QLGradientEditorItem* item : m_items)
		if (item != m_replace_item)
			gradient_stops.push_back(
				(std::to_string(item->stop.first) + ":" +
				item->stop.second.name().toStdString()).c_str());

	return gradient_stops;
}

bool QLGradientEditor::eventFilter(QObject* object, QEvent* event)
{
	if (event->type() == QEvent::Resize)
	{
		update_positions();
	}
	else if (event->type() == QEvent::MouseButtonPress)
	{
		QMouseEvent* mouse_event = static_cast<QMouseEvent*>(event);

		if (mouse_event->button() & Qt::LeftButton)
		{
			for (int i = 1; i < m_items.size() - 1; i++)
				if (m_items[i]->control->underMouse())
				{
					for (QLButton* add_stop_button : m_add_stop_buttons)
						delete add_stop_button;
					m_add_stop_buttons.clear();

					m_drag_item = m_items[i];
					m_drag_item->control->raise();
					m_drag_ctrl_initial_x = m_drag_item->control->pos().x();
					m_click_pos = mouse_event->pos();

					break;
				}
		}
	}
	else if (event->type() == QEvent::MouseMove && m_drag_item)
	{
		QMouseEvent* mouse_event = static_cast<QMouseEvent*>(event);
		QPoint delta_pos = mouse_event->pos() - m_click_pos;

		int new_x = m_drag_ctrl_initial_x + delta_pos.x();

		if (new_x < 0)
			new_x = 0;
		else if (new_x > width() - 40)
			new_x = width() - 40;

		m_drag_item->control->move(new_x, 0);
		m_drag_item->stop.first = qreal(new_x) / qreal(width() - 40);

		m_replace_item = nullptr;
		for (int i = 0; i < m_items.size(); i++)
			if (m_items[i] != m_drag_item)
			{
				int item_x = m_items[i]->control->x();
				int drag_item_x = m_drag_item->control->x();

				if (drag_item_x - 1 <= item_x && item_x <= drag_item_x + 1)
				{
					m_replace_item = m_items[i];
					break;
				}
			}

		update_gradient();
	}
	else if (event->type() == QEvent::MouseButtonRelease && m_drag_item)
	{
		QMouseEvent* mouse_event = static_cast<QMouseEvent*>(event);

		if (mouse_event->button() & Qt::LeftButton)
		{
			m_drag_item = nullptr;
			m_drag_ctrl_initial_x = 0;
			m_click_pos = QPoint();

			if (m_replace_item)
			{
				m_items.removeOne(m_replace_item);
				m_replace_item->control->deleteLater();
				delete m_replace_item;
				m_replace_item = nullptr;
			}

			init_add_stop_buttons();

			update_indexes();
			update_gradient();
			update_positions();
		}
	}

	return false;
}

QLGradientEditorItem* QLGradientEditor::create_item(const LString& stop)
{
	auto stop_parts =
		Layers::split<std::vector<LString>>(stop, ':');

	QGradientStop gradient_stop = QGradientStop(
		std::stod(stop_parts[0].c_str()),
		QString::fromStdString(stop_parts[1].c_str()));

	QLGradientEditorItem* item = new QLGradientEditorItem;
	item->stop = gradient_stop;
	item->control = new QLColorControl(this);
	item->control->fill()->set_value(stop_parts[1]);
	item->control->show();

	connect(item->control, &QLColorControl::color_changed,
		[this, item]
		{
			item->stop.second =
				QColor(QString::fromStdString(
					item->control->fill()->as<LString>().c_str()));

			update_gradient();
		});

	return item;
}

void QLGradientEditor::init_attributes(const std::vector<LString>& stops)
{
	m_border_fill->set_value("#000000");
	m_border_thickness->set_value(2.0);
	m_corner_radii_top_left->set_value(8.0);
	m_corner_radii_top_right->set_value(8.0);
	m_corner_radii_bottom_left->set_value(8.0);
	m_corner_radii_bottom_right->set_value(8.0);
	m_fill->set_value(stops);
	m_margins_left->set_value(18.0);
	m_margins_right->set_value(18.0);
}

void QLGradientEditor::init_items(const std::vector<LString>& stops)
{
	for (const auto& stop : stops)
		m_items.append(create_item(stop));
}

void QLGradientEditor::init_add_stop_buttons()
{
	for (QLButton* add_stop_button : m_add_stop_buttons)
		delete add_stop_button;
	m_add_stop_buttons.clear();

	for (int i = 0; i < m_items.size() - 1; i++)
	{
		QLButton* add_stop_button = new QLButton(
			QLGraphic(":/images/new_theme.svg", QSize(14, 14)), this);
		add_stop_button->show();
		add_stop_button->set_object_name("Add Stop Buttons");
		add_stop_button->set_padding(0);
		add_stop_button->setFixedSize(40, 40);
		m_add_stop_buttons.append(add_stop_button);

		connect(add_stop_button, &QLButton::clicked,
			[this, add_stop_button, i]
			{
				m_items.insert(i + 1,
					create_item(
						(std::to_string(
							double(add_stop_button->x()) /
								double(width() - 40)) +
						":" +
						grab().toImage().pixelColor(
							add_stop_button->pos().x(),
							height() / 2).name().toStdString()).c_str()));

				m_add_stop_buttons.removeOne(add_stop_button);
				add_stop_button->deleteLater();

				init_add_stop_buttons();
				update_gradient();
				update_positions();
			});

		if (current_theme_item())
			add_stop_button->apply_theme_item(
				current_theme_item()->find_item(
					add_stop_button->objectName().toStdString().c_str()));
	}
}

void QLGradientEditor::update_gradient()
{
	m_fill->set_value(stops());
}

void QLGradientEditor::update_indexes()
{
	std::sort(m_items.begin(), m_items.end(), compare_items);
}

void QLGradientEditor::update_positions()
{
	for (QLGradientEditorItem* item : m_items)
		item->control->move((width() - 40) * item->stop.first, 0);

	if (!m_add_stop_buttons.isEmpty())
	{
		for (int i = 0; i < m_items.size(); i++)
			if (i != m_items.size() - 1)
			{
				int left_ctrl_x = m_items[i]->control->x();
				int right_ctrl_x = m_items[i + 1]->control->x();
				int crtl_delta_x = right_ctrl_x - left_ctrl_x;

				if (crtl_delta_x < 80)
					m_add_stop_buttons[i]->hide();
				else
				{
					if (m_add_stop_buttons[i]->isHidden())
						m_add_stop_buttons[i]->show();

					m_add_stop_buttons[i]->move(
						left_ctrl_x + (crtl_delta_x / 2), 0);
				}
			}
	}
}

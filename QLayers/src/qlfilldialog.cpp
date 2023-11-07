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

#include <QLayers/qlfilldialog.h>

#include <QEvent>

#include <Layers/lattribute.h>

using Layers::LAttribute;
using Layers::LString;

using QLayers::QLFillDialog;

QLFillDialog::QLFillDialog(QWidget* parent) :
	QLDialog("Fill", parent)
{
	init_attributes();
	init_layout();
	set_icon(QLGraphic(":/images/fill_icon.svg", QSize(22, 20)));
	set_object_name("Fill Dialog");
	setFixedSize(165, 125);

	m_color_control->set_object_name("Color Control");
	m_gradient_control->set_object_name("Gradient Control");

	connect(m_color_control, &QLColorControl::color_changed,
		[this] { done(QDialog::Accepted); });

	connect(m_gradient_control, &QLGradientControl::gradient_changed,
		[this] { done(QDialog::Accepted); });

	m_fill_type_toggle->setFixedHeight(85);
	m_fill_type_toggle->set_object_name("Fill Type Toggle");

	connect(m_fill_type_toggle, &LToggleSwitch::toggled_event,
		[this](bool toggled)
		{
			if (toggled)
			{
				m_previous_color = m_color_control->fill()->as<LString>();

				m_gradient_control->fill()->set_value(m_previous_gradient);

				m_gradient_label_opacity->setOpacity(1.0);
				m_gradient_control->show();

				m_color_label_opacity->setOpacity(0.25);
				m_color_control->hide();
			}
			else
			{
				m_previous_gradient =
					m_gradient_control->fill()->as<std::vector<LString>>();

				m_color_control->fill()->set_value(m_previous_color);

				m_color_label_opacity->setOpacity(1.0);
				m_color_control->show();

				m_gradient_label_opacity->setOpacity(0.25);
				m_gradient_control->hide();
			}
		});

	m_color_label_opacity->setOpacity(1.0);

	m_color_label->set_font_size(14);
	m_color_label->setFixedHeight(40);
	m_color_label->setGraphicsEffect(m_color_label_opacity);
	m_color_label->set_object_name("Color Label");

	m_gradient_label_opacity->setOpacity(1.0);

	m_gradient_label->set_font_size(14);
	m_gradient_label->setFixedHeight(40);
	m_gradient_label->setGraphicsEffect(m_gradient_label_opacity);
	m_gradient_label->set_object_name("Gradient Label");
}

void QLFillDialog::set_attribute(LAttribute* attribute)
{
	m_gradient_control->fill()->set_link_attribute(attribute);
	m_color_control->fill()->set_link_attribute(attribute);

	if (const auto* gradient_stops =
		m_color_control->fill()->as_if<std::vector<LString>>())
	{
		m_fill_type_toggle->toggle(false);

		m_gradient_label_opacity->setOpacity(1.0);
		m_gradient_control->show();

		m_color_label_opacity->setOpacity(0.25);
		m_color_control->hide();
	}
	else if (const auto* color =
		m_color_control->fill()->as_if<LString>())
	{
		m_color_label_opacity->setOpacity(1.0);
		m_color_control->show();

		m_gradient_label_opacity->setOpacity(0.25);
		m_gradient_control->hide();
	}
}

void QLFillDialog::init_attributes()
{
	m_border_thickness->set_value(0.0);
	m_corner_radii_top_left->set_value(7.0);
	m_corner_radii_top_right->set_value(7.0);
	m_corner_radii_bottom_left->set_value(7.0);
	m_corner_radii_bottom_right->set_value(7.0);

	m_color_control->margins_top()->set_value(8.0);
	m_color_control->margins_bottom()->set_value(8.0);

	m_gradient_control->margins_top()->set_value(8.0);
	m_gradient_control->margins_bottom()->set_value(8.0);
}

void QLFillDialog::init_layout()
{
	QHBoxLayout* color_control_layout = new QHBoxLayout;
	color_control_layout->setContentsMargins(0, 0, 0, 0);
	color_control_layout->setSpacing(0);
	color_control_layout->addWidget(m_color_label);
	color_control_layout->addWidget(m_color_control);
	color_control_layout->addStretch();

	QHBoxLayout* gradient_control_layout = new QHBoxLayout;
	gradient_control_layout->setContentsMargins(0, 0, 0, 0);
	gradient_control_layout->setSpacing(0);
	gradient_control_layout->addWidget(m_gradient_label);
	gradient_control_layout->addWidget(m_gradient_control);
	gradient_control_layout->addStretch();

	QVBoxLayout* control_layouts = new QVBoxLayout;
	control_layouts->setContentsMargins(0, 0, 0, 0);
	control_layouts->setSpacing(0);
	control_layouts->addLayout(color_control_layout);
	control_layouts->addLayout(gradient_control_layout);

	QHBoxLayout* dialog_layout = new QHBoxLayout;
	dialog_layout->setContentsMargins(0, 0, 0, 0);
	dialog_layout->setSpacing(0);
	dialog_layout->addWidget(m_fill_type_toggle);
	dialog_layout->addLayout(control_layouts);
	setLayout(dialog_layout);
}

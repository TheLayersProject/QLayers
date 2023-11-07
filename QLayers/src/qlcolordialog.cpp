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

#include <QLayers/qlcolordialog.h>

#include <QRegularExpressionValidator>

#include <Layers/lstring.h>

#include <QLayers/qlcalculate.h>
#include <QLayers/qlapplication.h>

using Layers::LAttribute;
using Layers::LString;

using QLayers::QLColorDialog;
//using QLayers::QLThemeable;

QLColorDialog::QLColorDialog(QWidget* parent) :
	QLDialog("Color", parent)
{
	init_attributes();
	init_layout();
	set_icon(QLGraphic(":/images/color_icon.png"));
	set_object_name("Color Dialog");
	setFixedSize(315, 400);

	m_apply_button->set_object_name("Apply Button");
	m_apply_button->set_font_size_f(10.5);
	m_apply_button->set_padding(6);
	m_apply_button->setFixedHeight(30);

	connect(m_apply_button, &QLButton::clicked,
		[this] { done(QDialog::Accepted); });

	m_color_unit_label->set_object_name("Color Unit Label");

	m_color_name_editor->set_object_name("Color Name Editor");
	m_color_name_editor->setFixedSize(100, 40);
	//QRegularExpression rx("^#[0-9a-f]{3}([0-9a-f]{3})?$")
	//m_color_name_line_editor->set_validator(
	//	new QRegularExpressionValidator(rx));

	connect(m_color_name_editor, &QLLineEditor::text_edited,
		[this]
		{
			qsizetype text_size =
				QString::fromStdString(m_color_name_editor->text()->as<LString>().c_str()).size();

			if (text_size == 6) // || text_size == 8)
				m_color->set_value(
					"#" + m_color_name_editor->text()->as<LString>());
		});

	m_radio_button_hue->set_object_name("Hue Radio Button");
	connect(m_radio_button_hue, &QLRadioButton::clicked, [this]
		{ m_color_plane->set_z_dimension(HSV::Hue); });

	m_radio_button_sat->set_object_name("Saturation Radio Button");
	connect(m_radio_button_sat, &QLRadioButton::clicked, [this]
		{ m_color_plane->set_z_dimension(HSV::Saturation); });

	m_radio_button_val->set_object_name("Value Radio Button");
	connect(m_radio_button_val, &QLRadioButton::clicked, [this]
		{ m_color_plane->set_z_dimension(HSV::Value); });

	m_label_hue->set_object_name("Hue Label");

	m_label_hue_unit->set_object_name("Hue Unit Label");

	m_label_sat->set_object_name("Saturation Label");

	m_label_sat_unit->set_object_name("Saturation Unit Label");

	m_label_val->set_object_name("Value Label");

	m_label_val_unit->set_object_name("Value Unit Label");

	m_line_editor_hue->set_object_name("Hue Line Editor");
	m_line_editor_hue->setFixedSize(55, 40);

	m_line_editor_sat->set_object_name("Saturation Line Editor");
	m_line_editor_sat->setFixedSize(55, 40);

	m_line_editor_val->set_object_name("Value Line Editor");
	m_line_editor_val->setFixedSize(55, 40);

	connect(m_line_editor_hue, &QLLineEditor::text_edited,
		this, &QLColorDialog::hsv_changed);

	connect(m_line_editor_sat, &QLLineEditor::text_edited,
		this, &QLColorDialog::hsv_changed);

	connect(m_line_editor_val, &QLLineEditor::text_edited,
		this, &QLColorDialog::hsv_changed);

	m_color_plane->setFixedSize(160, 160);

	connect(m_color_plane, &QLColorPlane::z_dimension_changed,
		[this]
		{
			switch (m_color_plane->z_dimension())
				{
				case HSV::Hue:
					m_z_slider->set_limit(MAX_H);
					break;
				case HSV::Saturation:
				case HSV::Value:
					m_z_slider->set_limit(MAX_SV);
					break;
				}
		});

	m_z_slider->set_object_name("Z-Slider");
}

QLColorDialog::~QLColorDialog()
{
	//delete m_color;
}

LAttribute* QLColorDialog::color() const
{
	return m_color;
}

void QLColorDialog::hsv_changed()
{
	float hue_f = m_line_editor_hue->text()->as<double>() / float(MAX_H);
	float sat_f = m_line_editor_sat->text()->as<double>() / 100.f;
	float val_f = m_line_editor_val->text()->as<double>() / 100.f;

	QColor new_color;
	new_color.setHsvF(hue_f, sat_f, val_f);

	m_color->set_value(new_color.name().toStdString().c_str());
}

void QLColorDialog::init_attributes()
{
	m_color->set_link_attribute(m_color_plane->color());

	m_color->on_change(
		[this] {
			QColor color =
				QColor(QString::fromStdString(m_color->as<LString>().c_str()));

			m_color_name_editor->set_text(
				color.name().remove("#"));

			m_line_editor_hue->set_text(
				QString::number(color.hue()));

			m_line_editor_sat->set_text(
				QString::number(int(round(color.saturationF() * 100.f))));

			m_line_editor_val->set_text(
				QString::number(int(round(color.valueF() * 100.f))));
		}
	);

	m_z_slider->value()->set_link_attribute(m_color_plane->z_axis());
}

void QLColorDialog::init_layout()
{
	// Color Name Layout
	QHBoxLayout* color_name_layout = new QHBoxLayout;
	color_name_layout->setContentsMargins(0, 0, 0, 0);
	color_name_layout->setSpacing(0);
	color_name_layout->addWidget(m_color_unit_label);
	color_name_layout->addWidget(m_color_name_editor);

	// Left Layout
	QVBoxLayout* left_layout = new QVBoxLayout;
	left_layout->setContentsMargins(0, 0, 0, 0);
	left_layout->setSpacing(12);
	left_layout->addWidget(m_color_plane);
	left_layout->addLayout(color_name_layout);

	// Hue Layout
	QHBoxLayout* hue_layout = new QHBoxLayout;
	hue_layout->setContentsMargins(0, 0, 0, 0);
	hue_layout->setSpacing(0);
	hue_layout->addWidget(m_radio_button_hue);
	hue_layout->addWidget(m_label_hue);
	hue_layout->addWidget(m_line_editor_hue);
	hue_layout->addWidget(m_label_hue_unit);

	// Sat Layout
	QHBoxLayout* sat_layout = new QHBoxLayout;
	sat_layout->setContentsMargins(0, 0, 0, 0);
	sat_layout->setSpacing(0);
	sat_layout->addWidget(m_radio_button_sat);
	sat_layout->addWidget(m_label_sat);
	sat_layout->addWidget(m_line_editor_sat);
	sat_layout->addWidget(m_label_sat_unit);

	// Val Layout
	QHBoxLayout* val_layout = new QHBoxLayout;
	val_layout->setContentsMargins(0, 0, 0, 0);
	val_layout->setSpacing(0);
	val_layout->addWidget(m_radio_button_val);
	val_layout->addWidget(m_label_val);
	val_layout->addWidget(m_line_editor_val);
	val_layout->addWidget(m_label_val_unit);

	// Right Layout
	QVBoxLayout* right_layout = new QVBoxLayout;
	right_layout->setContentsMargins(0, 0, 0, 0);
	right_layout->setSpacing(0);
	right_layout->addLayout(hue_layout);
	right_layout->addLayout(sat_layout);
	right_layout->addLayout(val_layout);

	// Top Layout
	QHBoxLayout* top_layout = new QHBoxLayout;
	top_layout->setContentsMargins(0, 0, 0, 0);
	top_layout->setSpacing(12);
	top_layout->addLayout(left_layout);
	top_layout->addLayout(right_layout);

	// Main Layout
	QVBoxLayout* main_layout = new QVBoxLayout;
	main_layout->setContentsMargins(7, 7, 7, 7);
	main_layout->setSpacing(12);
	main_layout->addLayout(top_layout);
	main_layout->addWidget(m_z_slider);
	main_layout->addStretch();
	main_layout->addWidget(m_apply_button);
	main_layout->setAlignment(m_apply_button, Qt::AlignRight);
	setLayout(main_layout);

	main_layout->activate();
}

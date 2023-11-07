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

#include <QLayers/qlgradientdialog.h>

#include <QMouseEvent>

#include <QLayers/qlapplication.h>

using Layers::LString;

using QLayers::QLColorControl;
using QLayers::QLGradientDialog;
using QLayers::QLThemeable;

QLGradientDialog::QLGradientDialog(
	std::vector<LString> stops, QWidget* parent) :
	m_gradient_editor{ new QLGradientEditor(stops) },
	QLDialog("Gradient", parent)
{
	init_layout();
	set_icon(QLGraphic(":/images/gradient_icon.svg"));
	set_object_name("Gradient Dialog");
	resize(450, minimumSizeHint().height());

	m_apply_button->set_object_name("Apply Button");
	m_apply_button->set_font_size_f(10.5);
	m_apply_button->set_padding(6);
	m_apply_button->setFixedHeight(30);

	connect(m_apply_button, &QLButton::clicked,
		[this] { done(QDialog::Accepted); });
}

std::vector<LString> QLGradientDialog::stops() const
{
	return m_gradient_editor->stops();
}

void QLGradientDialog::init_layout()
{
	QVBoxLayout* layout = new QVBoxLayout;
	layout->setContentsMargins(7, 20, 7, 7);
	layout->setSpacing(12);
	layout->addWidget(m_gradient_editor);
	layout->addWidget(m_apply_button);
	layout->setAlignment(m_apply_button, Qt::AlignRight);
	setLayout(layout);

	/*
		Activate layout since position information is needed during
		initialization.
	*/
	layout->activate();
}

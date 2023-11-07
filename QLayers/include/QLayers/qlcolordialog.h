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

#ifndef QLCOLORDIALOG_H
#define QLCOLORDIALOG_H

#include <Layers/lattribute.h>

#include "qlayers_global.h"
#include "qlayers_export.h"

#include "qlcolor.h"
#include "qlcolorplane.h"
#include "qlcombobox.h"
#include "qldialog.h"
#include "qllineeditor.h"
#include "qlradiobutton.h"
#include "qlradiobuttonpool.h"
#include "qlslider.h"

QLAYERS_NAMESPACE_BEGIN
class QLAYERS_EXPORT QLColorDialog : public QLDialog
{
	Q_OBJECT

public:
	QLColorDialog(QWidget* parent = nullptr);

	~QLColorDialog();

	Layers::LAttribute* color() const;

private slots:
	void hsv_changed();

private:
	void init_attributes();
	void init_layout();

	QLButton* m_apply_button{
		new QLButton(QLGraphic(":/images/check.svg", QSize(16, 13)), "Apply") };

	QLLabel* m_color_unit_label{ new QLLabel("#")};

	QLLineEditor* m_color_name_editor{ new QLLineEditor };

	QLColorPlane* m_color_plane{ new QLColorPlane };

	QLSlider* m_z_slider{ new QLSlider(MAX_H) };

	Layers::LAttribute* m_color
		{ new Layers::LAttribute("color", "#000000")};

	QLRadioButton* m_radio_button_hue{ new QLRadioButton };
	QLRadioButton* m_radio_button_sat{ new QLRadioButton };
	QLRadioButton* m_radio_button_val{ new QLRadioButton };

	QLRadioButtonPool m_hsv_radio_button_pool{
		QLRadioButtonPool({
			m_radio_button_hue,
			m_radio_button_sat,
			m_radio_button_val
			}) };

	QLLabel* m_label_hue{ new QLLabel("H:") };
	QLLabel* m_label_hue_unit{ new QLLabel("°") };
	QLLabel* m_label_sat{ new QLLabel("S:") };
	QLLabel* m_label_sat_unit{ new QLLabel("%") };
	QLLabel* m_label_val{ new QLLabel("V:") };
	QLLabel* m_label_val_unit{ new QLLabel("%") };

	QLLineEditor* m_line_editor_hue{ new QLLineEditor };
	QLLineEditor* m_line_editor_sat{ new QLLineEditor };
	QLLineEditor* m_line_editor_val{ new QLLineEditor };
};
QLAYERS_NAMESPACE_END

#endif // QLCOLORDIALOG_H

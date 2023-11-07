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

#ifndef QLTOGGLESWITCH_H
#define QLTOGGLESWITCH_H

#include <QHBoxLayout>
#include <QVBoxLayout>

#include <Layers/lattribute.h>

#include "qlayers_global.h"
#include "qlayers_export.h"

#include "qlstatepool.h"
#include "qlwidget.h"

QLAYERS_NAMESPACE_BEGIN

class QLLabel;

class QLAYERS_EXPORT LToggleSwitch : public QLWidget
{
	Q_OBJECT

signals:
	void toggled_event(bool toggled);

public:
	LToggleSwitch(bool vertical = false, QWidget* parent = nullptr);

	void set_toggled(bool toggled);

	void setFixedHeight(int h);

	void toggle(bool emit_toggled_event = true);

	bool toggled() const;

	Layers::LAttribute a_padding_left
		{ Layers::LAttribute("Left Padding", 2.0) };

	Layers::LAttribute a_padding_top
		{ Layers::LAttribute("Top Padding", 2.0) };

	Layers::LAttribute a_padding_right
		{ Layers::LAttribute("Right Padding", 2.0) };

	Layers::LAttribute a_padding_bottom
		{ Layers::LAttribute("Bottom Padding", 2.0) };

protected:
	bool eventFilter(QObject* object, QEvent* event) override;

private:
	void init_attributes();

	void init_layout();

	void update_layout_margins();

	void update_spacer_size();

	QHBoxLayout* m_layout_h{ nullptr };

	QVBoxLayout* m_layout_v{ nullptr };

	QLWidget* m_spacer{ new QLWidget };
	QLWidget* m_square{ new QLWidget };

	bool m_vertical{ false };

	QLStatePool* m_toggle_states
		{ new QLStatePool("Toggle", { "Toggled", "Untoggled" })};
};
QLAYERS_NAMESPACE_END

#endif // QLTOGGLESWITCH_H

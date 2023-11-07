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

#ifndef QLTHEMEABLEBOX_H
#define QLTHEMEABLEBOX_H

#include <QPainter>

#include <Layers/lattribute.h>

#include "qlayers_global.h"
#include "qlayers_export.h"

#include "qlpaint.h"
#include "qlthemeable.h"

QLAYERS_NAMESPACE_BEGIN
class QLAYERS_EXPORT QLThemeableBox : public QLThemeable
{
public:
	Layers::LAttribute* border_fill() const;

	Layers::LAttribute* border_thickness() const;

	static QPainterPath box_path(
		const QRect& box_rect, const LCornerRadii& corner_radii);

	Layers::LAttribute* corner_radii_bottom_left() const;

	Layers::LAttribute* corner_radii_bottom_right() const;

	Layers::LAttribute* corner_radii_top_left() const;

	Layers::LAttribute* corner_radii_top_right() const;

	Layers::LAttribute* fill() const;

	Layers::LAttribute* margins_bottom() const;

	Layers::LAttribute* margins_left() const;

	Layers::LAttribute* margins_right() const;

	Layers::LAttribute* margins_top() const;

	void set_margin(double margin);

	void set_margin(double left, double top, double right, double bottom);

protected:
	void init_attributes();

	void paint(QWidget* widget);

	Layers::LAttribute* m_border_fill
		{ new Layers::LAttribute("Border.Fill", "#a0a0a4") };

	Layers::LAttribute* m_border_thickness
		{ new Layers::LAttribute("Border.Thickness", 0.0) };

	Layers::LAttribute* m_corner_radii_bottom_left
		{ new Layers::LAttribute("Corner Radii.Bottom Left", 0.0) };

	Layers::LAttribute* m_corner_radii_bottom_right
		{ new Layers::LAttribute("Corner Radii.Bottom Right", 0.0) };

	Layers::LAttribute* m_corner_radii_top_left
		{ new Layers::LAttribute("Corner Radii.Top Left", 0.0) };

	Layers::LAttribute* m_corner_radii_top_right
		{ new Layers::LAttribute("Corner Radii.Top Right", 0.0) };

	Layers::LAttribute* m_fill
		{ new Layers::LAttribute("Fill", "#ffffff") };

	Layers::LAttribute* m_margins_bottom
		{ new Layers::LAttribute("Margins.Bottom", 0.0) };

	Layers::LAttribute* m_margins_left
		{ new Layers::LAttribute("Margins.Left", 0.0) };

	Layers::LAttribute* m_margins_right
		{ new Layers::LAttribute("Margins.Right", 0.0) };

	Layers::LAttribute* m_margins_top
		{ new Layers::LAttribute("Margins.Top", 0.0) };
};

QLAYERS_NAMESPACE_END

#endif // QLTHEMEABLEBOX_H

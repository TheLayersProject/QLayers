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

#ifndef QLSCROLLBAR_H
#define QLSCROLLBAR_H

#include <QScrollBar>

#include <Layers/lattribute.h>

#include "qlayers_global.h"
#include "qlayers_export.h"

#include "qlthemeable.h"

QLAYERS_NAMESPACE_BEGIN
class QLAYERS_EXPORT QLScrollBar : public QScrollBar, public QLThemeable
{
	Q_OBJECT

public:
	QLScrollBar(QWidget* parent = nullptr);

	Layers::LAttribute* background_color() const;

	Layers::LAttribute* corner_radii_bottom_left() const;

	Layers::LAttribute* corner_radii_bottom_right() const;

	Layers::LAttribute* corner_radii_top_left() const;

	Layers::LAttribute* corner_radii_top_right() const;

	Layers::LAttribute* handle_color() const;

	Layers::LAttribute* handle_corner_radii_bottom_left() const;

	Layers::LAttribute* handle_corner_radii_bottom_right() const;

	Layers::LAttribute* handle_corner_radii_top_left() const;

	Layers::LAttribute* handle_corner_radii_top_right() const;

	virtual void update() override;

private:
	Layers::LAttribute* m_background_color
		{ new Layers::LAttribute("Background Color", "#a0a0a4", this) };

	Layers::LAttribute* m_corner_radii_bottom_left
		{ new Layers::LAttribute("Corner Radii.Bottom Left", 0.0, this) };

	Layers::LAttribute* m_corner_radii_bottom_right
		{ new Layers::LAttribute("Corner Radii.Bottom Right", 0.0, this) };

	Layers::LAttribute* m_corner_radii_top_left
		{ new Layers::LAttribute("Corner Radii.Top Left", 0.0, this) };

	Layers::LAttribute* m_corner_radii_top_right
		{ new Layers::LAttribute("Corner Radii.Top Right", 0.0, this) };

	Layers::LAttribute* m_handle_color
		{ new Layers::LAttribute("Handle Color", "#ffffff", this) };

	Layers::LAttribute* m_handle_corner_radii_bottom_left
		{ new Layers::LAttribute("Handle Corner Radii.Bottom Left", 5.0, this) };

	Layers::LAttribute* m_handle_corner_radii_bottom_right
		{ new Layers::LAttribute("Handle Corner Radii.Bottom Right", 5.0, this) };

	Layers::LAttribute* m_handle_corner_radii_top_left
		{ new Layers::LAttribute("Handle Corner Radii.Top Left", 5.0, this) };

	Layers::LAttribute* m_handle_corner_radii_top_right
		{ new Layers::LAttribute("Handle Corner Radii.Top Right", 5.0, this) };
};
QLAYERS_NAMESPACE_END

#endif // QLSCROLLBAR_H

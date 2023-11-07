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

#ifndef QLHEADERVIEW_H
#define QLHEADERVIEW_H

#include <QHeaderView>

#include <Layers/lattribute.h>

#include "qlayers_global.h"
#include "qlayers_export.h"

#include "qlthemeable.h"

QLAYERS_NAMESPACE_BEGIN
class QLAYERS_EXPORT QLHeaderView : public QHeaderView, public QLThemeable
{
	Q_OBJECT

public:
	QLHeaderView(Qt::Orientation orientation, QWidget* parent = nullptr);

	virtual void update() override;

private:
	Layers::LAttribute* m_border_fill{
		new Layers::LAttribute("Border.Fill", "#a0a0a4", this) };

	Layers::LAttribute* m_border_thickness{
		new Layers::LAttribute("Border.Thickness", 0.0, this) };

	Layers::LAttribute* m_corner_radii_bottom_left{
		new Layers::LAttribute("Corner Radii.Bottom Left", 0.0, this) };

	Layers::LAttribute* m_corner_radii_bottom_right{
		new Layers::LAttribute("Corner Radii.Bottom Right", 0.0, this) };

	Layers::LAttribute* m_corner_radii_top_left{
		new Layers::LAttribute("Corner Radii.Top Left", 2.0, this) };

	Layers::LAttribute* m_corner_radii_top_right{
		new Layers::LAttribute("Corner Radii.Top Right", 2.0, this) };

	Layers::LAttribute* m_fill{
		new Layers::LAttribute("Fill", "#808080", this) };

	Layers::LAttribute* m_text_color{
		new Layers::LAttribute("Text Color", "#000000", this) };
};
QLAYERS_NAMESPACE_END

#endif // QLHEADERVIEW_H  

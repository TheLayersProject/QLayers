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

#ifndef QLMENUBAR_H
#define QLMENUBAR_H

#include <QMenuBar>

#include <Layers/lattribute.h>

#include "qlayers_global.h"
#include "qlayers_export.h"

#include "qlthemeable.h"

QLAYERS_NAMESPACE_BEGIN
class QLAYERS_EXPORT QLMenuBar : public QMenuBar, public QLThemeable
{
	Q_OBJECT

public:
	QLMenuBar(QWidget* parent = nullptr);

	Layers::LAttribute* selected_text_color() const;

	Layers::LAttribute* text_color() const;

	virtual void update() override;

private:
	QString build_stylesheet();

	Layers::LAttribute* m_selected_text_color
		{ new Layers::LAttribute("selected_text_color", "#c0c0c0", this) };

	Layers::LAttribute* m_text_color
		{ new Layers::LAttribute("Text Color", "#a0a0a4", this) };
};
QLAYERS_NAMESPACE_END

#endif // QLMENUBAR_H

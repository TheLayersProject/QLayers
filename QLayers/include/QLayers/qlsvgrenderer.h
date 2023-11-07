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

#ifndef QLSVGRENDERER_H
#define QLSVGRENDERER_H

#include <QColor>
#include <QSvgRenderer>

#include <Layers/lattribute.h>

#include "qlayers_global.h"
#include "qlayers_export.h"

#include "qlthemeable.h"

QLAYERS_NAMESPACE_BEGIN
class QLAYERS_EXPORT QLSvgRenderer : public QSvgRenderer, public QLThemeable
{
	Q_OBJECT

public:
	QLSvgRenderer(const QString& file_path, QObject* parent = nullptr);

	QLSvgRenderer(const QLSvgRenderer& svg_renderer);

	//~QLSvgRenderer();

	Layers::LAttribute* color() const;

private:
	void init_svg_elements_list();

	void rebuild_svg_str();

	void update();

	Layers::LAttribute* m_color
		{ new Layers::LAttribute("Color", "#000000", this) };

	QStringList m_svg_elements;

	QString m_svg_str;
};
QLAYERS_NAMESPACE_END

#endif // QLSVGRENDERER_H

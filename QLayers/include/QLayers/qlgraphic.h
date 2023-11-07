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

#ifndef QLGRAPHIC_H
#define QLGRAPHIC_H

#include <QImage>

#include "qlayers_global.h"
#include "qlayers_export.h"

#include "qlimagesequence.h"
#include "qlsvgrenderer.h"

QLAYERS_NAMESPACE_BEGIN
class QLAYERS_EXPORT QLGraphic
{
public:
	QLGraphic(const QString& file_path, QSize size = QSize());

	QLGraphic(const QImage& image);

	QLGraphic(const QLGraphic& graphic);

	~QLGraphic();

	QImage* image() const;

	QLImageSequence* image_sequence() const;

	QSize size() const;

	QLSvgRenderer* svg_renderer() const;

private:
	QSize m_size;

	QLImageSequence* m_image_sequence{ nullptr };

	QImage* m_image{ nullptr };

	QLSvgRenderer* m_svg_renderer{ nullptr };
};
QLAYERS_NAMESPACE_END

#endif // QLGRAPHIC_H

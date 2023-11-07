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

#include <QLayers/qlgraphic.h>

using QLayers::QLGraphic;
using QLayers::QLImageSequence;
using QLayers::QLSvgRenderer;

QLGraphic::QLGraphic(const QString& file_path, QSize size)
{
	if (file_path.endsWith(".png") || file_path.endsWith(".jpg") ||
		file_path.endsWith(".jpeg") || file_path.endsWith(".bmp") ||
		file_path.endsWith(".gif"))
	{
		m_image = new QImage(file_path);
	}
	else if (file_path.endsWith(".svg"))
	{
		m_svg_renderer = new QLSvgRenderer(file_path);
		m_svg_renderer->set_object_name("Svg");
	}
	else if (file_path.endsWith(".imgseq"))
	{
		m_image_sequence = new QLImageSequence(QFile(file_path));
	}

	if (size.isValid())
		m_size = size;
	else if (m_svg_renderer)
		m_size = m_svg_renderer->defaultSize();
	else if (m_image)
		m_size = m_image->size();
	else if (m_image_sequence)
		if (QImage* first_frame = m_image_sequence->frame(0))
			m_size = first_frame->size();
}

QLGraphic::QLGraphic(const QImage& image) :
	m_image{ new QImage(image) }
{
	m_size = m_image->size();
}

QLGraphic::QLGraphic(const QLGraphic& graphic)
{
	if (graphic.m_svg_renderer)
	{
		m_svg_renderer = new QLSvgRenderer(*graphic.m_svg_renderer);
		m_svg_renderer->set_object_name("Svg");
	}
	else if (graphic.m_image)
	{
		m_image = new QImage(*graphic.m_image);
	}
	else if (graphic.m_image_sequence)
	{
		m_image_sequence = new QLImageSequence(*graphic.m_image_sequence);
	}

	m_size = graphic.m_size;
}

QLGraphic::~QLGraphic()
{
	if (m_svg_renderer)
		delete m_svg_renderer;
	else if (m_image)
		delete m_image;
	else if (m_image_sequence)
		delete m_image_sequence;
}

QImage* QLGraphic::image() const
{
	return m_image;
}

QLImageSequence* QLGraphic::image_sequence() const
{
	return m_image_sequence;
}

QSize QLGraphic::size() const
{
	return m_size;
}

QLSvgRenderer* QLGraphic::svg_renderer() const
{
	return m_svg_renderer;
}

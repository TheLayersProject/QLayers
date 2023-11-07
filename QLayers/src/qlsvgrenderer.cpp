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

#include <QLayers/qlsvgrenderer.h>

#include <QFile>
#include <QTextStream>

#include <Layers/lstring.h>

using Layers::LAttribute;
using Layers::LString;

using QLayers::QLSvgRenderer;

QLSvgRenderer::QLSvgRenderer(const QString& file_path, QObject* parent) :
	QSvgRenderer(parent)
{
	//LThemeable::init();

	QFile file(file_path);

	if (file.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		QTextStream in(&file);
		m_svg_str = in.readAll();
		file.close();
	}

	init_svg_elements_list();

	load(m_svg_str.toUtf8());
}

QLSvgRenderer::QLSvgRenderer(const QLSvgRenderer& svg_renderer) :
	QLThemeable(svg_renderer)
{
	m_svg_str = svg_renderer.m_svg_str;

	for (const QString& svg_element : svg_renderer.m_svg_elements)
		m_svg_elements.append(svg_element);

	load(m_svg_str.toUtf8());
}

//QLSvgRenderer::~QLSvgRenderer()
//{
//	//delete m_color;
//}

LAttribute* QLSvgRenderer::color() const
{
	return m_color;
}

void QLSvgRenderer::rebuild_svg_str()
{
	QString new_svg_str = "";

	for (const QString& tag : m_svg_elements)
	{
		new_svg_str += tag;
	}

	m_svg_str = new_svg_str;
}

void QLSvgRenderer::update()
{
	for (int i = 0; i < m_svg_elements.size(); i++)
	{
		if (m_svg_elements[i].startsWith("<path") &&
			m_svg_elements[i].contains("id="))
		{
			QString color_name =
				QString::fromStdString(
					m_color->as<LString>(state_combo()).c_str());

			m_svg_elements[i].replace(
				m_svg_elements[i].indexOf("fill=") + 6, 7, color_name);
		}
	}

	rebuild_svg_str();

	load(m_svg_str.toUtf8());
}

void QLSvgRenderer::init_svg_elements_list()
{
	QString temp_svg_str = QString(m_svg_str);

	while (temp_svg_str.contains("<"))
	{
		int tag_open_index = temp_svg_str.indexOf("<");
		int tag_close_index = temp_svg_str.indexOf(">");
		int tag_size = tag_close_index - tag_open_index + 1;

		m_svg_elements.append(temp_svg_str.mid(tag_open_index, tag_size));

		temp_svg_str.remove(tag_open_index, tag_size);
	}
}

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

#include <QLayers/qlgrowingdotprogressindicator.h>

#include <QPainter>
#include <QPainterPath>

#include <Layers/lstring.h>

using Layers::LString;

using QLayers::QLGrowingDotProgressIndicator;

QLGrowingDotProgressIndicator::QLGrowingDotProgressIndicator(QWidget* parent) :
	QWidget(parent)
{
	setFixedSize(24, 24);

	m_progress_timer->setSingleShot(true);

	m_update_timer_timeout_connection =
		connect(m_update_timer, &QTimer::timeout, [this]
			{ QWidget::update(); });

	m_progress_timer_timeout_connection =
		connect(m_progress_timer, &QTimer::timeout, [this]
		{
			emit timeout();

			m_update_timer->stop();
		});
}

QLGrowingDotProgressIndicator::~QLGrowingDotProgressIndicator()
{
	disconnect(m_update_timer_timeout_connection);
	disconnect(m_progress_timer_timeout_connection);
}

void QLGrowingDotProgressIndicator::start(int msec)
{
	m_progress_timer->start(msec);

	m_update_timer->start(17);
}

void QLGrowingDotProgressIndicator::paintEvent(QPaintEvent* event)
{
	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing);

	auto s = state_combo();

	QPoint center = rect().center() + QPoint(1, 1);

	qreal outline_outer_radius = (width() / 2);
	qreal outline_inner_radius = outline_outer_radius - 2;

	// Draw Outline Circle

	QPainterPath outline_inner_path;
	QPainterPath outline_outer_path;

	outline_inner_path.addEllipse(
		center, outline_inner_radius, outline_inner_radius);
	outline_outer_path.addEllipse(
		center, outline_outer_radius, outline_outer_radius);
	outline_outer_path = outline_outer_path - outline_inner_path;

	painter.fillPath(outline_outer_path,
		QColor(QString::fromStdString(m_color->as<LString>(s).c_str())));

	// Draw Growing Dot

	qreal interval = m_progress_timer->interval();

	qreal time_progressed =
		interval - qreal(m_progress_timer->remainingTime());

	qreal dot_radius =
		(outline_inner_radius + 1) * (time_progressed / interval);

	QPainterPath dot_path;

	dot_path.addEllipse(center, dot_radius, dot_radius);

	painter.fillPath(dot_path,
		QColor(QString::fromStdString(m_color->as<LString>(s).c_str())));
}

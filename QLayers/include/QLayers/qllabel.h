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

#ifndef QLLABEL_H
#define QLLABEL_H

#include <QLabel>
#include <QTimer>

#include <Layers/lattribute.h>

#include "qlayers_global.h"
#include "qlayers_export.h"

#include "qlgraphic.h"
#include "qlthemeable.h"

QLAYERS_NAMESPACE_BEGIN
class QLAYERS_EXPORT QLLabel : public QLabel, public QLThemeable
{
	Q_OBJECT

public:
	QLLabel(QWidget* parent = nullptr);

	QLLabel(const QString& text, QWidget* parent = nullptr);

	QLLabel(const QLGraphic& graphic, QWidget* parent = nullptr);

	~QLLabel();

	virtual QList<QLThemeable*> q_child_themeables(
		Qt::FindChildOptions options = Qt::FindDirectChildrenOnly
	) override;

	Layers::LAttribute* fill() const;

	QLGraphic* graphic() const;

	void set_font_size(int size);

	void set_font_size_f(qreal size);

	virtual QSize sizeHint() const override;

	Layers::LAttribute* text_color() const;

	virtual void update() override;

protected:
	void paintEvent(QPaintEvent* event);

private:
	void init();
	void init_attributes();

	int m_frame{ 0 };

	QLGraphic* m_graphic{ nullptr };

	Layers::LAttribute* m_fill{
		new Layers::LAttribute("Fill", "#ffffff", this) };

	Layers::LAttribute* m_text_color{
		new Layers::LAttribute("Text Color", "#000000") };

	QMetaObject::Connection m_repaint_connection;

	QTimer m_timer;
};
QLAYERS_NAMESPACE_END

#endif // QLLABEL_H

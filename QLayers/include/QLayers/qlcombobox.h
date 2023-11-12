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

#ifndef QLCOMBOBOX_H
#define QLCOMBOBOX_H

#include <QComboBox>
#include <QPainterPath>

#include <Layers/lattribute.h>

#include "qlayers_global.h"
#include "qlayers_export.h"

#include "qlpaint.h"
#include "qlthemeable.h"

QLAYERS_NAMESPACE_BEGIN
class QLAYERS_EXPORT QLComboBox : public QComboBox, public QLThemeable
{
	Q_OBJECT

public:
	QLComboBox(QWidget* parent = nullptr);

	Layers::LAttribute* border_fill() const;

	Layers::LAttribute* border_thickness() const;

	virtual QList<QLThemeable*> child_qlthemeables(
		Qt::FindChildOptions options = Qt::FindDirectChildrenOnly
	) override;

	Layers::LAttribute* corner_radius() const;

	Layers::LAttribute* fill() const;

	void setFixedHeight(int h);

	void setFixedSize(const QSize& s);

	void setFixedSize(int w, int h);

	void setFixedWidth(int w);

	virtual void showPopup() override;

	Layers::LAttribute* text_color() const;

	virtual void update() override;

protected:
	virtual bool eventFilter(QObject* object, QEvent* event) override;

	bool is_view_positioned_above() const;

	void paint_box(QPainter* painter);

	virtual void paintEvent(QPaintEvent* event) override;

	Layers::LAttribute* m_border_fill
		{ new Layers::LAttribute("Border.Fill", "#a0a0a4", this) };

	Layers::LAttribute* m_border_thickness
		{ new Layers::LAttribute("Border.Thickness", 0.0, this) };

	Layers::LAttribute* m_corner_radius
		{ new Layers::LAttribute("Corner Radius", 4.0, this) };

	Layers::LAttribute* m_fill
		{ new Layers::LAttribute("Fill", "#31323b", this)};

	Layers::LAttribute* m_text_color
		{ new Layers::LAttribute("Text Color", "#e1e1e1", this) };
};
QLAYERS_NAMESPACE_END

#endif // QLCOMBOBOX_H

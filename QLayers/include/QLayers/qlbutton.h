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

#ifndef QLBUTTON_H
#define QLBUTTON_H

#include <QGraphicsOpacityEffect>
#include <QHBoxLayout>

#include "qlayers_global.h"
#include "qlayers_export.h"

#include "qllabel.h"
#include "qlwidget.h"

QLAYERS_NAMESPACE_BEGIN
class QLAYERS_EXPORT QLButton : public QLWidget
{
	Q_OBJECT

signals:
	void clicked();

public:
	QLButton(const QLGraphic& graphic, const QString& text,
		QWidget* parent = nullptr);

	QLButton(const QLGraphic& graphic, QWidget* parent = nullptr);

	QLButton(const QString& text, QWidget* parent = nullptr);

	QLButton(const QLGraphic& graphic, const QLGraphic& graphic_after,
		QWidget* parent = nullptr);

	bool disabled() const;

	QLLabel* graphic_label() const;

	void set_disabled(bool cond = true);

	void set_font_size(int size);
	
	void set_font_size_f(qreal size);

	void set_padding(int padding);

	void set_padding(int left, int top, int right, int bottom);

	void toggle_graphics();

protected:
	virtual bool eventFilter(QObject* object, QEvent* event) override;

private:
	void init();
	void init_layout();

	QHBoxLayout* main_layout{ new QHBoxLayout };

	QGraphicsOpacityEffect* m_button_opacity{ new QGraphicsOpacityEffect };

	bool m_disabled{ false };

	QLLabel* m_graphic_label{ nullptr };
	QLLabel* m_graphic_after_label{ nullptr };

	QLLabel* m_text_label{ nullptr };

	QLStatePool* m_select_states{
		new QLStatePool("Select", { "Selected", "Unselected" }) };
};
QLAYERS_NAMESPACE_END

#endif // QLBUTTON_H

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

#ifndef QLLINEEDITOR_H
#define QLLINEEDITOR_H

#include <QLineEdit>

#include <Layers/lattribute.h>

#include "qlayers_global.h"
#include "qlayers_export.h"

#include "qlwidget.h"

QLAYERS_NAMESPACE_BEGIN
class QLAYERS_EXPORT QLLineEditor : public QLWidget
{
	Q_OBJECT

signals:
	void text_edited(const QString& text);

public:
	QLLineEditor(QWidget* parent = nullptr);

	~QLLineEditor();

	Layers::LAttribute* left_padding() const;

	void set_default_value(const QString& default_value);

	void set_font_size(int size);

	void set_font_size_f(qreal size);

	void set_text(const QString& text);

	void set_validator(const QValidator* validator);

	Layers::LAttribute* text() const;

	Layers::LAttribute* text_color() const;

	virtual void update() override;

protected:
	bool eventFilter(QObject* object, QEvent* event) override;

private:
	void init_attributes();

	Layers::LAttribute* m_left_padding
		{ new Layers::LAttribute("left_padding", 3.0) };

	Layers::LAttribute* m_text_color
		{ new Layers::LAttribute("Text Color", "#000000", this) };

	Layers::LAttribute* m_text
		{ new Layers::LAttribute("text", "") };

	QString* m_default_value{ nullptr };

	QLineEdit* m_line_edit{ new QLineEdit(this) };
};
QLAYERS_NAMESPACE_END

#endif // QLLINEEDITOR_H

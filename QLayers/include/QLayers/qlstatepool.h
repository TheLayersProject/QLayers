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

#ifndef QLSTATEPOOL_H
#define QLSTATEPOOL_H

#include <QObject>

#include "qlayers_global.h"
#include "qlayers_export.h"

QLAYERS_NAMESPACE_BEGIN
class QLAYERS_EXPORT QLStatePool : public QObject
{
	Q_OBJECT

signals:
	void changed();

public:
	QLStatePool(const QString& name, QObject* parent = nullptr);

	QLStatePool(const QString& name, QStringList states,
		QObject* parent = nullptr);

	void add_state(const QString& state);

	void set_state(const QString& state);

	QString state() const;

private:
	QString m_name;

	QString m_state;

	QStringList m_states;
};
QLAYERS_NAMESPACE_END

#endif // !QLSTATEPOOL_H

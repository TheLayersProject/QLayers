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

#ifndef QLTHEMECOMBOBOXITEMMODEL_H
#define QLTHEMECOMBOBOXITEMMODEL_H

#include <QAbstractListModel>

#include <Layers/ltheme.h>

#include "qlayers_global.h"
#include "qlayers_export.h"

QLAYERS_NAMESPACE_BEGIN
class QLAYERS_EXPORT QLThemeComboBoxItemModel : public QAbstractListModel
{
	Q_OBJECT

public:
	QLThemeComboBoxItemModel(QObject* parent = nullptr);

	void append(Layers::LTheme* theme);

	void clear();

	virtual QVariant data(const QModelIndex& index, int role) const override;

	virtual int rowCount(const QModelIndex& parent = QModelIndex()) const override;

private:
	QList<Layers::LTheme*> m_themes{ QList<Layers::LTheme*>() };
};
QLAYERS_NAMESPACE_END

#endif // QLTHEMECOMBOBOXITEMMODEL_H  

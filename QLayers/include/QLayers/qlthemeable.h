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

#ifndef QLTHEMEABLE_H
#define QLTHEMEABLE_H

#include <Layers/lstring.h>
#include <Layers/lthemeable.h>

#include "qlayers_global.h"
#include "qlayers_export.h"

#include "qlstatepool.h"

QLAYERS_NAMESPACE_BEGIN

class QLGraphic;

class QLAYERS_EXPORT QLThemeable : public Layers::LThemeable
{
public:
	QLThemeable();

	QLThemeable(const Layers::LThemeable& other);

	void add_state_pool(QLStatePool* state_pool, bool include_children = true);

	QList<Layers::LAttribute*> child_attributes(
		Qt::FindChildOptions options = Qt::FindDirectChildrenOnly);

	virtual std::vector<LThemeable*> child_themeables(
		bool recursive = false) override;

	virtual QList<QLThemeable*> q_child_themeables(
		Qt::FindChildOptions options = Qt::FindDirectChildrenOnly);

	virtual Layers::LString path() override;

	void set_object_name(const Layers::LString& name);

	QList<QLStatePool*> state_pools() const;

	std::vector<Layers::LString> state_combo() const;

	virtual void update() override;

private:
	QLThemeable* _parent_themeable();

	QString _name();

	QList<QLStatePool*> m_state_pools;
};
QLAYERS_NAMESPACE_END

#endif // !QLTHEMEABLE_H

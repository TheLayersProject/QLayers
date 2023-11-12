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

#include <QLayers/qlthemeable.h>

#include <QWidget>

#include <QLayers/qlgraphic.h>

using Layers::LAttribute;
using Layers::LAttributeList;
using Layers::LString;
using Layers::LThemeItem;
using Layers::LThemeable;

using QLayers::QLStatePool;
using QLayers::QLThemeable;

QLThemeable::QLThemeable() {}

QLThemeable::QLThemeable(const QLThemeable& other) :
	LThemeable(other) {}

void QLThemeable::add_state_pool(QLStatePool* state_pool, bool include_children)
{
	m_state_pools.append(state_pool);

	state_pool->connect(state_pool, &QLStatePool::changed,
		[this] { update(); });

	if (include_children)
		for (QLThemeable* child_themeable : child_qlthemeables())
			child_themeable->add_state_pool(state_pool, include_children);
}

QList<LAttribute*> QLThemeable::child_attributes(Qt::FindChildOptions options)
{
	QList<LAttribute*> child_attributes;

	if (QObject* object = dynamic_cast<QObject*>(this))
	{
		LAttributeList found_attributes = find_children<LAttribute>();

		for (const auto& attr : found_attributes)
		{
			child_attributes.append(attr);
		}

		if (options == Qt::FindChildrenRecursively)
		{
			for (QLThemeable* child_themeable : child_qlthemeables())
			{
				child_attributes.append(
					child_themeable->child_attributes(options));
			}
		}
	}

	return child_attributes;
}

QList<QLThemeable*> QLThemeable::child_qlthemeables(Qt::FindChildOptions options)
{
	/*	IMPORTANT NOTE:
		This function only calls QObject::findChildren() with
		Qt::FindDirectChildrenOnly, even if *options* is
		Qt::FindChildrenRecursively. Recursion is handled after finding
		the direct children and calling child_qlthemeables() on them.

		This is important because child_qlthemeables() is a virtual function and
		calling QObject::findChildren() with Qt::FindChildrenRecursively will
		cause subsequent child_qlthemeables() calls to be missed.
	*/

	QList<QLThemeable*> child_qlthemeables;

	if (QObject* object = dynamic_cast<QObject*>(this))
	{
		QList<QObject*> child_objects =
			object->findChildren<QObject*>(Qt::FindDirectChildrenOnly);

		for (QObject* child_object : child_objects)
		{
			if (QLThemeable* child_themeable =
				dynamic_cast<QLThemeable*>(child_object))
			{
				child_qlthemeables.append(child_themeable);

				if (options == Qt::FindChildrenRecursively)
					child_qlthemeables.append(
						child_themeable->child_qlthemeables(options));
			}
		}
	}

	return child_qlthemeables;
}

std::vector<LThemeable*> QLThemeable::child_themeables(bool recursive)
{
	std::vector<LThemeable*> children;

	Qt::FindChildOptions options = recursive ?
		Qt::FindChildrenRecursively : Qt::FindDirectChildrenOnly;

	for (LThemeable* child : child_qlthemeables(options))
		children.push_back(child);

	return children;
}

LString QLThemeable::path()
{
	LString path;

	if (QObject* object = dynamic_cast<QObject*>(this))
	{
		if (QLThemeable* parent_t = _parent_themeable())
			path = parent_t->path();
		else if (QWidget* widget = dynamic_cast<QWidget*>(this))
			if (widget->isWindow())
				path = "App";

		if (path.empty())
			path = object->objectName().toStdString().c_str();
		else
			path = path + "/" + object->objectName().toStdString().c_str();
	}

	return path;
}

void QLThemeable::set_object_name(const LString& name)
{
	if (QObject* object = dynamic_cast<QObject*>(this))
		object->setObjectName(QString::fromStdString(name.c_str()));

	LObject::set_object_name(name);
}

QList<QLStatePool*> QLThemeable::state_pools() const
{
	return m_state_pools;
}

std::vector<LString> QLThemeable::state_combo() const
{
	std::vector<LString> state_combo;

	for (QLStatePool* state_pool : m_state_pools)
		state_combo.push_back(state_pool->state().toStdString().c_str());

	return state_combo;
}

void QLThemeable::update()
{
	if (QWidget* widget = dynamic_cast<QWidget*>(this))
		widget->update();
}

QLThemeable* QLThemeable::_parent_themeable()
{
	if (QObject* object = dynamic_cast<QObject*>(this))
		if (QObject* parent = object->parent())
			if (QLThemeable* parent_themeable =
				dynamic_cast<QLThemeable*>(parent))
			{
				return parent_themeable;
			}

	return nullptr;
}

QString QLThemeable::_name()
{
	if (QObject* object = dynamic_cast<QObject*>(this))
		return object->objectName();

	return QString();
}

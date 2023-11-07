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

#ifndef QLAYERS_EXPORT_H
#define QLAYERS_EXPORT_H

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(QLAYERS_LIB)
#  define QLAYERS_EXPORT Q_DECL_EXPORT
# else
#  define QLAYERS_EXPORT Q_DECL_IMPORT
# endif
#else
# define QLAYERS_EXPORT
#endif

#endif // QLAYERS_EXPORT_H

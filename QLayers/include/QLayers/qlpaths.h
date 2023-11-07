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

#ifndef QLPATHS_H
#define QLPATHS_H

#include <filesystem>
#include <string>

#include "qlayers_global.h"
#include "qlayers_export.h"

QLAYERS_NAMESPACE_BEGIN

QLAYERS_EXPORT std::filesystem::path app_path(const std::string& app_name);
QLAYERS_EXPORT std::filesystem::path latest_T_version_path();
QLAYERS_EXPORT std::filesystem::path layers_path();
QLAYERS_EXPORT std::filesystem::path themes_path();
QLAYERS_EXPORT std::filesystem::path T1_path();
QLAYERS_EXPORT std::filesystem::path local_app_data_path();

QLAYERS_NAMESPACE_END

#endif // QLPATHS_H

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

#include <QLayers/qlpaths.h>

std::filesystem::path QLayers::app_path(const std::string& app_name)
{
	return local_app_data_path() / app_name;
}

std::filesystem::path QLayers::latest_T_version_path()
{
	return T1_path();
}

std::filesystem::path QLayers::layers_path()
{
	return local_app_data_path() / "Layers";
}

std::filesystem::path QLayers::themes_path()
{
	return layers_path() / "Themes";
}

std::filesystem::path QLayers::T1_path()
{
	return themes_path() / "T1";
}


std::filesystem::path QLayers::local_app_data_path()
{
	char* app_data_ptr = nullptr;
	size_t app_data_size = 0;
	if (_dupenv_s(&app_data_ptr, &app_data_size, "LOCALAPPDATA") != 0 ||
		app_data_ptr == nullptr)
	{
		throw std::runtime_error(
			"Failed to retrieve LOCALAPPDATA environment variable.");
	}

	std::string app_data_str = app_data_ptr;
	delete[] app_data_ptr;
	app_data_ptr = nullptr;

	return std::filesystem::path(app_data_str);
}

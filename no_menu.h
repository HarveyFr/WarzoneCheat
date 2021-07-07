#pragma once

bool Menu_Init() {
	printf("\nDRAWING MENU");
	androidgui::window_input(L"GDI+ Hook Window Class", L"GDI+ Window (AnyDesk.exe)");
	if (androidgui::begin_window("harvey", androidgui::vec2({ 545, 580 }), VK_INSERT, androidgui::androidgui_window_flags_none))
	{
		androidgui::checkbox("ESP", Settings::ESP);
		if (Settings::ESP) {
			androidgui::checkbox("ESP Box", Settings::ESP_Box);
			androidgui::checkbox("ESP Lines", Settings::ESP_Lines);
			androidgui::checkbox("ESP Names", Settings::ESP_Names);
			androidgui::checkbox("ESP Distance", Settings::ESP_Distance);
		}
		androidgui::separator(10, true);
		androidgui::checkbox("Aimbot", Settings::Aimbot);
		if (Settings::Aimbot) {
			androidgui::slider_int("Smoothness", 1, 20, Settings::smooth);
			androidgui::slider_int("Fov Circle Value", 30, 250, Settings::FovCircleValue);
			androidgui::checkbox("Show Fov Circle", Settings::ShowFovCircle);
		}

		androidgui::separator(10, true);

		if (androidgui::button("Unload", androidgui::vec2({ 40, 20 }))) {
			system("taskkill /f /im AnyDesk.exe");
			//system("explorer.exe");
			exit(0);
		}
		androidgui::end_window();
	}
	printf("\DREW MENU");
	return true;
}
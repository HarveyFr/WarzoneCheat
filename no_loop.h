#pragma once

bool FirstTime = true;

void ReadAddresses() {
	while (true) {
		Addresses::INFO = GetClientInfo();
		Addresses::BASE = GetClientBase(Addresses::INFO);
		Addresses::REFDEF = GetRefDef();
		Addresses::NAMES = GetNameList();
		utils::loghex("[*] Dec Info Ptr: ", Addresses::INFO);
		utils::loghex("[*] Dec Base Ptr: ", Addresses::BASE);
		utils::loghex("[*] Dec Refdef Ptr: ", Addresses::REFDEF);
		utils::loghex("[*] Name List Ptr: ", Addresses::NAMES);
		Sleep(15000);
	}
}	
ImFont* font;
static void DrawLineImGui(int x1, int y1, int x2, int y2, ImU32 color, int thickness)
{
	if (x2 != 0 && y2 != 0)
	{
		ImGui::GetOverlayDrawList()->AddLine(ImVec2(x1, y1), ImVec2(x2, y2), ImGui::ColorConvertFloat4ToU32(ImColor(color)), thickness);
	}
}
void DrawBoxImGui(int x1, int y1, int bx, int by, ImU32 color, int thickness)
{
	DrawLineImGui(x1 - (bx / 2), y1 - by, x1 - (bx / 2) + bx, y1 - by, color, thickness);
	DrawLineImGui(x1 - (bx / 2) + bx, y1 - by, x1 - (bx / 2) + bx, y1 - by + by, color, thickness);
	DrawLineImGui(x1 - (bx / 2) + bx, y1 - by + by, x1 - (bx / 2), y1 - by + by, color, thickness);
	DrawLineImGui(x1 - (bx / 2), y1 - by + by, x1 - (bx / 2), y1 - by, color, thickness);
}
//int local_index() {
//	auto local_index = driver::read<uintptr_t>(Addresses::INFO + offsets::local_index);
//	return driver::read<int>(local_index + 0x1FC);
//}
void DrawFilledRectImGui2(int x, int y, int w, int h, ImU32 color)
{
	ImGui::GetOverlayDrawList()->AddRectFilled(ImVec2(x, y), ImVec2(x + w, y + h), ImGui::ColorConvertFloat4ToU32(ImColor(color)));

}
void DrawCornerBoxImGui(int x, int y, int w, int h, int borderPx, ImU32 c)
{
	DrawFilledRectImGui2(x + borderPx, y, w / 3, borderPx, c); //top 
	DrawFilledRectImGui2(x + w - w / 3 + borderPx, y, w / 3, borderPx, c); //top 
	DrawFilledRectImGui2(x, y, borderPx, h / 3, c); //left 
	DrawFilledRectImGui2(x, y + h - h / 3 + borderPx * 2, borderPx, h / 3, c); //left 
	DrawFilledRectImGui2(x + borderPx, y + h + borderPx, w / 3, borderPx, c); //bottom 
	DrawFilledRectImGui2(x + w - w / 3 + borderPx, y + h + borderPx, w / 3, borderPx, c); //bottom 
	DrawFilledRectImGui2(x + w + borderPx, y, borderPx, h / 3, c);//right 
	DrawFilledRectImGui2(x + w + borderPx, y + h - h / 3 + borderPx * 2, borderPx, h / 3, c);//right
}

void Aimbot_Function(Vector2 Head_W2S)
{

	if (Head_W2S.y != 0 || Head_W2S.y != 0)
	{
		float ScreenCenterX = (No_Renderer_Define::Width / 2);
		float ScreenCenterY = (No_Renderer_Define::Height / 2);

		float TargetX = 0;
		float TargetY = 0;

		if (Head_W2S.x != 0)
		{
			if (Head_W2S.x > ScreenCenterX)
			{
				TargetX = -(ScreenCenterX - Head_W2S.x);
				TargetX /= Settings::smooth;
				if (TargetX + ScreenCenterX > ScreenCenterX * 2) TargetX = 0;
			}

			if (Head_W2S.x < ScreenCenterX)
			{
				TargetX = Head_W2S.x - ScreenCenterX;
				TargetX /= Settings::smooth;
				if (TargetX + ScreenCenterX < 0) TargetX = 0;
			}
		}

		if (Head_W2S.y != 0)
		{
			if (Head_W2S.y > ScreenCenterY)
			{
				TargetY = -(ScreenCenterY - Head_W2S.y);
				TargetY /= Settings::smooth;
				if (TargetY + ScreenCenterY > ScreenCenterY * 2) TargetY = 0;
			}

			if (Head_W2S.y < ScreenCenterY)
			{
				TargetY = Head_W2S.y - ScreenCenterY;
				TargetY /= Settings::smooth;
				if (TargetY + ScreenCenterY < 0) TargetY = 0;
			}
		}

		mouse_event(MOUSEEVENTF_MOVE, static_cast<DWORD>(TargetX), static_cast<DWORD>(TargetY), NULL, NULL);

		return;
	}
}
bool ActorLoop(ImDrawList* ExplorerHook) {
	if (FirstTime) {
		No_Define::ProcessID = driver::get_process_id("ModernWarfare.exe");
		No_Define::BaseAddress = driver::get_module_base_address("ModernWarfare.exe");
		No_Define::PEB = driver::get_peb();
		std::cout << "ProcessID: " << No_Define::ProcessID << "\n";
		std::cout << "Base Address: " << No_Define::BaseAddress << "\n";
		std::cout << "PEB: " << No_Define::PEB << "\n";
		std::thread ReadAddressesThread(ReadAddresses);	ReadAddressesThread.detach();

		FirstTime = false;
	}

	if (!Addresses::BASE || !Addresses::NAMES) return false;

	Vector3 LocalPlayerPosition = Framework->GetLocalPlayerPosition();
	auto RefDef = driver::read<refdef_t>(Addresses::REFDEF);

	Vector2 Bottom_W2S;
	Vector2 Head_W2S;

	for (int i = 0; i < 155; i++) {
		
		Player* CurrentActor = Player::GetCurrentActor(i);
//		Player* LocalActor = Player::GetLocalActor();
		//if (LocalActor == CurrentActor) continue;
		NameEntry Name_Entry = CurrentActor->GetNameEntry();
		if (!is_bad_ptr(CurrentActor) && !CurrentActor->isDead() && Name_Entry.health > 0) {
			
			Vector3 Bottom_No_W2S = CurrentActor->GetBottomPos();
			Vector3 Head_No_W2S = Bottom_No_W2S + Vector3(0.0, 0.0, 58.0);
			int Distance = LocalPlayerPosition.Distance(Bottom_No_W2S) / 40;
			if (Distance < Settings::ESP_MaxDistance){ //and Framework->IsInScreen(CurrentActor, LocalPlayerPosition, RefDef, No_Renderer_Define::Width, No_Renderer_Define::Height)) {
				Bottom_W2S = Framework->WorldToScreen(Bottom_No_W2S, LocalPlayerPosition, RefDef.width, RefDef.height, RefDef.view.tanHalfFov, RefDef.view.axis);
				Head_W2S = Framework->WorldToScreen(Head_No_W2S, LocalPlayerPosition, RefDef.width, RefDef.height, RefDef.view.tanHalfFov, RefDef.view.axis);

				float PawnHeight = Bottom_W2S.y - Head_W2S.y; float PawnWidth = PawnHeight / 4.0;

				Vector2 Pelvis_W2S = Vector2(Head_W2S.x, Head_W2S.y + PawnHeight / 2);

				//////////////////////////////////////////////////// E S P ////////////////////////////////////////////////////
				float BoxHeight = Head_W2S.y - Bottom_W2S.y;
				float BoxWidth = (BoxHeight / 2) * 1.25f;
				//Box
				if (Settings::ESP_Box) {
					DrawCornerBoxImGui(Head_W2S.x, Head_W2S.y, BoxWidth, PawnHeight, 1 , ImColor(255, 255, 255));
				}

				if (Settings::Aimbot)
				{
					if (GetAsyncKeyState(VK_RBUTTON) & 0x8000)
					{
						Aimbot_Function(Head_W2S);
					}
				}

				//Lines
				if (Settings::ESP_Lines) {
					ExplorerHook->AddLine(ImVec2(No_Renderer_Define::Width / 2, No_Renderer_Define::Height), ImVec2(Pelvis_W2S.x, Pelvis_W2S.y), ImColor(255, 255, 255));
				}

				//Names
				if ((Settings::ESP_Names or Settings::ESP_Distance) or (Settings::ESP_Names and Settings::ESP_Distance)) {
					
					std::string FullString;

					if (Settings::ESP_Names) {
						FullString = FullString + "[ " + Name_Entry.name + " ]  ";
					}

					if (Settings::ESP_Distance) {
						FullString = FullString + "[" + std::to_string(Distance) + "m] ";
					}

					int txtwidth, txtheight; androidgui::functions.get_text_size(FullString.c_str(), txtwidth, txtheight);


					ExplorerHook->AddText(ImVec2(Head_W2S.x - (txtwidth / 2), (Head_W2S.y - txtheight / 2) - 3), ImColor(255, 255, 255), FullString.c_str());

				}
			}
		}
	}

	return true;
}
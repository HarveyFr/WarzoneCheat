#pragma once

/* ==== STRUCTS ===================*/
struct RefdefView {
	Vector2 tanHalfFov;		// 0x00
	uint8_t unk1[0xC];		// 0x08
	Vector3 axis[3];      // 0x14
};

struct refdef_t {
	int x;           // 0x00
	int y;           // 0x04
	int width;       // 0x08
	int height;      // 0x0C
	RefdefView view; // 0x10
};

struct refdefKeyStruct
{
	DWORD ref0; // 0x00
	DWORD ref1; // 0x04
	DWORD ref2; // 0x08
};

struct NameEntry {
	uint32_t idx;
	char name[0x24];
	uint8_t unk1[0x64];
	uint32_t health;
};
/* =================================*/


bool is_bad_ptr(void* adr) { return adr == nullptr; }
namespace utils {
	
	void log(const char* str) {
		std::cout << str << std::endl;
	}
	void loghex(const char* str, uint64_t val) {
		std::cout << str << std::hex << val << std::endl;
	}
}


namespace offsets {
	constexpr auto Camera_Base = 0x14417F80; // ok

	constexpr auto Camera_Pos = 0x1D8; // ok

	constexpr auto CLIENT_INFO = 0x17219218; // ok

	constexpr auto CLIENT_BASE = 0x9DBF8; // ok

	constexpr auto Ref_Def = 0x1721BBB0; // ok

	constexpr auto Dead_1 = 0x64BD;// ok

	constexpr auto Dead_2 = 0x7FB0;// ok

	constexpr auto Player_Pos_Info = 0x448; // ok

	constexpr auto Player_Size = 0x3AA8; // ok

	constexpr auto Player_Team = 0x2DF4; // ok

	constexpr auto Player_Valid = 0x488; // ok

	constexpr auto Name_Array = 0x17226E58; // ok

	constexpr auto Name_Array_Padding = 0x4C70; // ok

	constexpr auto Name_Size = 0xD0; // ok
}


namespace decryption
{

	auto DecryptClientInfo(uint64_t enc_client) -> uint64_t
	{
		uint64_t RAX = 0, RBX = 0, RCX = 0, RDX = 0, R8 = 0, RDI = 0, RSI = 0, R9 = 0, R10 = 0, R11 = 0, R12 = 0, R13 = 0, R14 = 0, R15 = 0;

		RBX = driver::read<uint64_t>(No_Define::BaseAddress + 0x17219218);
		RCX = No_Define::PEB; // mov rcx,gs:[rax]
		RCX = ~RCX;
		RDX = 0x6D70CEFD9593A4F9;
		RAX = 0x0;
		RAX = _rotl64(RAX, 0x10);
		RAX ^= driver::read<uint64_t>(No_Define::BaseAddress +0x660310D);
		RAX = _byteswap_uint64(RAX);
		RBX *= driver::read<uint64_t>(RAX + 0x17);
		RAX = RBX;
		RAX >>= 0x24;
		RBX ^= RAX;
		RAX = 0x3938DE18C6D75C93;
		RBX *= RDX;
		RBX += RAX;
		RBX ^= RCX;
		RBX ^= R8;
		return RBX;
	}
 
	/*
	auto DecryptClientInfo(uint64_t enc_client) -> uint64_t
	{
		uint64_t RAX = 0, RBX = 0, RCX = 0, RDX = 0, R8 = 0, RDI = 0, R9 = 0, R10 = 0, R11 = 0, R12 = 0, R13 = 0, R14 = 0, RSI = 0, RSP = 0, RBP = 0;
		RBX = enc_client;
		if (!RBX)
			return 0;

		R8 = No_Define::BaseAddress;
		RCX = globals::peb;
		RCX = (~RCX);
		RAX = No_Define::BaseAddress;
		RDX = No_Define::BaseAddress + 0xE9D;
		RAX -= RDX;
		RCX += RBX;
		RAX = 0; // Special case
		RCX += R8;
		RAX = _rotl64(RAX, 0x10);
		RDX = 0xD0FDC0E5AC56A3F1;
		RAX ^= driver::driver::read<uint64_t>(No_Define::BaseAddress + 0x68FE0DC);
		RCX *= RDX;
		RAX = _byteswap_uint64(RAX);
		RDX = 0x7C09AF42D8BF321D;
		RCX += RDX;
		if (utils::is_bad_ptr((void*)(RAX + 0x17))) return 0xFFFFFFFFFFFFFFFF;
		RAX = driver::driver::read<uint64_t>(RAX + 0x17);
		RAX *= RCX;
		RBX = RAX;
		RBX >>= 0x27;
		RBX ^= RAX;
		RBX += R8;
		return RBX;
	}
	*/

	/////////////////////////////////////////SEPARATOREEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE//////////////////////////////////////


	auto DecryptClientBase(uint64_t client_info) -> uint64_t
	{
		uint64_t RAX = 0, RBX = 0, RCX = 0, RDX = 0, R8 = 0, RDI = 0, RSI = 0, R9 = 0, R10 = 0, R11 = 0, R12 = 0, R13 = 0, R14 = 0, R15 = 0, RSP = 0, RBP = 0;

		RAX = driver::read<uint64_t>(client_info + 0x9DBF8);
		RBX = No_Define::PEB; // mov rbx,gs:[rcx]
		// test rax,rax
		// je 00007FF670623D55h
		RCX = RBX;
		RCX >>= 0xF;
		RCX &= 0xF;
		// cmp rcx,0Eh
		// ja 00007FF6706238FBh
		switch (RCX) {
		case 0: { // Correct
			R14 = No_Define::BaseAddress + 0x3C431634;
			R10 = driver::read<uint64_t>(No_Define::BaseAddress + 0x6603146);
			RCX = 0x2C52EE7E5CA1CE96;
			RAX -= RCX;
			RCX = 0x0;
			RCX = _rotl64(RCX, 0x10);
			RCX ^= R10;
			RCX = ~RCX;
			RAX *= driver::read<uint64_t>(RCX + 0x9);
			RCX = RBX;
			RCX ^= R14;
			RAX -= RCX;
			RAX += RBX;
			RCX = RAX;
			RCX >>= 0x14;
			RAX ^= RCX;
			RCX = RAX;
			RCX >>= 0x28;
			RAX ^= RCX;
			RAX += RBX;
			RCX = 0x9C83A6ED81709013;
			RAX *= RCX;
			RCX = 0x709DC8ADED0BA319;
			RAX += RCX;
			return RAX;
		}
		case 1: { // Correct
			R9 = driver::read<uint64_t>(No_Define::BaseAddress + 0x6603146);
			RCX = 0x1A69AD46E3A25C75;
			RAX -= RCX;
			RCX = RAX;
			RCX >>= 0xC;
			RAX ^= RCX;
			RCX = RAX;
			RCX >>= 0x18;
			RAX ^= RCX;
			RCX = RAX;
			RCX >>= 0x30;
			RCX ^= RBX;
			RAX ^= RCX;
			RCX = 0x6ECEBD9C03D02936;
			RAX -= RCX;
			RCX = No_Define::BaseAddress;
			RAX += RCX;
			RCX = 0x0;
			RCX = _rotl64(RCX, 0x10);
			RCX ^= R9;
			RCX = ~RCX;
			RCX = driver::read<uint64_t>(RCX + 0x9);
			RBP = 0x3CE1F452114BE5D;
			RCX *= RBP;
			RAX *= RCX;
			RAX += RBX;
			return RAX;
		}
		case 2: {
			R11 = No_Define::BaseAddress + 0xAE07;
			RDX = driver::read<uint64_t>(No_Define::BaseAddress + 0x6603146);
			RAX += RBX;
			RCX = RAX;
			RCX >>= 0x13;
			RAX ^= RCX;
			RCX = RAX;
			RCX >>= 0x26;
			RAX ^= RCX;
			RCX = 0x337FEE03C131D861;
			RAX ^= RCX;
			RCX = 0xBCA9BFAF51DA6757;
			RAX *= RCX;
			RCX = 0x5434E82D28CC28F9;
			RAX -= RCX;
			RCX = 0x0;
			RCX = _rotl64(RCX, 0x10);
			RCX ^= RDX;
			RCX = ~RCX;
			RAX *= driver::read<uint64_t>(RCX + 0x9);
			RCX = No_Define::BaseAddress;
			RAX -= RCX;
			RAX += 0xFFFFFFFFE2253F2C;
			RAX += RBX;
			RCX = R11;
			RCX = ~RCX;
			RCX += RBX;
			RAX ^= RCX;
			return RAX;
		}
		case 3: {
			R10 = driver::read<uint64_t>(No_Define::BaseAddress + 0x6603146);
			R15 = No_Define::BaseAddress + 0x576A2168;
			RCX = 0x0;
			RCX = _rotl64(RCX, 0x10);
			RCX ^= R10;
			RCX = ~RCX;
			RCX = driver::read<uint64_t>(RCX + 0x9);
			RSP = 0x8035B07E6320667D;
			RCX *= RSP;
			RAX *= RCX;
			RCX = RBX;
			RCX *= R15;
			RCX ^= RBX;
			RAX ^= RCX;
			RCX = No_Define::BaseAddress;
			RAX -= RBX;
			RAX -= RCX;
			RAX -= 0x31E8;
			RCX = RAX;
			RCX >>= 0x1;
			RAX ^= RCX;
			RCX = RAX;
			RCX >>= 0x2;
			RAX ^= RCX;
			RCX = RAX;
			RCX >>= 0x4;
			RAX ^= RCX;
			RCX = RAX;
			RCX >>= 0x8;
			RAX ^= RCX;
			RCX = RAX;
			RCX >>= 0x10;
			RAX ^= RCX;
			RCX = RAX;
			RCX >>= 0x20;
			RAX ^= RCX;
			RCX = RAX;
			RCX >>= 0x4;
			RAX ^= RCX;
			RCX = RAX;
			RCX >>= 0x8;
			RAX ^= RCX;
			RCX = RAX;
			RCX >>= 0x10;
			RAX ^= RCX;
			RCX = RAX;
			RCX >>= 0x20;
			RAX ^= RCX;
			RCX = RAX;
			RCX >>= 0x1E;
			RAX ^= RCX;
			RCX = RAX;
			RCX >>= 0x3C;
			RAX ^= RCX;
			return RAX;
		}
		case 4: {
			R9 = driver::read<uint64_t>(No_Define::BaseAddress + 0x6603146);
			RCX = No_Define::BaseAddress;
			RCX += 0x281F;
			RCX += RBX;
			RAX ^= RCX;
			RCX = 0xDF286BBF83F616D1;
			RAX *= RCX;
			RCX = RAX;
			RCX >>= 0x8;
			RAX ^= RCX;
			RCX = RAX;
			RCX >>= 0x10;
			RAX ^= RCX;
			RCX = RAX;
			RCX >>= 0x20;
			RAX ^= RCX;
			RCX = No_Define::BaseAddress;
			RAX ^= RCX;
			RAX -= RCX;
			RAX += 0xFFFFFFFFE4385B97;
			RAX += RBX;
			RCX = 0x0;
			RCX = _rotl64(RCX, 0x10);
			RCX ^= R9;
			RCX = ~RCX;
			RAX *= driver::read<uint64_t>(RCX + 0x9);
			RCX = 0x4A4FFCF706C23293;
			RAX -= RCX;
			RCX = RAX;
			RCX >>= 0x22;
			RAX ^= RCX;
			return RAX;
		}
		case 5: {
			R10 = driver::read<uint64_t>(No_Define::BaseAddress + 0x6603146);
			RCX = No_Define::BaseAddress + 0x9128;
			RCX -= RBX;
			RAX += RCX;
			RCX = RAX;
			RCX >>= 0x26;
			RDX = 0x0;
			RCX ^= RAX;
			RDX = _rotl64(RDX, 0x10);
			RCX -= RBX;
			RDX ^= R10;
			RDX = ~RDX;
			RAX = driver::read<uint64_t>(RDX + 0x9);
			RAX *= RCX;
			RCX = 0x347EE6669F93372E;
			RAX -= RCX;
			RCX = 0xCC4AC21D5E07EAFD;
			RAX *= RCX;
			RCX = No_Define::BaseAddress;
			RAX -= RCX;
			RAX += 0xFFFFFFFFC0A98326;
			RAX += RBX;
			RCX = 0x25D8C69821A4B1C1;
			RAX *= RCX;
			return RAX;
		}
		case 6: {
			R10 = driver::read<uint64_t>(No_Define::BaseAddress + 0x6603146);
			RCX = No_Define::BaseAddress;
			RAX -= RCX;
			RAX += 0xFFFFFFFFFFFF0A85;
			RAX += RBX;
			RCX = 0xDD3029A8BCE8D4D;
			RAX *= RCX;
			RDX = 0x0;
			RDX = _rotl64(RDX, 0x10);
			RCX = 0xFCFBF307C71E86A5;
			RAX ^= RCX;
			RDX ^= R10;
			RCX = No_Define::BaseAddress;
			RDX = ~RDX;
			RAX -= RCX;
			RCX = RBX + 18446744073709487871;
			RCX += RAX;
			RAX = No_Define::BaseAddress + 0x48A8C848;
			RAX = ~RAX;
			RAX *= RBX;
			RCX ^= RAX;
			RAX = driver::read<uint64_t>(RDX + 0x9);
			RAX *= RCX;
			RCX = RAX;
			RCX >>= 0x24;
			RAX ^= RCX;
			RCX = 0x2F5690490931B637;
			RAX *= RCX;
			return RAX;
		}
		case 7: {
			R14 = No_Define::BaseAddress + 0x2491D7D9;
			R9 = driver::read<uint64_t>(No_Define::BaseAddress + 0x6603146);
			RCX = 0x635E4B2FC3D0A10D;
			RAX *= RCX;
			RCX = R14;
			RCX = ~RCX;
			RCX ^= RBX;
			RAX += RCX;
			RCX = 0x51256D5DC16562EC;
			RAX ^= RCX;
			RCX = RAX;
			RCX >>= 0x6;
			RAX ^= RCX;
			RCX = RAX;
			RCX >>= 0xC;
			RAX ^= RCX;
			RCX = RAX;
			RCX >>= 0x18;
			RAX ^= RCX;
			RCX = RAX;
			RCX >>= 0x30;
			RAX ^= RCX;
			RCX = RBX;
			RSP = No_Define::BaseAddress + 0x5E98C991;
			RCX *= RSP;
			RAX += RCX;
			RCX = No_Define::BaseAddress;
			RAX -= RCX;
			RCX = RAX;
			RCX >>= 0xC;
			RAX ^= RCX;
			RCX = RAX;
			RCX >>= 0x18;
			RAX ^= RCX;
			RCX = RAX;
			RCX >>= 0x30;
			RAX ^= RCX;
			RCX = 0x0;
			RCX = _rotl64(RCX, 0x10);
			RCX ^= R9;
			RCX = ~RCX;
			RAX *= driver::read<uint64_t>(RCX + 0x9);
			return RAX;
		}
		case 8: {
			R10 = driver::read<uint64_t>(No_Define::BaseAddress + 0x6603146);
			RDX = 0x0;
			RDX = _rotl64(RDX, 0x10);
			RDX ^= R10;
			RCX = 0xF9180DCDF5F228B4;
			RCX += RAX;
			RDX = ~RDX;
			RAX = driver::read<uint64_t>(RDX + 0x9);
			RAX *= RCX;
			RAX += RBX;
			RCX = RAX;
			RCX >>= 0x5;
			RAX ^= RCX;
			RCX = RAX;
			RCX >>= 0xA;
			RAX ^= RCX;
			RCX = RAX;
			RCX >>= 0x14;
			RAX ^= RCX;
			RCX = RAX;
			RCX >>= 0x28;
			RAX ^= RCX;
			RCX = No_Define::BaseAddress;
			RAX ^= RCX;
			RCX = 0xEE1131A827DCAA68;
			RAX -= RBX;
			RAX ^= RCX;
			RCX = 0xB6B2FC7C21D1D489;
			RAX *= RCX;
			return RAX;
		}
		case 9: {
			R15 = No_Define::BaseAddress + 0x74E0B964;
			R10 = driver::read<uint64_t>(No_Define::BaseAddress + 0x6603146);
			RAX += RBX;
			RCX = No_Define::BaseAddress + 0x2E0E6E37;
			RAX += RCX;
			RCX = 0xFA547910F03B3987;
			RAX *= RCX;
			RCX = No_Define::BaseAddress + 0x91DC;
			RCX = ~RCX;
			RCX *= RBX;
			RAX ^= RCX;
			RCX = RAX;
			RCX >>= 0x2;
			RAX ^= RCX;
			RCX = RAX;
			RCX >>= 0x4;
			RAX ^= RCX;
			RCX = RAX;
			RCX >>= 0x8;
			RAX ^= RCX;
			RCX = RAX;
			RCX >>= 0x10;
			RAX ^= RCX;
			RCX = RAX;
			RCX >>= 0x20;
			RAX ^= RCX;
			RCX = RAX;
			RCX >>= 0xB;
			RAX ^= RCX;
			RCX = RAX;
			RCX >>= 0x16;
			RAX ^= RCX;
			RCX = RAX;
			RCX >>= 0x2C;
			RAX ^= RCX;
			RCX = No_Define::BaseAddress;
			RAX ^= RCX;
			RCX = 0x0;
			RCX = _rotl64(RCX, 0x10);
			RCX ^= R10;
			RCX = ~RCX;
			RAX *= driver::read<uint64_t>(RCX + 0x9);
			RCX = R15;
			RCX = ~RCX;
			RCX ^= RBX;
			RAX += RCX;
			return RAX;
		}
		case 10: {
			R10 = driver::read<uint64_t>(No_Define::BaseAddress + 0x6603146);
			RCX = RAX;
			RCX >>= 0x1B;
			RAX ^= RCX;
			RCX = RAX;
			RCX >>= 0x36;
			RAX ^= RCX;
			RCX = RAX;
			RCX >>= 0x22;
			RCX ^= RBX;
			RAX ^= RCX;
			RCX = RAX;
			RCX >>= 0x15;
			RAX ^= RCX;
			RCX = RAX;
			RCX >>= 0x2A;
			RAX ^= RCX;
			RCX = 0x0;
			RCX = _rotl64(RCX, 0x10);
			RCX ^= R10;
			RCX = ~RCX;
			RAX *= driver::read<uint64_t>(RCX + 0x9);
			RCX = 0x5D93FBAC7F625877;
			RAX *= RCX;
			RCX = 0x52B757443CDBD28B;
			RAX += RCX;
			RCX = 0x5E17A54EAA80B6A5;
			RAX *= RCX;
			return RAX;
		}
		case 11: {
			R10 = driver::read<uint64_t>(No_Define::BaseAddress + 0x6603146);
			RCX = 0x4041D2698092818B;
			RAX *= RCX;
			RCX = 0x6E7B1B11ABDFF2FA;
			RAX ^= RCX;
			RDX = 0x0;
			RDX = _rotl64(RDX, 0x10);
			RCX = RBX + RAX;
			RDX ^= R10;
			RDX = ~RDX;
			RAX = driver::read<uint64_t>(RDX + 0x9);
			RAX *= RCX;
			RCX = RAX;
			RCX >>= 0x14;
			RAX ^= RCX;
			RCX = RAX;
			RCX >>= 0x28;
			RAX ^= RCX;
			RCX = RAX;
			RCX >>= 0x6;
			RAX ^= RCX;
			RCX = RAX;
			RCX >>= 0xC;
			RAX ^= RCX;
			RCX = RAX;
			RCX >>= 0x18;
			RAX ^= RCX;
			RCX = RAX;
			RCX >>= 0x30;
			RAX ^= RCX;
			RCX = 0x40077D00487E24C2;
			RAX += RCX;
			RAX -= RBX;
			return RAX;
		}
		case 12: {
			R9 = driver::read<uint64_t>(No_Define::BaseAddress + 0x6603146);
			R11 = No_Define::BaseAddress + 0x1263;
			RCX = 0xA8101149FD4CA7C3;
			RAX *= RCX;
			R15 = 0x4EC0B4781CB32BBF;
			RCX = RBX;
			RCX = ~RCX;
			RCX *= R11;
			RCX += R15;
			RAX += RCX;
			RCX = 0x0;
			RCX = _rotl64(RCX, 0x10);
			RCX ^= R9;
			RCX = ~RCX;
			RAX *= driver::read<uint64_t>(RCX + 0x9);
			RCX = RAX;
			RCX >>= 0x1E;
			RAX ^= RCX;
			RCX = RAX;
			RCX >>= 0x3C;
			RAX ^= RCX;
			RAX ^= RBX;
			RCX = 0x4E80F1A0C98C468;
			RAX += RCX;
			RAX -= RBX;
			return RAX;
		}
		case 13: {
			R10 = driver::read<uint64_t>(No_Define::BaseAddress + 0x6603146);
			R11 = No_Define::BaseAddress + 0x6267F8D9;
			RCX = 0x0;
			RCX = _rotl64(RCX, 0x10);
			RCX ^= R10;
			RCX = ~RCX;
			RCX = driver::read<uint64_t>(RCX + 0x9);
			RAX *= RCX;
			RCX = 0x87FBBF81F585A7F5;
			RAX *= RCX;
			RCX = No_Define::BaseAddress;
			RAX += RCX;
			RCX = RBX + RAX;
			RAX = 0xE2DF381128AD7D;
			RCX ^= RAX;
			RAX = RCX;
			RAX >>= 0x15;
			RCX ^= RAX;
			RAX = RCX;
			RAX >>= 0x2A;
			RAX ^= RCX;
			RCX = R11;
			RCX = ~RCX;
			RAX -= RBX;
			RAX += RCX;
			RCX = No_Define::BaseAddress;
			RAX -= RCX;
			return RAX;
		}
		case 14: {
			R11 = driver::read<uint64_t>(No_Define::BaseAddress + 0x6603146);
			RDX = No_Define::BaseAddress + 0xB8FD;
			RCX = RBX;
			RCX *= RDX;
			R8 = 0x0;
			R8 = _rotl64(R8, 0x10);
			R8 ^= R11;
			RDX = RAX + RCX;
			R8 = ~R8;
			RAX = No_Define::BaseAddress + 0x3DA2C48A;
			RDX += RAX;
			RAX = driver::read<uint64_t>(R8 + 0x9);
			RAX *= RDX;
			RCX = RAX;
			RCX >>= 0x15;
			RAX ^= RCX;
			RCX = RAX;
			RCX >>= 0x2A;
			RAX ^= RCX;
			RCX = 0x63F739E7ACE8DEFA;
			RAX -= RCX;
			RCX = 0xECA41A7D230C65B;
			RAX *= RCX;
			return RAX;
		}
		case 15: {
			R15 = No_Define::BaseAddress + 0x4A2;
			R10 = driver::read<uint64_t>(No_Define::BaseAddress + 0x6603146);
			RCX = No_Define::BaseAddress;
			RAX -= RCX;
			RCX = RAX;
			RCX >>= 0x15;
			RAX ^= RCX;
			RCX = RAX;
			RCX >>= 0x2A;
			RDX = 0x0;
			RCX ^= RAX;
			RDX = _rotl64(RDX, 0x10);
			RDX ^= R10;
			RDX = ~RDX;
			RAX = driver::read<uint64_t>(RDX + 0x9);
			RAX *= RCX;
			RAX += RBX;
			RCX = 0xC3EBCF9689C9BEB;
			RAX *= RCX;
			RCX = 0x7631FAD984D70CD9;
			RAX *= RCX;
			RCX = 0x2D351ADE4F41F93F;
			RAX += RCX;
			RAX ^= RBX;
			RAX ^= R15;
			return RAX;
		}
		}

	}

	/*
	auto DecryptClientBase(uint64_t client_info) -> uint64_t
	{
		uint64_t RAX = No_Define::BaseAddress, RBX = No_Define::BaseAddress, RCX = No_Define::BaseAddress, RDX = No_Define::BaseAddress, R8 = No_Define::BaseAddress, RDI = No_Define::BaseAddress, R9 = No_Define::BaseAddress, R10 = No_Define::BaseAddress, R11 = No_Define::BaseAddress, R12 = No_Define::BaseAddress, R13 = No_Define::BaseAddress, R14 = No_Define::BaseAddress, R15 = No_Define::BaseAddress, RSI = No_Define::BaseAddress, RSP = No_Define::BaseAddress, RBP = No_Define::BaseAddress;
		RAX = client_info;
		if (!RAX)
			return 0;
		RDI = globals::peb;
		// test rax,rax
		// je near ptr 00000000020648E4h
		RCX = RDI;
		RCX >>= 0x17;
		// and ecx,0Fh
		RCX &= 0xF;
		switch (RCX)
		{
		case 0:
		{
			R9 = driver::driver::read<uint64_t>(No_Define::BaseAddress + 0x68FE117);
			RSI = No_Define::BaseAddress + 0x6AC;
			// mov rcx,[rbp+0E8h]
			RCX -= RSI;
			RCX = 0; // Special case
			RCX = _rotl64(RCX, 0x10);
			RCX ^= R9;
			RCX = _byteswap_uint64(RCX);
			if (utils::is_bad_ptr((void*)(RCX + 0x11))) return 0xFFFFFFFFFFFFFFFF; RAX *= driver::driver::read<uint64_t>(RCX + 0x11);
			RCX = No_Define::BaseAddress;
			RAX += RCX;
			RCX = 0x5CD525BAF45D4153;
			RAX *= RCX;
			RCX = RAX;
			RCX >>= 0x4;
			RAX ^= RCX;
			RCX = RAX;
			RCX >>= 0x8;
			RAX ^= RCX;
			RCX = RAX;
			RCX >>= 0x10;
			RAX ^= RCX;
			RCX = RAX;
			RCX >>= 0x20;
			RAX ^= RCX;
			RCX = 0x3E9F9DBB6E66EB1A;
			RAX ^= RCX;
			RCX = No_Define::BaseAddress;
			RAX -= RCX;
			RAX += 0xFFFFFFFF856D9D0D;
			RAX += RDI;
			RCX = RAX;
			RCX >>= 0x6;
			RAX ^= RCX;
			RCX = RAX;
			RCX >>= 0xC;
			RAX ^= RCX;
			RCX = RAX;
			RCX >>= 0x18;
			RAX ^= RCX;
			RCX = RAX;
			RCX >>= 0x30;
			RAX ^= RCX;
			RCX = RAX;
			RCX >>= 0xE;
			RAX ^= RCX;
			RCX = RAX;
			RCX >>= 0x1C;
			RAX ^= RCX;
			RCX = RAX;
			RCX >>= 0x38;
			RAX ^= RCX;
			return RAX;
		}
		case 1:
		{
			R10 = driver::driver::read<uint64_t>(No_Define::BaseAddress + 0x68FE117);
			RSI = No_Define::BaseAddress + 0x6AC;
			R15 = No_Define::BaseAddress + 0x64C85167;
			RDX = RDI;
			RDX = (~RDX);
			RCX = No_Define::BaseAddress + 0x4224;
			RCX = (~RCX);
			RDX *= RCX;
			RCX = 0xACCE08093FB3EFFD;
			RAX ^= RDX;
			RAX *= RCX;
			RCX = 0x5FB21A878C77BA33;
			RAX += RCX;
			RCX = R15;
			RCX = (~RCX);
			RCX += RDI;
			RAX ^= RCX;
			RCX = 0x22C2431C8FB82D9B;
			RAX += RCX;
			RCX = RAX;
			RCX >>= 0x1C;
			RAX ^= RCX;
			RCX = RAX;
			RCX >>= 0x38;
			RAX ^= RCX;
			RCX = RAX;
			RCX >>= 0x14;
			RAX ^= RCX;
			RCX = RAX;
			// mov rdx,[rbp+0E8h]
			RDX -= RSI;
			RCX >>= 0x28;
			RDX = 0; // Special case
			RCX ^= RAX;
			RDX = _rotl64(RDX, 0x10);
			RDX ^= R10;
			RDX = _byteswap_uint64(RDX);
			if (utils::is_bad_ptr((void*)(RDX + 0x11))) return 0xFFFFFFFFFFFFFFFF; RAX = driver::driver::read<uint64_t>(RDX + 0x11);
			RAX *= RCX;
			return RAX;
		}
		case 2:
		{
			RBX = driver::driver::read<uint64_t>(No_Define::BaseAddress + 0x68FE117);
			RSI = No_Define::BaseAddress + 0x6AC;
			RCX = 0xD6D9DEEDA5248D76;
			RAX ^= RCX;
			RCX = RAX;
			RCX >>= 0x11;
			RAX ^= RCX;
			RCX = RAX;
			RCX >>= 0x22;
			RAX ^= RCX;
			R8 = RDI;
			R8 = (~R8);
			// mov r9,[rbp+0E8h]
			R9 -= RSI;
			R9 = 0; // Special case
			R9 = _rotl64(R9, 0x10);
			RCX = No_Define::BaseAddress + 0x2EC9;
			R9 ^= RBX;
			RDX = 0xDDE2E61B691384A0;
			RDX += RAX;
			RCX = (~RCX);
			RDX ^= R8;
			RAX = No_Define::BaseAddress + 0x20F5092D;
			RAX ^= RDX;
			RAX += R8;
			RCX += RAX;
			R9 = _byteswap_uint64(R9);
			if (utils::is_bad_ptr((void*)(R9 + 0x11))) return 0xFFFFFFFFFFFFFFFF; RAX = driver::driver::read<uint64_t>(R9 + 0x11);
			RAX *= RCX;
			RAX ^= RDI;
			RCX = 0x565E27B475312525;
			RAX *= RCX;
			return RAX;
		}
		case 3:
		{
			R10 = driver::driver::read<uint64_t>(No_Define::BaseAddress + 0x68FE117);
			RSI = No_Define::BaseAddress + 0x6AC;
			R11 = No_Define::BaseAddress + 0x7D269E03;
			RCX = 0xB179BC20C4853E9B;
			RAX *= RCX;
			RCX = No_Define::BaseAddress;
			RAX -= RCX;
			RCX = 0x4A9F7DDA7B6600D7;
			RAX -= RCX;
			RCX = RAX;
			RCX >>= 0x22;
			RAX ^= RCX;
			RCX = RAX;
			RCX >>= 0x8;
			RAX ^= RCX;
			RCX = RAX;
			RCX >>= 0x10;
			RAX ^= RCX;
			RCX = RAX;
			RCX >>= 0x20;
			RAX ^= RCX;
			// mov rdx,[rbp+0E8h]
			RCX = 0x67EE65DA588AACB0;
			RCX += RAX;
			RDX -= RSI;
			RDX = 0; // Special case
			RDX = _rotl64(RDX, 0x10);
			RDX ^= R10;
			RDX = _byteswap_uint64(RDX);
			if (utils::is_bad_ptr((void*)(RDX + 0x11))) return 0xFFFFFFFFFFFFFFFF; RAX = driver::driver::read<uint64_t>(RDX + 0x11);
			RAX *= RCX;
			RCX = RDI;
			RCX ^= R11;
			RAX -= RCX;
			return RAX;
		}
		case 4:
		{
			RSI = No_Define::BaseAddress + 0x6AC;
			R11 = No_Define::BaseAddress + 0x379408E5;
			R9 = driver::driver::read<uint64_t>(No_Define::BaseAddress + 0x68FE117);
			// mov rcx,[rbp+0E8h]
			RCX -= RSI;
			RCX = 0; // Special case
			RCX = _rotl64(RCX, 0x10);
			RCX ^= R9;
			RCX = _byteswap_uint64(RCX);
			if (utils::is_bad_ptr((void*)(RCX + 0x11))) return 0xFFFFFFFFFFFFFFFF; RCX = driver::driver::read<uint64_t>(RCX + 0x11);
			RSP = 0x62E007A4AB5B56AB;
			RCX *= RSP;
			RAX *= RCX;
			RCX = RDI;
			RCX = (~RCX);
			RCX ^= R11;
			RAX += RCX;
			RCX = RAX;
			RCX >>= 0x15;
			RAX ^= RCX;
			RCX = RAX;
			RCX >>= 0x2A;
			RAX ^= RCX;
			RAX ^= RDI;
			RCX = 0xC1E61306CF319D97;
			RAX *= RCX;
			RCX = 0xF6A67E73491A1EFB;
			RCX -= No_Define::BaseAddress;
			RAX += RCX;
			return RAX;
		}
		case 5:
		{
			RSI = No_Define::BaseAddress + 0x6AC;
			R10 = driver::driver::read<uint64_t>(No_Define::BaseAddress + 0x68FE117);
			RCX = No_Define::BaseAddress;
			RAX = RAX + RCX * 0x2;
			RAX ^= RCX;
			RCX = 0x76E88693C2A89DC9;
			RAX *= RCX;
			RCX = No_Define::BaseAddress;
			RAX ^= RCX;
			// mov rdx,[rbp+0E8h]
			RDX -= RSI;
			RDX = 0; // Special case
			RCX = RDI + RAX;
			RDX = _rotl64(RDX, 0x10);
			RAX = No_Define::BaseAddress + 0x2D9B;
			RCX += RAX;
			RDX ^= R10;
			RDX = _byteswap_uint64(RDX);
			if (utils::is_bad_ptr((void*)(RDX + 0x11))) return 0xFFFFFFFFFFFFFFFF; RAX = driver::driver::read<uint64_t>(RDX + 0x11);
			RAX *= RCX;
			RCX = RAX;
			RCX >>= 0x26;
			RAX ^= RCX;
			return RAX;
		}
		case 6:
		{
			RSI = No_Define::BaseAddress + 0x6AC;
			R15 = No_Define::BaseAddress + 0x25792B82;
			R10 = driver::driver::read<uint64_t>(No_Define::BaseAddress + 0x68FE117);
			RCX = No_Define::BaseAddress;
			RDX = RCX + 0x44E66251;
			RCX += RAX;
			RDX += RDI;
			RDX ^= RCX;
			RCX = RDX;
			RAX = RDX;
			RCX >>= 0xE;
			RAX ^= RCX;
			RCX = RAX;
			RCX >>= 0x1C;
			RAX ^= RCX;
			RDX = No_Define::BaseAddress + 0x3ED51D49;
			RCX = RAX;
			RCX >>= 0x38;
			RAX ^= RCX;
			RCX = RDI;
			RCX ^= RDX;
			RAX -= RCX;
			RCX = RDI;
			RCX *= R15;
			RAX ^= RCX;
			RCX = No_Define::BaseAddress;
			RAX += RCX;
			// mov rcx,[rbp+0E8h]
			RCX -= RSI;
			RCX = 0; // Special case
			RCX = _rotl64(RCX, 0x10);
			RCX ^= R10;
			RCX = _byteswap_uint64(RCX);
			if (utils::is_bad_ptr((void*)(RCX + 0x11))) return 0xFFFFFFFFFFFFFFFF; RAX *= driver::driver::read<uint64_t>(RCX + 0x11);
			RCX = 0xD821E1F8F10CC0E5;
			RAX *= RCX;
			return RAX;
		}
		case 7:
		{
			RSI = No_Define::BaseAddress + 0x6AC;
			R9 = driver::driver::read<uint64_t>(No_Define::BaseAddress + 0x68FE117);
			RCX = No_Define::BaseAddress;
			RAX += RCX;
			RCX = 0xCDD63885C351FBB5;
			RAX *= RCX;
			RCX = RAX;
			RCX >>= 0x28;
			RAX ^= RCX;
			// mov rcx,[rbp+0E8h]
			RCX -= RSI;
			RCX = 0; // Special case
			RCX = _rotl64(RCX, 0x10);
			RCX ^= R9;
			RCX = _byteswap_uint64(RCX);
			if (utils::is_bad_ptr((void*)(RCX + 0x11))) return 0xFFFFFFFFFFFFFFFF; RCX = driver::driver::read<uint64_t>(RCX + 0x11);
			RBP = 0xD86054F77497C21F;
			RCX *= RBP;
			RAX *= RCX;
			RCX = 0xE9FBCF5BFD0D9235;
			RAX *= RCX;
			RCX = No_Define::BaseAddress + 0x2B58;
			RCX -= RDI;
			RAX += RCX;
			RAX += RDI;
			return RAX;
		}
		case 8:
		{
			R10 = driver::driver::read<uint64_t>(No_Define::BaseAddress + 0x68FE117);
			RSI = No_Define::BaseAddress + 0x6AC;
			R15 = No_Define::BaseAddress + 0x261CDD99;
			RBX = No_Define::BaseAddress + 0x6877DAE4;
			RCX = 0x74F032451C0F3AAB;
			RAX += RCX;
			RCX = 0x91AAF2F4B147480D;
			RAX ^= RCX;
			RCX = RAX;
			RCX >>= 0x28;
			RAX ^= RCX;
			RCX = RAX;
			RCX >>= 0xD;
			RAX ^= RCX;
			RCX = RAX;
			RCX >>= 0x1A;
			RAX ^= RCX;
			RDX = RAX;
			RDX >>= 0x34;
			RDX ^= RAX;
			RAX = RDI;
			RAX ^= RBX;
			RCX = 0xAE4F1D68CD4FA409;
			RAX += RDX;
			RAX *= RCX;
			// mov rcx,[rbp+0E8h]
			RCX -= RSI;
			RCX = 0; // Special case
			RCX = _rotl64(RCX, 0x10);
			RCX ^= R10;
			RCX = _byteswap_uint64(RCX);
			if (utils::is_bad_ptr((void*)(RCX + 0x11))) return 0xFFFFFFFFFFFFFFFF; RAX *= driver::driver::read<uint64_t>(RCX + 0x11);
			RCX = R15;
			RCX = (~RCX);
			RCX += RDI;
			RAX ^= RCX;
			return RAX;
		}
		case 9:
		{
			R10 = driver::driver::read<uint64_t>(No_Define::BaseAddress + 0x68FE117);
			RSI = No_Define::BaseAddress + 0x6AC;
			R15 = No_Define::BaseAddress + 0x19301967;
			RCX = 0xA03A5CAEA4279C49;
			RAX *= RCX;
			RCX = 0x71C02514CF8A9DA8;
			RAX += RCX;
			// mov rcx,[rbp+0E8h]
			RCX -= RSI;
			RCX = 0; // Special case
			RCX = _rotl64(RCX, 0x10);
			RCX ^= R10;
			RCX = _byteswap_uint64(RCX);
			if (utils::is_bad_ptr((void*)(RCX + 0x11))) return 0xFFFFFFFFFFFFFFFF; RAX *= driver::driver::read<uint64_t>(RCX + 0x11);
			RCX = 0x9EDB961AC1CA708C;
			RAX ^= RCX;
			RAX += R15;
			RDX = RDI;
			RDX = (~RDX);
			RAX += RDX;
			RCX = RAX;
			RCX >>= 0x10;
			RAX ^= RCX;
			RCX = RAX;
			RCX >>= 0x20;
			RAX ^= RCX;
			RCX = No_Define::BaseAddress;
			RAX ^= RCX;
			RCX = RAX;
			RCX >>= 0x7;
			RAX ^= RCX;
			RCX = RAX;
			RCX >>= 0xE;
			RAX ^= RCX;
			RCX = RAX;
			RCX >>= 0x1C;
			RAX ^= RCX;
			RCX = RAX;
			RCX >>= 0x38;
			RAX ^= RCX;
			return RAX;
		}
		case 10:
		{
			RSI = No_Define::BaseAddress + 0x6AC;
			RBX = No_Define::BaseAddress + 0x1A015076;
			R9 = driver::driver::read<uint64_t>(No_Define::BaseAddress + 0x68FE117);
			RCX = RAX;
			RCX >>= 0x1C;
			RAX ^= RCX;
			RCX = RAX;
			RCX >>= 0x38;
			RAX ^= RCX;
			// mov rcx,[rbp+0E8h]
			RCX -= RSI;
			RCX = 0; // Special case
			RCX = _rotl64(RCX, 0x10);
			RCX ^= R9;
			RCX = _byteswap_uint64(RCX);
			if (utils::is_bad_ptr((void*)(RCX + 0x11))) return 0xFFFFFFFFFFFFFFFF; RAX *= driver::driver::read<uint64_t>(RCX + 0x11);
			RCX = RAX;
			RCX >>= 0x15;
			RAX ^= RCX;
			RCX = RAX;
			RCX >>= 0x2A;
			RAX ^= RCX;
			RCX = RDI;
			RCX ^= RBX;
			RAX += RCX;
			RCX = RAX;
			RCX >>= 0xC;
			RAX ^= RCX;
			RCX = RAX;
			RCX >>= 0x18;
			RAX ^= RCX;
			RCX = RAX;
			RCX >>= 0x30;
			RAX ^= RCX;
			RCX = 0x11B19D41A5FE8AE1;
			RAX *= RCX;
			RCX = RAX;
			RCX >>= 0x26;
			RAX ^= RCX;
			RCX = No_Define::BaseAddress;
			RAX ^= RCX;
			return RAX;
		}
		case 11:
		{
			RSI = No_Define::BaseAddress + 0x6AC;
			R15 = No_Define::BaseAddress + 0x78378FCB;
			RBX = No_Define::BaseAddress + 0x7998;
			R9 = driver::driver::read<uint64_t>(No_Define::BaseAddress + 0x68FE117);
			RCX = No_Define::BaseAddress;
			RAX += RCX;
			RCX = RAX;
			RCX >>= 0x1F;
			RAX ^= RCX;
			RCX = RAX;
			RCX >>= 0x3E;
			RAX ^= RCX;
			RCX = 0x41CF04660260443;
			RAX += RCX;
			RCX = 0x740D13B79DE35AE6;
			RAX += RCX;
			// mov rcx,[rbp+0E8h]
			RCX -= RSI;
			RCX = 0; // Special case
			RCX = _rotl64(RCX, 0x10);
			RCX ^= R9;
			RCX = _byteswap_uint64(RCX);
			if (utils::is_bad_ptr((void*)(RCX + 0x11))) return 0xFFFFFFFFFFFFFFFF; RCX = driver::driver::read<uint64_t>(RCX + 0x11);
			RAX *= RCX;
			RAX ^= RDI;
			RAX ^= RBX;
			RCX = 0x7712A4C8F3E6DF2D;
			RAX *= RCX;
			RCX = RDI;
			RCX = (~RCX);
			RAX += RCX;
			RAX += R15;
			return RAX;
		}
		case 12:
		{
			RSI = No_Define::BaseAddress + 0x6AC;
			R9 = driver::driver::read<uint64_t>(No_Define::BaseAddress + 0x68FE117);
			RAX -= RDI;
			// mov rcx,[rbp+0E8h]
			RCX -= RSI;
			RCX = 0; // Special case
			RCX = _rotl64(RCX, 0x10);
			RCX ^= R9;
			RCX = _byteswap_uint64(RCX);
			if (utils::is_bad_ptr((void*)(RCX + 0x11))) return 0xFFFFFFFFFFFFFFFF; RCX = driver::driver::read<uint64_t>(RCX + 0x11);
			RSP = 0xDCBB02268230C67;
			RCX *= RSP;
			RAX *= RCX;
			RCX = RDI + RDI;
			RCX -= No_Define::BaseAddress;
			RCX += 0xFFFFFFFFFFFF5629;
			RAX += RCX;
			RCX = RAX;
			RCX >>= 0x12;
			RAX ^= RCX;
			RCX = RAX;
			RCX >>= 0x24;
			RAX ^= RCX;
			RCX = RAX;
			RCX >>= 0xD;
			RAX ^= RCX;
			RCX = RAX;
			RCX >>= 0x1A;
			RAX ^= RCX;
			RCX = RAX;
			RCX >>= 0x34;
			RAX ^= RCX;
			RAX += RDI;
			return RAX;
		}
		case 13:
		{
			RSI = No_Define::BaseAddress + 0x6AC;
			R15 = No_Define::BaseAddress + 0x22DB7F31;
			R10 = driver::driver::read<uint64_t>(No_Define::BaseAddress + 0x68FE117);
			RDX = RAX;
			RDX >>= 0x21;
			RDX ^= RAX;
			RAX = RDI;
			RAX = (~RAX);
			RAX *= R15;
			RAX += RDX;
			RAX += RDI;
			// mov rcx,[rbp+0E8h]
			RCX -= RSI;
			RCX = 0; // Special case
			RCX = _rotl64(RCX, 0x10);
			RCX ^= R10;
			RCX = _byteswap_uint64(RCX);
			if (utils::is_bad_ptr((void*)(RCX + 0x11))) return 0xFFFFFFFFFFFFFFFF; RCX = driver::driver::read<uint64_t>(RCX + 0x11);
			RAX *= RCX;
			RCX = 0x8DDCF2B3E1571114;
			RAX ^= RCX;
			RCX = No_Define::BaseAddress;
			RAX -= RCX;
			RCX = 0x6010B0A9C3D8407D;
			RAX ^= RCX;
			RCX = 0x4B13677AC2BC8B55;
			RAX *= RCX;
			return RAX;
		}
		case 14:
		{
			RSI = No_Define::BaseAddress + 0x6AC;
			RBX = No_Define::BaseAddress + 0x7B82;
			R10 = driver::driver::read<uint64_t>(No_Define::BaseAddress + 0x68FE117);
			RCX = RAX;
			RCX >>= 0xD;
			RAX ^= RCX;
			RCX = RAX;
			RCX >>= 0x1A;
			RAX ^= RCX;
			// mov rdx,[rbp+0E8h]
			RDX -= RSI;
			RDX = 0; // Special case
			RDX = _rotl64(RDX, 0x10);
			RCX = RAX;
			RDX ^= R10;
			RCX >>= 0x34;
			RCX ^= RAX;
			RAX = No_Define::BaseAddress;
			RDX = _byteswap_uint64(RDX);
			RCX ^= RAX;
			if (utils::is_bad_ptr((void*)(RDX + 0x11))) return 0xFFFFFFFFFFFFFFFF; RAX = driver::driver::read<uint64_t>(RDX + 0x11);
			RAX *= RCX;
			RCX = 0x294BF04F8056DBA0;
			RAX += RCX;
			RCX = RDI;
			RCX ^= RBX;
			RAX -= RCX;
			RAX += RDI;
			RCX = No_Define::BaseAddress + 0x22D3C70A;
			RAX += RCX;
			RCX = 0xF4E5078B5230FB51;
			RAX *= RCX;
			RCX = 0x5B401C942FFFFB4D;
			RAX += RCX;
			return RAX;
		}
		case 15:
		{
			R10 = driver::driver::read<uint64_t>(No_Define::BaseAddress + 0x68FE117);
			RSI = No_Define::BaseAddress + 0x6AC;
			RAX -= RDI;
			RCX = 0x867F13D085A61055;
			RAX *= RCX;
			// mov rcx,[rbp+0E8h]
			RCX -= RSI;
			RCX = 0; // Special case
			RCX = _rotl64(RCX, 0x10);
			RCX ^= R10;
			RCX = _byteswap_uint64(RCX);
			if (utils::is_bad_ptr((void*)(RCX + 0x11))) return 0xFFFFFFFFFFFFFFFF; RCX = driver::driver::read<uint64_t>(RCX + 0x11);
			RSP = 0x341894F65D84D9E7;
			RCX *= RSP;
			RAX *= RCX;
			RCX = RAX;
			RCX >>= 0x1A;
			RAX ^= RCX;
			RCX = RAX;
			RCX >>= 0x34;
			RAX ^= RCX;
			RCX = No_Define::BaseAddress;
			RAX -= RCX;
			RCX = 0x5AB80474995D546;
			RAX += RCX;
			RAX += RDI;
			RCX = No_Define::BaseAddress;
			RAX += RCX;
			return RAX;
		}
		default:
			return 0;
		}
	}
	*/
	auto DecryptRef_Def(refdefKeyStruct crypt) -> uint64_t
	{
		uint64_t baseAddr = No_Define::BaseAddress;

		DWORD lower = crypt.ref0 ^ (crypt.ref2 ^ (uint64_t)(baseAddr + offsets::Ref_Def)) * ((crypt.ref2 ^ (uint64_t)(baseAddr + offsets::Ref_Def)) + 2);
		DWORD upper = crypt.ref1 ^ (crypt.ref2 ^ (uint64_t)(baseAddr + offsets::Ref_Def + 0x4)) * ((crypt.ref2 ^ (uint64_t)(baseAddr + offsets::Ref_Def + 0x4)) + 2);

		return (uint64_t)upper << 32 | lower; // Merge Both DWORD into QWORD
	}
}

uint64_t GetRefDef()
{
	auto encRef_Def = driver::read<refdefKeyStruct>(No_Define::BaseAddress + offsets::Ref_Def);
	return decryption::DecryptRef_Def(encRef_Def);
}
uint64_t GetClientInfo() {
	auto encinfo = driver::read<uint64_t>(No_Define::BaseAddress + offsets::CLIENT_INFO);
	return decryption::DecryptClientInfo(encinfo);
}
uint64_t GetClientBase(uint64_t client_info) {
	auto encbase = driver::read<uint64_t>(client_info + offsets::CLIENT_BASE);
	return decryption::DecryptClientBase(encbase);
}
uint64_t GetNameList() {
	auto ptr = driver::read<uint64_t>(No_Define::BaseAddress + offsets::Name_Array);
	return ptr + offsets::Name_Array_Padding;
}

#include "HookManager.h"
#include "AddressManager.h"
#include "Memory.h"

#include <polyhook2/Detour/x86Detour.hpp>

#include <iostream>
#include <Windows.h>

std::function<bool(char *i_szPacket)> g_pRecvCallback;
PLH::x86Detour *g_pRecvDetour = nullptr;
uint64 g_iRecvTrampoline;

std::function<bool(char *i_szPacket)> g_pSendCallback;
PLH::x86Detour *g_pSendDetour = nullptr;
uint64 g_iSendTrampoline;


void RecvPacketHelper(char* packet) {
	if (g_pRecvCallback(packet)) {
		packet[0] = 0x00;
	}
}

void __declspec(naked) RecvPacketHook() {
	__asm {
		// Save context
		pushad
		pushfd

		// Get packet from EDX, push as argument for helper
		mov eax, edx
		push eax

		// Call helper
		call RecvPacketHelper
		add esp, 4

		// Restore context and jump to original
		popfd
		popad
		jmp dword ptr [g_iRecvTrampoline]
	}
}

bool SendPacketHelper(char* packet) {
	return g_pSendCallback(packet);
}

void __declspec(naked) SendPacketHook() {
	__asm {
		// Save context
		pushad
		pushfd

		// Get packet from EDX, push as argument for helper
		mov eax, edx
		push eax

		// Call helper
		call SendPacketHelper
		add esp, 4

		// Check return value in AL
		test al, al
		jz send_packet // If AL is zero (false), jump to send_packet label

		// --- Packet IS blocked ---
		popfd
		popad
		ret

	send_packet:
		// --- Packet is NOT blocked ---
		popfd
		popad
		jmp dword ptr [g_iSendTrampoline]
	}
}

void HookManager::Initialize(std::function<bool(char *i_szPacket)> i_pRecvCallback, std::function<bool(char *i_szPacket)> i_pSendCallback)
{
	if (!g_pRecvDetour) {
		g_pRecvCallback = i_pRecvCallback;
		g_pRecvDetour = new PLH::x86Detour(
			static_cast<uint64_t>(AddressManager::Get(EAddress::ARecvHook)),
			reinterpret_cast<uint64_t>(&RecvPacketHook),
			&g_iRecvTrampoline
		);
		g_pRecvDetour->hook();
	}

	if (!g_pSendDetour) {
		g_pSendCallback = i_pSendCallback;
		g_pSendDetour = new PLH::x86Detour(
			static_cast<uint64_t>(AddressManager::Get(EAddress::ASendHook)), 
			reinterpret_cast<uint64_t>(&SendPacketHook), 
			&g_iSendTrampoline);
		g_pSendDetour->hook();
	}
}


void HookManager::Unhook()
{
	if (g_pRecvDetour) {
		g_pRecvDetour->unHook();
		delete g_pRecvDetour;
		g_pRecvDetour = nullptr;
	}
	
	if (g_pSendDetour) {
		g_pSendDetour->unHook();
		delete g_pSendDetour;
		g_pSendDetour = nullptr;
	}
}
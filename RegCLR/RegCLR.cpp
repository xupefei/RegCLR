// RegCLR.cpp : main project file.

#include "stdafx.h"

#pragma comment(lib, "advapi32.lib")

using namespace System;
using namespace System::Runtime::InteropServices;
using namespace System::Reflection;

int main(array<System::String ^> ^args)
{
	Console::WriteLine(L"RegCLR - CLR assembly registration tool");
	Console::WriteLine();

	if (args->Length == 0) {
		Console::WriteLine(L"Usage: RegCLR.exe <clr_library_path> [/remove]");
		Console::ReadKey();
		return 0;
	}

	bool is_remove = (args->Length > 1 && args[1] == "/remove");

	Console::WriteLine(L"Registering " + args[0]);

	HKEY key;

	if (0 == RegOpenKeyEx(HKEY_CURRENT_USER, TEXT("Software\\Classes"), 0, KEY_ALL_ACCESS, &key)) {
		Console::WriteLine(L"RegOpenKeyEx success");
	}
	else {
		Console::WriteLine(L"RegOpenKeyEx failed.");
		Console::ReadKey();
		return 0;
	}

	if (0 == RegOverridePredefKey(HKEY_CLASSES_ROOT, key)) {
		Console::WriteLine(L"RegOverridePredefKey success");
	}
	else {
		Console::WriteLine(L"RegOverridePredefKey failed.");
		Console::ReadKey();
		return 0;
	}

	if (!is_remove) {
		Console::WriteLine(L"Performing registration");
		auto rs = gcnew RegistrationServices;
		rs->RegisterAssembly(Assembly::LoadFile(args[0]), AssemblyRegistrationFlags::SetCodeBase);
	}
	else {
		Console::WriteLine(L"Performing un-register");
		auto rs = gcnew RegistrationServices;
		rs->UnregisterAssembly(Assembly::LoadFile(args[0]));
	}

	return 0;
}

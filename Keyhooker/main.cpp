#include <Windows.h>
#include <WinUser.h>
#include <stdio.h>
HHOOK hhk;
void SendStringInput(char*);
_declspec(dllexport) LRESULT CALLBACK KeyEvent(int Code, WPARAM wParam, LPARAM lParam) {
	if ((Code == HC_ACTION) && ((wParam == WM_KEYDOWN || wParam == WM_SYSKEYDOWN))) {
		KBDLLHOOKSTRUCT keyhook = *((KBDLLHOOKSTRUCT*)lParam);

		DWORD dwMsg = 1;

		dwMsg += keyhook.scanCode << 16;
		dwMsg += keyhook.flags << 24;

		char KeyName[0xFF] = { 0 };

		GetKeyNameText(dwMsg, KeyName, 0xFF);
		char *CheatCode;
		CheatCode = (char*)malloc(30 * sizeof(char));
		if (KeyName[1] == '\0' || KeyName[1] == ' ') {
			switch (KeyName[0]) {
			case '0':
				strcpy(CheatCode, "leavemealone\0");
				SendStringInput(CheatCode);
				break;
			case '+':
				strcpy(CheatCode, "preciousprotection\0");
				SendStringInput(CheatCode);
				break;
			case '1':
				strcpy(CheatCode, "aspirine\0");
				SendStringInput(CheatCode);
				break;
			case '2':
				strcpy(CheatCode, "thugstools\0");
				SendStringInput(CheatCode);
				break;
			case '3':
				strcpy(CheatCode, "professionaltools\0");
				SendStringInput(CheatCode);
				break;
			case '4':
				strcpy(CheatCode, "nuttertools\0");
				SendStringInput(CheatCode);

				break;
			case 'S':
				strcpy(CheatCode, "gripiseverything\0");
				SendStringInput(CheatCode);

				break;
			case 'F':
				strcpy(CheatCode, "comeflywithme\0");
				SendStringInput(CheatCode);

				break;
			case 'T':
				strcpy(CheatCode, "panzer\0");
				SendStringInput(CheatCode);

				break;
			case 'B':
				strcpy(CheatCode, "bigbang\0");
				SendStringInput(CheatCode);
				break;
			case 'R':
				strcpy(CheatCode, "rubbishcar\0");
				SendStringInput(CheatCode);
				break;
			case 'I':
				strcpy(CheatCode, "travelinstyle\0");
				SendStringInput(CheatCode);
				break;
			case 'Q':
				strcpy(CheatCode, "gettherequickly\0");
				SendStringInput(CheatCode);

				break;
			case 'C':
				strcpy(CheatCode, "betterthanwalking\0");
				SendStringInput(CheatCode);
				break;
			case 'W':
				strcpy(CheatCode, "seaways\0");
				SendStringInput(CheatCode);
				break;
			case 'G':
				strcpy(CheatCode, "getthereveryfastindeed\0");
				SendStringInput(CheatCode);
				break;
			case 'A':
				strcpy(CheatCode, "getthereamazinglyfast\0");
				SendStringInput(CheatCode);
				break;
			default:

				break;
			}
		}
	}
	return CallNextHookEx(hhk, Code, wParam, lParam);
}

void SendStringInput(char* String) {


	//INPUT in;
	int i = 0;
	//in.type=INPUT_KEYBOARD;
	//in.ki.dwExtraInfo=0;
	//in.ki.dwFlags=KEYEVENTF_UNICODE;
	//in.ki.wVk=0;
	while (String[i] != '\0') {
		keybd_event(VkKeyScan(String[i]), 0x45, KEYEVENTF_EXTENDEDKEY | 0, 0);
		keybd_event(VkKeyScan(String[i]), 0x45, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0);
		//  in.ki.wScan=String[i];
		//  SendInput(1,&in,sizeof(in));
		i++;
	}
}

DWORD WINAPI EventThreadProc(LPVOID Param) {
	HINSTANCE hExe = GetModuleHandle(NULL);
	if (!hExe) hExe = LoadLibrary((LPSTR)Param);
	if (!hExe) return 1;
	hhk = SetWindowsHookEx(WH_KEYBOARD_LL, KeyEvent, hExe, NULL);
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	UnhookWindowsHookEx(hhk);
	return 1;
}

int main(int argc, char* argv[]) {
	HANDLE thread;
	DWORD dwThreadID;

	printf("0 : Zero Police \n");
	printf("+ : Armor \n");
	printf("1 : Health \n");
	printf("2 : Weapons (tier 1) \n");
	printf("3 : Weapons (tier 2) \n");
	printf("4 : Weapons (tier 3) \n");
	printf("S : Better driving skills \n");
	printf("F : Flying Cars \n");
	printf("T : Tank \n");
	printf("B : Big Bang \n");
	printf("R : Rubbish Car \n");
	printf("I : Bloodring Banger (style 1) \n");
	printf("Q : Bloodring Banger (style 2) \n");
	printf("C : Caddy \n");
	printf("W : Sea Ways \n");
	printf("G : Engines are faster \n");
	printf("A : Engines very fast \n");

	thread = CreateThread(0, 0, EventThreadProc, argv[0], NULL, &dwThreadID);
	if (thread) {
		return WaitForSingleObject(thread, INFINITE);
	}
	else {
		return 1;
	}
}
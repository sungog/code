//***************************
//**** 2005-11-26*************
//**** Winscard.cpp************
//***************************
#include        <windows.h>

typedef        long (_stdcall *PEstablishContext)(long Para_1, long Para_2, long Para_3, long *Para_4);
typedef        long (_stdcall *PListReadersA)(long Para_1, long Para_2, char **Para_3, long *Para_4);
typedef        long (_stdcall *PFreeMemory)(long Para_1, char *Para_2);
typedef        long (_stdcall *PConnectA)(long Para_1, char *Para_2, long Para_3, long Para_4, long *Para_5, long *Para_6);
typedef        long (_stdcall *PStatusA)(long Para_1, char *Para_2, long *Para_3, long *Para_4, long *Para_5, char *Para_6, long *Para_7);
typedef        long (_stdcall *PDisconnect)(long Para_1, long Para_2);
typedef        long (_stdcall *PTransmit)(long Handle, long Para_2, unsigned char *InBuf, long InLen, long Para_5, unsigned char *OutBuf, long *OutLen);
typedef        long (_stdcall *PFun)(void);

PEstablishContext        ProcSCardEstablishContext;
PListReadersA                ProcSCardListReadersA;
PFreeMemory                        ProcSCardFreeMemory;
PConnectA                        ProcSCardConnectA;
PStatusA                        ProcSCardStatusA;
PDisconnect                        ProcSCardDisconnect;
PTransmit                        ProcSCardTransmit;
PFun        ProcClassInstall32;
PFun        ProcSCardAccessNewReaderEvent;
PFun        ProcSCardAccessStartedEvent;
PFun        ProcSCardAddReaderToGroupA;
PFun        ProcSCardAddReaderToGroupW;
PFun        ProcSCardBeginTransaction;
PFun        ProcSCardCancel;
PFun        ProcSCardConnectW;
PFun        ProcSCardControl;
PFun        ProcSCardEndTransaction;
PFun        ProcSCardForgetCardTypeA;
PFun        ProcSCardForgetCardTypeW;
PFun        ProcSCardForgetReaderA;
PFun        ProcSCardForgetReaderGroupA;
PFun        ProcSCardForgetReaderGroupW;
PFun        ProcSCardForgetReaderW;
PFun        ProcSCardGetAttrib;
PFun        ProcSCardGetCardTypeProviderNameA;
PFun        ProcSCardGetCardTypeProviderNameW;
PFun        ProcSCardGetProviderIdA;
PFun        ProcSCardGetProviderIdW;
PFun        ProcSCardGetStatusChangeA;
PFun        ProcSCardGetStatusChangeW;
PFun        ProcSCardIntroduceCardTypeA;
PFun        ProcSCardIntroduceCardTypeW;
PFun        ProcSCardIntroduceReaderA;
PFun        ProcSCardIntroduceReaderGroupA;
PFun        ProcSCardIntroduceReaderGroupW;
PFun        ProcSCardIntroduceReaderW;
PFun        ProcSCardIsValidContext;
PFun        ProcSCardListCardsA;
PFun        ProcSCardListCardsW;
PFun        ProcSCardListInterfacesA;
PFun        ProcSCardListInterfacesW;
PFun        ProcSCardListReaderGroupsA;
PFun        ProcSCardListReaderGroupsW;
PFun        ProcSCardListReadersW;
PFun        ProcSCardLocateCardsA;
PFun        ProcSCardLocateCardsByATRA;
PFun        ProcSCardLocateCardsByATRW;
PFun        ProcSCardLocateCardsW;
PFun        ProcSCardReconnect;
PFun        ProcSCardReleaseAllEvents;
PFun        ProcSCardReleaseContext;
PFun        ProcSCardReleaseNewReaderEvent;
PFun        ProcSCardReleaseStartedEvent;
PFun        ProcSCardRemoveReaderFromGroupA;
PFun        ProcSCardRemoveReaderFromGroupW;
PFun        ProcSCardSetAttrib;
PFun        ProcSCardSetCardTypeProviderNameA;
PFun        ProcSCardSetCardTypeProviderNameW;
PFun        ProcSCardState;
PFun        ProcSCardStatusW;
long        g_rgSCardT1Pci[2] = {2, 8};
long        g_rgSCardT0Pci[2] = {1, 8};
long        g_rgSCardRawPci[2] = {0x10000, 8};

unsigned char        RunType = 0;
HINSTANCE        Lib = 0;

void        DebugExe(void)
{
        long        File;
        char        Buffer[MAX_PATH];
        SYSTEMTIME        TimeInfo;

        GetLocalTime(&TimeInfo);
        File = (long)CreateFile("C:\\WinSCard.LOG", GENERIC_WRITE, 0, 0, CREATE_NEW, FILE_ATTRIBUTE_ARCHIVE, 0);
        if (File != (long)INVALID_HANDLE_VALUE)
                CloseHandle((void *)File);
        File = _lopen("C:\\WinSCard.LOG", OF_WRITE);
        _llseek(File, 0, FILE_END);
        _lwrite(File, "\r\n", 2);
        _lclose(File);
}

void        LoadLibraryEx(void)
{
        Lib = LoadLibrary("SysCard.DLL");
        ProcSCardEstablishContext = (PEstablishContext)GetProcAddress(Lib, "SCardEstablishContext");
        ProcSCardListReadersA = (PListReadersA)GetProcAddress(Lib, "SCardListReadersA");
        ProcSCardFreeMemory = (PFreeMemory)GetProcAddress(Lib, "SCardFreeMemory");
        ProcClassInstall32 = (PFun)GetProcAddress(Lib, "ClassInstall32");
        ProcSCardConnectA = (PConnectA)GetProcAddress(Lib, "SCardConnectA");
        ProcSCardStatusA = (PStatusA)GetProcAddress(Lib, "SCardStatusA");
        ProcSCardDisconnect = (PDisconnect)GetProcAddress(Lib, "SCardDisconnect");
        ProcSCardTransmit = (PTransmit)GetProcAddress(Lib, "SCardTransmit");
        ProcSCardAccessNewReaderEvent = (PFun)GetProcAddress(Lib, "SCardAccessNewReaderEvent");
        ProcSCardAccessStartedEvent = (PFun)GetProcAddress(Lib, "SCardAccessStartedEvent");
        ProcSCardAddReaderToGroupA = (PFun)GetProcAddress(Lib, "SCardAddReaderToGroupA");
        ProcSCardAddReaderToGroupW = (PFun)GetProcAddress(Lib, "SCardAddReaderToGroupW");
        ProcSCardBeginTransaction = (PFun)GetProcAddress(Lib, "SCardBeginTransaction");
        ProcSCardCancel = (PFun)GetProcAddress(Lib, "SCardCancel");
        ProcSCardConnectW = (PFun)GetProcAddress(Lib, "SCardConnectW");
        ProcSCardControl = (PFun)GetProcAddress(Lib, "SCardControl");
        ProcSCardEndTransaction = (PFun)GetProcAddress(Lib, "SCardEndTransaction");
        ProcSCardForgetCardTypeA = (PFun)GetProcAddress(Lib, "SCardForgetCardTypeA");
        ProcSCardForgetCardTypeW = (PFun)GetProcAddress(Lib, "SCardForgetCardTypeW");
        ProcSCardForgetReaderA = (PFun)GetProcAddress(Lib, "SCardForgetReaderA");
        ProcSCardForgetReaderGroupA = (PFun)GetProcAddress(Lib, "SCardForgetReaderGroupA");
        ProcSCardForgetReaderGroupW = (PFun)GetProcAddress(Lib, "SCardForgetReaderGroupW");
        ProcSCardForgetReaderW = (PFun)GetProcAddress(Lib, "SCardForgetReaderW");
        ProcSCardGetAttrib = (PFun)GetProcAddress(Lib, "SCardGetAttrib");
        ProcSCardGetCardTypeProviderNameA = (PFun)GetProcAddress(Lib, "SCardGetCardTypeProviderNameA");
        ProcSCardGetCardTypeProviderNameW = (PFun)GetProcAddress(Lib, "SCardGetCardTypeProviderNameW");
        ProcSCardGetProviderIdA = (PFun)GetProcAddress(Lib, "SCardGetProviderIdA");
        ProcSCardGetProviderIdW = (PFun)GetProcAddress(Lib, "SCardGetProviderIdW");
        ProcSCardGetStatusChangeA = (PFun)GetProcAddress(Lib, "SCardGetStatusChangeA");
        ProcSCardGetStatusChangeW = (PFun)GetProcAddress(Lib, "SCardGetStatusChangeW");
        ProcSCardIntroduceCardTypeA = (PFun)GetProcAddress(Lib, "SCardIntroduceCardTypeA");
        ProcSCardIntroduceCardTypeW = (PFun)GetProcAddress(Lib, "SCardIntroduceCardTypeW");
        ProcSCardIntroduceReaderA = (PFun)GetProcAddress(Lib, "SCardIntroduceReaderA");
        ProcSCardIntroduceReaderGroupA = (PFun)GetProcAddress(Lib, "SCardIntroduceReaderGroupA");
        ProcSCardIntroduceReaderGroupW = (PFun)GetProcAddress(Lib, "SCardIntroduceReaderGroupW");
        ProcSCardIntroduceReaderW = (PFun)GetProcAddress(Lib, "SCardIntroduceReaderW");
        ProcSCardIsValidContext = (PFun)GetProcAddress(Lib, "SCardIsValidContext");
        ProcSCardListCardsA = (PFun)GetProcAddress(Lib, "SCardListCardsA");
        ProcSCardListCardsW = (PFun)GetProcAddress(Lib, "SCardListCardsW");
        ProcSCardListInterfacesA = (PFun)GetProcAddress(Lib, "SCardListInterfacesA");
        ProcSCardListInterfacesW = (PFun)GetProcAddress(Lib, "SCardListInterfacesW");
        ProcSCardListReaderGroupsA = (PFun)GetProcAddress(Lib, "SCardListReaderGroupsA");
        ProcSCardListReaderGroupsW = (PFun)GetProcAddress(Lib, "SCardListReaderGroupsW");
        ProcSCardListReadersW = (PFun)GetProcAddress(Lib, "SCardListReadersW");
        ProcSCardLocateCardsA = (PFun)GetProcAddress(Lib, "SCardLocateCardsA");
        ProcSCardLocateCardsByATRA = (PFun)GetProcAddress(Lib, "SCardLocateCardsByATRA");
        ProcSCardLocateCardsByATRW = (PFun)GetProcAddress(Lib, "SCardLocateCardsByATRW");
        ProcSCardLocateCardsW = (PFun)GetProcAddress(Lib, "SCardLocateCardsW");
        ProcSCardReconnect = (PFun)GetProcAddress(Lib, "SCardReconnect");
        ProcSCardReleaseAllEvents = (PFun)GetProcAddress(Lib, "SCardReleaseAllEvents");
        ProcSCardReleaseContext = (PFun)GetProcAddress(Lib, "SCardReleaseContext");
        ProcSCardReleaseNewReaderEvent = (PFun)GetProcAddress(Lib, "SCardReleaseNewReaderEvent");
        ProcSCardReleaseStartedEvent = (PFun)GetProcAddress(Lib, "SCardReleaseStartedEvent");
        ProcSCardRemoveReaderFromGroupA = (PFun)GetProcAddress(Lib, "SCardRemoveReaderFromGroupA");
        ProcSCardRemoveReaderFromGroupW = (PFun)GetProcAddress(Lib, "SCardRemoveReaderFromGroupW");
        ProcSCardSetAttrib = (PFun)GetProcAddress(Lib, "SCardSetAttrib");
        ProcSCardSetCardTypeProviderNameA = (PFun)GetProcAddress(Lib, "SCardSetCardTypeProviderNameA");
        ProcSCardSetCardTypeProviderNameW = (PFun)GetProcAddress(Lib, "SCardSetCardTypeProviderNameW");
        ProcSCardState = (PFun)GetProcAddress(Lib, "SCardState");
        ProcSCardStatusW = (PFun)GetProcAddress(Lib, "SCardStatusW");
}
bool APIENTRY DllMain( HANDLE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                                         )
{
        if (ul_reason_for_call == DLL_PROCESS_DETACH)
                FreeLibrary(Lib);
        else if (ul_reason_for_call == DLL_PROCESS_ATTACH) {
                RunType = GetPrivateProfileInt("Main", "Run", 0, "C:\\WinSCard.INI");
                if (RunType > 2)
                        RunType = 0;
                LoadLibraryEx(); }
        return TRUE;
}

long        _stdcall        ClassInstall32(void)
{
        return ProcClassInstall32();
}

long        _stdcall        SCardAccessNewReaderEvent(void)
{
        return ProcSCardAccessNewReaderEvent();
}

long        _stdcall        SCardAccessStartedEvent(void)
{
        return ProcSCardAccessStartedEvent();
}

long        _stdcall        SCardAddReaderToGroupA(void)
{
        return ProcSCardAddReaderToGroupA();
}

long        _stdcall        SCardAddReaderToGroupW(void)
{
        return ProcSCardAddReaderToGroupW();
}

long        _stdcall        SCardBeginTransaction(void)
{
        return ProcSCardBeginTransaction();
}

long        _stdcall        SCardCancel(void)
{
        return ProcSCardCancel();
}

long        _stdcall        SCardConnectW(void)
{
        return ProcSCardConnectW();
}

long        _stdcall        SCardControl(void)
{
        return ProcSCardControl();
}

long        _stdcall        SCardEndTransaction(void)
{
        return ProcSCardEndTransaction();
}

long        _stdcall        SCardForgetCardTypeA(void)
{
        return ProcSCardForgetCardTypeA();
}

long        _stdcall        SCardForgetCardTypeW(void)
{
        return ProcSCardForgetCardTypeW();
}

long        _stdcall        SCardForgetReaderA(void)
{
        return ProcSCardForgetReaderA();
}

long        _stdcall        SCardForgetReaderGroupA(void)
{
        return ProcSCardForgetReaderGroupA();
}

long        _stdcall        SCardForgetReaderGroupW(void)
{
        return ProcSCardForgetReaderGroupW();
}

long        _stdcall        SCardForgetReaderW(void)
{
        return ProcSCardForgetReaderW();
}

long        _stdcall        SCardGetAttrib(void)
{
        return ProcSCardGetAttrib();
}

long        _stdcall        SCardGetCardTypeProviderNameA(void)
{
        return ProcSCardGetCardTypeProviderNameA();
}

long        _stdcall        SCardGetCardTypeProviderNameW(void)
{
        return ProcSCardGetCardTypeProviderNameW();
}

long        _stdcall        SCardGetProviderIdA(void)
{
        return ProcSCardGetProviderIdA();
}

long        _stdcall        SCardGetProviderIdW(void)
{
        return ProcSCardGetProviderIdW();
}

long        _stdcall        SCardGetStatusChangeA(void)
{
        return ProcSCardGetStatusChangeA();
}

long        _stdcall        SCardGetStatusChangeW(void)
{
        return ProcSCardGetStatusChangeW();
}

long        _stdcall        SCardIntroduceCardTypeA(void)
{
        return ProcSCardIntroduceCardTypeA();
}

long        _stdcall        SCardIntroduceCardTypeW(void)
{
        return ProcSCardIntroduceCardTypeW();
}

long        _stdcall        SCardIntroduceReaderA(void)
{
        return ProcSCardIntroduceReaderA();
}

long        _stdcall        SCardIntroduceReaderGroupA(void)
{
        return ProcSCardIntroduceReaderGroupA();
}

long        _stdcall        SCardIntroduceReaderGroupW(void)
{
        return ProcSCardIntroduceReaderGroupW();
}

long        _stdcall        SCardIntroduceReaderW(void)
{
        return ProcSCardIntroduceReaderW();
}

long        _stdcall        SCardIsValidContext(void)
{
        return ProcSCardIsValidContext();
}

long        _stdcall        SCardListCardsA(void)
{
        return ProcSCardListCardsA();
}

long        _stdcall        SCardListCardsW(void)
{
        return ProcSCardListCardsW();
}

long        _stdcall        SCardListInterfacesA(void)
{
        return ProcSCardListInterfacesA();
}

long        _stdcall        SCardListInterfacesW(void)
{
        return ProcSCardListInterfacesW();
}

long        _stdcall        SCardListReaderGroupsA(void)
{
        return ProcSCardListReaderGroupsA();
}

long        _stdcall        SCardListReaderGroupsW(void)
{
        return ProcSCardListReaderGroupsW();
}

long        _stdcall        SCardListReadersW(void)
{
        return ProcSCardListReadersW();
}

long        _stdcall        SCardLocateCardsA(void)
{
        return ProcSCardLocateCardsA();
}

long        _stdcall        SCardLocateCardsByATRA(void)
{
        return ProcSCardLocateCardsByATRA();
}

long        _stdcall        SCardLocateCardsByATRW(void)
{
        return ProcSCardLocateCardsByATRW();
}

long        _stdcall        SCardLocateCardsW(void)
{
        return ProcSCardLocateCardsW();
}

long        _stdcall        SCardReconnect(void)
{
        return ProcSCardReconnect();
}

long        _stdcall        SCardReleaseAllEvents(void)
{
        return ProcSCardReleaseAllEvents();
}

long        _stdcall        SCardReleaseContext(void)
{
        return ProcSCardReleaseContext();
}

long        _stdcall        SCardReleaseNewReaderEvent(void)
{
        return ProcSCardReleaseNewReaderEvent();
}

long        _stdcall        SCardReleaseStartedEvent(void)
{
        return ProcSCardReleaseStartedEvent();
}

long        _stdcall        SCardRemoveReaderFromGroupA(void)
{
        return ProcSCardRemoveReaderFromGroupA();
}

long        _stdcall        SCardRemoveReaderFromGroupW(void)
{
        return ProcSCardRemoveReaderFromGroupW();
}

long        _stdcall        SCardSetAttrib(void)
{
        return ProcSCardSetAttrib();
}

long        _stdcall        SCardSetCardTypeProviderNameA(void)
{
        return ProcSCardSetCardTypeProviderNameA();
}

long        _stdcall        SCardSetCardTypeProviderNameW(void)
{
        return ProcSCardSetCardTypeProviderNameW();
}

long        _stdcall        SCardState(void)
{
        return ProcSCardState();
}

long        _stdcall        SCardStatusW(void)
{
        return ProcSCardStatusW();
}

long        _stdcall        SCardEstablishContext(long Para_1, long Para_2, long Para_3, long *Para_4)
{
        if (RunType != 1)
                return ProcSCardEstablishContext(Para_1, Para_2, Para_3, Para_4);
        *Para_4 = 0x12345678;
        return 0;
}

char        Readers[] = "FT SCR2000 0\0";

long        _stdcall        SCardListReadersA(long Para_1, long Para_2, char **Para_3, long *Para_4)
{
        if (RunType != 1)
                return ProcSCardListReadersA(Para_1, Para_2, Para_3, Para_4);
        *Para_3 = Readers;
        *Para_4 = sizeof(Readers);
        return 0;
}

long        _stdcall        SCardFreeMemory(long Para_1, char *Para_2)
{
        if (RunType != 1)
                return ProcSCardFreeMemory(Para_1, Para_2);
        return 0;
}

long        _stdcall        SCardConnectA(long Para_1, char *Para_2, long Para_3, long Para_4, long *Para_5, long *Para_6)
{
        if (RunType == 1) {
                *Para_5 = 0xFFFFFFFF;
                *Para_6 = 0;
                return 0; }
        if (RunType == 2)
                Para_2 = "FT SCR2000A 0";
        return ProcSCardConnectA(Para_1, Para_2, Para_3, Para_4, Para_5, Para_6);
}

char        StatusAttr[0x14] = {0x3B, 0x7F, 0x13, 0x00, 0x00, 0x50, 0x4B, 0x50, 0x4D, 0x20, 0x43, 0x41, 0x44, 0x00, 0x6F, 0x46, 0x00, 0x74, 0x4E, 0x5D}; 
long        _stdcall        SCardStatusA(long Para_1, char *Para_2, long *Para_3, long *Para_4, long *Para_5, char *Para_6, long *Para_7)
{
        if (RunType != 1)
                return ProcSCardStatusA(Para_1, Para_2, Para_3, Para_4, Para_5, Para_6, Para_7);
        MoveMemory(Para_2, Readers, sizeof(Readers));
        *Para_3 = sizeof(Readers);
        *Para_4 = 5;
        *Para_5 = 2;
        MoveMemory(Para_6, StatusAttr, sizeof(StatusAttr));
        *Para_7 = sizeof(StatusAttr);
        return 0;
}

long        _stdcall        SCardDisconnect(long Para_1, long Para_2)
{
        if (RunType != 1)
                return ProcSCardDisconnect(Para_1, Para_2);
        return 0;
}

void        DebugLog(unsigned char *InBuf, long InLen, unsigned char *OutBuf, long OutLen)
{
        long        File, i;
        char        Buffer[0x10];

        File = _lopen("C:\\WinSCard.LOG", OF_WRITE);
        _llseek(File, 0, FILE_END);
        for (i = 0; i < InLen; i++)
                _lwrite(File, Buffer, wsprintf(Buffer, "%02X ", InBuf[i]));
        _lwrite(File, "- ", 2);
        for (i = 0; i < OutLen; i++)
                _lwrite(File, Buffer, wsprintf(Buffer, "%02X ", OutBuf[i]));
        _lwrite(File, "\r\n", 2);
        _lclose(File);
}

double        Table00DD[7][8][4][2] = {
                {{{0.5150, +0.0005}, {0.4800, +0.0010}, {0.4350, +0.0015}, {0.3550, +0.0025}},
                 {{0.5500, -0.0002}, {0.5200, +0.0002}, {0.4800, +0.0006}, {0.4200, +0.0012}},
                 {{0.5700, -0.0003}, {0.5800, -0.0004}, {0.5600, -0.0002}, {0.5600, -0.0002}},
                 {{0.6000, -0.0005}, {0.5800, -0.0004}, {0.5600, -0.0002}, {0.4700, +0.0004}},
                 {{0.5600, -0.0004}, {0.5400, -0.0002}, {0.5200, +0.0000}, {0.5500, +0.0000}},
                 {{0.6100, -0.0006}, {0.6400, -0.0006}, {0.6200, -0.0004}, {0.6000, -0.0002}},
                 {{0.4900, -0.0002}, {0.5800, -0.0004}, {0.6200, -0.0004}, {0.6000, -0.0002}},
                 {{0.4200, +0.0000}, {0.4400, +0.0000}, {0.4700, +0.0000}, {0.5300, +0.0000}}},
                {{{0.5150, +0.0005}, {0.4800, +0.0010}, {0.4250, +0.0015}, {0.3550, +0.0025}},
                 {{0.5500, -0.0002}, {0.5200, +0.0002}, {0.4800, +0.0006}, {0.4200, +0.0012}},
                 {{0.5700, -0.0004}, {0.5800, -0.0004}, {0.5500, -0.0002}, {0.5600, -0.0002}},
                 {{0.6000, -0.0006}, {0.5800, -0.0004}, {0.5600, -0.0002}, {0.4700, +0.0004}},
                 {{0.5600, -0.0004}, {0.5400, -0.0002}, {0.5200, +0.0000}, {0.5500, +0.0000}},
                 {{0.6100, -0.0006}, {0.6400, -0.0006}, {0.6200, -0.0004}, {0.6000, -0.0002}},
                 {{0.4900, -0.0002}, {0.5800, -0.0004}, {0.6200, -0.0004}, {0.6000, -0.0002}},
                 {{0.6900, +0.0000}, {0.8300, +0.0000}, {0.9600, +0.0000}, {1.2300, +0.0000}}},
                {{{0.5050, +0.0005}, {0.4550, +0.0015}, {0.4250, +0.0015}, {0.3550, +0.0025}},
                 {{0.5500, -0.0004}, {0.5400, -0.0002}, {0.4800, +0.0004}, {0.4400, +0.0008}},
                 {{0.5500, -0.0004}, {0.5600, -0.0004}, {0.5200, +0.0000}, {0.5000, +0.0002}},
                 {{0.5800, -0.0006}, {0.5600, -0.0004}, {0.5800, -0.0004}, {0.5300, +0.0000}},
                 {{0.5400, -0.0004}, {0.6000, -0.0006}, {0.5800, -0.0004}, {0.5700, -0.0002}},
                 {{0.5400, -0.0004}, {0.5000, -0.0002}, {0.5300, -0.0002}, {0.5700, -0.0002}},
                 {{0.6000, -0.0006}, {0.5600, -0.0004}, {0.5900, -0.0004}, {0.5700, -0.0002}},
                 {{0.6800, +0.0000}, {0.9800, +0.0000}, {0.9500, +0.0000}, {1.2300, +0.0000}}},
                {{{0.5600, -0.0010}, {0.5250, -0.0005}, {0.4650, +0.0005}, {0.3850, +0.0015}},
                 {{0.5300, -0.0004}, {0.5100, -0.0002}, {0.4900, +0.0000}, {0.4300, +0.0006}},
                 {{0.5700, -0.0008}, {0.5700, -0.0008}, {0.5100, -0.0002}, {0.4900, +0.0000}},
                 {{0.5400, -0.0006}, {0.5100, -0.0004}, {0.5400, -0.0004}, {0.5200, -0.0002}},
                 {{0.5800, -0.0008}, {0.5500, -0.0006}, {0.5800, -0.0006}, {0.5600, -0.0004}},
                 {{0.3800, +0.0000}, {0.4000, +0.0000}, {0.4300, +0.0000}, {0.4600, +0.0000}},
                 {{0.5000, -0.0004}, {0.5200, -0.0004}, {0.5500, -0.0004}, {0.5200, -0.0002}},
                 {{0.2100, +0.0000}, {0.3500, +0.0000}, {0.6400, +0.0000}, {0.9100, +0.0000}}},
                {{{0.4850, +0.0005}, {0.4500, +0.0010}, {0.3900, +0.0020}, {0.3350, +0.0025}},
                 {{0.5600, -0.0010}, {0.5300, -0.0006}, {0.5000, -0.0002}, {0.4400, +0.0004}},
                 {{0.5400, -0.0008}, {0.5700, -0.0010}, {0.5600, -0.0008}, {0.5200, -0.0004}},
                 {{0.5400, -0.0008}, {0.4800, -0.0004}, {0.5000, -0.0004}, {0.5200, -0.0004}},
                 {{0.5000, -0.0006}, {0.5600, -0.0008}, {0.5800, -0.0008}, {0.5200, -0.0004}},
                 {{0.4500, -0.0004}, {0.4100, -0.0002}, {0.3800, +0.0000}, {0.4200, +0.0000}},
                 {{0.4500, -0.0004}, {0.4700, -0.0004}, {0.5000, -0.0004}, {0.6000, -0.0006}},
                 {{0.6600, +0.0000}, {0.8000, +0.0000}, {1.0900, +0.0000}, {1.2100, +0.0000}}},
                {{{0.4950, -0.0005}, {0.4600, +0.0000}, {0.4150, +0.0005}, {0.3450, +0.0015}},
                 {{0.5300, -0.0012}, {0.5000, -0.0008}, {0.4600, -0.0004}, {0.4200, +0.0000}},
                 {{0.5300, -0.0012}, {0.5400, -0.0012}, {0.5200, -0.0010}, {0.5000, -0.0008}},
                 {{0.4700, -0.0008}, {0.3600, +0.0000}, {0.4600, -0.0006}, {0.4400, -0.0004}},
                 {{0.4700, -0.0008}, {0.6400, -0.0014}, {0.4600, -0.0006}, {0.4800, -0.0006}},
                 {{0.3200, -0.0002}, {0.3900, -0.0004}, {0.4100, -0.0004}, {0.3800, -0.0002}},
                 {{0.3800, -0.0004}, {0.3300, -0.0002}, {0.3500, -0.0002}, {0.3800, -0.0002}},
                 {{0.3200, +0.0000}, {0.4600, +0.0000}, {0.5900, +0.0000}, {0.8700, +0.0000}}},
                {{{0.4700, -0.0010}, {0.4250, -0.0005}, {0.4000, +0.0000}, {0.3450, +0.0005}},
                 {{0.5100, -0.0018}, {0.4900, -0.0016}, {0.4600, -0.0012}, {0.4000, -0.0006}},
                 {{0.4500, -0.0012}, {0.4300, -0.0010}, {0.4400, -0.0010}, {0.4200, -0.0008}},
                 {{0.3600, -0.0006}, {0.3700, -0.0006}, {0.3500, -0.0004}, {0.3900, -0.0006}},
                 {{0.3600, -0.0006}, {0.3700, -0.0006}, {0.4200, -0.0008}, {0.3500, -0.0004}},
                 {{0.3100, -0.0004}, {0.3200, -0.0004}, {0.2700, -0.0002}, {0.1500, +0.0004}},
                 {{0.3100, -0.0004}, {0.3200, -0.0004}, {0.3300, -0.0004}, {0.5700, -0.0010}},
                 {{0.1200, +0.0000}, {0.2500, +0.0000}, {0.4000, +0.0000}, {0.5200, +0.0000}}}};
bool        Flag0023 = false;
bool        Flag02E0 = false;
unsigned long        CacheLen;
unsigned char        CacheBuf[0x100];
unsigned char        Head0[2] = {0x55, 0x00};
unsigned char        Head1[10] = {0x65, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x90, 0x00};
unsigned char        Head2[18] = {0x30, 0xAF, 0x2E, 0x3E, 0x5A, 0xD8, 0x04, 0x72, 0x79, 0x28, 0xD6, 0x3C, 0x37, 0x32, 0x31, 0x30, 0x90, 0x00};
unsigned char        Head3[24] = {0x00, 0x3F, 0xFE, 0x20, 0xC8, 0x00, 0x50, 0x4B, 0x50, 0x4D, 0x56, 0x32, 0x30, 0x31, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x90, 0x00};

void        _stdcall        SCardTransmit1(long Handle, long Para_2, unsigned char *InBuf, long InLen, long Para_5, unsigned char *OutBuf, long *OutLen)
{
        long        i, j;
        double        Value;

        switch (*(long *)InBuf) {
                case 0x1A80:
                case 0x1AF0:
                        *OutLen = sizeof(Head1);
                        MoveMemory(OutBuf, Head1, *OutLen);
                        break;
                case 0x1C80:
                case 0x1CF0:
                        *OutLen = sizeof(Head2);
                        MoveMemory(OutBuf, Head2, *OutLen);
                        break;
                case 0x1880:
                case 0x68F0:
                        *OutLen = sizeof(Head3);
                        MoveMemory(OutBuf, Head3, *OutLen);
                        break;
                case 0x0021:
                        *OutLen = 2;
                        OutBuf[0] = 0x61;
                        OutBuf[1] = 0x10;
                        CacheLen = 0x10;
                        i = *(long *)(InBuf+5+9*4)*(*(long *)(InBuf+5+6*4)*2+1)*2;
                        *(long *)(CacheBuf+0*4) = i+*(long *)(InBuf+5+0*4)+*(long *)(InBuf+5+7*4);
                        *(long *)(CacheBuf+1*4) = *(long *)(InBuf+5+7*4);
                        *(long *)(CacheBuf+2*4) = i;
                        *(long *)(CacheBuf+3*4) = i+*(long *)(InBuf+5+7*4)+1;
                        if (*(long *)(InBuf+5+3*4) == 1) {
                                *(long *)(CacheBuf+0*4) += 1;
                                if (*(long *)(InBuf+5+7*4))
                                        *(long *)(CacheBuf+1*4) += 1;
                                *(long *)(CacheBuf+2*4) += 1;
                                *(long *)(CacheBuf+3*4) += 1; }
                        if (*(long *)(InBuf+5+7*4))
                                *(long *)(CacheBuf+1*4) += i+*(long *)(InBuf+5+0*4);
                        else {
                                (*(long *)(CacheBuf+0*4))++;
                                (*(long *)(CacheBuf+3*4))++; }
                        break;
                case 0x0022:
                        *OutLen = 2;
                        OutBuf[0] = 0x61;
                        OutBuf[1] = 0x10;
                        CacheLen = 0x10;
                        MoveMemory(CacheBuf, InBuf+5+InBuf[4]-0x10, 0x10);
                        break;
                case 0x0023:
                        *OutLen = 2;
                        OutBuf[0] = 0x61;
                        OutBuf[1] = 0x10;
                        CacheLen = 0x10;
                        if (Flag0023)
                                *(double *)CacheBuf = 44.7214;
                        else
                                *(double *)CacheBuf = 38.7298;
                        Flag0023 = !Flag0023;
                        *(double *)(CacheBuf+8) = *(double *)CacheBuf;
                        if (Flag0023)
                                CacheBuf[0] = 0x67;
                        break;
                case 0x0025:
                        *OutLen = 2;
                        OutBuf[0] = 0x61;
                        OutBuf[1] = 0x0C;
                        CacheLen = 0x0C;
                        ZeroMemory(CacheBuf, 0x0C);
                        break;
                case 0x002B:
                        *OutLen = 2;
                        OutBuf[0] = 0x61;
                        OutBuf[1] = 8;
                        CacheLen = 8;
                        for (i = 0; i < 8; i++)
                                CacheBuf[i] = InBuf[i+5]^InBuf[i+9];
                        break;
                case 0x002E:
                        *OutLen = 2;
                        OutBuf[0] = 0x61;
                        OutBuf[1] = 4;
                        CacheLen = 4;
                        *(long *)CacheBuf = *(long *)(InBuf+5+4*4)+*(long *)(InBuf+5+5*4);
                        break;
                case 0x00DB:
                        *OutLen = 2;
                        OutBuf[0] = 0x61;
                        OutBuf[1] = 0x10;
                        CacheLen = 0x10;
                        if (InBuf[7] < 0x40) {
                                *(double *)CacheBuf = 0.08;
                                *(double *)(CacheBuf+8) = 0.5; }
                        else {
                                *(double *)CacheBuf = 0.32;
                                *(double *)(CacheBuf+8) = 1.4; }
                        break;
                case 0x00DD:
                        *OutLen = 2;
                        OutBuf[0] = 0x61; 
OutBuf[1] = 8;
                        CacheLen = 8;
                        Value = *(double *)(InBuf+5+8);
                        if (Value < 30)
                                Value = 30;
                        else if (Value > 350)
                                Value = 350;
                        i = *(long *)(InBuf+5+16)-1;
                        if ((unsigned long)i > 3)
                                *(double *)CacheBuf = 0;
                        else {
                                if (*(double *)(InBuf+5+8) < Value/30)
                                        j = 0;
                                else if (*(double *)(InBuf+5+8) < Value/5)
                                        j = 1;
                                else if (*(double *)(InBuf+5+8) < Value/3)
                                        j = 2;
                                else if (*(double *)(InBuf+5+8) < Value/2)
                                        j = 3;
                                else if (*(double *)(InBuf+5+8) < Value)
                                        j = 4;
                                else if (*(double *)(InBuf+5+8) < Value*2)
                                        j = 5;
                                else
                                        j = 6;
                                *(double *)CacheBuf = Table00DD[j][(long)(Value/50)][i][0]+Value*Table00DD[j][(long)(Value/50)][i][1]; }
                        break;
                case 0x00E1:
                        *OutLen = 2;
                        OutBuf[0] = 0x61;
                        OutBuf[1] = 0xFC;
                        CacheLen = 0xFC;
                        MoveMemory(CacheBuf, InBuf+5, 0x98);
                        ZeroMemory(CacheBuf+0x98, sizeof(CacheBuf)-0x98);
                        j = 0;
                        for (i = 0; i < CacheBuf[0]; i++) {
                                if (!i || (CacheBuf[i+2] != CacheBuf[0x98+j-1])) {
                                        CacheBuf[0x98+j] = CacheBuf[i+2];
                                        j++; }
                                CacheBuf[i+2] = (unsigned char)j; }
                        if ((i == 1) && (j == 1))
                                j = 0;
                        CacheBuf[0] = (unsigned char)j;
                        break;
                case 0x00E2:
                        *OutLen = 2;
                        OutBuf[0] = 0x61;
                        OutBuf[1] = 0xA0;
                        CacheLen = 0xA0;
                        MoveMemory(CacheBuf, InBuf+5+8, 0xA0);
                        for (i = 0; i < 10; i++) {
                                *(double *)(CacheBuf+i*8) *= *(double *)(CacheBuf+i*8+80);
                                *(double *)(CacheBuf+i*8+80) *= *(double *)(CacheBuf+i*8); }
                        break;
                case 0x00E3:
                        *OutLen = 2;
                        OutBuf[0] = 0x61;
                        OutBuf[1] = 0x28;
                        CacheLen = 0x28;
                        i = *(long *)(InBuf+5+12*4)**(long *)(InBuf+5+13*4)**(long *)(InBuf+5+14*4);
                        *(long *)(CacheBuf+0*4) = 0x81CC+*(long *)(InBuf+5+10*4)*0x0C;
                        *(long *)(CacheBuf+1*4) = 0x8A;
                        *(long *)(CacheBuf+2*4) = *(long *)(InBuf+5+2*4);
                        *(long *)(CacheBuf+3*4) = 0x031A+*(long *)(InBuf+5+10*4)*0x0C;
                        *(long *)(CacheBuf+4*4) = 0;
                        *(long *)(CacheBuf+5*4) = 0xA73F+*(long *)(InBuf+5+10*4)*0x0C;
                        *(long *)(CacheBuf+6*4) = 0x1639+(*(long *)(InBuf+5+1*4)&1)*0x10C5+*(long *)(InBuf+5+10*4)*0x0C;
                        *(long *)(CacheBuf+7*4) = 0x28B5+(*(long *)(InBuf+5+1*4)&1)*0x223E+*(long *)(InBuf+5+10*4)*0x0C;
                        *(long *)(CacheBuf+8*4) = 0;
                        *(long *)(CacheBuf+9*4) = 0x5E9D+*(long *)(InBuf+5+10*4)*0x0C;
                        if (!(*(long *)(InBuf+5+1*4)&1)) {
                                *(long *)(CacheBuf+0*4) += i-0x4355;
                                *(long *)(CacheBuf+2*4) += 0x5A10+*(long *)(InBuf+5+10*4)*0x0C+i;
                                *(long *)(CacheBuf+5*4) += i-0x53E2;
                                *(long *)(CacheBuf+8*4) += 0x624E+*(long *)(InBuf+5+2*4)*0x03+*(long *)(InBuf+5+10*4)*0x0C+i;
                                *(long *)(CacheBuf+9*4) += i-0x3300; }
                        else if (*(unsigned long *)(InBuf+5+2*4) > 0x500)
                                *(long *)(CacheBuf+5*4) += *(long *)(InBuf+5+2*4)-0x2543;
                        break;
                case 0x00E6:
                        *OutLen = 2;
                        OutBuf[0] = 0x61;
                        OutBuf[1] = 0x40;
                        CacheLen = 0x40;
                        i = *(long *)(InBuf+5+0x10*4);
                        *(long *)(CacheBuf+0x0*4) = 0x02;
                        *(long *)(CacheBuf+0x1*4) = 0x4F54+i;
                        *(long *)(CacheBuf+0x2*4) = 0x76D7+i;
                        *(long *)(CacheBuf+0x3*4) = 0x006F+i;
                        *(long *)(CacheBuf+0x4*4) = 0x27D9+i;
                        *(long *)(CacheBuf+0x5*4) = 0x7BA7+i;
                        *(long *)(CacheBuf+0x6*4) = 0x173E93+i;
                        *(long *)(CacheBuf+0x7*4) = 0x167957+i;
                        *(long *)(CacheBuf+0x8*4) = 0x174395+i;
                        *(long *)(CacheBuf+0x9*4) = 0x1734E7+i;
                        *(long *)(CacheBuf+0xA*4) = 0x178A4B+i;
                        *(long *)(CacheBuf+0xB*4) = 0x181942+i;
                        *(long *)(CacheBuf+0xC*4) = 0x181956+i;
                        *(long *)(CacheBuf+0xD*4) = 0x181996+i;
                        *(long *)(CacheBuf+0xE*4) = 0x181710+i;
                        *(long *)(CacheBuf+0xF*4) = 0x181E22;
                        break;
                case 0x02E0:
                        *OutLen = 2;
                        OutBuf[0] = 0x61;
                        OutBuf[1] = 4;
                        CacheLen = 4;
                        if (*(long *)(InBuf+5) == 0xDBA0ADB2)
                                *(long *)CacheBuf = 0x44A0A4E3;
                        else
                                *(long *)CacheBuf = 0x2D2C6A64;
                        if (Flag02E0)
                                CacheBuf[2] ^= 7;
                        Flag02E0 = !Flag02E0;
                        break;
                case 0x04E0:
                        *OutLen = 2;
                        OutBuf[0] = 0x61;
                        OutBuf[1] = 0x0C;
                        CacheLen = 0x0C;
                        switch (*(long *)(InBuf+5)) {
                                case 0x00000001:
                                        *(long *)CacheBuf = 0xB40BFDD6;
                                        break;
                                case 0x00000002:
                                        *(long *)CacheBuf = 0xB40BFDA8;
                                        break;
                                case 0x00000004:
                                        *(long *)CacheBuf = 0xB40BFC04;
                                        break;
                                case 0x00000008:
                                        *(long *)CacheBuf = 0xB40BFCAC;
                                        break;
                                case 0x00000010:
                                        *(long *)CacheBuf = 0xB40BFF5C;
                                        break;
                                case 0x00000800:
                                        *(long *)CacheBuf = 0xB4080DFC;
                                        break;
                                case 0x00002000:
                                        *(long *)CacheBuf = 0xB4113DFC;
                                        break;
                                case 0x00010004:
                                        *(long *)CacheBuf = 0xB40BFC3C;
                                        break;
                                case 0x00010040:
                                        *(long *)CacheBuf = 0x01F8A8F9;
                                        break;
                                case 0x00010100:
                                        *(long *)CacheBuf = 0xB40BEDFC;
                                        break;
                                default:
                                        *(long *)CacheBuf = 0; }
                        *(long *)(CacheBuf+8) = *(long *)CacheBuf^*(long *)(InBuf+9+8);
                        *(long *)(CacheBuf+4) = *(long *)CacheBuf^*(long *)(InBuf+9+4);
                        *(long *)CacheBuf ^= *(long *)(InBuf+9);
                        break;
                case 0xC000:
                        if (CacheLen) {
                                i = InBuf[4];
                                *OutLen = i+2;
                                MoveMemory(OutBuf, CacheBuf, i);
                                CacheLen -= i;
                                MoveMemory(CacheBuf, CacheBuf+i, CacheLen);
                                if (!CacheLen)
                                        OutBuf[i] = 0x90;
                                else
                                        OutBuf[i] = 0x61;
                                OutBuf[i+1] = (char)CacheLen; }
                        break;
                default:
                        if (RunType == 1) {
                                DebugExe();
                                DebugLog(InBuf, InLen, 0, 0); }
                        CacheLen = 0;
                case 0x6880:
                        *OutLen = sizeof(Head0);
                        MoveMemory(OutBuf, Head0, *OutLen); }
}

void        _stdcall        SCardTransmit2(long Handle, long Para_2, unsigned char *InBuf, long InLen, long Para_5, unsigned char *OutBuf, long *OutLen)
{
        bool        Flag28 = false;

        if (InBuf[1] == 2) {
                InBuf[1] = 8;
                Flag28 = true; }
        ProcSCardTransmit(Handle, Para_2, InBuf, InLen, Para_5, OutBuf, OutLen);
        switch (*(long *)InBuf) {
                case 0x1A80:
                case 0x1AF0:
                        *OutLen = sizeof(Head1);
                        MoveMemory(OutBuf, Head1, *OutLen);
                        break;
                case 0x1C80:
                case 0x1CF0:
                        *OutLen = sizeof(Head2);
                        MoveMemory(OutBuf, Head2, *OutLen);
                        break;
                case 0x1880:
                case 0x68F0:
                        *OutLen = sizeof(Head3);
                        MoveMemory(OutBuf, Head3, *OutLen);
                        break; }
        if (Flag28)
                InBuf[1] = 2;
}

bool        Flag0025 = false;
bool        Flag00DD = false;

unsigned long        LastLen;
unsigned char        LastBuf[0x100];

long        _stdcall        SCardTransmit(long Handle, long Para_2, unsigned char *InBuf, long InLen, long Para_5, unsigned char *OutBuf, long *OutLen)
{
        char        FPU[0x100];
        unsigned char        MyOutBuf[0x100];
        long        MyOutLen;
        long        Temp[2][3];

        if (!RunType)
                return ProcSCardTransmit(Handle, Para_2, InBuf, InLen, Para_5, OutBuf, OutLen);
        if (*(short *)InBuf == 0x2680)
                *(long *)InBuf >>= 0x10;
        _asm        FNSAVE        FPU;
        if (RunType == 1) {
                SCardTransmit1(Handle, Para_2, InBuf, InLen, Para_5, OutBuf, OutLen);
                _asm        FRSTOR        FPU;
                return 0; }
        if (*(long *)InBuf != 0xC000) {
                LastLen = InLen;
                MoveMemory(LastBuf, InBuf, InLen); }
        SCardTransmit1(Handle, Para_2, InBuf, InLen, Para_5, MyOutBuf, &MyOutLen);
        SCardTransmit2(Handle, Para_2, InBuf, InLen, Para_5, OutBuf, OutLen);
        if (*(long *)InBuf == 0x0025)
                Flag0025 = true;
        if (*(long *)InBuf == 0x00DD)
                Flag00DD = true;
        if ((*OutLen != MyOutLen) || memcmp(OutBuf, MyOutBuf, MyOutLen)) {
                if (*(long *)InBuf == 0xC000) {
                        if (Flag0025) {
                                Flag0025 = false;
                                MoveMemory(Temp[0], MyOutBuf, 0x0C);
                                MoveMemory(Temp[1], OutBuf, 0x0C);
                                Temp[0][0] ^= Temp[0][1];
                                Temp[0][1] ^= Temp[0][2];
                                Temp[1][0] ^= Temp[1][1];
                                Temp[1][1] ^= Temp[1][2];
                                if ((long)((*(double *)&Temp[0]-*(double *)&Temp[1])*10000000000)) {
                                        DebugLog(LastBuf, LastLen, 0, 0);
                                        DebugLog(InBuf, InLen, (unsigned char *)Temp[1], 0x0C); }
                                _asm        FRSTOR        FPU;
                                return 0; }
                        if (Flag00DD) {
                                Flag00DD = false;
                                if ((long)((*(double *)OutBuf-*(double *)MyOutBuf)*100000000)) {
                                        DebugLog(LastBuf, LastLen, 0, 0);
                                        DebugLog(InBuf, InLen, (unsigned char *)Temp[1], 0x0C); }
                                _asm        FRSTOR        FPU;
                                return 0; }
        _asm        FRSTOR        FPU;
        return 0;
} 
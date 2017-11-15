//http://ig4l.net/forum/topic/15405-how-to-hackshield-bypass-code-2009/
#define HS_JMP            0x63B31D
#define HS_JMP2            0x63B323

typedef int            (__cdecl *HS_GetProcAddress_t)( int hModule, int a2 );
typedef int            (__stdcall *HackshieldComm_t )( int, void*, void* );
typedef signed int    (__stdcall *KickProc_t)( int a1, int a2, int a3 );

HS_GetProcAddress_t                pHS_GetProcAddress        = NULL;
HackshieldComm_t                pHackshieldComm            = NULL;
KickProc_t                        pKickProc                = NULL;

signed int __stdcall new_KickProc( int a1, int a2, int a3 )
{
    return 1;
}

int __stdcall new_HackshieldComm( int hsCommCode, void *Param1, void *Param2 )
{
    if( hsCommCode == 4 || hsCommCode == 5 || hsCommCode == 13 ) //kill!
    {
        if( hsCommCode == 4 ) //replace kick proc
        {
            DWORD *dwParam1 = (DWORD *)Param1;

            pKickProc    = (KickProc_t)*dwParam1;
            *dwParam1    = (DWORD)new_KickProc;
        }

        int iReturn = pHackshieldComm( hsCommCode, Param1, Param2 );

        return 1;
    }

    int iReturn = pHackshieldComm( hsCommCode, Param1, Param2 );

    return iReturn;
}

void HookCommunication( EXCEPTION_POINTERS* pExceptionInfo )
{
    DWORD dwEbp        = pExceptionInfo->ContextRecord->Ebp;
    DWORD dwParam2    = 0;

    __asm
    {
        push eax;
        push edx;
        mov eax, dwEbp;
        mov edx, [eax+0xC];
        mov dwParam2, edx;
        pop edx;
        pop eax;
    }

    if( dwParam2 == 0xA ) //this is the ordinal of some export...hmm..
    {
        pHackshieldComm                        = (HackshieldComm_t)pExceptionInfo->ContextRecord->Eax;
        pExceptionInfo->ContextRecord->Eax    = (DWORD)new_HackshieldComm;
    }

    pExceptionInfo->ContextRecord->Eip        = HS_JMP2;

    return;
}

PVOID pContextHandler = NULL;

LONG WINAPI TGSExceptionHandler( EXCEPTION_POINTERS* pExceptionInfo )
{
    if( pExceptionInfo->ExceptionRecord->ExceptionCode != EXCEPTION_SINGLE_STEP )
    {
        return EXCEPTION_CONTINUE_SEARCH;
    }

    if( pExceptionInfo->ExceptionRecord->ExceptionAddress == (PVOID)HS_JMP ) 
    {
        HookCommunication( pExceptionInfo );
        return EXCEPTION_CONTINUE_EXECUTION;
    }

    return EXCEPTION_CONTINUE_SEARCH;
}

void InitContextHook()
{
    pContextHandler = AddVectoredExceptionHandler( 0x50BE17, TGSExceptionHandler );

    CONTEXT Context;
    Context.ContextFlags = CONTEXT_DEBUG_REGISTERS;
    GetThreadContext(GetCurrentThread(), &Context);
    Context.Dr0 = HS_JMP;
    Context.Dr7 = (1<<0)|(1<<2)|(1<<4)|(1<<6);
    SetThreadContext(GetCurrentThread(), &Context);
}  
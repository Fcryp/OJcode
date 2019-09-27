#include <cstdlib>
#include <ctime>
#include <cstdio>
#include <windows.h>
#include <processthreadsapi.h>
using namespace std;
TCHAR CommandLine[]="cerc2008_tower.exe";
TCHAR StdTestCommandLine[] = "test.exe";

HANDLE hStdInRead;
HANDLE hStdInWrite;
HANDLE hStdOutRead;
HANDLE hStdOutWrite;
HANDLE hStdErrWrite;
SECURITY_ATTRIBUTES saAttr;

STARTUPINFO siStartInfo;
PROCESS_INFORMATION piProcInfo;

char cWriteStr[35];
char cReadStr[35];

bool WriteToPipe(){
    DWORD dwWritten;
    bool bSuccess;
    long long a2, n, m;
    srand((unsigned)time(NULL));
    a2 = rand() % (1000000000) + 1;
    n = rand() % (1000000000) + 1;
    m = rand() % (1000000000) + 2;
    printf("%lld %lld %lld\n",a2,n,m);
    sprintf(cWriteStr, "1\n%lld %lld %lld", a2, n, m);
    bSuccess = WriteFile(hStdInWrite, cWriteStr, 35, &dwWritten, NULL);
    return bSuccess;
}
bool ReadFromPipe(){
    DWORD dwRead;
    bool bSuccess = FALSE;
    bSuccess = ReadFile(hStdOutRead, cReadStr, 35, &dwRead, NULL);
    if((bSuccess)&&(dwRead!=0)){
        
        printf("echo:%s",cReadStr);
    }
    return bSuccess;
} 
 int main(int argc, char const *argv[])
{
    bool bSuccess,bIsTheSame;
    DWORD dwErrorCode;
    saAttr.nLength = sizeof(SECURITY_ATTRIBUTES);
    saAttr.bInheritHandle = TRUE;
    saAttr.lpSecurityDescriptor = NULL;   

    if(!CreatePipe(&hStdInRead,&hStdInWrite,&saAttr,0))
        return -1;
    if(!CreatePipe(&hStdOutRead,&hStdOutWrite,&saAttr,0))
        return -2;
    if(!DuplicateHandle(GetCurrentProcess(),hStdOutWrite,GetCurrentProcess(),&hStdErrWrite,0,TRUE,DUPLICATE_SAME_ACCESS))
        return -3;
    ZeroMemory(&siStartInfo, sizeof(STARTUPINFO));
    siStartInfo.dwFlags |= STARTF_USESHOWWINDOW;
    siStartInfo.dwFlags |= STARTF_USESTDHANDLES;
    siStartInfo.hStdOutput = hStdOutWrite;
    siStartInfo.hStdError = hStdErrWrite;
    siStartInfo.hStdInput = hStdInRead;
    
    while(ReadFromPipe()){
        bSuccess = CreateProcess(
            NULL,
            CommandLine,
            NULL,
            NULL,
            TRUE,
            0,
            NULL,
            NULL,
            &siStartInfo,
            &piProcInfo);
        if(!bSuccess){
            dwErrorCode=GetLastError();
            printf("ErrorCode:%d\n",dwErrorCode);
            return -4;
        }
        WriteToPipe();
        ReadFromPipe();
        bSuccess = CreateProcess(
            NULL,
            StdTestCommandLine,
            NULL,
            NULL,
            TRUE,
            0,
            NULL,
            NULL,
            &siStartInfo,
            &piProcInfo);
        if(!bSuccess){
            dwErrorCode=GetLastError();
            printf("ErrorCode:%d\n",dwErrorCode);
            return -4;
        }
        WriteToPipe();
        ReadFromPipe();
    }
    return 0;
}
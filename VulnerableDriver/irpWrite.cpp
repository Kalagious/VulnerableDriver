#include "general.h"

NTSTATUS IrpWriteHandler(PDEVICE_OBJECT DeviceObject, PIRP Irp) {
    UNREFERENCED_PARAMETER(DeviceObject);


    PIO_STACK_LOCATION stack = IoGetCurrentIrpStackLocation(Irp);
    ULONG buffSize = stack->Parameters.Write.Length;


    MDL* mdl = IoAllocateMdl(Irp->UserBuffer, buffSize, FALSE, FALSE, NULL);
    MmProbeAndLockPages(mdl, KernelMode, IoWriteAccess);
    PVOID userInput = MmGetSystemAddressForMdlSafe(mdl, NormalPagePriority);

    if (!userInput)
    {
        DbgPrintEx(DPFLTR_IHVDRIVER_ID, DPFLTR_ERROR_LEVEL, "Input Failed\n");
        return STATUS_FAIL_CHECK;
    }


    switch (stack->MajorFunction) {
    case IRP_MJ_WRITE:
        DbgPrintEx(DPFLTR_IHVDRIVER_ID, DPFLTR_ERROR_LEVEL, " [*] IRP_MJ_WRITE\n");


        UINT64 writeBufferSize = ((UINT64*)userInput)[0];
        UINT64 writeAddress = *((UINT64*)((UINT64)userInput + sizeof(UINT64)));

        char* writeData = (char*)((UINT64)userInput + sizeof(UINT64) * 2);

        memcpy((void*)writeAddress, writeData, writeBufferSize);

        //DbgBreakPoint();
    
        break;
    }

    MmUnlockPages(mdl);

    return STATUS_SUCCESS;
}
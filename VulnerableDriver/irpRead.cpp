#include "general.h"




// Handle Irp for read
NTSTATUS IrpReadHandler(PDEVICE_OBJECT DeviceObject, PIRP Irp) {

    UNREFERENCED_PARAMETER(DeviceObject);


    PIO_STACK_LOCATION stack = IoGetCurrentIrpStackLocation(Irp);
    ULONG buffSize = stack->Parameters.Write.Length;

    // Get the input buffer from the user
    MDL* mdl = IoAllocateMdl(Irp->UserBuffer, buffSize, FALSE, FALSE, NULL);
    MmProbeAndLockPages(mdl, KernelMode, IoWriteAccess);
    PVOID userInput = MmGetSystemAddressForMdlSafe(mdl, NormalPagePriority);

    if (!userInput)
    {
        DbgPrintEx(DPFLTR_IHVDRIVER_ID, DPFLTR_ERROR_LEVEL, "Input Failed\n");
        return STATUS_FAIL_CHECK;
    }



    // Verify the IRP
    switch (stack->MajorFunction) {
    case IRP_MJ_READ:
        DbgPrintEx(DPFLTR_IHVDRIVER_ID, DPFLTR_ERROR_LEVEL, " [*] IRP_MJ_READ\n");


        UINT64 readBufferSize = ((UINT64*)userInput)[0];
        UINT64 readAddress = *((UINT64*)((UINT64)userInput + sizeof(UINT64)));



        memcpy(userInput, (void*)readAddress, readBufferSize);



        break;
    }



    
    MmUnlockPages(mdl);


    return STATUS_SUCCESS;
}
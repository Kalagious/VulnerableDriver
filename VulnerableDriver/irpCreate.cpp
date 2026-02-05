#include "general.h"


NTSTATUS IrpCreateHandler(PDEVICE_OBJECT DeviceObject, PIRP Irp) {
    // Code for the read IRP
    // Get the buffer from the IRP
    UNREFERENCED_PARAMETER(DeviceObject);
    PIO_STACK_LOCATION stack = IoGetCurrentIrpStackLocation(Irp);

    switch (stack->MajorFunction) {
    case IRP_MJ_CREATE:
        // Read the buffer
        DbgPrintEx(DPFLTR_IHVDRIVER_ID, DPFLTR_ERROR_LEVEL, " [*] IRP_MJ_CREATE\n");
        break;
    }
    return STATUS_SUCCESS;
}
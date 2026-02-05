#include "general.h"
#include "irpHandlers.h"


VOID UnloadDriver(PDRIVER_OBJECT DriverObject);


extern "C" NTSTATUS DriverEntry(PDRIVER_OBJECT DriverObject, PUNICODE_STRING RegistryPath) {
    UNREFERENCED_PARAMETER(RegistryPath);
    DbgPrintEx(DPFLTR_IHVDRIVER_ID, DPFLTR_ERROR_LEVEL, " [*] Creating Device\n");

    // Create a device object
    UNICODE_STRING devName;
    RtlInitUnicodeString(&devName, L"\\Device\\VulnDriver");


    PDEVICE_OBJECT DeviceObject;
    NTSTATUS status = IoCreateDevice(DriverObject, 0, &devName, FILE_DEVICE_UNKNOWN, FILE_DEVICE_SECURE_OPEN, FALSE, &DeviceObject);
    
    
    if (!NT_SUCCESS(status)) 
        return status;
    

   


    DbgPrintEx(DPFLTR_IHVDRIVER_ID, DPFLTR_ERROR_LEVEL, " [*] Creating Symlink\n");

    // Create a symbolic link
    UNICODE_STRING symLink;
    RtlInitUnicodeString(&symLink, L"\\??\\VulnDriver");

    status = IoCreateSymbolicLink(&symLink, &devName);

    if (!NT_SUCCESS(status)) {
        IoDeleteDevice(DeviceObject);
        return status;
    }



    // Set up handlers
    DriverObject->DriverUnload = UnloadDriver;
    DriverObject->MajorFunction[IRP_MJ_CREATE] = IrpCreateHandler;
    DriverObject->MajorFunction[IRP_MJ_READ] = IrpReadHandler;
    DriverObject->MajorFunction[IRP_MJ_WRITE] = IrpWriteHandler;

    DriverObject->Flags |= DO_DIRECT_IO;
    DriverObject->Flags &= ~DO_DEVICE_INITIALIZING;



    DbgPrintEx(DPFLTR_IHVDRIVER_ID, DPFLTR_ERROR_LEVEL, " [*] Driver loaded\n");
    return STATUS_SUCCESS;
}











VOID UnloadDriver(PDRIVER_OBJECT DriverObject) {
    // Code for the unload driver situation
    // Delete the device object and symbolic link
    DbgPrintEx(DPFLTR_IHVDRIVER_ID, DPFLTR_ERROR_LEVEL, " [*] Unloading Driver\n");

    UNICODE_STRING symLink = RTL_CONSTANT_STRING(L"\\??\\VulnDriver");
    IoDeleteSymbolicLink(&symLink);
    IoDeleteDevice(DriverObject->DeviceObject);
}

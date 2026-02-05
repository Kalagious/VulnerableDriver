#pragma once
#include "general.h"


NTSTATUS IrpCreateHandler(PDEVICE_OBJECT DeviceObject, PIRP Irp);
NTSTATUS IrpReadHandler(PDEVICE_OBJECT DeviceObject, PIRP Irp);
NTSTATUS IrpWriteHandler(PDEVICE_OBJECT DeviceObject, PIRP Irp);
/*++

Module Name:

    public.h

Abstract:

    This module contains the common declarations shared by driver
    and user applications.

Environment:

    user and kernel

--*/

//
// Define an Interface Guid so that apps can find the device and talk to it.
//

DEFINE_GUID (GUID_DEVINTERFACE_VulnerableDriver,
    0x43717b26,0x91f8,0x4d87,0x84,0x21,0x38,0xd6,0x8a,0x1e,0xe6,0xf4);
// {43717b26-91f8-4d87-8421-38d68a1ee6f4}

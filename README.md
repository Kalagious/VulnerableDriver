
Unsigned Driver, requires signing and secure boot to be off. 

Exposes 2 IRP Handlers for IRP_MJ_READ and IRP_MJ_WRITE.

Each one can read and write kernel memory respectively using a user supplied buffer.

The buffer format is the following for each request:
  IRP_MJ_READ:
    *Buffer must be big enough to contain the read result*
    Bytes 0-7: Byte count of data to read
    Bytes 8-15: Address to start read from
    Remaining Bytes: Empty space for read result

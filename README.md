
Unsigned Driver, requires signing and secure boot to be off. <br>

Exposes 2 IRP Handlers for IRP_MJ_READ and IRP_MJ_WRITE.<br>

Each one can read and write kernel memory respectively using a user supplied buffer.<br>

The buffer format is the following for each request:<br>
* IRP_MJ_READ:<br>
    *Buffer must be big enough to contain the read result*<br>
    Bytes 0-7: Byte count of data to read<br>
    Bytes 8-15: Address to start read from<br>
    Remaining Bytes: Empty space for read result<br>
<br><br>
* IRP_MJ_WRITE:<br>
    Bytes 0-7: Byte count of data to write<br>
    Bytes 8-15: Address to start write from<br>
    Remaining Bytes: Data to write<br>

<br><br>
Each IRP Handler can be access like so:<br>
ReadFile(device, buffer, sizeof(buffer), &bytesRead, 0);
WriteFile(device, buffer, sizeof(buffer), &bytesWritten, 0);

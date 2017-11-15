NTSTATUS LogMessage(PCHAR szFormat, ...) {
/*++
Routine Description:

   Log msg into debug console and file

Arguments:

   szFormat - message format string

   ... - data

Return Value:

   NT status code

--*/
    ULONG Length;
    char messagebuf[1024];
    va_list va;
    IO_STATUS_BLOCK  IoStatus;
    OBJECT_ATTRIBUTES objectAttributes;
    NTSTATUS status;
    HANDLE FileHandle;
    UNICODE_STRING fileName;
    
    //format the string
    va_start(va,szFormat);
    _vsnprintf(messagebuf,sizeof(messagebuf),szFormat,va);
    va_end(va);
    
    //get a handle to the log file object
    fileName.Buffer = NULL;
    fileName.Length = 0;
    fileName.MaximumLength = sizeof(DEFAULT_LOG_FILE_NAME) + sizeof(UNICODE_NULL);
    fileName.Buffer = ExAllocatePool(PagedPool,
                                     fileName.MaximumLength);
    if (!fileName.Buffer) {
        DbgPrint ("LogMessageInFile: FAIL. ExAllocatePool Failed.\n");
        return FALSE;
    }
    RtlZeroMemory(fileName.Buffer, fileName.MaximumLength);
    status = RtlAppendUnicodeToString(&fileName, (PWSTR)DEFAULT_LOG_FILE_NAME);
     
    InitializeObjectAttributes (&objectAttributes,
                                (PUNICODE_STRING)&fileName,
                                OBJ_CASE_INSENSITIVE,
                                NULL,
                                NULL );
    
    status = ZwCreateFile( &FileHandle,
                           FILE_APPEND_DATA,
                           &objectAttributes,
                           &IoStatus,
                           0, 
                           FILE_ATTRIBUTE_NORMAL,
                           FILE_SHARE_WRITE,
                           FILE_OPEN_IF,
                           FILE_SYNCHRONOUS_IO_NONALERT,
                           NULL,     
                           0 );
    
    if( NT_SUCCESS(status) ) {
        CHAR buf[1024];
        
        sprintf(buf,"%s",messagebuf);
        
        //format the string to make sure it appends a newline carrage-return to the 
        //end of the string.
        Length=strlen(buf);
        if( buf[Length-1]=='\n' ) {
            buf[Length-1]='\r';
            strcat(buf,"\n");
            Length++;
        } else {
            strcat(buf,"\r\n");
            Length+=2;
        }
        
        DbgPrint("%s", buf); 

        ZwWriteFile( FileHandle, NULL, NULL, NULL, &IoStatus, buf, Length, NULL, NULL );
        
        ZwClose( FileHandle );
    }

    if( fileName.Buffer ) {
        ExFreePool (fileName.Buffer);
    }

    return STATUS_SUCCESS;
}
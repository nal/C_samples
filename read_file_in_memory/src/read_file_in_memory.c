#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

/* Define DEBUG 1 to allow debuggin errno in local_perror */

#define DEBUG 0

enum error_code {
    NOT_S_ISREG     = -2, // File is not a regular file: socket, device etc.
    UNKNOWN_ERROR   = -3
};

/* Definitions */
long get_file_size( char *file_path );
void local_perror ( void );

/* Functions */

/*  On success this function returns long int with file size in bytes.
    On error it return -1 and sets errno to negative value
    (see enum error_code).
*/
long get_file_size( char *file_path ) {
    /* Init section */
    struct stat buf;
    int stat_result;

    enum error_code error_code;

    /* Main code section */
    stat_result = stat(file_path, &buf);

    if ( stat_result == 0 ) {
        if ( S_ISREG(buf.st_mode)  ) {
            /* This is regular file, all OK */
            return (long)buf.st_size;
        }
        else {
            /* Set error code in errno */
            error_code = NOT_S_ISREG;
            errno = error_code;
            return -1;
        }
    }
    else {
        /* Error code in errno */
        return -1;
    }
}

/*  This function acts like system function perror( char *) but have
    some modifications to handle local negative error codes. */
void local_perror () {
    if ( errno > 0 ) {
        perror("get_file_size failed:");
    }
    else if ( errno < 0 ) {
        #if DEBUG
            printf("debug: in function 'local_perror' errno = %d\n", errno);
        #endif

        switch ( errno ) {
            case NOT_S_ISREG:
                printf("Error: file is not a regular file\n");
                break;
            case UNKNOWN_ERROR:
                printf("Error: Unknown error\n");
                break;
        }
    }
}

/*  Main function prints file size of self in bytes or argv[1] if supplied.
    Works only for regular files.
*/
int main( int argc, char *argv[] ) {
    long file_size = 0L;
    char *file_path;

    if ( argc == 2 ) {
        file_path = argv[1];
    }
    else {
        file_path = argv[0];
    }

    file_size = get_file_size( file_path );

    if ( file_size < 0 ) {
        local_perror();
        return 1;
    }

    /* Allocating memory for file in heap */
    unsigned char *file_contents;
    file_contents = malloc( file_size + 1 );

    if ( file_contents == NULL ) {
        perror( "Failed to allocate memory for file" );
        return 1;
    }

    /* ALL OK, now we have allocated memory for file contents */
    FILE *fp;

    if ( (fp = fopen(file_path, "rb")) == NULL ) {
        char error_message[255];
        snprintf(error_message, sizeof(error_message), "%s %s %s", "Couldn't open file", file_path, "for reading");

        exit(1);
    }

    // read all file contents in 1 attempt as chars
    int read_blocks;
    read_blocks = fread(file_contents, file_size, 1, fp);
    #if DEBUG
        printf("debug: in function 'main'; file_size = %ld\n", file_size);
        printf("debug: in function 'main' read %d blocks from input file\n", read_blocks);
    #endif
    fclose(fp);

    printf("File contents: %s\n", file_contents);

    free( file_contents );

    return 0;
}

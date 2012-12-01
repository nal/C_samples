#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>

/* Define DEBUG 1 to allow debuggin errno in local_perror */

#define DEBUG 0

enum error_code {
    NOT_S_ISREG     = -2, /* Input file in not a regular file. It is socket, block device etc. */
    UNKNOWN_ERROR   = -3
};

/* Definitions */
long get_file_size( char *file_path );
void local_perror ();

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
        return 0;
    }

    printf("File size of file %s is %ld bytes\n", file_path, file_size);
    return 0;
}

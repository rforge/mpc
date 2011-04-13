# autoconf configure.ac > configure
AC_INIT([mpc])
AC_CONFIG_SRCDIR([DESCRIPTION])

case "$target" in
 *freebsd*)
   CFLAGS="$CFLAGS -L/usr/local/lib -I/usr/local/include"
esac

PKG_CPPFLAGS=$CPPFLAGS
PKG_CFLAGS=$CFLAGS
PKG_LDFLAGS=$LDFLAGS

## Hhmm, how can I check that the headers mpfr.h & gmp.h are "visible"
## It is *not* AC_CONFIG_HEADERS(....)

AC_CHECK_LIB(gmp, __gmpz_init, ,
    [AC_MSG_ERROR([GNU MP not found, see README])])

AC_CHECK_LIB(mpfr, mpfr_init, ,
    [AC_MSG_ERROR([MPFR Library not found, see README])])

AC_CHECK_LIB(mpc, mpc_init2, ,
    [AC_MSG_ERROR([MPC Library not found, see README])])

AC_SUBST(PKG_CPPFLAGS)
AC_SUBST(PKG_CFLAGS)
AC_SUBST(PKG_LDFLAGS)

AC_CONFIG_FILES(src/Makevars)
AC_OUTPUT

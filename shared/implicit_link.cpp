/* Pantheios Header Files */
#include <pantheios/implicit_link/core.h>
#include <pantheios/implicit_link/fe.simple.h>
#include <pantheios/implicit_link/be.N.h>
#include <platformstl/platformstl.h>
#include <pantheios/implicit_link/be.file.h>
#if defined(PLATFORMSTL_OS_IS_UNIX)
#include <pantheios/implicit_link/bec.fprintf.h>
#elif defined(PLATFORMSTL_OS_IS_WINDOWS)
#include <pantheios/implicit_link/bec.WindowsConsole.WithCallback.h>
#else
#error platform not descriminated
#endif

#if (   defined(UNIX) || \
        defined(unix))&& \
    (   defined(_WIN32) || \
        defined(_WIN64))
# include <unixem/implicit_link.h>
#endif /* _WIN32 || _WIN64 */

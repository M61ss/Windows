# Notes

Keeping here some miscellaneous notes about Windows programming.

## Macros

### Setting up Unicode

You need to define these macros to set up Unicode in your application:

```c++
#ifndef UNICODE
#define UNICODE
#endif // !UNICODE

#ifndef _UNICODE
#define _UNICODE
#endif // !_UNICODE
```

By default Visual Studio doesn't require the definition of these macros because it defines them by itself. Anyway, it is necessary to put them into code because, if we exit from Visual Studio, these macros may be no longer defined.

### Compatibility

To defend itself from obsolet code, to run the `GetVersionExW` function Windows needs the definition of this macro:

```c++
#define BUILD_WINDOWS
```

### Mutex

This is a functionality used subsequently in the threatment of mutex's concept:

```c++
#define WM_NOTIFY_INSTANCE (WM_USER + 100)
```

## Includes

Necessary includes are:

```c++
#include <windows.h>
#include <stdio.h>
#include <atlstr.h>
```

Where `#include <atlstr.h>` is necessary for CString's usage.

## Special data types

### Unicode

In Windows there are some special data types to manage characters and strings in Unicode:

| Common type     | ASCII type          | Unicode type            |
| :-------------- | :------------------ | :---------------------- |
| TCHAR           | char, CHAR          | wchar_t, WCHAR          |
| LPSTR, PTSTR    | char*, CHAR*, PSTR  | wchar_t*, WCHAR*, PWSTR |
| LPCTSTR, PCTSTR | const char\*, PCSTR | const wchar_t\*, PCWSTR |



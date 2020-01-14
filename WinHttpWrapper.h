#pragma once
extern void LoadWinInet();
extern HMODULE WinhttpModule;

LPVOID WINAPI WinHttpQueryHeaders(IN LPVOID hRequest, IN DWORD dwInfoLevel, IN LPCWSTR  pwszName, LPVOID lpBuffer, IN OUT LPDWORD lpdwBufferLength, IN OUT LPDWORD lpdwIndex);
LPVOID WINAPI WinHttpSendRequest(IN LPVOID hRequest, LPCWSTR  lpszHeaders, IN DWORD   dwHeadersLength, LPVOID lpOptional, IN DWORD  dwOptionalLength, IN DWORD  dwTotalLength, IN DWORD_PTR dwContext);
LPVOID WINAPI WinHttpOpenRequest(IN LPVOID hConnect, IN LPCWSTR   pwszVerb, IN LPCWSTR   pwszObjectName, IN LPCWSTR   pwszVersion, IN LPCWSTR   pwszReferrer, IN LPCWSTR *ppwszAcceptTypes, IN DWORD dwFlags);
LPVOID WINAPI WinHttpAddRequestHeaders(IN LPVOID hRequest, _When_(dwHeadersLength == (DWORD)-1, _In_z_)	_When_(dwHeadersLength != (DWORD)-1, _In_reads_(dwHeadersLength)) LPCWSTR lpszHeaders, IN DWORD dwHeadersLength, IN DWORD dwModifiers);
LPVOID WINAPI WinHttpSetOption(LPVOID hInternet, DWORD     dwOption, LPVOID    lpBuffer, DWORD     dwBufferLength);
LPVOID WINAPI WinHttpQueryDataAvailable(IN LPVOID hRequest, LPDWORD lpdwNumberOfBytesAvailable);
LPVOID WINAPI WinHttpReadData(LPVOID hRequest, LPVOID lpBuffer, IN DWORD dwNumberOfBytesToRead, OUT LPDWORD lpdwNumberOfBytesRead);
LPVOID WINAPI WinHttpCloseHandle(IN LPVOID hInternet);
LPVOID WINAPI WinHttpSetStatusCallback(IN LPVOID hInternet, IN LPVOID lpfnInternetCallback, IN DWORD dwNotificationFlags, IN DWORD_PTR dwReserved);
LPVOID WINAPI WinHttpConnect(IN LPVOID hSession, IN LPCWSTR pswzServerName, IN DWORD nServerPort, IN DWORD dwReserved);
LPVOID WINAPI WinHttpOpen(LPCWSTR pszAgentW, DWORD   dwAccessType, LPCWSTR pszProxyW, LPCWSTR pszProxyBypassW, DWORD   dwFlags);
LPVOID WINAPI WinHttpSetTimeouts(IN LPVOID hInternet, IN int       nResolveTimeout, IN int       nConnectTimeout, IN int       nSendTimeout, IN int       nReceiveTimeout);
LPVOID WINAPI WinHttpWriteData(IN LPVOID hRequest, LPCVOID      lpBuffer, IN DWORD     dwNumberOfBytesToWrite, OUT LPDWORD  lpdwNumberOfBytesWritten);
LPVOID WINAPI WinHttpReceiveResponse(IN LPVOID hRequest, IN LPVOID    lpReserved);
LPVOID WINAPI WinHttpGetIEProxyConfigForCurrentUser(IN OUT LPVOID *pProxyConfig);
LPVOID WINAPI WinHttpGetProxyForUrl(IN LPVOID                hSession, IN LPCWSTR                   lpcwszUrl, IN LPVOID *pAutoProxyOptions, OUT LPVOID       *pProxyInfo);
LPVOID WINAPI WinHttpCrackUrl(LPCWSTR          pwszUrl, DWORD            dwUrlLength, DWORD            dwFlags, LPVOID lpUrlComponents);
DWORD WINAPI WinHttpCreateProxyResolver(LPVOID hSession, LPVOID *phResolver);
LPVOID WINAPI WinHttpGetProxyForUrl(IN LPVOID               hSession, IN LPCWSTR                   lpcwszUrl, IN LPVOID *pAutoProxyOptions, OUT LPVOID       *pProxyInfo);
LPVOID WINAPI WinHttpGetProxyForUrlEx(LPVOID                 hResolver, PCWSTR                    pcwszUrl, LPVOID *pAutoProxyOptions, DWORD_PTR                 pContext);
LPVOID WINAPI WinHttpGetProxyForUrlEx2(_In_ LPVOID hResolver, _In_ PCWSTR pcwszUrl, _In_ LPVOID *pAutoProxyOptions, _In_ DWORD cbInterfaceSelectionContext, _In_reads_bytes_opt_(cbInterfaceSelectionContext) BYTE *pInterfaceSelectionContext, _In_opt_ DWORD_PTR pContext);
DWORD WINAPI WinHttpGetProxyResultEx(_In_ LPVOID hResolver, _Out_ LPVOID *pProxyResultEx);
DWORD WINAPI WinHttpFreeProxyResultEx(_Inout_ LPVOID *pProxyResultEx);
DWORD WINAPI WinHttpResetAutoProxy(_In_ LPVOID hSession, _In_ DWORD dwFlags);
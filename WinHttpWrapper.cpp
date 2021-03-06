#include "stdafx.h"
#include "WinHttpWrapper.h"


LPVOID WINAPI WinHttpQueryHeaders(IN LPVOID hRequest, IN DWORD dwInfoLevel, IN LPCWSTR  pwszName, LPVOID lpBuffer, IN OUT LPDWORD lpdwBufferLength, IN OUT LPDWORD lpdwIndex) {
	ConsoleWrite("WinHttpQueryHeaders \n");
	if (WinhttpModule != NULL) {
		typedef LPVOID(WINAPI* IGCS)(IN LPVOID hRequest, IN DWORD dwInfoLevel, IN LPCWSTR  pwszName, LPVOID lpBuffer, IN OUT LPDWORD lpdwBufferLength, IN OUT LPDWORD lpdwIndex);
		IGCS origCall = (IGCS)GetProcAddress(WinhttpModule, "WinHttpQueryHeaders");
		LPVOID retVar = origCall(hRequest, dwInfoLevel, pwszName, lpBuffer, lpdwBufferLength, lpdwIndex);
		return retVar;
	}
	return NULL;

}


LPVOID WINAPI WinHttpSendRequest(IN LPVOID hRequest, LPCWSTR  lpszHeaders, IN DWORD   dwHeadersLength, LPVOID lpOptional, IN DWORD  dwOptionalLength, IN DWORD  dwTotalLength, IN DWORD_PTR dwContext) {
	if (WinhttpModule != NULL) {
		typedef LPVOID(WINAPI* IGCS)(IN LPVOID hRequest, LPCWSTR  lpszHeaders, IN DWORD   dwHeadersLength, LPVOID lpOptional, IN DWORD  dwOptionalLength, IN DWORD  dwTotalLength, IN DWORD_PTR dwContext);
		IGCS origCall = (IGCS)GetProcAddress(WinhttpModule, "WinHttpSendRequest");
		LPVOID retVar = origCall(hRequest, lpszHeaders, dwHeadersLength, lpOptional, dwOptionalLength, dwTotalLength, dwContext);
		std::string output = "WinHttpSendRequest return:" + n2hexstr((long long)retVar) + "\n";
		ConsoleWrite(output.c_str());
		return retVar;
	}
	return NULL;
}


LPVOID WINAPI WinHttpOpenRequest(IN LPVOID hConnect, IN LPCWSTR   pwszVerb, IN LPCWSTR   pwszObjectName, IN LPCWSTR   pwszVersion, IN LPCWSTR   pwszReferrer, IN LPCWSTR *ppwszAcceptTypes, IN DWORD dwFlags) {
	if (WinhttpModule != NULL) {
		typedef LPVOID(WINAPI* IGCS)(IN LPVOID hConnect, IN LPCWSTR   pwszVerb, IN LPCWSTR   pwszObjectName, IN LPCWSTR   pwszVersion, IN LPCWSTR   pwszReferrer, IN LPCWSTR *ppwszAcceptTypes, IN DWORD dwFlags);
		IGCS origCall = (IGCS)GetProcAddress(WinhttpModule, "WinHttpOpenRequest");

		std::wstring Verb = std::wstring(pwszVerb);
		std::wstring ObjectName = std::wstring(pwszObjectName);
		std::string output = "WinHttpOpenRequest hConnect:" + n2hexstr((long long)hConnect) + " pwszVerb:" + std::string(Verb.begin(), Verb.end()) + " pwszObjectName:" + std::string(ObjectName.begin(), ObjectName.end()) + " dwFlags:" + n2hexstr(dwFlags) + "\n";

		ConsoleWrite(output.c_str());

		return origCall(hConnect, pwszVerb, pwszObjectName, pwszVersion, pwszReferrer, ppwszAcceptTypes, NULL); //dwFlags <------------ insert flags to enable ssl
	}
	return NULL;
}

LPVOID WINAPI WinHttpAddRequestHeaders(IN LPVOID hRequest, _When_(dwHeadersLength == (DWORD)-1, _In_z_)	_When_(dwHeadersLength != (DWORD)-1, _In_reads_(dwHeadersLength)) LPCWSTR lpszHeaders, IN DWORD dwHeadersLength, IN DWORD dwModifiers) {
	if (WinhttpModule != NULL) {
		typedef LPVOID(WINAPI* IGCS)(IN LPVOID hRequest, _When_(dwHeadersLength == (DWORD)-1, _In_z_)	_When_(dwHeadersLength != (DWORD)-1, _In_reads_(dwHeadersLength)) LPCWSTR lpszHeaders, IN DWORD dwHeadersLength, IN DWORD dwModifiers);
		IGCS origCall = (IGCS)GetProcAddress(WinhttpModule, "WinHttpAddRequestHeaders");

		std::wstring Headers;
		if (dwHeadersLength > 0) {
			Headers = std::wstring(lpszHeaders, dwHeadersLength);
		}
		else {
			Headers = std::wstring(lpszHeaders);
		}
		std::string output = "WinHttpAddRequestHeaders hRequest:" + n2hexstr((long long)hRequest) + " Headers:" + std::string(Headers.begin(), Headers.end()) + "\n";
		ConsoleWrite(output.c_str());

		return origCall(hRequest, lpszHeaders, dwHeadersLength, dwModifiers);
	}
	return NULL;
}

LPVOID WINAPI WinHttpSetOption(LPVOID hInternet, DWORD     dwOption, LPVOID    lpBuffer, DWORD     dwBufferLength) {
	if (WinhttpModule != NULL) {
		typedef LPVOID(WINAPI* IGCS)(LPVOID hInternet, DWORD     dwOption, LPVOID    lpBuffer, DWORD     dwBufferLength);
		IGCS origCall = (IGCS)GetProcAddress(WinhttpModule, "WinHttpSetOption");

		std::string output = "WinHttpSetOption hInternet:" + n2hexstr((long long)hInternet) + " dwOption:" + n2hexstr((long long)dwOption) + " lpBuffer:" + PrintCharArray((const char*)lpBuffer, dwBufferLength) + " dwBufferLength:" + n2hexstr(dwBufferLength) + "\n";

		ConsoleWrite(output.c_str());
		return origCall(hInternet, dwOption, lpBuffer, dwBufferLength);
	}
	return NULL;
}

LPVOID WINAPI  WinHttpQueryDataAvailable(IN LPVOID hRequest, LPDWORD lpdwNumberOfBytesAvailable) {
	ConsoleWrite("WinHttpQueryDataAvailable \n");
	if (WinhttpModule != NULL) {
		typedef LPVOID(WINAPI* IGCS)(IN LPVOID hRequest, LPDWORD lpdwNumberOfBytesAvailable);
		IGCS origCall = (IGCS)GetProcAddress(WinhttpModule, "WinHttpQueryDataAvailable");
		return origCall(hRequest, lpdwNumberOfBytesAvailable);
	}
	return NULL;
}

LPVOID WINAPI WinHttpReadData(LPVOID hRequest, LPVOID lpBuffer, IN DWORD dwNumberOfBytesToRead, OUT LPDWORD lpdwNumberOfBytesRead) {
	if (WinhttpModule != NULL) {
		typedef LPVOID(WINAPI* IGCS)(LPVOID hRequest, LPVOID lpBuffer, IN DWORD dwNumberOfBytesToRead, OUT LPDWORD lpdwNumberOfBytesRead);
		IGCS origCall = (IGCS)GetProcAddress(WinhttpModule, "WinHttpReadData");
		LPVOID retVar = origCall(hRequest, lpBuffer, dwNumberOfBytesToRead, lpdwNumberOfBytesRead);
		std::string StringData((char*)lpBuffer, (char*)lpBuffer + dwNumberOfBytesToRead);
		StringData.insert(0, "WinHttpReadData:");
		StringData += '\n';
		ConsoleWrite(StringData.c_str());
		return retVar;
	}
	return NULL;
}

LPVOID WINAPI  WinHttpCloseHandle(IN LPVOID hInternet) {
	ConsoleWrite("WinHttpCloseHandle \n");
	if (WinhttpModule != NULL) {
		typedef LPVOID(WINAPI* IGCS)(IN LPVOID hInternet);
		IGCS origCall = (IGCS)GetProcAddress(WinhttpModule, "WinHttpCloseHandle");
		return origCall(hInternet);
	}
	return NULL;
}

LPVOID WINAPI WinHttpSetStatusCallback(IN LPVOID hInternet, IN LPVOID lpfnInternetCallback, IN DWORD dwNotificationFlags, IN DWORD_PTR dwReserved) {
	ConsoleWrite("WinHttpSetStatusCallback \n");
	if (WinhttpModule != NULL) {
		typedef LPVOID(WINAPI* IGCS)(IN LPVOID hInternet, IN LPVOID lpfnInternetCallback, IN DWORD dwNotificationFlags, IN DWORD_PTR dwReserved);
		IGCS origCall = (IGCS)GetProcAddress(WinhttpModule, "WinHttpSetStatusCallback");
		return origCall(hInternet, lpfnInternetCallback, dwNotificationFlags, dwReserved);
	}
	return NULL;
}

LPVOID WINAPI WinHttpConnect(IN LPVOID hSession, IN LPCWSTR pswzServerName, IN DWORD nServerPort, IN DWORD dwReserved) {
	if (WinhttpModule != NULL) {
		typedef LPVOID(WINAPI* IGCS)(IN LPVOID hSession, IN LPCWSTR pswzServerName, IN DWORD nServerPort, IN DWORD dwReserved);
		IGCS origCall = (IGCS)GetProcAddress(WinhttpModule, "WinHttpConnect");

		std::wstring ServerName = std::wstring(pswzServerName);
		std::string output = "WinHttpConnect hConnect:" + n2hexstr((long long)hSession) + " pswzServerName:" + std::string(ServerName.begin(), ServerName.end()) + " nServerPort:" + n2hexstr(nServerPort) + "\n";
		ConsoleWrite(output.c_str());
		return origCall(hSession, L"127.0.0.1", 80, dwReserved); //<-------------- Set remote server ip and port
		//return origCall(hSession, pswzServerName, nServerPort, dwReserved);
	}
	return NULL;
}

LPVOID WINAPI WinHttpOpen(LPCWSTR pszAgentW, DWORD   dwAccessType, LPCWSTR pszProxyW, LPCWSTR pszProxyBypassW, DWORD   dwFlags) {
	if (WinhttpModule != NULL) {
		typedef LPVOID(WINAPI* IGCS)(LPCWSTR pszAgentW, DWORD   dwAccessType, LPCWSTR pszProxyW, LPCWSTR pszProxyBypassW, DWORD   dwFlags);
		IGCS origCall = (IGCS)GetProcAddress(WinhttpModule, "WinHttpOpen");
		LPVOID test = origCall(pszAgentW, dwAccessType, pszProxyW, pszProxyBypassW, dwFlags);
		if (test == NULL) {
			ConsoleWrite("WinHttpOpen FAILED \n");
		}

		return test;
	}
	return NULL;
}

LPVOID WINAPI WinHttpSetTimeouts(IN LPVOID hInternet, IN int nResolveTimeout, IN int nConnectTimeout, IN int nSendTimeout, IN int nReceiveTimeout) {
	ConsoleWrite("WinHttpSetTimeouts \n");
	if (WinhttpModule != NULL) {
		typedef LPVOID(WINAPI* IGCS)(IN LPVOID hInternet, IN int       nResolveTimeout, IN int       nConnectTimeout, IN int       nSendTimeout, IN int       nReceiveTimeout);
		IGCS origCall = (IGCS)GetProcAddress(WinhttpModule, "WinHttpSetTimeouts");
		return origCall(hInternet, nResolveTimeout, nConnectTimeout, nSendTimeout, nReceiveTimeout);
	}
	return NULL;
}

LPVOID WINAPI WinHttpWriteData(IN LPVOID hRequest, LPCVOID lpBuffer, IN DWORD dwNumberOfBytesToWrite, OUT LPDWORD  lpdwNumberOfBytesWritten) {
	if (WinhttpModule != NULL) {
		typedef LPVOID(WINAPI* IGCS)(IN LPVOID hRequest, LPCVOID      lpBuffer, IN DWORD     dwNumberOfBytesToWrite, OUT LPDWORD  lpdwNumberOfBytesWritten);
		IGCS origCall = (IGCS)GetProcAddress(WinhttpModule, "WinHttpWriteData");
		std::string StringData((char*)lpBuffer, (char*)lpBuffer + dwNumberOfBytesToWrite);
		StringData.insert(0, "WinHttpWriteData:");
		StringData += '\n';
		ConsoleWrite(StringData.c_str());
		return origCall(hRequest, lpBuffer, dwNumberOfBytesToWrite, lpdwNumberOfBytesWritten);
	}
	return NULL;
}

LPVOID WINAPI WinHttpReceiveResponse(IN LPVOID hRequest, IN LPVOID    lpReserved) {
	ConsoleWrite("WinHttpReceiveResponse \n");
	if (WinhttpModule != NULL) {
		typedef LPVOID(WINAPI* IGCS)(IN LPVOID hRequest, IN LPVOID    lpReserved);
		IGCS origCall = (IGCS)GetProcAddress(WinhttpModule, "WinHttpReceiveResponse");
		return origCall(hRequest, lpReserved);
	}
	return NULL;
}

LPVOID WINAPI  WinHttpGetIEProxyConfigForCurrentUser(IN OUT LPVOID *pProxyConfig) {
	ConsoleWrite("WinHttpGetIEProxyConfigForCurrentUser \n");
	if (WinhttpModule != NULL) {
		typedef LPVOID(WINAPI* IGCS)(IN OUT LPVOID *pProxyConfig);
		IGCS origCall = (IGCS)GetProcAddress(WinhttpModule, "WinHttpGetIEProxyConfigForCurrentUser");
		return origCall(pProxyConfig);
	}
	return NULL;
}

LPVOID WINAPI  WinHttpGetProxyForUrl(IN LPVOID  hSession, IN LPCWSTR lpcwszUrl, IN LPVOID *pAutoProxyOptions, OUT LPVOID *pProxyInfo) {
	ConsoleWrite("WinHttpGetProxyForUrl \n");
	if (WinhttpModule != NULL) {
		typedef LPVOID(WINAPI* IGCS)(IN LPVOID hSession, IN LPCWSTR lpcwszUrl, IN LPVOID *pAutoProxyOptions, OUT LPVOID *pProxyInfo);
		IGCS origCall = (IGCS)GetProcAddress(WinhttpModule, "WinHttpGetProxyForUrl");
		return origCall(hSession, lpcwszUrl, pAutoProxyOptions, pProxyInfo);
	}
	return NULL;
}

LPVOID WINAPI  WinHttpCrackUrl(LPCWSTR pwszUrl, DWORD dwUrlLength, DWORD dwFlags, LPVOID lpUrlComponents) {
	ConsoleWrite("WinHttpCrackUrl \n");
	if (WinhttpModule != NULL) {
		typedef LPVOID(WINAPI* IGCS)(LPCWSTR pwszUrl, DWORD dwUrlLength, DWORD dwFlags, LPVOID lpUrlComponents);
		IGCS origCall = (IGCS)GetProcAddress(WinhttpModule, "WinHttpCrackUrl");
		return origCall(pwszUrl, dwUrlLength, dwFlags, lpUrlComponents);
	}
	return NULL;
}

DWORD WINAPI WinHttpCreateProxyResolver(LPVOID hSession, LPVOID *phResolver) {
	ConsoleWrite("WinHttpCreateProxyResolver \n");
	if (WinhttpModule != NULL) {
		typedef DWORD(WINAPI* IGCS)(LPVOID hSession, LPVOID *phResolver);
		IGCS origCall = (IGCS)GetProcAddress(WinhttpModule, "WinHttpCreateProxyResolver");
		return origCall(hSession, phResolver);
	}
	return NULL;
}

LPVOID WINAPI WinHttpGetProxyForUrlEx(LPVOID  hResolver, PCWSTR pcwszUrl, LPVOID *pAutoProxyOptions, DWORD_PTR  pContext) {
	ConsoleWrite("WinHttpGetProxyForUrlEx \n");
	if (WinhttpModule != NULL) {
		typedef LPVOID(WINAPI* IGCS)(LPVOID hResolver, PCWSTR pcwszUrl, LPVOID *pAutoProxyOptions, DWORD_PTR pContext);
		IGCS origCall = (IGCS)GetProcAddress(WinhttpModule, "WinHttpGetProxyForUrlEx");
		return origCall(hResolver, pcwszUrl, pAutoProxyOptions, pContext);
	}
	return NULL;
}

LPVOID WINAPI WinHttpGetProxyForUrlEx2(_In_ LPVOID hResolver, _In_ PCWSTR pcwszUrl, _In_ LPVOID *pAutoProxyOptions, _In_ DWORD cbInterfaceSelectionContext, _In_reads_bytes_opt_(cbInterfaceSelectionContext) BYTE *pInterfaceSelectionContext, _In_opt_ DWORD_PTR pContext) {
	ConsoleWrite("WinHttpGetProxyForUrlEx2 \n");
	if (WinhttpModule != NULL) {
		typedef LPVOID(WINAPI* IGCS)(_In_ LPVOID hResolver, _In_ PCWSTR pcwszUrl, _In_ LPVOID *pAutoProxyOptions, _In_ DWORD cbInterfaceSelectionContext, _In_reads_bytes_opt_(cbInterfaceSelectionContext) BYTE *pInterfaceSelectionContext, _In_opt_ DWORD_PTR pContext);
		IGCS origCall = (IGCS)GetProcAddress(WinhttpModule, "WinHttpGetProxyForUrlEx2");
		return origCall(hResolver, pcwszUrl, pAutoProxyOptions, cbInterfaceSelectionContext, pInterfaceSelectionContext, pContext);
	}
	return NULL;
}

DWORD WINAPI WinHttpGetProxyResultEx(_In_ LPVOID hResolver, _Out_ LPVOID *pProxyResultEx) {
	ConsoleWrite("WinHttpGetProxyResultEx \n");
	if (WinhttpModule != NULL) {
		typedef DWORD(WINAPI* IGCS)(_In_ LPVOID hResolver, _Out_ LPVOID *pProxyResultEx);
		IGCS origCall = (IGCS)GetProcAddress(WinhttpModule, "WinHttpGetProxyResultEx");
		return origCall(hResolver, pProxyResultEx);
	}
	return NULL;
}

DWORD WINAPI WinHttpFreeProxyResultEx(_Inout_ LPVOID *pProxyResultEx) {
	ConsoleWrite("WinHttpFreeProxyResultEx \n");
	if (WinhttpModule != NULL) {
		typedef DWORD(WINAPI* IGCS)(_Inout_ LPVOID *pProxyResultEx);
		IGCS origCall = (IGCS)GetProcAddress(WinhttpModule, "WinHttpFreeProxyResultEx");
		return origCall(pProxyResultEx);
	}
	return NULL;
}

DWORD WINAPI WinHttpResetAutoProxy(_In_ LPVOID hSession, _In_ DWORD dwFlags) {
	ConsoleWrite("WinHttpResetAutoProxy \n");
	if (WinhttpModule != NULL) {
		typedef DWORD(WINAPI* IGCS)(_In_ LPVOID hSession, _In_ DWORD dwFlags);
		IGCS origCall = (IGCS)GetProcAddress(WinhttpModule, "WinHttpResetAutoProxy");
		return origCall(hSession, dwFlags);
	}
	return NULL;
}
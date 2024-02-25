/**
 *
 * Retro Code
 *
 * MIT License
 *
 * Copyright(c) 2014-2024 Retro Technique
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files(the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and /or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions :
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 */

#include "pch.h"

namespace retro
{
    namespace core
    {

        constexpr const CHAR CB64[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
        constexpr const CHAR CD64[] = "|$$$}rstuvwxyz{$$$$$$$>?@ABCDEFGHIJKLMNOPQRSTUVW$$$$$$XYZ[\\]^_`abcdefghijklmnopq";

        static inline void EncodeBlock(const BYTE pszIn[3], BYTE pszOut[4], size_t uLength)
        {
            pszOut[0] = CB64[pszIn[0] >> 2];
            pszOut[1] = CB64[((pszIn[0] & 0x03) << 4) | ((pszIn[1] & 0xf0) >> 4)];
            pszOut[2] = static_cast<BYTE>(uLength > 1 ? CB64[((pszIn[1] & 0x0f) << 2) | ((pszIn[2] & 0xc0) >> 6)] : '=');
            pszOut[3] = static_cast<BYTE>(uLength > 2 ? CB64[pszIn[2] & 0x3f] : '=');
        }

        static inline void DecodeBlock(const BYTE pszIn[4], BYTE pszOut[3])
        {
            pszOut[0] = static_cast<BYTE>(pszIn[0] << 2 | pszIn[1] >> 4);
            pszOut[1] = static_cast<BYTE>(pszIn[1] << 4 | pszIn[2] >> 2);
            pszOut[2] = static_cast<BYTE>(((pszIn[2] << 6) & 0xc0) | pszIn[3]);
        }

        HRESULT Base64Encode(LPCVOID pBuffer, UINT_PTR uSize, CString& strOut)
        {
            if (!pBuffer)
            {
                return E_INVALIDARG;
            }

            BYTE in[3], out[4];
            const BYTE* pInput = reinterpret_cast<const BYTE*>(pBuffer);
            LPTSTR pszOutput = strOut.GetBufferSetLength(static_cast<INT>(uSize + 3 - uSize % 3) * 4 / 3 + 1);
            UINT uPos = 0;

            UINT_PTR j = 0;
            while (j < uSize)
            {
                INT nLen = 0;

                for (INT i = 0; i < 3; ++i)
                {
                    if (j < uSize)
                    {
                        in[i] = pInput[j++];
                        nLen++;
                    }
                    else
                    {
                        in[i] = 0;
                    }
                }

                if (nLen)
                {
                    EncodeBlock(in, out, nLen);
                    for (INT i = 0; i < 4; i++)
                    {
                        CHAR a = out[i];
                        pszOutput[uPos++] = a;
                    }
                }
            }

            strOut.ReleaseBuffer(uPos);

            return S_OK;
        }

        HRESULT Base64Encode(LPCTSTR pszIn, CString& strOut)
        {
            if (!pszIn)
            {
                return E_INVALIDARG;
            }
          
            UINT_PTR uLength = 0;
            HRESULT hr = StringCchLength(pszIn, STRSAFE_MAX_CCH, &uLength);
            if (FAILED(hr))
            {
                return hr;
            }

            LPCVOID pBuffer = reinterpret_cast<LPCVOID>(pszIn);
            const UINT_PTR uSize = (uLength + 1) * sizeof(TCHAR);

            return Base64Encode(pBuffer, uSize, strOut);
        }

        UINT_PTR Base64QuerySize(LPCTSTR pszIn)
        {
            if (!pszIn)
            {
                return 0;
            }

            UINT_PTR uLength = 0;
            HRESULT hr = StringCchLength(pszIn, STRSAFE_MAX_CCH, &uLength);
            if (FAILED(hr))
            {
                return 0;
            }

            const UINT_PTR uSizeOut = (uLength * 3) / 4 + 1;

            return uSizeOut;
        }

        HRESULT Base64Decode(LPCTSTR pszIn, LPVOID pBuffer, UINT_PTR uSize)
        {
            if (!pszIn)
            {
                return E_INVALIDARG;
            }

            if (!pBuffer) 
            {
                return E_INVALIDARG;
            }

            BYTE in[4], out[3];
            BYTE* pResult = reinterpret_cast<BYTE*>(pBuffer);
            UINT_PTR uPos = 0;

            while (*pszIn)
            {
                INT nLen = 0;
                for (INT i = 0; i < 4 && *pszIn; ++i)
                {
                    INT v = 0;

                    while (*pszIn && v == 0)
                    {
                        v = static_cast<BYTE>(*pszIn);
                        v = static_cast<BYTE>((v < 43 || v > 122) ? 0 : CD64[v - 43]);

                        if (v)
                        {
                            v = static_cast<BYTE>((v == '$') ? 0 : v - 61);
                        }

                        pszIn++;
                    }

                    if (*pszIn || v)
                    {
                        nLen++;

                        if (v)
                        {
                            in[i] = static_cast<BYTE>(v - 1);
                        }
                    }
                    else
                    {
                        in[i] = 0;
                    }
                }

                if (nLen)
                {
                    DecodeBlock(in, out);

                    for (INT i = 0; i < nLen - 1; i++)
                    {
                        if (uPos < uSize)
                        {
                            pResult[uPos] = out[i];
                        }
                        uPos++;
                    }
                }
            }

            return S_OK;
        }

    }
}
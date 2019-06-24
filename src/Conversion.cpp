/**
 * Meet Programming Language Conversion.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at:
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * Copyright (c) 2019 Turaiiao
 * Email: 1171840237@qq.com
 * Github: https://github.com/turaiiao
 */
#include <locale>
#include <codecvt>
#include <string>

#include "Conversion.hpp"

template <class Facet>

struct DeletableFacet : Facet {
    template <class ...Args>

    DeletableFacet(Args& ...args): Facet(std::forward<Args>(args)...) {}

    ~DeletableFacet() {}
};

inline std::string utf16ToGbk(const std::wstring &utf16) {
#ifdef _MSC_VER
    const char* GBK_LOCALE_NAME = ".936";
#else
    const char* GBK_LOCALE_NAME = "zh_CN.GBK";
#endif

    typedef DeletableFacet<std::codecvt_byname<wchar_t, char, std::mbstate_t>> GBFacet;

    std::wstring_convert<GBFacet> conv(new GBFacet(GBK_LOCALE_NAME));

    std::string gbk = conv.to_bytes(utf16);

    return std::move(gbk);
}

inline std::wstring utf8ToUtf16(const std::string &utf8) {
    std::wstring_convert<std::codecvt_utf8<wchar_t>> conv;

    std::wstring utf16 = conv.from_bytes(utf8);

    return std::move(utf16);
}

std::string utf8ToGbk(const std::string &utf8) {
    return utf16ToGbk(utf8ToUtf16(utf8));
}
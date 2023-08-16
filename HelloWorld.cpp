#include "./include/SoSharedLibDefs.h"
#include "HellowWorld.h"
#include <stdlib.h>
#include <stdio.h>
#include <string>

//#define EXPORT __declspec(dllexport)

#if defined (_WINDOWS)
#pragma warning( push )
#pragma warning(disable : 4996) // Security warning about strcpy on win
#define strdup _strdup
#endif


namespace {
    /// この拡張機能固有のエクスポート関数名定義
    char EXTENSION_FUNCTIONS[] = {
        "extGetAlertMessageDefault," /// デフォルトメッセージ取得
        "extGetAlertMessage_u,"      /// 番号に対応するメッセージ取得
    };

    constexpr long HELLO_WORLD_VERSION = 1;
} // namespace

////////////////////////
// 必須のエクスポート関数
extern "C" {
    /// バージョン取得
    EXPORT long ESGetVersion() {
        return HELLO_WORLD_VERSION;
    }

    /// 拡張機能を初期化
    EXPORT char* ESInitialize(TaggedData*, long) {
        return EXTENSION_FUNCTIONS;
    }

    /// 拡張機能を破棄
    EXPORT void ESTerminate() {
    }

    /// メモリアロケート
    EXPORT void* ESMallocMem(size_t size) {
        void* p = malloc(size);
        return p;
    }

    /// メモリ解放
    EXPORT void ESFreeMem(void* p) {
        if (p != nullptr) {
            free(p);
        }
    }

} // 必須のエクスポート関数


////////////////////////
// この拡張機能固有のエクスポート関数
extern "C" {
    /// デフォルトメッセージ取得
    EXPORT long extGetAlertMessageDefault(TaggedData* inputData, long inputDataCount, TaggedData* outputData) {
        const char* message = "hello from ExtendScript.";

        char* str = nullptr;
        {
            const auto length = strlen(message) + 1;
            str = (char*)malloc(length);
            strcpy_s(str, length, message);
        }
        outputData->data.string = str;
        outputData->type = kTypeString;

        return kESErrOK;
    }

    /// 番号に対応するメッセージ取得
    EXPORT long extGetAlertMessage(TaggedData* inputData, long inputDataCount, TaggedData* outputData) {
        const char* messages[] = {
            "Hello CEP.",
            "Hello World.",
            "Hello Native Extension.",
        };

        if (inputDataCount < 1) {
            return kESErrSyntax;
        }

        char* str = nullptr;
        {
            const char* message = messages[inputData[0].data.intval];
            const auto length = strlen(message) + 1;
            str = (char*)malloc(length);
            strcpy_s(str, length, message);

        }
        outputData->data.string = str;
        outputData->type = kTypeString;

        return kESErrOK;
    }
} // この拡張機能固有のエクスポート関数

#if defined (_WINDOWS)
#pragma warning( pop )
#endif


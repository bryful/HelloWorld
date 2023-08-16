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
    /// ���̊g���@�\�ŗL�̃G�N�X�|�[�g�֐�����`
    char EXTENSION_FUNCTIONS[] = {
        "extGetAlertMessageDefault," /// �f�t�H���g���b�Z�[�W�擾
        "extGetAlertMessage_u,"      /// �ԍ��ɑΉ����郁�b�Z�[�W�擾
    };

    constexpr long HELLO_WORLD_VERSION = 1;
} // namespace

////////////////////////
// �K�{�̃G�N�X�|�[�g�֐�
extern "C" {
    /// �o�[�W�����擾
    EXPORT long ESGetVersion() {
        return HELLO_WORLD_VERSION;
    }

    /// �g���@�\��������
    EXPORT char* ESInitialize(TaggedData*, long) {
        return EXTENSION_FUNCTIONS;
    }

    /// �g���@�\��j��
    EXPORT void ESTerminate() {
    }

    /// �������A���P�[�g
    EXPORT void* ESMallocMem(size_t size) {
        void* p = malloc(size);
        return p;
    }

    /// ���������
    EXPORT void ESFreeMem(void* p) {
        if (p != nullptr) {
            free(p);
        }
    }

} // �K�{�̃G�N�X�|�[�g�֐�


////////////////////////
// ���̊g���@�\�ŗL�̃G�N�X�|�[�g�֐�
extern "C" {
    /// �f�t�H���g���b�Z�[�W�擾
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

    /// �ԍ��ɑΉ����郁�b�Z�[�W�擾
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
} // ���̊g���@�\�ŗL�̃G�N�X�|�[�g�֐�

#if defined (_WINDOWS)
#pragma warning( pop )
#endif


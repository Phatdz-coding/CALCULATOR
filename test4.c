#include <windows.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    int a;
    float b;
    char name[64];
} SharedData;

int main(int argc, char* argv[]) {
    system("chcp 65001 >nul");

    HANDLE hMapFile;
    SharedData* data;

    if (argc > 1 && strcmp(argv[1], "child") == 0) {
        // Tiến trình con
        hMapFile = OpenFileMappingW(FILE_MAP_ALL_ACCESS, FALSE, (LPCWSTR) "Global\\MySharedStruct");
        if (!hMapFile) {
            printf("Child: Không thể mở vùng nhớ.\n");
            return 1;
        }

        data = (SharedData*) MapViewOfFile(hMapFile, FILE_MAP_ALL_ACCESS, 0, 0, sizeof(SharedData));
        if (!data) {
            printf("Child: Không thể ánh xạ vùng nhớ.\n");
            return 1;
        }

        // HANDLE hConsole = CreateFileA("CONOUT$", GENERIC_WRITE, FILE_SHARE_WRITE, NULL, OPEN_EXISTING, 0, NULL);
        // if (hConsole != INVALID_HANDLE_VALUE) {
        //     DWORD written;
        //     char msg[128];
        //     snprintf(msg, sizeof(msg), "Child terminal mở được: Đang sửa giá trị...\n");
        //     WriteFile(hConsole, msg, strlen(msg), &written, NULL);
        //     CloseHandle(hConsole);
        // }
        puts("Finished modifying value of the struct\n");

        // Sửa nội dung vùng nhớ
        data->a += 100;
        data->b *= 2;
        strcpy(data->name, "Đã chỉnh sửa từ tiến trình con");

        // Giải phóng
        UnmapViewOfFile(data);
        CloseHandle(hMapFile);
        return 0;
    }

    // Tiến trình cha
    hMapFile = CreateFileMappingW(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, sizeof(SharedData), (LPCWSTR) "Global\\MySharedStruct");
    if (!hMapFile) {
        printf("Parent: Không thể tạo vùng nhớ.\n");
        return 1;
    }

    data = (SharedData*) MapViewOfFile(hMapFile, FILE_MAP_ALL_ACCESS, 0, 0, sizeof(SharedData));
    if (!data) {
        printf("Parent: Không thể ánh xạ vùng nhớ.\n");
        return 1;
    }

    // Khởi tạo dữ liệu
    data->a = 10;
    data->b = 3.14f;
    strcpy(data->name, "Dữ liệu ban đầu từ cha");

    // Tạo tiến trình con
    STARTUPINFOA si = { sizeof(si) };
    PROCESS_INFORMATION pi;
    char cmdLine[256];
    snprintf(cmdLine, sizeof(cmdLine), "cmd /k \"test4.exe child\""); // /c giúp terminal tự đóng

    BOOL success = CreateProcessA(NULL, cmdLine, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi);
    if (!success) {
        printf("Parent: Không thể tạo tiến trình con.\n");
        UnmapViewOfFile(data);
        CloseHandle(hMapFile);
        return 1;
    }

    // Đợi con chạy xong
    WaitForSingleObject(pi.hProcess, INFINITE);

    // In kết quả sau chỉnh sửa
    printf("Parent đọc lại vùng nhớ sau khi con xử lý:\n");
    printf("a = %d\n", data->a);
    printf("b = %.2f\n", data->b);
    printf("name = %s\n", data->name);

    // Giải phóng
    UnmapViewOfFile(data);
    CloseHandle(hMapFile);
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
    return 0;
}

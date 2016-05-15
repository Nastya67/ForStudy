#include <windows.h>
#include <CommCtrl.h>
#include <stdio.h>
#include <stdlib.h>

#define NE_OK 666
#define VSE_OK 777
#define NU_OK 333
#define NAME_CLASS "Window"

enum {
    STATIC_ID = 1,
    BUTTON_ID,
    BTN_DEL_ID,
    EDIT_ID,
    LIST_ID,
};

struct tax{
    char name[20];
    char surname[20];
    int exp;
    double tariif;
    char date[15];
}tax;

LRESULT CALLBACK WndProc2(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam, HINSTANCE * hInst) {
    static HWND hName, hSurname, hDate, hTariff, hExperience;
    static HWND h_name, h_surname, h_date, h_tariff, h_exoerience;
    static HWND hOk, hHead, hClear;
    static char buf_str[20], buf_str2[20];
    static const int shurina = 23, dlina = 100, otstup = 25;
    switch(msg){
        case WM_CREATE:  {
            hHead = CreateWindowEx(0,
                                  WC_STATIC,
                                  "    Taxist",
                                  WS_CHILD | WS_VISIBLE | WS_BORDER,
                                  60, 2, 75, shurina-3,
                                  hwnd, (HMENU)STATIC_ID, hInst, NULL);
            hName = CreateWindowEx(0,
                                  WC_STATIC,
                                  "Name",
                                  WS_CHILD | WS_VISIBLE,
                                  10, otstup, dlina, shurina,
                                  hwnd, (HMENU)STATIC_ID, hInst, NULL);
            hSurname = CreateWindowEx(0,
                                  WC_STATIC,
                                  "Surname",
                                  WS_CHILD | WS_VISIBLE,
                                  10, otstup*2, dlina, shurina,
                                  hwnd, (HMENU)STATIC_ID, hInst, NULL);
            hDate = CreateWindowEx(0,
                                  WC_STATIC,
                                  "Date",
                                  WS_CHILD | WS_VISIBLE,
                                  10, otstup*4, dlina, shurina,
                                  hwnd, (HMENU)STATIC_ID, hInst, NULL);
            hTariff = CreateWindowEx(0,
                                  WC_STATIC,
                                  "Tariff",
                                  WS_CHILD | WS_VISIBLE,
                                  10, otstup*3, dlina, shurina,
                                  hwnd, (HMENU)STATIC_ID, hInst, NULL);
            hExperience = CreateWindowEx(0,
                                  WC_STATIC,
                                  "Experience",
                                  WS_CHILD | WS_VISIBLE,
                                  10, otstup*5, dlina, shurina,
                                  hwnd, (HMENU)STATIC_ID, hInst, NULL);
            h_name = CreateWindowEx(0,
                                  WC_STATIC,
                                  tax.name,
                                  WS_CHILD | WS_VISIBLE,
                                  110, otstup, dlina, shurina-1,
                                  hwnd, (HMENU)STATIC_ID, hInst, NULL);
            h_surname = CreateWindowEx(0,
                                  WC_STATIC,
                                  tax.surname,
                                  WS_CHILD | WS_VISIBLE,
                                  110, otstup*2, dlina, shurina-1,
                                  hwnd, (HMENU)STATIC_ID, hInst, NULL);
            h_date = CreateWindowEx(0,
                                  WC_STATIC,
                                  tax.date,
                                  WS_CHILD | WS_VISIBLE,
                                  110, otstup*4, dlina, shurina-1,
                                  hwnd, (HMENU)STATIC_ID, hInst, NULL);
            sprintf(buf_str, "%i", tax.exp);
            h_exoerience = CreateWindowEx(0,
                                  WC_STATIC,
                                  buf_str,
                                  WS_CHILD | WS_VISIBLE,
                                  110, otstup*5, dlina, shurina-1,
                                  hwnd, (HMENU)STATIC_ID, hInst, NULL);
            sprintf(buf_str2, "%.2f", tax.tariif);
            h_tariff = CreateWindowEx(0,
                                  WC_STATIC,
                                  buf_str2,
                                  WS_CHILD | WS_VISIBLE,
                                  110, otstup*3, dlina, shurina-1,
                                  hwnd, (HMENU)STATIC_ID, hInst, NULL);
            hOk = CreateWindowEx(0,
                                  WC_BUTTON,
                                  "OK",
                                  WS_CHILD | WS_VISIBLE  | WS_TABSTOP | BS_DEFPUSHBUTTON,
                                  5, otstup*7, dlina, shurina,
                                  hwnd, (HMENU)BUTTON_ID, hInst, NULL);
                break;
            }
            case WM_COMMAND:
            case WM_CLOSE:
                DestroyWindow(hwnd);
            break;
            case WM_DESTROY:
                PostQuitMessage(0);
            break;
            default:
                return DefWindowProc(hwnd, msg, wParam, lParam);
        }
    return 0;
}

static int child(HINSTANCE * hInst){
    WNDCLASSEX  wc2;
    //HWND hwnd;
    //MSG Msg;

    wc2.cbSize        = sizeof(WNDCLASSEX);
    wc2.style         = 0;
    wc2.lpfnWndProc   = WndProc2;
    wc2.cbClsExtra    = 0;
    wc2.cbWndExtra    = 0;
    wc2.hInstance     = hInst;
    wc2.hIcon         = LoadIcon(NULL, IDI_APPLICATION);
    wc2.hCursor       = LoadCursor(NULL, IDC_ARROW);
    wc2.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
    wc2.lpszMenuName  = NULL;
    wc2.lpszClassName = "child";
    wc2.hIconSm       = LoadIcon(NULL, IDI_APPLICATION);

    if(!RegisterClassEx(&wc2)){
        MessageBox(NULL, "Window Registration Failed!", "Error!",
            MB_ICONEXCLAMATION | MB_OK);
        return 0 ;
    }
    return 1;
}

int test_str(char str[20]){
    if(str[0] == '\0')
        return NU_OK;
    if(str[0] < 'A' || str[0] > 'Z'){
        MessageBox(NULL, "Respect the taxi driver! Write his name\\surname with a capital letter!", "Error!",
            MB_ICONEXCLAMATION | MB_OK);
        return NE_OK;
    }
    int i;
    for(i = 1; i < 20; i++){
        if(str[i] == '\0')
            break;
        if(str[i] < 'a' || str[i] > 'z'){
            MessageBox(NULL, "An incorrect format name\\surname.", "Error!",
                MB_ICONEXCLAMATION | MB_OK);
            return NE_OK;
        }
    }
    return VSE_OK;
}
int test_int(char str[20]){
    if(str[0] == '\0')
        return NU_OK;
    int i;
    for(i = 0; i < 20; i++){
        if(str[i] == '\0')
            break;
        if(str[i] < '0' || str[i] >'9'){
            MessageBox(NULL, "Not a number", "Error!",
            MB_ICONEXCLAMATION | MB_OK);
            return NE_OK;
        }
    }
    int res = atoi(str);
    if(res > 83){
        MessageBox(NULL, "Too much experience! People do not live so much!", "Error!",
            MB_ICONEXCLAMATION | MB_OK);
        return NE_OK;
    }
    return VSE_OK;
}
int test_double(char str[20]){
    if(str[0] == '\0')
        return NU_OK;
    int i, c = 0;
    for(i = 0; i < 20; i++){
        if(str[i] == '\0')
            break;
        if(str[i] == '.' || str[i] == ','){
            c++;
            continue;
        }
        if(str[i] < '0' || str[i] >'9' || c > 1){
            MessageBox(NULL, "Not a number", "Error!",
            MB_ICONEXCLAMATION | MB_OK);
            return NE_OK;
        }
    }
    return VSE_OK;
}
int test_date(char str[20]){
    if(str[0] == '\0')
        return NU_OK;
    int i, c = 0;

    for(i = 0; i < 20; i++){
        if(str[i] == '\0')
            break;
        if(str[i] == '-'){
            c++;
            continue;
        }
        if(str[i] < '0' || str[i] >'9' || c > 2){
            MessageBox(NULL, "An incorrect date format\n\trecord numbers: day-month-year", "Error!",
            MB_ICONEXCLAMATION | MB_OK);
            return NE_OK;
        }
    }
    if(c != 2 || str[2] != '-' || str[5] != '-'){
        MessageBox(NULL, "An incorrect date format\n\t(day-month-year)", "Error!",
            MB_ICONEXCLAMATION | MB_OK);
        return NE_OK;
    }

    if(str[0] > '3' || (str[0] == '3' && str[1] > '1')){
        MessageBox(NULL, "The wrong day.", "Error!",
            MB_ICONEXCLAMATION | MB_OK);
        return NE_OK;
    }
    if(str[3] > '1' || (str[3] == '1' && str[4] > '2')){
        MessageBox(NULL, "The wrong month.", "Error!",
            MB_ICONEXCLAMATION | MB_OK);
        return NE_OK;
    }
    return VSE_OK;
}


LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam, HINSTANCE * hInst) {
    static HWND hName, hSurname, hDate, hTariff, hExperience;
    static HWND h_name, h_surname, h_date, h_tariff, h_exoerience;
    static HWND hOk, hHead, hClear, hStatic, hChild;
    MSG Msg;
    static char buf_str[20];
    static const int shurina = 23, dlina = 100, otstup = 25;
        switch(msg){
            case WM_CREATE:  {
                hStatic = CreateWindowEx(0,
                                  WC_STATIC,
                                  "",
                                  WS_CHILD | WS_VISIBLE | WS_BORDER,
                                  60, 2, 75, shurina-3,
                                  hwnd, (HMENU)STATIC_ID, hInst, NULL);
                hHead = CreateWindowEx(0,
                                  WC_STATIC,
                                  "    Taxist",
                                  WS_CHILD | WS_VISIBLE | WS_BORDER,
                                  60, 2, 75, shurina-3,
                                  hwnd, (HMENU)STATIC_ID, hInst, NULL);
                hName = CreateWindowEx(0,
                                  WC_STATIC,
                                  "Name",
                                  WS_CHILD | WS_VISIBLE,
                                  10, otstup, dlina, shurina,
                                  hwnd, (HMENU)STATIC_ID, hInst, NULL);
                hSurname = CreateWindowEx(0,
                                  WC_STATIC,
                                  "Surname",
                                  WS_CHILD | WS_VISIBLE,
                                  10, otstup*2, dlina, shurina,
                                  hwnd, (HMENU)STATIC_ID, hInst, NULL);
                hDate = CreateWindowEx(0,
                                  WC_STATIC,
                                  "Date",
                                  WS_CHILD | WS_VISIBLE,
                                  10, otstup*4, dlina, shurina,
                                  hwnd, (HMENU)STATIC_ID, hInst, NULL);
                hTariff = CreateWindowEx(0,
                                  WC_STATIC,
                                  "Tariff",
                                  WS_CHILD | WS_VISIBLE,
                                  10, otstup*3, dlina, shurina,
                                  hwnd, (HMENU)STATIC_ID, hInst, NULL);
                hExperience = CreateWindowEx(0,
                                  WC_STATIC,
                                  "Experience",
                                  WS_CHILD | WS_VISIBLE,
                                  10, otstup*5, dlina, shurina,
                                  hwnd, (HMENU)STATIC_ID, hInst, NULL);
                h_name = CreateWindowEx(0,
                                  WC_EDIT,
                                  "",
                                  WS_CHILD | WS_VISIBLE | WS_BORDER,
                                  110, otstup, dlina, shurina-1,
                                  hwnd, (HMENU)EDIT_ID, hInst, NULL);
                h_surname = CreateWindowEx(0,
                                  WC_EDIT,
                                  "",
                                  WS_CHILD | WS_VISIBLE | WS_BORDER,
                                  110, otstup*2, dlina, shurina-1,
                                  hwnd, (HMENU)EDIT_ID, hInst, NULL);
                h_date = CreateWindowEx(0,
                                  WC_EDIT,
                                  "",
                                  WS_CHILD | WS_VISIBLE | WS_BORDER,
                                  110, otstup*4, dlina, shurina-1,
                                  hwnd, (HMENU)EDIT_ID, hInst, NULL);
                h_exoerience = CreateWindowEx(0,
                                  WC_EDIT,
                                  "",
                                  WS_CHILD | WS_VISIBLE | WS_BORDER,
                                  110, otstup*5, dlina, shurina-1,
                                  hwnd, (HMENU)EDIT_ID, hInst, NULL);
                h_tariff = CreateWindowEx(0,
                                  WC_EDIT,
                                  "",
                                  WS_CHILD | WS_VISIBLE | WS_BORDER,
                                  110, otstup*3, dlina, shurina-1,
                                  hwnd, (HMENU)EDIT_ID, hInst, NULL);
                hOk = CreateWindowEx(0,
                                  WC_BUTTON,
                                  "OK",
                                  WS_CHILD | WS_VISIBLE  | WS_TABSTOP | BS_DEFPUSHBUTTON,
                                  5, otstup*7, dlina, shurina,
                                  hwnd, (HMENU)BUTTON_ID, hInst, NULL);
                hClear = CreateWindowEx(0,
                                  WC_BUTTON,
                                  "Clear all",
                                  WS_CHILD | WS_VISIBLE  | WS_TABSTOP | BS_DEFPUSHBUTTON,
                                  110, otstup*7, dlina, shurina,
                                  hwnd, (HMENU)BTN_DEL_ID, hInst, NULL);
                break;
            }
            case WM_COMMAND: {
                switch (LOWORD(wParam)) {
                    case BUTTON_ID: {
                        static int lll = 0;
                        int res = 0;
                        GetWindowText(h_name, buf_str, sizeof(buf_str));
                        res = test_str(buf_str);
                        if(res == VSE_OK)
                            strcpy(tax.name, buf_str);
                        memset(buf_str, 0, 20);
                        GetWindowText(h_surname, buf_str, sizeof(buf_str));
                        res = test_str(buf_str);
                        if(res == VSE_OK)
                            strcpy(tax.surname, buf_str);
                        memset(buf_str, 0, 20);
                        GetWindowText(h_exoerience, buf_str, sizeof(buf_str));
                        res = test_int(buf_str);
                        if(res == VSE_OK)
                            tax.exp = atoi(buf_str);
                        memset(buf_str, 0, 20);
                        GetWindowText(h_tariff, buf_str, sizeof(buf_str));
                        res = test_double(buf_str);
                        if(res == VSE_OK)
                            tax.tariif = atof(buf_str);
                        memset(buf_str, 0, 20);
                        GetWindowText(h_date, buf_str, sizeof(buf_str));
                        res = test_date(buf_str);
                        if(res == VSE_OK)
                            strcpy(tax.date, buf_str);
                        memset(buf_str, 0, 20);
                        if(lll == 0){
                            child(hInst);
                            lll = 1;
                        }
                        hChild = CreateWindowEx(WS_EX_CLIENTEDGE, "child", "Window2", WS_OVERLAPPEDWINDOW,
                                                CW_USEDEFAULT, CW_USEDEFAULT, 250, 250,
                                                NULL, NULL, hInst, NULL);

                        if(hChild == NULL){
                            MessageBox(NULL, "Window Creation Failed!", "Error!",
                                MB_ICONEXCLAMATION | MB_OK);
                           // return 0;
                        }

                        ShowWindow(hChild, 10);
                        UpdateWindow(hChild);

                        while(GetMessage(&Msg, NULL, 0, 0) > 0){
                            TranslateMessage(&Msg);
                            DispatchMessage(&Msg);
                        }

                    break;
                    }
                    case BTN_DEL_ID: {
                        SetWindowText(h_name, TEXT(""));
                        SetWindowText(h_surname, TEXT(""));
                        SetWindowText(h_date, TEXT(""));
                        SetWindowText(h_exoerience, TEXT(""));
                        SetWindowText(h_tariff, TEXT(""));
                        break;
                    }
                }
                break;
            }
            case WM_CLOSE:
                DestroyWindow(hwnd);
            break;
            case WM_DESTROY:
                PostQuitMessage(0);
            break;
            default:
                return DefWindowProc(hwnd, msg, wParam, lParam);
        }
    return 0;
}


static void parent (HINSTANCE * hInst){
    WNDCLASSEX  wc;
    //HWND hwnd;
    MSG Msg;

    wc.cbSize        = sizeof(WNDCLASSEX);
    wc.style         = 0;
    wc.lpfnWndProc   = WndProc;
    wc.cbClsExtra    = 0;
    wc.cbWndExtra    = 0;
    wc.hInstance     = hInst;
    wc.hIcon         = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW);
    wc.lpszMenuName  = NULL;
    wc.lpszClassName = NAME_CLASS;
    wc.hIconSm       = LoadIcon(NULL, IDI_APPLICATION);

    if(!RegisterClassEx(&wc)){
        MessageBox(NULL, "Window Registration Failed!", "Error!",
            MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow){
    HINSTANCE hInst = hInstance;
    HWND hwnd, hChild;
    MSG Msg;

    parent(hInst);

    hwnd = CreateWindowEx(WS_EX_CLIENTEDGE, NAME_CLASS, "Window", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 250, 250,
        NULL, NULL, hInst, NULL);
    if(hwnd == NULL){
        MessageBox(NULL, "Window Creation Failed!", "Error!",
            MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }
    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);
    //ShowWindow(hChild, nCmdShow);
    //UpdateWindow(hChild);

    while(GetMessage(&Msg, NULL, 0, 0) > 0){
        TranslateMessage(&Msg);
        DispatchMessage(&Msg);
    }
    return Msg.wParam;
    //return 0;
}

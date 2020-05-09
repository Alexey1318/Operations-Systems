#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>

/* оконна€ процедура */
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

/* обработка сообщений */
VOID CALLBACK proc(HWND, UINT, UINT, DWORD);

int WINAPI WinMain(HINSTANCE hInstance, /* указатель handle на текущий экземпл€р приложени€ */
    HINSTANCE hPrevInstance, /* всегда = NULL  */
    LPSTR lpCmdLine, /* параметр командной строки */
    int nCmdShow /* способ отображени€ главного окна - свернутоб развернутоб etc */
)
{
    HWND hwnd;
    HWND hWnd_edit1;
    HWND hWnd_button1;
    HWND hWnd_button2;
    HWND hWnd_label1;
    HWND rButton1;
    HWND rButton2;
    MSG msg;

    /* создание класса окна */
    WNDCLASS w;

    /* заполнение полей класса окна:
    большинство из них будет иметь нулевое значение,
    потому сначала устанавливаем 0 всем пол€м*/
    memset(&w, 0, sizeof(WNDCLASS));

    /* инициализаци€ полей класса окна */
    w.style = CS_HREDRAW | CS_VREDRAW; // стиль окна
    w.lpfnWndProc = WndProc;
    w.hInstance = hInstance; // дескриптор экземпл€ра окна = текущий экземпл€р приложени€
    w.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH); // цвет фона
    w.lpszClassName = "My Class"; // им€ класса окна



    /* регистраци€ класса в системе */
    RegisterClass(&w);

    /* создание окна
    функци€ возвращает handle на созданное окно */
    int e_Height = 25, e_Width = 125;
    int w_Height = 120, w_Width = 275;
    hwnd = CreateWindow("My Class", "Lr5_1", WS_OVERLAPPEDWINDOW,
        300, 200, w_Width, w_Height, NULL, NULL, hInstance, NULL);

    hWnd_label1 = CreateWindow("Edit", "—ообщение:", WS_CHILD | WS_VISIBLE | WS_BORDER | WS_DISABLED,
        5, 5, e_Width, e_Height, hwnd, (HMENU)2, hInstance, NULL);
    hWnd_edit1 = CreateWindow("Edit", "", WS_CHILD | WS_VISIBLE | WS_BORDER,
        e_Width + 5, 5, e_Width, e_Height, hwnd, (HMENU)3, hInstance, NULL);
    hWnd_button1 = CreateWindow("button", "ќчистить", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        5, e_Height + 5, e_Width, e_Height, hwnd, (HMENU)1, hInstance, NULL);
    hWnd_button2 = CreateWindow("button", "ѕередать текст", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        e_Width + 5, e_Height + 5, e_Width, e_Height, hwnd, (HMENU)2, hInstance, NULL);
    rButton1 = CreateWindow("button", "Option 1",
        WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
        5, (e_Height * 2) + 5, e_Width, e_Height, hwnd, (HMENU)10001, hInstance, NULL);
    rButton2 = CreateWindow("button", "Option 2",
        WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
        e_Width + 5, (e_Height * 2) + 5, e_Width, e_Height, hwnd, (HMENU)10002, hInstance, NULL);

    /* отрисовка и обновление созданного окна */
    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    /* цикл обработки сообщений */
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return (int)msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, /* окно, в которое передетс€ сообщение Windows */
    UINT Message, /* полученное сообщение */
    WPARAM wParam, /* дополнительный параметр сообщени€ (некоторыми сообщени€ми не используютс€) */
    LPARAM lParam /* дополнительный параметр сообщени€ (некоторыми сообщени€ми не используютс€) */
)
{
    PAINTSTRUCT ps;
    HDC hdc;
    /* выбор действи€ в зависиомтси от полученного сообщени€ */
    switch (Message)
    {
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    case WM_PAINT:
        break;
    case WM_COPYDATA:
    {
        PCOPYDATASTRUCT s = (PCOPYDATASTRUCT)lParam;
        hdc = BeginPaint(hwnd, &ps);
        SetDlgItemText(hwnd, 3, (LPSTR)s->lpData);
        EndPaint(hwnd, &ps);
        break;
    }
    case WM_COMMAND:
    {
        if (LOWORD(wParam) == 1)
        {
            hdc = BeginPaint(hwnd, &ps);
            SetDlgItemText(hwnd, 3, "");
            EndPaint(hwnd, &ps);
        }
        if (LOWORD(wParam) == 2)
        {
            char* str = new char[50];
            GetDlgItemText(hwnd, 3, str, 25);
            COPYDATASTRUCT cd;
            int length = strlen(str);
            cd.dwData = (ULONG_PTR)&str;
            cd.cbData = length + 1;
            cd.lpData = str;
            HWND hRecieverWnd = FindWindow(NULL, "Lr5_2");
            if (hRecieverWnd != 0) {
                SendMessage(hRecieverWnd, WM_COPYDATA, 0, (LPARAM)&cd);
            }
            else
                MessageBox(NULL, "ќкно приемника не создано", "Message", NULL);
        }

        break;
    }
    /* дефолтна€ ветка нужна дл€ того, чтобы очередь сообщений двигалась */
    default:
        return DefWindowProc(hwnd, Message, wParam, lParam);
    }
    return 0;
}
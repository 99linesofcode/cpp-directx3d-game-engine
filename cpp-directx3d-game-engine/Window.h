#pragma once
#include "BaseException.h"
#include "LinesOfCodeWin.h"

class Window {
public:
    class Exception : public BaseException {
    public:
        Exception(int line, const char* file, HRESULT hr) noexcept;
        const char* what() const noexcept override;
        virtual const char* GetType() const noexcept override;
        static std::string TranslateErrorCode(HRESULT hr) noexcept;
        HRESULT GetErrorCode() const noexcept;
        std::string GetErrorString() const noexcept;
    private:
        HRESULT hr;
    };


    Window(int width, int height, const char* name);
    ~Window();
    Window(const Window&) = delete;
    Window& operator = (const Window&) = delete;

private:
    class WindowClass {
    public:
        static const char* GetName() noexcept;
        static HINSTANCE GetInstance() noexcept;
    private:
        WindowClass() noexcept;
        ~WindowClass();
        WindowClass(const WindowClass&) = delete;
        WindowClass& operator = (const WindowClass&) = delete;
        static constexpr const char* wndClassName = "99linesofcode Direct3D Game Engine Window";
        static WindowClass wndClass;
        HINSTANCE hInst;
    };

    static LRESULT CALLBACK HandleMsgSetup(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;
    static LRESULT CALLBACK HandleMsgThunk(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;
    LRESULT HandleMsg(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;

    int width;
    int height;
    HWND hWnd;
};

#define LOCWND_EXCEPT(hr) Window::Exception(__LINE__, __FILE__, hr)
#define LOCWND_LAST_EXCEPT() Window::Exception(__LINE__, __FILE__, GetLastError());

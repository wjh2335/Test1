#include "pch.h"
#include <microsoft.ui.xaml.window.h>
#include "MainWindow.xaml.h"
#if __has_include("MainWindow.g.cpp")
#include "MainWindow.g.cpp"
#endif

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::Test1::implementation
{
    MainWindow::MainWindow()
    {
        InitializeComponent();

        auto windowNative{ this->try_as<::IWindowNative>() };
        HWND hWnd{ 0 };
        windowNative->get_WindowHandle(&hWnd);
        SetWindowPos(hWnd, NULL, 200, 200, 640, 620, NULL);
        this->Title(L"Andong Nation University");
    }

    int32_t MainWindow::MyProperty()
    {
        throw hresult_not_implemented();
    }

    void MainWindow::MyProperty(int32_t /* value */)
    {
        throw hresult_not_implemented();
    }
}

void winrt::Test1::implementation::MainWindow::CanvasControl_Draw(winrt::Microsoft::Graphics::Canvas::UI::Xaml::CanvasControl const& sender, winrt::Microsoft::Graphics::Canvas::UI::Xaml::CanvasDrawEventArgs const& args)
{
    CanvasControl canvas = sender.as<CanvasControl>();
    int n = vx.size();
    for (int i = 1; i < n; i++)
    {
        if (vx[i] == 0 && vy[i] == 0)
        {
            i++; continue;
        }
        args.DrawingSession().DrawLine(vx[i - 1], vy[i - 1], vx[i], vy[i], col[i], size[i]);
        args.DrawingSession().FillCircle(vx[i - 1], vy[i - 1], size[i] / 2, col[i]);
        args.DrawingSession().FillCircle(vx[i], vy[i], size[i] / 2, col[i]);
    }
    canvas.Invalidate();
}

void winrt::Test1::implementation::MainWindow::CanvasControl_PointerMoved(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::Input::PointerRoutedEventArgs const& e)
{
    CanvasControl canvas = sender.as<CanvasControl>();
    px = e.GetCurrentPoint(canvas).Position().X;
    py = e.GetCurrentPoint(canvas).Position().Y;
    if (flag)
    {
        vx.push_back(px);
        vy.push_back(py);
        size.push_back(mySize);
        col.push_back(myCol);
        canvas.Invalidate();
    }
}

void winrt::Test1::implementation::MainWindow::CanvasControl_PointerPressed(winrt::Windows::Foundation::IInspectable const&, winrt::Microsoft::UI::Xaml::Input::PointerRoutedEventArgs const&)
{
    flag = true;
}

void winrt::Test1::implementation::MainWindow::CanvasControl_PointerReleased(winrt::Windows::Foundation::IInspectable const&, winrt::Microsoft::UI::Xaml::Input::PointerRoutedEventArgs const&)
{
    flag = false;
    px = py = 0;
    vx.push_back(px);
    vy.push_back(py);
    col.push_back(myCol);
    size.push_back(mySize);
}

void winrt::Test1::implementation::MainWindow::ColorPicker_ColorChanged(winrt::Microsoft::UI::Xaml::Controls::ColorPicker const&, winrt::Microsoft::UI::Xaml::Controls::ColorChangedEventArgs const& args)
{
    myCol = args.NewColor();
}


void winrt::Test1::implementation::MainWindow::sldPen_ValueChanged(winrt::Windows::Foundation::IInspectable const&, winrt::Microsoft::UI::Xaml::Controls::Primitives::RangeBaseValueChangedEventArgs const& e)
{
    mySize = e.NewValue();
    txtSize().Text(L"펜 굵기 : " + to_hstring(mySize));
}

void winrt::Test1::implementation::MainWindow::MenuFlyoutItem_Click(winrt::Windows::Foundation::IInspectable const&, winrt::Microsoft::UI::Xaml::RoutedEventArgs const&)
{
    vx.clear();
    vy.clear();
    size.clear();
    col.clear();
}

void winrt::Test1::implementation::MainWindow::MenuFlyoutItem_Click_1(winrt::Windows::Foundation::IInspectable const&, winrt::Microsoft::UI::Xaml::RoutedEventArgs const&)
{
    //저장
    FILE* fp;
    fopen_s(&fp, "C:/Users/woo/Desktop/1.txt", "w");

    if (fp)
    {
        int n = vx.size();
        for (int i = 1; i < n; i++)
        {
            fprintf(fp, "%d %d %d %d %d %d\n", vx[i], vy[i], size[i], col[i].R, col[i].G, col[i].B);
        }
        fclose(fp);
    }
}

void winrt::Test1::implementation::MainWindow::MenuFlyoutItem_Click_2(winrt::Windows::Foundation::IInspectable const&, winrt::Microsoft::UI::Xaml::RoutedEventArgs const&)
{
    //불러오기
    FILE* fp;
    fopen_s(&fp, "C:/Users/woo/Desktop/1.txt", "r");

    if (fp)
    {
        vx.clear(); vy.clear(); size.clear(); col.clear();

        int x, y, s, r, g, b;
        while (EOF != fscanf_s(fp, "%d %d %d %d %d %d\n", &x, &y, &s, &r, &g, &b))
        {
            vx.push_back(x);
            vy.push_back(y);
            size.push_back(s);

            Windows::UI::Color tempCol;
            tempCol.R = r; tempCol.G = g; tempCol.B = b;
            col.push_back(tempCol);
        }
        fclose(fp);
    }
}

void winrt::Test1::implementation::MainWindow::MenuFlyoutItem_Click_3(winrt::Windows::Foundation::IInspectable const&, winrt::Microsoft::UI::Xaml::RoutedEventArgs const&)
{
    //종료
    this->Close();
}

void winrt::Test1::implementation::MainWindow::Button_Click(winrt::Windows::Foundation::IInspectable const&, winrt::Microsoft::UI::Xaml::RoutedEventArgs const&)
{
    ColorPickerPanel().Flyout().Hide();
}
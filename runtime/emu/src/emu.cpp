//-----------------------------------------------------------------------------
// File   : emu.cpp
// Desc   : Game-Boy Emulator.
// Author : Pocol.
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Includes
//-----------------------------------------------------------------------------
#include <emu.h>
#include <renderer.h>


namespace {

//-----------------------------------------------------------------------------
// Constant Values.
//-----------------------------------------------------------------------------
#if PLATFORM_WIN64
static const char* GBEMU_NAME = "GB-Emu";
#endif

} // namespace


///////////////////////////////////////////////////////////////////////////////
// Emulator class
///////////////////////////////////////////////////////////////////////////////

//-----------------------------------------------------------------------------
//      初期化処理です.
//-----------------------------------------------------------------------------
bool Emulator::Init()
{
    if (!m_Memory.Init())
    { return false; }

    m_CPU.SetMemory(&m_Memory);
    m_PPU.SetMemory(&m_Memory);

    m_ROM = nullptr;

    if (!InitWnd(640, 480))
    { return false; }

    return true;
}

//-----------------------------------------------------------------------------
//      終了処理です.
//-----------------------------------------------------------------------------
void Emulator::Term()
{
    TermWnd();

    m_CPU.SetMemory(nullptr);
    m_PPU.SetMemory(nullptr);

    m_Memory.Term();
}


//-----------------------------------------------------------------------------
//      実行処理です.
//-----------------------------------------------------------------------------
void Emulator::Run()
{
    if (Init())
    { MainLoop(); }

    Term();
}

//-----------------------------------------------------------------------------
//      更新処理です.
//-----------------------------------------------------------------------------
void Emulator::Update()
{
    // GameBoy更新処理.
    m_CPU.Execute();
    m_PPU.Execute();
    m_APU.Execute();

    // フレームバッファを描画.
    //RenderPixels(m_PPU.GetFrameBuffer());
}

//-----------------------------------------------------------------------------
//      ROMを設定します.
//-----------------------------------------------------------------------------
void Emulator::SetRom(const Cartridge* rom)
{
    m_ROM = rom;

    // TODO
}

//-----------------------------------------------------------------------------
//      ジョイパッドを設定します.
//-----------------------------------------------------------------------------
void Emulator::SetJoyPad(uint8_t value)
{
    // TODO
}


#if PLATFORM_WIN64
//-----------------------------------------------------------------------------
//      ウィンドウの初期化処理です.
//-----------------------------------------------------------------------------
bool Emulator::InitWnd(uint32_t w, uint32_t h)
{
    // COM初期化.
    auto hr = CoInitialize(nullptr);
    if (FAILED(hr))
    { return false; }

    // インスタンスハンドル取得.
    HINSTANCE hInst = GetModuleHandleA(nullptr);
    if (hInst == nullptr)
    { return false; }

    // ウィンドウクラスを登録.
    WNDCLASSEXA wc = {};
    wc.cbSize           = sizeof(wc);
    wc.style            = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc      = MsgProc;
    wc.cbClsExtra       = 0;
    wc.cbWndExtra       = 0;
    wc.hInstance        = hInst;
    wc.hIcon            = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor          = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground    = (HBRUSH)(COLOR_WINDOW + 1);
    wc.lpszMenuName     = NULL;
    wc.lpszClassName    = GBEMU_NAME;
    wc.hIconSm          = LoadIcon(NULL, IDI_APPLICATION);
    RegisterClassExA(&wc);

    m_hInst = hInst;
    DWORD style = WS_OVERLAPPEDWINDOW;

    // ウィンドウサイズを調整.
    RECT rc = { 0, 0, LONG(w), LONG(h) };
    AdjustWindowRect(&rc, style, FALSE);

    // ウィンドウ生成.
    m_hWnd = CreateWindowA(
        GBEMU_NAME,
        "GB-Emu",
        style,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        (rc.right - rc.left),
        (rc.bottom - rc.top),
        nullptr,
        nullptr,
        hInst,
        this);
    if (m_hWnd == nullptr)
    { return false; }

    // レンダラー初期化.
    if (!InitRenderer(w, h, m_hInst, m_hWnd))
    { return false; }

    // ウィンドウを表示.
    ShowWindow(m_hWnd, SW_SHOWNORMAL);
    UpdateWindow(m_hWnd);

    // 正常終了.
    return true;
}

//-----------------------------------------------------------------------------
//      ウィンドウの終了処理です.
//-----------------------------------------------------------------------------
void Emulator::TermWnd()
{
    TermRenderer();

    if (m_hInst)
    { UnregisterClassA(GBEMU_NAME, m_hInst); }

    m_hInst = nullptr;
    m_hWnd  = nullptr;
}

//-----------------------------------------------------------------------------
//      メインループ処理です.
//-----------------------------------------------------------------------------
void Emulator::MainLoop()
{
    MSG msg = {};

    while(WM_QUIT != msg.message)
    {
        auto hasMsg = PeekMessageA(&msg, nullptr, 0, 0, PM_REMOVE);
        if (hasMsg)
        {
            TranslateMessage(&msg);
            DispatchMessageA(&msg);
        }
        else
        {
            Update();
        }
    }
}

//-----------------------------------------------------------------------------
//      メッセージプロシージャです.
//-----------------------------------------------------------------------------
LRESULT CALLBACK Emulator::MsgProc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp)
{
    auto pEmu = reinterpret_cast<Emulator*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));

    switch(msg)
    {
    case WM_CREATE:
        {
            auto args = reinterpret_cast<LPCREATESTRUCTA>(lp);
            SetWindowLongPtrA(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(args->lpCreateParams));
        }
        return 0;

    case WM_DESTROY:
        {
            PostQuitMessage(0);
        }
        return 0;

    default:
        break;
    }

    return DefWindowProcA(hWnd, msg, wp, lp);
}
#endif

#ifndef GUIInterface__
#define GUIInterface__

#include <Windows.h>
#include <string>
#include <type_traits>
#include "Sun.h"
#include "Enums.h"

namespace KHAS {
    class GUIInterface
    {
    private:
        HWND hwnd_;
        HDC hdc_;
        RECT window_rect_;
        RECT drawing_rect_;
        RECT header_rect_;
        RECT menu_rect_;
        TEXTMETRIC text_metric_;
        COLORREF drawing_section_background_color_;
        COLORREF rest_section_background_color_;
        COLORREF rest_section_text_color_;

        int top_offset_;
        int right_offset_;

        MoveTypes move_type_;

    private:

        void hideCursor()                               const;
        void setWindowPosition()                        const;
        void setBufferWindowSize()                      const;
        void updateStyleWindow()                        const;
        void disableSelectionInConsole()                const;
        void deletePropertiesFromSystemMenu()           const;
        void showHeader(const HDC& hdc)                 const;
        void showMenuMoveTypes(const HDC& hdc)               ;
        void showDraw(const HDC& hdc)                        ;
        void fillRect(const HDC& hdc, const RECT& rect, COLORREF color) const;

        constexpr std::wstring delimiter(size_t lenght, char del = ' ') const;

        constexpr std::wstring joinToString() const { return {}; };

        template <typename FirstElem, typename ... TString, typename = std::enable_if_t<
            std::is_convertible_v<std::decay_t<FirstElem>, std::wstring>
            && (std::is_convertible_v<std::decay_t<TString>, std::wstring> && ...) >>
        constexpr std::wstring joinToString(FirstElem&& first_elem, TString&& ... str) const;

        template <typename Container, typename CheckValue, typename = std::enable_if_t<
            std::is_same_v<std::void_t<decltype(std::declval<Container>().begin())>, void>
            && std::is_same_v<std::void_t<decltype(std::declval<Container>().end())>, void>
            >>
        void drawMenu(Container&& con, const HDC& hdc, CheckValue&& cv);


    public:
        GUIInterface() = delete;
        GUIInterface(long width, long height);

        void loop();
    };
}

#include "GUIInterface.hpp"

#endif
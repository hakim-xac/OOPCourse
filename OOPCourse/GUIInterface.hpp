#include <string>
#include <vector>
#include <algorithm>
#include "GUIInterface.h"
namespace KHAS {


	template<typename FirstElem, typename ...TString, typename T3>
	constexpr std::wstring GUIInterface::joinToString(FirstElem&& first_elem, TString && ...str) const
	{
		std::wstring new_str;
		if constexpr (std::is_same_v<std::decay_t<FirstElem>, std::wstring>) {
			new_str = std::forward<FirstElem>(first_elem);
		}
		else {
			new_str = std::wstring(std::forward<FirstElem>(first_elem));
		}

		if (sizeof...(TString) > 0) {
			return ( new_str + std::wstring(L" ") + joinToString(std::forward<TString>(str)... ) );
		}
		else {
			return new_str;
		}
	}

	template <typename Container, typename CheckValue, typename T3>
	void GUIInterface::drawMenu(Container&& con, const HDC& hdc, CheckValue&& cv) {


		auto base{ std::forward<Container>(con) };
		auto check_value{ std::forward<CheckValue>(cv) };

		int step{ window_rect_.bottom - 185 };
		auto del{ delimiter(78, '=') };
		auto border{ delimiter(78, '=') };


		SetBkMode(hdc, TRANSPARENT);
		SelectObject(hdc, GetStockObject(DC_PEN));
		SetTextColor(hdc, rest_section_text_color_);
		TextOut(hdc, 0, step, del.c_str(), static_cast<int>(del.length()));
		auto text_pos{ window_rect_.right / 2 - 40 };

		for (auto&& elem : base) {
			if (check_value == elem.first) {
				TextOut(hdc, 0, (step += 20), border.c_str(), static_cast<int>(border.length()));
				TextOut(hdc, text_pos, (step += 10), elem.second.c_str(), static_cast<int>(elem.second.length()));
				TextOut(hdc, 0, step += 10, border.c_str(), static_cast<int>(border.length()));
				continue;
			}
			
			TextOut(hdc, text_pos, (step += 20), elem.second.c_str(), static_cast<int>(elem.second.length()));

		}

		TextOut(hdc, 0, step += 20, del.c_str(), static_cast<int>(del.length()));

	}	
}
#pragma once
#include <string>
#include <vector>
#include <htmlTag.hpp>

class HtmlVal;

std::vector<HtmlTag> operator+(std::vector<HtmlTag> left,const HtmlVal& right) noexcept;
std::vector<HtmlTag> operator+(std::vector<HtmlTag> left,HtmlVal&& right) noexcept;
std::vector<HtmlTag>&& operator+(std::vector<HtmlTag>&& left,const HtmlVal& right) noexcept;
std::vector<HtmlTag>&& operator+(std::vector<HtmlTag>&& left,HtmlVal&& right) noexcept;

/**
 * @brief html構造のタグ内のテキストを管理します
 * 
 */
class HtmlVal : public HtmlTag
{
public:
	HtmlVal(const HtmlVal& other) noexcept;
	HtmlVal(HtmlVal&& other) noexcept;
	HtmlVal(const std::string& text) noexcept;
	HtmlVal(std::string&& text) noexcept;
	HtmlVal& operator=(HtmlVal&& other) noexcept;
	HtmlVal operator+(const HtmlVal& right) const noexcept;
	HtmlVal operator+(HtmlVal&& right) const noexcept;
	~HtmlVal() noexcept;
};
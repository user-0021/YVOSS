#pragma once
#include <string>
#include <vector>
#include <htmlTag.hpp>
#include <jsValue.hpp>

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
	HtmlVal(const JsValue& jsValue) noexcept;
	HtmlVal(JsValue&& jsValue) noexcept;
	HtmlVal& operator=(HtmlVal&& other) noexcept;
	std::vector<HtmlTag> operator+(const HtmlVal& right) const noexcept;
	std::vector<HtmlTag> operator+(HtmlVal&& right) const noexcept;
	~HtmlVal() noexcept;
};
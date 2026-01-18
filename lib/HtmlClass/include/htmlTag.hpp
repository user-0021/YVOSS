#pragma once
#include <vector>
#include <string>
#include <memory>
#include <jsValue.hpp>

#define HTML_TAG_FOREACH_BEGIN(...) [&]() -> std::vector<HtmlTag>{std::vector<HtmlTag> ____________dontuse_tags; for(__VA_ARGS__){____________dontuse_tags = ____________dontuse_tags+[&]() -> std::vector<HtmlTag>
#define HTML_TAG_FOREACH_END ();}return ____________dontuse_tags;}()


enum TagType{
	TAG_TYPE_ELEM,
	TAG_TYPE_VALUE
};

std::vector<HtmlTag> operator+(const std::vector<HtmlTag>& left  ,std::vector<HtmlTag>&& right) noexcept;
std::vector<HtmlTag>&& operator+(std::vector<HtmlTag>&& left,std::vector<HtmlTag>&& right) noexcept;

std::vector<HtmlTag> operator+(std::vector<HtmlTag> left,const HtmlTag& right) noexcept;
std::vector<HtmlTag> operator+(std::vector<HtmlTag> left,HtmlTag&& right) noexcept;
std::vector<HtmlTag>&& operator+(std::vector<HtmlTag>&& left,const HtmlTag& right) noexcept;
std::vector<HtmlTag>&& operator+(std::vector<HtmlTag>&& left,HtmlTag&& right) noexcept;

/**
 * @brief html構造のtag情報を管理します
 * 
 */
class HtmlTag
{
protected:
	TagType type;
	std::string tag;
	std::string option;

	std::vector<HtmlTag> children;
	std::unique_ptr<JsValue> jsValues;
public:
	HtmlTag() noexcept:tag(),option(),children(),type(){};
	HtmlTag(const HtmlTag& other) noexcept;
	HtmlTag(HtmlTag&& other) noexcept;
	HtmlTag(const std::string& tag,const std::string& option) noexcept;
	HtmlTag(std::string&& tag,std::string&& option) noexcept;
	HtmlTag(const std::string& tag,const std::string& option,std::vector<HtmlTag> children) noexcept;
	HtmlTag(std::string&& tag,std::string&& option,std::vector<HtmlTag> children) noexcept;
	~HtmlTag() noexcept;

	TagType getTagType() const {return this->type;}
	std::string encord() const;
	
	operator std::vector<HtmlTag>() const{return std::vector<HtmlTag>{*this};}
	HtmlTag& operator=(const HtmlTag& other) noexcept;
	HtmlTag& operator=(HtmlTag&& other) noexcept;
	std::vector<HtmlTag> operator+(HtmlTag& right) const noexcept;
	std::vector<HtmlTag> operator+(HtmlTag&& right) const noexcept;
};
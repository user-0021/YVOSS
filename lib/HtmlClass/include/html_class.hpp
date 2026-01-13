#pragma once
#include <vector>
#include <string>

#define HTML_TAG_FOREACH_BEGIN(...) [&]() -> std::vector<htmlTag>{std::vector<htmlTag> ____________dontuse_tags; for(__VA_ARGS__){____________dontuse_tags = ____________dontuse_tags+[&]() -> std::vector<htmlTag>
#define HTML_TAG_FOREACH_END ();}return ____________dontuse_tags;}()


enum TagType{
	TAG_TYPE_ELEM,
	TAG_TYPE_VALUE
};

/**
 * @brief html構造のtag情報を管理します
 * 
 */
class htmlTag
{
protected:
	TagType type;
	std::string tag;
	std::string option;

	std::vector<htmlTag> children;
public:
	htmlTag() noexcept:tag(),option(),children(),type(){};
	htmlTag(const htmlTag& other) noexcept;
	htmlTag(htmlTag&& other) noexcept;
	htmlTag(const std::string& tag,const std::string& option) noexcept;
	htmlTag(std::string&& tag,std::string&& option) noexcept;
	htmlTag(const std::string& tag,const std::string& option,std::vector<htmlTag> children) noexcept;
	htmlTag(std::string&& tag,std::string&& option,std::vector<htmlTag> children) noexcept;
	~htmlTag() noexcept;

	TagType getTagType() const {return this->type;}
	std::string encord() const;
	
	operator std::vector<htmlTag>() const{return std::vector<htmlTag>{*this};}
	htmlTag& operator=(const htmlTag& other) noexcept;
	htmlTag& operator=(htmlTag&& other) noexcept;
	std::vector<htmlTag> operator+(htmlTag& right) noexcept;
	std::vector<htmlTag> operator+(htmlTag&& right) noexcept;
};

/**
 * @brief html構造のタグ内のテキストを管理します
 * 
 */
class htmlVal : public htmlTag
{
public:
	htmlVal(const htmlVal& other) noexcept;
	htmlVal(htmlVal&& other) noexcept;
	htmlVal(const std::string& text) noexcept;
	htmlVal(std::string&& text) noexcept;
	htmlVal& operator=(htmlVal&& other) noexcept;
	std::vector<htmlTag> operator+(const htmlVal& right) const noexcept;
	std::vector<htmlTag> operator+(htmlVal&& right) const noexcept;
	~htmlVal() noexcept;
};


class htmlPage
{
private:
	htmlTag head;
	htmlTag body;	
public:
	//htmlPage() noexcept:head(),body(){};
	std::string encord() const {return head.encord() + body.encord();}
	void setHead(const htmlTag&  head) noexcept{this->head = head;}
	void setHead(const htmlTag&& head) noexcept{this->head = std::move(head);}
	void setBody(const htmlTag&  body) noexcept{this->body = body;}
	void setBody(const htmlTag&& body) noexcept{this->body = std::move(body);}
};

std::vector<htmlTag> operator+(const std::vector<htmlTag>& left  ,std::vector<htmlTag>&& right) noexcept;
std::vector<htmlTag>&& operator+(std::vector<htmlTag>&& left,std::vector<htmlTag>&& right) noexcept;

std::vector<htmlTag> operator+(std::vector<htmlTag> left,const htmlTag& right) noexcept;
std::vector<htmlTag> operator+(std::vector<htmlTag> left,htmlTag&& right) noexcept;
std::vector<htmlTag>&& operator+(std::vector<htmlTag>&& left,const htmlTag& right) noexcept;
std::vector<htmlTag>&& operator+(std::vector<htmlTag>&& left,htmlTag&& right) noexcept;

std::vector<htmlTag> operator+(std::vector<htmlTag> left,const htmlVal& right) noexcept;
std::vector<htmlTag> operator+(std::vector<htmlTag> left,htmlVal&& right) noexcept;
std::vector<htmlTag>&& operator+(std::vector<htmlTag>&& left,const htmlVal& right) noexcept;
std::vector<htmlTag>&& operator+(std::vector<htmlTag>&& left,htmlVal&& right) noexcept;


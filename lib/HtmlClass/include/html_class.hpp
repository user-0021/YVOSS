#pragma once
#include <vector>
#include <string>
#include <memory>
#include <stdint.h>

#define HTML_TAG_FOREACH_BEGIN(...) [&]() -> std::vector<HtmlTag>{std::vector<HtmlTag> ____________dontuse_tags; for(__VA_ARGS__){____________dontuse_tags = ____________dontuse_tags+[&]() -> std::vector<HtmlTag>
#define HTML_TAG_FOREACH_END ();}return ____________dontuse_tags;}()


enum TagType{
	TAG_TYPE_ELEM,
	TAG_TYPE_VALUE
};


class HtmlTag;
class HtmlVal;
class HtmlPage;
class JsValue;


std::vector<HtmlTag> operator+(const std::vector<HtmlTag>& left  ,std::vector<HtmlTag>&& right) noexcept;
std::vector<HtmlTag>&& operator+(std::vector<HtmlTag>&& left,std::vector<HtmlTag>&& right) noexcept;

std::vector<HtmlTag> operator+(std::vector<HtmlTag> left,const HtmlTag& right) noexcept;
std::vector<HtmlTag> operator+(std::vector<HtmlTag> left,HtmlTag&& right) noexcept;
std::vector<HtmlTag>&& operator+(std::vector<HtmlTag>&& left,const HtmlTag& right) noexcept;
std::vector<HtmlTag>&& operator+(std::vector<HtmlTag>&& left,HtmlTag&& right) noexcept;

std::vector<HtmlTag> operator+(std::vector<HtmlTag> left,const HtmlVal& right) noexcept;
std::vector<HtmlTag> operator+(std::vector<HtmlTag> left,HtmlVal&& right) noexcept;
std::vector<HtmlTag>&& operator+(std::vector<HtmlTag>&& left,const HtmlVal& right) noexcept;
std::vector<HtmlTag>&& operator+(std::vector<HtmlTag>&& left,HtmlVal&& right) noexcept;


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
	std::vector<HtmlTag> operator+(HtmlTag& right) noexcept;
	std::vector<HtmlTag> operator+(HtmlTag&& right) noexcept;
};

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
	std::vector<HtmlTag> operator+(const HtmlVal& right) const noexcept;
	std::vector<HtmlTag> operator+(HtmlVal&& right) const noexcept;
	~HtmlVal() noexcept;
};


class HtmlPage
{
private:
	HtmlTag head;
	HtmlTag body;	
public:
	std::string encord() const {return head.encord() + body.encord();}
	void setHead(const HtmlTag&  head) noexcept{this->head = head;}
	void setHead(const HtmlTag&& head) noexcept{this->head = std::move(head);}
	void setBody(const HtmlTag&  body) noexcept{this->body = body;}
	void setBody(const HtmlTag&& body) noexcept{this->body = std::move(body);}
};

enum JsValueType{
	JS_INT    = 0,
	JS_DOUBLE = 1,
	JS_NUM_MAX = 2,
	JS_STRING = 3
};

enum NodeType{
	NODE_VALUE,
	NODE_EQ,
	NODE_ADD,
	NODE_SUB,
	NODE_MUL,
	NODE_DIV,
};

struct ExprNode
{
	uint16_t refCount;
	const void* left;
	const void* right;
	NodeType type;
};


class JsValue{
protected:
	//state	
	bool isStatic;
	JsValueType valueType; 
	
	//for static value
	void* staticValue;

	//dor dynamic
	ExprNode* node; 

	void* copyStaticResource() const noexcept; 
	void releaseResource() noexcept;

public:
	JsValue(const JsValue& other);
	JsValue(JsValue&& other);
	JsValue(const JsValue& left,const JsValue& right,const NodeType& nodeType);
	//JsValue(const JsValue& left,JsValue&&      right,const NodeType& nodeType);
	//JsValue(JsValue&&      left,const JsValue& right,const NodeType& nodeType);
	//JsValue(JsValue&&      left,JsValue&&      right,const NodeType& nodeType);
	JsValue(const std::string& s);
	JsValue(const int& i);
	JsValue(const double& d);

	~JsValue();

	JsValue& operator=(const JsValue& right) noexcept;
	JsValue& operator=(JsValue&& right) noexcept;
	JsValue operator+(const JsValue& right) const;
	JsValue operator-(const JsValue& right) const;
	JsValue operator*(const JsValue& right) const;
	JsValue operator/(const JsValue& right) const;
};


#pragma once
#include <vector>
#include <string>


/**
 * @brief html構造のtag情報を管理します
 * 
 */
class htmlTag
{
protected:
	std::string tag;
	std::string option;

	std::vector<htmlTag> children;
public:
	htmlTag() noexcept:tag(),option(),children(){};
	htmlTag(const htmlTag& other) noexcept;
	htmlTag(htmlTag&& other) noexcept;
	htmlTag(const std::string& tag,const std::string& option) noexcept;
	htmlTag(std::string&& tag,std::string&& option) noexcept;
	htmlTag(const std::string& tag,const std::string& option,std::vector<htmlTag> children) noexcept;
	htmlTag(std::string&& tag,std::string&& option,std::vector<htmlTag> children) noexcept;
	~htmlTag() noexcept;

	bool isNotTag() const {return tag.empty();}
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
	std::vector<htmlTag> operator+(htmlVal& right) noexcept;
	std::vector<htmlTag> operator+(htmlVal&& right) noexcept;
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

std::vector<htmlTag> operator+(std::vector<htmlTag> left,const htmlTag& right) noexcept;
std::vector<htmlTag> operator+(std::vector<htmlTag> left,htmlTag&& right) noexcept;
std::vector<htmlTag> operator+(std::vector<htmlTag>&& left,const htmlTag& right) noexcept;
std::vector<htmlTag> operator+(std::vector<htmlTag>&& left,htmlTag&& right) noexcept;

std::vector<htmlTag> operator+(std::vector<htmlTag> left,const htmlVal& right) noexcept;
std::vector<htmlTag> operator+(std::vector<htmlTag> left,htmlVal&& right) noexcept;
std::vector<htmlTag> operator+(std::vector<htmlTag>&& left,const htmlVal& right) noexcept;
std::vector<htmlTag> operator+(std::vector<htmlTag>&& left,htmlVal&& right) noexcept;


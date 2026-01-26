#include <htmlVal.hpp>

//opeator
std::vector<HtmlTag> operator+(std::vector<HtmlTag> left,const HtmlVal& right) noexcept{
	if(left.empty() || left[0].getTagType() == TagType::TAG_TYPE_VALUE)
		left.push_back(right);
	return std::move(left);
}
std::vector<HtmlTag> operator+(std::vector<HtmlTag> left,HtmlVal&& right) noexcept{
	if(left.empty() || left[0].getTagType() == TagType::TAG_TYPE_VALUE)
		left.push_back(std::move(right));
	return std::move(left);
}
std::vector<HtmlTag>&& operator+(std::vector<HtmlTag>&& left,const HtmlVal& right) noexcept{
	if(left.empty() || left[0].getTagType() == TagType::TAG_TYPE_VALUE)
		left.push_back(right);
	return std::move(left);
}
std::vector<HtmlTag>&& operator+(std::vector<HtmlTag>&& left,HtmlVal&& right) noexcept{
	if(left.empty() || left[0].getTagType() == TagType::TAG_TYPE_VALUE)
		left.push_back(std::move(right));
	return std::move(left);
}








/**********************************
 * 		HTML VALUE CLASS
 * ********************************
 */

 
//コピー初期化
HtmlVal::HtmlVal(const HtmlVal& other) noexcept:
	HtmlTag::HtmlTag(other){};

//ムーブ初期化
HtmlVal::HtmlVal(HtmlVal&& other) noexcept:
	HtmlTag::HtmlTag(std::move(other)){};

//通常初期化
HtmlVal::HtmlVal(const std::string& text) noexcept{
	this->tag      = "";
	this->type     = TagType::TAG_TYPE_VALUE;
	this->option   = text;
	this->children = std::vector<HtmlTag>();
}

//通常初期化
HtmlVal::HtmlVal(std::string&& text) noexcept{
	this->tag      = "";
	this->type     = TagType::TAG_TYPE_VALUE;
	this->option   = std::move(text);
	this->children = std::vector<HtmlTag>();
}


HtmlVal::~HtmlVal() noexcept{

}

//ムーブ演算
HtmlVal& HtmlVal::operator=(HtmlVal&& other) noexcept{
	if(this != &other){

		this->tag      = std::move(other.tag);
		this->type     = std::move(other.type);
		this->option   = std::move(other.option);
		this->children = std::move(other.children);
	}
	return *this;
};

//リストの連結
HtmlVal HtmlVal::operator+(const HtmlVal& right) const noexcept{		
	return this->option + right.option;
}

//リストの連結
HtmlVal HtmlVal::operator+(HtmlVal&& right) const noexcept{
	return this->option + right.option;
}
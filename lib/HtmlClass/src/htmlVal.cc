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
	this->jsValues = std::unique_ptr<JsValue>(nullptr);
}

//通常初期化
HtmlVal::HtmlVal(std::string&& text) noexcept{
	this->tag      = "";
	this->type     = TagType::TAG_TYPE_VALUE;
	this->option   = std::move(text);
	this->children = std::vector<HtmlTag>();
	this->jsValues = std::unique_ptr<JsValue>(nullptr);
}

HtmlVal::HtmlVal(const JsValue& jsValue) noexcept{
	this->tag      = "";
	this->type     = TagType::TAG_TYPE_VALUE;
	this->option   = "";
	this->children = std::vector<HtmlTag>();
	this->jsValues = std::unique_ptr<JsValue>(new JsValue(jsValue));
}

HtmlVal::HtmlVal(JsValue&& jsValue) noexcept{
	this->tag      = "";
	this->type     = TagType::TAG_TYPE_VALUE;
	this->option   = "";
	this->children = std::vector<HtmlTag>();
	this->jsValues = std::unique_ptr<JsValue>(new JsValue(std::move(jsValue)));
}

HtmlVal::~HtmlVal() noexcept{

}

//ムーブ演算
HtmlVal& HtmlVal::operator=(HtmlVal&& other) noexcept{
	if(this != &other){
		if(this->jsValues)
			this->jsValues.release();

		this->tag      = std::move(other.tag);
		this->type     = std::move(other.type);
		this->option   = std::move(other.option);
		this->children = std::move(other.children);
		this->jsValues = std::move(other.jsValues);
	}
	return *this;
};

//リストの連結
std::vector<HtmlTag> HtmlVal::operator+(const HtmlVal& right) const noexcept{
	std::vector<HtmlTag> res;
	
	if(this->getTagType() == TagType::TAG_TYPE_VALUE)
		res.push_back(*this);
	if(right.getTagType() == TagType::TAG_TYPE_VALUE)
		res.push_back(right);
		
	return res;
}

//リストの連結
std::vector<HtmlTag> HtmlVal::operator+(HtmlVal&& right) const noexcept{
	std::vector<HtmlTag> res;
	
	if(this->getTagType() == TagType::TAG_TYPE_VALUE)
		res.push_back(*this);
	if(right.getTagType() == TagType::TAG_TYPE_VALUE)
		res.push_back(std::move(right));
		
	return res;
}
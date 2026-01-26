#include <htmlTag.hpp>

//operator
std::vector<HtmlTag> operator+(const std::vector<HtmlTag>& left  ,std::vector<HtmlTag>&& right) noexcept{
	auto copyed_left = left;
	if((left.empty() || right.empty()) || (left[0].getTagType() == right[0].getTagType()))
		copyed_left.insert(copyed_left.end(), std::make_move_iterator(right.begin()), std::make_move_iterator(right.end()));
	return std::move(copyed_left);
}
std::vector<HtmlTag>&& operator+(std::vector<HtmlTag>&& left,std::vector<HtmlTag>&& right) noexcept{
	if((left.empty() || right.empty()) || (left[0].getTagType() == right[0].getTagType()))
		left.insert(left.end(), std::make_move_iterator(right.begin()), std::make_move_iterator(right.end()));
	return std::move(left);
}



std::vector<HtmlTag> operator+(std::vector<HtmlTag> left,const HtmlTag& right) noexcept{
	if(left.empty() || left[0].getTagType() == TagType::TAG_TYPE_ELEM)
		left.push_back(right);
	return std::move(left);
}
std::vector<HtmlTag> operator+(std::vector<HtmlTag> left,HtmlTag&& right) noexcept{
	if(left.empty() || left[0].getTagType() == TagType::TAG_TYPE_ELEM)
		left.push_back(std::move(right));
	return std::move(left);
}
std::vector<HtmlTag>&& operator+(std::vector<HtmlTag>&& left,const HtmlTag& right) noexcept{
	if(left.empty() || left[0].getTagType() == TagType::TAG_TYPE_ELEM)
		left.push_back(right);
	return std::move(left);
}
std::vector<HtmlTag>&& operator+(std::vector<HtmlTag>&& left,HtmlTag&& right) noexcept{
	if(left.empty() || left[0].getTagType() == TagType::TAG_TYPE_ELEM)
		left.push_back(std::move(right));
	return std::move(left);
}






/**********************************
 * 		HTML TAG CLASS
 * ********************************
 */

//コピー初期化
HtmlTag::HtmlTag(const HtmlTag& other) noexcept
	:tag(other.tag),
	option(other.option),
	children(other.children),
	type(other.type){
	};

//ムーブ初期化
HtmlTag::HtmlTag(HtmlTag&& other) noexcept
	:tag(std::move(other.tag)),
	option(std::move(other.option)),
	children(std::move(other.children)),
	type(std::move(other.type)){};

//子なし初期化
HtmlTag::HtmlTag(const std::string& tag,const std::string& option) noexcept
	:option(option),children(),type(TagType::TAG_TYPE_ELEM){
		this->tag = tag.substr(0,tag.find(' '));
		//insert space for split tag and option
		if(!this->option.empty() && this->option[0] != ' ')
			this->option.insert(this->option.begin(),' ');
}

//子なし初期化
HtmlTag::HtmlTag(std::string&& tag,std::string&& option) noexcept
:option(option),children(),type(TagType::TAG_TYPE_ELEM){
		this->tag = tag.substr(0,tag.find(' '));
		//insert space for split tag and option
		if(!this->option.empty() && this->option[0] != ' ')
			this->option.insert(this->option.begin(),' ');
}

//通常初期化
HtmlTag::HtmlTag(const std::string& tag,const std::string& option,std::vector<HtmlTag> children) noexcept
	:option(option),children(children),type(TagType::TAG_TYPE_ELEM){
		this->tag = tag.substr(0,tag.find(' '));
		//insert space for split tag and option
		if(!this->option.empty() && this->option[0] != ' ')
			this->option.insert(this->option.begin(),' ');
}

//通常初期化
HtmlTag::HtmlTag(std::string&& tag,std::string&& option,std::vector<HtmlTag> children) noexcept
	:option(option),children(children),type(TagType::TAG_TYPE_ELEM){
		this->tag = tag.substr(0,tag.find(' '));
		//insert space for split tag and option
		if(!this->option.empty() && this->option[0] != ' ')
			this->option.insert(this->option.begin(),' ');
}

HtmlTag::~HtmlTag() noexcept{

}

//encord
std::string HtmlTag::encord() const{
	std::string ret("");
	if(this->getTagType() == TagType::TAG_TYPE_VALUE){
		ret += this->option;
	}else{
		if(this->tag.empty()){
			for(const auto& element : this->children){
				ret += element.encord();
			}
		}else{
			ret += "<" + this->tag + this->option + ">";
			for(const auto& element : this->children){
				ret += element.encord();
			}
			ret += "</" + this->tag + ">";
		}
	}
	return ret;
}

//代入演算
HtmlTag& HtmlTag::operator=(const HtmlTag& other) noexcept{
	if(this != &other){
		this->tag      = other.tag;
		this->type     = other.type;
		this->option   = other.option;
		this->children = other.children;

	}
	return *this;
}

//ムーブ演算
HtmlTag& HtmlTag::operator=(HtmlTag&& other) noexcept{
	if(this != &other){

		this->tag      = std::move(other.tag);
		this->type     = std::move(other.type);
		this->option   = std::move(other.option);
		this->children = std::move(other.children);
	}
	return *this;
}

//リストの連結
std::vector<HtmlTag> HtmlTag::operator+(HtmlTag& right) const noexcept{
	std::vector<HtmlTag> res;
	
	if(this->getTagType() == TagType::TAG_TYPE_ELEM)
		res.push_back(*this);
	if(right.getTagType() == TagType::TAG_TYPE_ELEM)
		res.push_back(right);
		
	return res;
}

//リストの連結
std::vector<HtmlTag> HtmlTag::operator+(HtmlTag&& right) const noexcept{
	std::vector<HtmlTag> res;
	
	if(this->getTagType() == TagType::TAG_TYPE_ELEM)
		res.push_back(*this);
	if(right.getTagType() == TagType::TAG_TYPE_ELEM)
		res.push_back(std::move(right));
		
	return res;
}
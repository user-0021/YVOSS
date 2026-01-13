#include <html_class.hpp>



//operator
std::vector<htmlTag> operator+(const std::vector<htmlTag>& left  ,std::vector<htmlTag>&& right) noexcept{
	auto copyed_left = left;
	if((left.empty() || right.empty()) || (left[0].getTagType() == right[0].getTagType()))
		copyed_left.insert(copyed_left.end(), std::make_move_iterator(right.begin()), std::make_move_iterator(right.end()));
	return std::move(copyed_left);
}
std::vector<htmlTag>&& operator+(std::vector<htmlTag>&& left,std::vector<htmlTag>&& right) noexcept{
	if((left.empty() || right.empty()) || (left[0].getTagType() == right[0].getTagType()))
		left.insert(left.end(), std::make_move_iterator(right.begin()), std::make_move_iterator(right.end()));
	return std::move(left);
}



std::vector<htmlTag> operator+(std::vector<htmlTag> left,const htmlTag& right) noexcept{
	if(left.empty() || left[0].getTagType() == TagType::TAG_TYPE_ELEM)
		left.push_back(right);
	return std::move(left);
}
std::vector<htmlTag> operator+(std::vector<htmlTag> left,htmlTag&& right) noexcept{
	if(left.empty() || left[0].getTagType() == TagType::TAG_TYPE_ELEM)
		left.push_back(std::move(right));
	return std::move(left);
}
std::vector<htmlTag>&& operator+(std::vector<htmlTag>&& left,const htmlTag& right) noexcept{
	if(left.empty() || left[0].getTagType() == TagType::TAG_TYPE_ELEM)
		left.push_back(right);
	return std::move(left);
}
std::vector<htmlTag>&& operator+(std::vector<htmlTag>&& left,htmlTag&& right) noexcept{
	if(left.empty() || left[0].getTagType() == TagType::TAG_TYPE_ELEM)
		left.push_back(std::move(right));
	return std::move(left);
}




std::vector<htmlTag> operator+(std::vector<htmlTag> left,const htmlVal& right) noexcept{
	if(left.empty() || left[0].getTagType() == TagType::TAG_TYPE_VALUE)
		left.push_back(right);
	return std::move(left);
}
std::vector<htmlTag> operator+(std::vector<htmlTag> left,htmlVal&& right) noexcept{
	if(left.empty() || left[0].getTagType() == TagType::TAG_TYPE_VALUE)
		left.push_back(std::move(right));
	return std::move(left);
}
std::vector<htmlTag>&& operator+(std::vector<htmlTag>&& left,const htmlVal& right) noexcept{
	if(left.empty() || left[0].getTagType() == TagType::TAG_TYPE_VALUE)
		left.push_back(right);
	return std::move(left);
}
std::vector<htmlTag>&& operator+(std::vector<htmlTag>&& left,htmlVal&& right) noexcept{
	if(left.empty() || left[0].getTagType() == TagType::TAG_TYPE_VALUE)
		left.push_back(std::move(right));
	return std::move(left);
}






/**********************************
 * 		HTML TAG CLASS
 * ********************************
 */

//コピー初期化
htmlTag::htmlTag(const htmlTag& other) noexcept
	:tag(other.tag),
	option(other.option),
	children(other.children),
	type(other.type){};

//ムーブ初期化
htmlTag::htmlTag(htmlTag&& other) noexcept
	:tag(std::move(other.tag)),
	option(std::move(other.option)),
	children(std::move(other.children)),
	type(other.type){};

//子なし初期化
htmlTag::htmlTag(const std::string& tag,const std::string& option) noexcept
	:option(option),children(),type(TagType::TAG_TYPE_ELEM){
	this->tag = tag.substr(0,tag.find(' '));
	//insert space for split tag and option
	if(!this->option.empty() && this->option[0] != ' ')
		this->option.insert(this->option.begin(),' ');
}

//子なし初期化
htmlTag::htmlTag(std::string&& tag,std::string&& option) noexcept
:option(option),children(),type(TagType::TAG_TYPE_ELEM){
	this->tag = tag.substr(0,tag.find(' '));
	//insert space for split tag and option
	if(!this->option.empty() && this->option[0] != ' ')
		this->option.insert(this->option.begin(),' ');
}

//通常初期化
htmlTag::htmlTag(const std::string& tag,const std::string& option,std::vector<htmlTag> children) noexcept
	:option(option),children(children),type(TagType::TAG_TYPE_ELEM){
	this->tag = tag.substr(0,tag.find(' '));
	//insert space for split tag and option
	if(!this->option.empty() && this->option[0] != ' ')
		this->option.insert(this->option.begin(),' ');
}

//通常初期化
htmlTag::htmlTag(std::string&& tag,std::string&& option,std::vector<htmlTag> children) noexcept
	:option(option),children(children),type(TagType::TAG_TYPE_ELEM){
	this->tag = tag.substr(0,tag.find(' '));
	//insert space for split tag and option
	if(!this->option.empty() && this->option[0] != ' ')
		this->option.insert(this->option.begin(),' ');
}

htmlTag::~htmlTag() noexcept{

}

//encord
std::string htmlTag::encord() const{
	std::string ret("");
	if(this->getTagType() == TagType::TAG_TYPE_VALUE){
		ret += this->option;
	}else{
		ret += "<" + this->tag + this->option + ">";
		for(const auto& element : this->children){
			ret += element.encord();
		}
		ret += "</" + this->tag + ">";
	}
	return ret;
}

//代入演算
htmlTag& htmlTag::operator=(const htmlTag& other) noexcept{
	this->tag = other.tag;
	this->type = other.type;
	this->option = other.option;
	this->children = other.children;
	return *this;
}

//ムーブ演算
htmlTag& htmlTag::operator=(htmlTag&& other) noexcept{
	if(this != &other){
		this->tag      = std::move(other.tag);
		this->type     = std::move(other.type);
		this->option   = std::move(other.option);
		this->children = std::move(other.children);
	}
	return *this;
}

//リストの連結
std::vector<htmlTag> htmlTag::operator+(htmlTag& right) noexcept{
	std::vector<htmlTag> res;
	
	if(this->getTagType() == TagType::TAG_TYPE_ELEM)
		res.push_back(*this);
	if(right.getTagType() == TagType::TAG_TYPE_ELEM)
		res.push_back(right);
		
	return res;
}

//リストの連結
std::vector<htmlTag> htmlTag::operator+(htmlTag&& right) noexcept{
	std::vector<htmlTag> res;
	
	if(this->getTagType() == TagType::TAG_TYPE_ELEM)
		res.push_back(*this);
	if(right.getTagType() == TagType::TAG_TYPE_ELEM)
		res.push_back(std::move(right));
		
	return res;
}



/**********************************
 * 		HTML VALUE CLASS
 * ********************************
 */

 
//コピー初期化
htmlVal::htmlVal(const htmlVal& other) noexcept:
	htmlTag::htmlTag(other){};

//ムーブ初期化
htmlVal::htmlVal(htmlVal&& other) noexcept:
	htmlTag::htmlTag(std::move(other)){};

//通常初期化
htmlVal::htmlVal(const std::string& text) noexcept{
	this->tag      = "";
	this->type     = TagType::TAG_TYPE_VALUE;
	this->option   = text;
	this->children = std::vector<htmlTag>();
}

//通常初期化
htmlVal::htmlVal(std::string&& text) noexcept{
	this->tag      = "";
	this->type     = TagType::TAG_TYPE_VALUE;
	this->option   = std::move(text);
	this->children = std::vector<htmlTag>();
}

htmlVal::~htmlVal() noexcept{

}

//ムーブ演算
htmlVal& htmlVal::operator=(htmlVal&& other) noexcept{
	if(this != &other){
		this->tag      = std::move(other.tag);
		this->type     = std::move(other.type);
		this->option   = std::move(other.option);
		this->children = std::move(other.children);
	}
	return *this;
};

//リストの連結
std::vector<htmlTag> htmlVal::operator+(const htmlVal& right) const noexcept{
	std::vector<htmlTag> res;
	
	if(this->getTagType() == TagType::TAG_TYPE_VALUE)
		res.push_back(*this);
	if(right.getTagType() == TagType::TAG_TYPE_VALUE)
		res.push_back(right);
		
	return res;
}

//リストの連結
std::vector<htmlTag> htmlVal::operator+(htmlVal&& right) const noexcept{
	std::vector<htmlTag> res;
	
	if(this->getTagType() == TagType::TAG_TYPE_VALUE)
		res.push_back(*this);
	if(right.getTagType() == TagType::TAG_TYPE_VALUE)
		res.push_back(std::move(right));
		
	return res;
}
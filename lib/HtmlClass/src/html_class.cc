#include <html_class.hpp>



//operator
std::vector<htmlTag> operator+(std::vector<htmlTag> left,const htmlTag& right) noexcept{
	if(left.empty() || !left[0].isNotTag())
		left.push_back(right);
	return std::move(left);
}
std::vector<htmlTag> operator+(std::vector<htmlTag> left,htmlTag&& right) noexcept{
	if(left.empty() || !left[0].isNotTag())
		left.push_back(std::move(right));
	return std::move(left);
}
std::vector<htmlTag> operator+(std::vector<htmlTag>&& left,const htmlTag& right) noexcept{
	if(left.empty() || !left[0].isNotTag())
		left.push_back(right);
	return std::move(left);
}
std::vector<htmlTag> operator+(std::vector<htmlTag>&& left,htmlTag&& right) noexcept{
	if(left.empty() || !left[0].isNotTag())
		left.push_back(std::move(right));
	return std::move(left);
}

std::vector<htmlTag> operator+(std::vector<htmlTag> left,const htmlVal& right) noexcept{
	if(left.empty() || left[0].isNotTag())
		left.push_back(right);
	return std::move(left);
}
std::vector<htmlTag> operator+(std::vector<htmlTag> left,htmlVal&& right) noexcept{
	if(left.empty() || left[0].isNotTag())
		left.push_back(std::move(right));
	return std::move(left);
}
std::vector<htmlTag> operator+(std::vector<htmlTag>&& left,const htmlVal& right) noexcept{
	if(left.empty() || left[0].isNotTag())
		left.push_back(right);
	return std::move(left);
}
std::vector<htmlTag> operator+(std::vector<htmlTag>&& left,htmlVal&& right) noexcept{
	if(left.empty() || left[0].isNotTag())
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
	children(other.children){};

//ムーブ初期化
htmlTag::htmlTag(htmlTag&& other) noexcept
	:tag(std::move(other.tag)),
	option(std::move(other.option)),
	children(std::move(other.children)){};

//子なし初期化
htmlTag::htmlTag(const std::string& tag,const std::string& option) noexcept
	:option(option),children(){
	this->tag = tag.substr(0,tag.find(' '));
	//insert space for split tag and option
	if(!(this->isNotTag() || this->option.empty()) && this->option[0] != ' ')
		this->option.insert(this->option.begin(),' ');
}

//子なし初期化
htmlTag::htmlTag(std::string&& tag,std::string&& option) noexcept
:option(option),children(){
	this->tag = tag.substr(0,tag.find(' '));
	//insert space for split tag and option
	if(!(this->isNotTag() || this->option.empty()) && this->option[0] != ' ')
		this->option.insert(this->option.begin(),' ');
}

//通常初期化
htmlTag::htmlTag(const std::string& tag,const std::string& option,std::vector<htmlTag> children) noexcept
	:option(option),children(children){
	this->tag = tag.substr(0,tag.find(' '));
	//insert space for split tag and option
	if(!(this->isNotTag() || this->option.empty()) && this->option[0] != ' ')
		this->option.insert(this->option.begin(),' ');
}

//通常初期化
htmlTag::htmlTag(std::string&& tag,std::string&& option,std::vector<htmlTag> children) noexcept
	:option(option),children(children){
	this->tag = tag.substr(0,tag.find(' '));
	//insert space for split tag and option
	if(!(this->isNotTag() || this->option.empty()) && this->option[0] != ' ')
		this->option.insert(this->option.begin(),' ');
}

htmlTag::~htmlTag() noexcept{

}

//encord
std::string htmlTag::encord() const{
	std::string ret("");
	if(this->isNotTag()){
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
	this->option = other.option;
	this->children = other.children;
	return *this;
}

//ムーブ演算
htmlTag& htmlTag::operator=(htmlTag&& other) noexcept{
	if(this != &other){
		this->tag      = std::move(other.tag);
		this->option   = std::move(other.option);
		this->children = std::move(other.children);
	}
	return *this;
}

//リストの連結
std::vector<htmlTag> htmlTag::operator+(htmlTag& right) noexcept{
	std::vector<htmlTag> res;
	
	if(!this->tag.empty())
		res.push_back(*this);
	if(!right.tag.empty())
		res.push_back(right);
		
	return res;
}

//リストの連結
std::vector<htmlTag> htmlTag::operator+(htmlTag&& right) noexcept{
	std::vector<htmlTag> res;
	
	if(!this->tag.empty())
		res.push_back(*this);
	if(!right.tag.empty())
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
htmlVal::htmlVal(const std::string& text) noexcept
	:htmlTag::htmlTag("",text,std::vector<htmlTag>()){
}

//通常初期化
htmlVal::htmlVal(std::string&& text) noexcept
	:htmlTag::htmlTag("",text,std::vector<htmlTag>()){
}

htmlVal::~htmlVal() noexcept{

}

//ムーブ演算
htmlVal& htmlVal::operator=(htmlVal&& other) noexcept{
	if(this != &other){
		this->tag      = std::move(other.tag);
		this->option   = std::move(other.option);
		this->children = std::move(other.children);
	}
	return *this;
};

//リストの連結
std::vector<htmlTag> htmlVal::operator+(htmlVal& right) noexcept{
	std::vector<htmlTag> res;
	
	if(this->tag.empty())
		res.push_back(*this);
	if(right.tag.empty())
		res.push_back(right);
		
	return res;
}

//リストの連結
std::vector<htmlTag> htmlVal::operator+(htmlVal&& right) noexcept{
	std::vector<htmlTag> res;
	
	if(this->tag.empty())
		res.push_back(*this);
	if(right.tag.empty())
		res.push_back(std::move(right));
		
	return res;
}
#include <html_class.hpp>



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
 * 		HTML TAG CLASS
 * ********************************
 */

//コピー初期化
HtmlTag::HtmlTag(const HtmlTag& other) noexcept
	:tag(other.tag),
	option(other.option),
	children(other.children),
	type(other.type){};

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
		ret += "<" + this->tag + this->option + ">";
		for(const auto& element : this->children){
			ret += element.encord();
		}
		ret += "</" + this->tag + ">";
	}
	return ret;
}

//代入演算
HtmlTag& HtmlTag::operator=(const HtmlTag& other) noexcept{
	this->tag = other.tag;
	this->type = other.type;
	this->option = other.option;
	this->children = other.children;
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
std::vector<HtmlTag> HtmlTag::operator+(HtmlTag& right) noexcept{
	std::vector<HtmlTag> res;
	
	if(this->getTagType() == TagType::TAG_TYPE_ELEM)
		res.push_back(*this);
	if(right.getTagType() == TagType::TAG_TYPE_ELEM)
		res.push_back(right);
		
	return res;
}

//リストの連結
std::vector<HtmlTag> HtmlTag::operator+(HtmlTag&& right) noexcept{
	std::vector<HtmlTag> res;
	
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






/***********************************
*           JsValue
 * *****************************
 */


// 静的リソースのコピー
void* JsValue::copyStaticResource() const noexcept{
	switch (this->valueType)
	{
	case JsValueType::JS_STRING:
		return new std::string(*(std::string*)this->staticValue);
	case JsValueType::JS_INT:
		return new int(*(int*)this->staticValue);
	case JsValueType::JS_DOUBLE:
		return new double(*(double*)this->staticValue);
	default:
		return nullptr;
	}
}

//リソースの開放
void JsValue::releaseResource() noexcept{
	if(this->isStatic){
		switch (this->valueType)
		{
		case JsValueType::JS_STRING:
				delete (std::string*) this->staticValue;
			break;
		case JsValueType::JS_INT:
				delete (int*) this->staticValue;
			break;
		case JsValueType::JS_DOUBLE:
				delete (double*) this->staticValue;
			break;
		default:
			break;
		}
	}else{
		this->deleteNode(this->node);
	}
}

void JsValue::deleteNode(const ExprNode* node) noexcept{
	//deleate
	if(node != nullptr){
		if(node->type != NodeType::NODE_VALUE){
			//if node
			this->deleteNode((ExprNode*)node->left);
			this->deleteNode((ExprNode*)node->right);
		}else{
			//if JsValue
			delete (JsValue*)node->left;
		}
	}
	delete node;
}

// ノードコピー
ExprNode* JsValue::copyNode(const ExprNode& node) const{
	if(node.type == NodeType::NODE_VALUE){
		return new ExprNode(node);
	}else{
		ExprNode newNode;
		newNode.type = node.type;
		newNode.left = JsValue::copyNode(*(ExprNode*)node.left);
		newNode.right = JsValue::copyNode(*(ExprNode*)node.right);
		return new ExprNode(newNode);
	}
}

//コピー初期化
JsValue::JsValue(const JsValue& other):
	isStatic(other.isStatic),
	staticValue(other.staticValue),
	valueType(other.valueType),
	node(other.node){}

//ムーブ初期化
JsValue::JsValue(JsValue&& other):
	isStatic(std::move(other.isStatic)),
	staticValue(std::move(other.staticValue)),
	valueType(std::move(other.valueType)),
	node(std::move(other.node)){}

// node 
JsValue::JsValue(const JsValue& left,const JsValue& right,const NodeType& nodeType):
	isStatic(false),
	staticValue(nullptr),
	valueType(left.valueType){
		
	ExprNode* newNode = new ExprNode;
	//set type
	newNode->type = nodeType;

	//set left
	if(left.isStatic){
		newNode->left = new ExprNode;
		((ExprNode*)newNode->left)->type = NodeType::NODE_VALUE;
		((ExprNode*)newNode->left)->left = new JsValue(left);
	}else{
		newNode->left = JsValue::copyNode(*left.node);
	}
	
	//set right
	if(right.isStatic){
		newNode->right = new ExprNode;
		((ExprNode*)newNode->right)->type = NodeType::NODE_VALUE;
		((ExprNode*)newNode->right)->left = new JsValue(right);
	}else{
		newNode->right = JsValue::copyNode(*right.node);
	}

	this->node = newNode;
}
//JsValue::JsValue(const JsValue& left,JsValue&&      right);
//JsValue::JsValue(JsValue&&      left,const JsValue& right);
//JsValue::JsValue(JsValue&&      left,JsValue&&      right):

// string
JsValue::JsValue(const std::string& s):
	isStatic(true),
	node(nullptr),
	valueType(JsValueType::JS_STRING){
		this->staticValue = new std::string(s);
}

// int
JsValue::JsValue(const int& i):
	isStatic(true),
	node(nullptr),
	valueType(JsValueType::JS_INT){
		this->staticValue = new int(i);
}

// double
JsValue::JsValue(const double& d):
	isStatic(true),
	node(nullptr),
	valueType(JsValueType::JS_DOUBLE){
		this->staticValue = new double(d);
}

// デストラクタ
JsValue::~JsValue(){
	this->releaseResource();
}

// 代入
JsValue JsValue::operator=(const JsValue& right) noexcept{
	this->releaseResource();
	this->valueType = right.valueType;

	if(right.isStatic){
		this->staticValue = right.copyStaticResource();
	}else{
		this->node = new ExprNode(*right.node);
	}
}

// ムーブ代入
JsValue JsValue::operator=(JsValue&& right) noexcept{
	this->releaseResource();
	this->valueType = std::move(right.valueType);

	if(right.isStatic){
		this->staticValue = std::move(right.staticValue);
		right.staticValue = nullptr;
	}else{
		this->node = std::move(right.node);
		right.node = nullptr;
	}
}

///////// 演算子

JsValue JsValue::operator+(const JsValue& right) const{
	// check assert
	if(this->valueType != right.valueType && std::max(this->valueType,right.valueType) > JsValueType::JS_NUM_MAX){
		throw "JsValue::operator+: value type is invalid.";
	}
	
	//check static
	if(this->isStatic ^ right.isStatic){
		// switch by value type
		switch (this->valueType)
		{
		//left is int
		case JsValueType::JS_INT:
			switch (right.valueType)
			{
			//right is int
			case JsValueType::JS_INT:
				return JsValue((*(int*)this->staticValue) + (*(int*)right.staticValue));
			//right is double
			case JsValueType::JS_DOUBLE:
				return JsValue((*(int*)this->staticValue) + (*(double*)right.staticValue));
			}
		
		//left is double
		case JsValueType::JS_DOUBLE:
			switch (right.valueType)
			{
			//right is int
			case JsValueType::JS_INT:
				return JsValue((*(double*)this->staticValue) + (*(int*)right.staticValue));
			//right is double
			case JsValueType::JS_DOUBLE:
				return JsValue((*(double*)this->staticValue) + (*(double*)right.staticValue));
			}

		// left is string
		case JsValueType::JS_STRING:
			return JsValue((*(std::string*)this->staticValue) + (*(std::string*)right.staticValue));
		}
	}else{
		return JsValue(*this,right,NodeType::NODE_ADD);
	}
}

JsValue JsValue::operator-(const JsValue& right) const{
	// check assert
	if(std::max(this->valueType,right.valueType) > JsValueType::JS_NUM_MAX){
		throw "JsValue::operator+: value type is invalid.";
	}
	
	//check static
	if(this->isStatic ^ right.isStatic){
		// switch by value type
		switch (this->valueType)
		{
		//left is int
		case JsValueType::JS_INT:
			switch (right.valueType)
			{
			//right is int
			case JsValueType::JS_INT:
				return JsValue((*(int*)this->staticValue) - (*(int*)right.staticValue));
			//right is double
			case JsValueType::JS_DOUBLE:
				return JsValue((*(int*)this->staticValue) - (*(double*)right.staticValue));
			}
		
		//left is double
		case JsValueType::JS_DOUBLE:
			switch (right.valueType)
			{
			//right is int
			case JsValueType::JS_INT:
				return JsValue((*(double*)this->staticValue) - (*(int*)right.staticValue));
			//right is double
			case JsValueType::JS_DOUBLE:
				return JsValue((*(double*)this->staticValue) - (*(double*)right.staticValue));
			}
		}
	}else{
		return JsValue(*this,right,NodeType::NODE_SUB);
	}
}

JsValue JsValue::operator*(const JsValue& right) const{
	// check assert
	if(std::max(this->valueType,right.valueType) > JsValueType::JS_NUM_MAX){
		throw "JsValue::operator+: value type is invalid.";
	}
	
	//check static
	if(this->isStatic ^ right.isStatic){
		// switch by value type
		switch (this->valueType)
		{
		//left is int
		case JsValueType::JS_INT:
			switch (right.valueType)
			{
			//right is int
			case JsValueType::JS_INT:
				return JsValue((*(int*)this->staticValue) - (*(int*)right.staticValue));
			//right is double
			case JsValueType::JS_DOUBLE:
				return JsValue((*(int*)this->staticValue) - (*(double*)right.staticValue));
			}
		
		//left is double
		case JsValueType::JS_DOUBLE:
			switch (right.valueType)
			{
			//right is int
			case JsValueType::JS_INT:
				return JsValue((*(double*)this->staticValue) - (*(int*)right.staticValue));
			//right is double
			case JsValueType::JS_DOUBLE:
				return JsValue((*(double*)this->staticValue) - (*(double*)right.staticValue));
			}
		}
	}else{
		return JsValue(*this,right,NodeType::NODE_MUL);
	}
}

JsValue JsValue::operator/(const JsValue& right) const{
	// check assert
	if(std::max(this->valueType,right.valueType) > JsValueType::JS_NUM_MAX){
		throw "JsValue::operator+: value type is invalid.";
	}
	
	//check static
	if(this->isStatic ^ right.isStatic){
		// switch by value type
		switch (this->valueType)
		{
		//left is int
		case JsValueType::JS_INT:
			switch (right.valueType)
			{
			//right is int
			case JsValueType::JS_INT:
				return JsValue((*(int*)this->staticValue) / (*(int*)right.staticValue));
			//right is double
			case JsValueType::JS_DOUBLE:
				return JsValue((*(int*)this->staticValue) / (*(double*)right.staticValue));
			}
		
		//left is double
		case JsValueType::JS_DOUBLE:
			switch (right.valueType)
			{
			//right is int
			case JsValueType::JS_INT:
				return JsValue((*(double*)this->staticValue) / (*(int*)right.staticValue));
			//right is double
			case JsValueType::JS_DOUBLE:
				return JsValue((*(double*)this->staticValue) / (*(double*)right.staticValue));
			}
		}
	}else{
		return JsValue(*this,right,NodeType::NODE_DIV);
	}
}

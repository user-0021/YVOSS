#include <jsValue.hpp>



/***********************************
*           JsValue
 * *****************************
 */
 
ExprNode* createNode(const JsValue& v);
ExprNode* createNode(ExprNode& left,ExprNode& right,const NodeType& type);
ExprNode* copyNode(ExprNode& node);
void deleteNode(ExprNode* node) noexcept;

//リソースの文字への変換
std::string JsValue::asString() const{
	if(this->isStatic){
		//check type
		switch (this->valueType)
		{
		// convert string
		case JsValueType::JS_INT:
			return std::to_string(*(int*)this->staticValue);
		case JsValueType::JS_DOUBLE:
			return std::to_string(*(double*)this->staticValue);
		case JsValueType::JS_STRING:
			return *(std::string*)this->staticValue;

		//failed
		default:
			break;
		}
	}

	throw "JsValue::asString(): failed convert";
}

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
		deleteNode(this->node);
	}
}



//コピー初期化
JsValue::JsValue(const JsValue& other):
	isStatic(other.isStatic),
	valueType(other.valueType),
	staticValue(nullptr),
	node(other.node){
		//check static value
		if(other.staticValue){
			switch (this->valueType)
			{
			case JsValueType::JS_INT:
				 this->staticValue = new int(*(int*)other.staticValue);
				break;
			case JsValueType::JS_DOUBLE:
				 this->staticValue = new double(*(double*)other.staticValue);
				break;
			case JsValueType::JS_STRING:
				 this->staticValue = new std::string(*(std::string*)other.staticValue);
				break;


			default:
				break;
			}
		}
	}

//ムーブ初期化
JsValue::JsValue(JsValue&& other):
	isStatic(std::move(other.isStatic)),
	staticValue(std::move(other.staticValue)),
	valueType(std::move(other.valueType)),
	node(std::move(other.node)){
		other.staticValue = nullptr;
		other.node = nullptr;
	}

// node 
JsValue::JsValue(const JsValue& left,const JsValue& right,const NodeType& nodeType):
	isStatic(false),
	staticValue(nullptr),
	valueType(left.valueType){
	
	// create new node param
	ExprNode* newNode_left;
	ExprNode* newNode_right;

	//set left
	if(left.isStatic){
		newNode_left = createNode(left);
	}else{
		newNode_left = left.node;
	}
	
	//set right
	if(right.isStatic){
		newNode_right = createNode(right);
	}else{
		newNode_right = right.node;
	}

	this->node = createNode(*newNode_left,*newNode_right,nodeType);
}

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

//encord
std::string JsValue::encord() const{
	return this->asString();
}
	



// 代入
JsValue& JsValue::operator=(const JsValue& right) noexcept{
	this->releaseResource();
	this->valueType = right.valueType;

	if(right.isStatic){
		this->staticValue = right.copyStaticResource();
	}else{
		this->node = copyNode(*right.node);
	}

	return *this;
}

// ムーブ代入
JsValue& JsValue::operator=(JsValue&& right) noexcept{
	this->releaseResource();
	this->valueType = std::move(right.valueType);

	if(right.isStatic){
		this->staticValue = std::move(right.staticValue);
		right.staticValue = nullptr;
	}else{
		this->node = std::move(right.node);
		right.node = nullptr;
	}
	
	return *this;
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

	return JsValue("operator+ failed");
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
	
	return JsValue("operator- failed");
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

	return JsValue("operator* failed");
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
	
	return JsValue("operator/ failed");
}



///// helper

ExprNode* createNode(const JsValue& v){
	//create
	ExprNode* newNode = new ExprNode;
	newNode->refCount++;
	newNode->type = NodeType::NODE_VALUE;

	//set brunch
	newNode->left = new JsValue(v);

	return newNode;
}

ExprNode* createNode(ExprNode& left,ExprNode& right,const NodeType& type){
	//create
	ExprNode* newNode = new ExprNode;
	newNode->refCount++;
	newNode->type = type;

	//set brunch
	newNode->left = copyNode(left);
	newNode->right = copyNode(right);

	return newNode;
}

// ノードコピー
ExprNode* copyNode(ExprNode& node){
	if(node.type != NodeType::NODE_VALUE){
		copyNode(*(ExprNode*)node.left);
		copyNode(*(ExprNode*)node.right);
	}
	
	//copy
	node.refCount++;
	return &node;
}

//　ノード削除
void deleteNode(ExprNode* node) noexcept{
	//deleate
	if(node != nullptr){
		if(node->type != NodeType::NODE_VALUE){
			//if node
			deleteNode((ExprNode*)node->left);
			deleteNode((ExprNode*)node->right);
		}else{
			//if JsValue
			delete (JsValue*)node->left;
		}
	}

	//ref dec
	node->refCount--;
	if(!node->refCount)
		delete node;
}
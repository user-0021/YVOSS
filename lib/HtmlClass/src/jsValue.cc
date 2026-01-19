#include <jsValue.hpp>



/***********************************
*           JsValue
 * *****************************
 */



//コピー初期化
JsValue::JsValue(const JsValue& other):
	isStatic(other.isStatic),
	staticValue(other.staticValue){
		if(!other.isStatic && other.node)
			this->node = copyNode(other.node);
	}

//ムーブ初期化
JsValue::JsValue(JsValue&& other):
	isStatic(std::move(other.isStatic)),
	staticValue(std::move(other.staticValue)),
	node(std::move(other.node)){
		other.node = nullptr;
	}
	
JsValue::JsValue(ExprNode* left,ExprNode* right,NodeType type):
	isStatic(false),
	staticValue(){
	node = createNode(left,right,type);
}

// デストラクタ
JsValue::~JsValue(){
	if(!this->isStatic && this->node)
		deleteNode(this->node);
}

//set new node
ExprNode* JsValue::setNode(ExprNode* node){
	if(!this->isStatic){
		deleteNode(this->node);
		this->node = nullptr;
	}

	if(node != nullptr)
		this->node = copyNode(node);
	else
		this->node = nullptr;
}

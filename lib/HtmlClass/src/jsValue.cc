#include <jsValue.hpp>



/***********************************
*           JsValue
 * *****************************
 */
 
ExprNode* createNode(ExprNode& left,ExprNode& right,const NodeType& type);
ExprNode* copyNode(ExprNode& node);
void deleteNode(ExprNode* node) noexcept;



//コピー初期化
JsValue::JsValue(const JsValue& other):
	isStatic(other.isStatic){
		if(!other.isStatic && other.node)
			this->node = copyNode(*other.node);
	}

//ムーブ初期化
JsValue::JsValue(JsValue&& other):
	isStatic(std::move(other.isStatic)),
	node(std::move(other.node)){
		other.node = nullptr;
	}
	
JsValue::JsValue(ExprNode* left,ExprNode* right,NodeType type):
	isStatic(false){
	node = createNode(*left,*right,type);
}

// デストラクタ
JsValue::~JsValue(){
	if(!this->isStatic && this->node)
		deleteNode(this->node);
}

//set new node
ExprNode* JsValue::setNode(ExprNode& node){
	if(!this->isStatic){
		deleteNode(this->node);
		this->node = nullptr;
	}

	this->node = copyNode(node);
}

ExprNode* JsValue::setNode(ExprNode&& node){
	if(!this->isStatic){
		deleteNode(this->node);
		this->node = nullptr;
	}

	this->node = std::move(&node);
}

///// helper

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
		if(node.left)
			copyNode(*(ExprNode*)node.left);
		if(node.right)
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
#pragma once
#include <stdint.h>
#include <string>
#include <vector>

enum JsValueType{
	JS_INT    = 0,
	JS_DOUBLE = 1,
	JS_NUM_MAX = 2,
	JS_STRING = 3
};

enum NodeType{
	NODE_VALUE,
	NODE_SET,
	NODE_ADD,
	NODE_SUB,
	NODE_MUL,
	NODE_DIV,
	NODE_REM,
	NODE_CALL
};

struct ExprNode
{
	uint16_t refCount;
	const void* left;
	const void* right;
	NodeType type;
};

struct JsFunctionNode{
	ExprNode node;
	std::string funcName;
	std::string jsCode;
};

struct JsDepend
{
	std::string import;
	std::string from;
};



class JsValue{
protected:
	//state	
	bool isStatic;
	std::string staticValue;

	//dor dynamic
	ExprNode* node; 

	//copy node
	ExprNode* setNode(ExprNode* node);


	///// helper
	static JsValue callFunc(const std::string& funName,const std::vector<JsValue>& args,const std::vector<JsDepend>& dependes){
		
	};


	// get node
	static ExprNode* getNode(const JsValue* obj){
		if(obj->isStatic)
			return createSingleNode(obj,NodeType::NODE_VALUE);
		else
			return obj->node;
	};

	// ノードの作成
	static ExprNode* createNode(ExprNode* left,ExprNode* right,const NodeType& type){
		//create
		ExprNode* newNode = new ExprNode;
		newNode->refCount++;
		newNode->type = type;

		//set brunch
		newNode->left = copyNode(left);
		newNode->right = copyNode(right);

		return newNode;
	};

	static ExprNode* createSingleNode(const JsValue* obj,const NodeType& type){
		if(obj->isStatic){
			return new ExprNode(ExprNode{
					.refCount = 0,
					.left = new std::string(obj->staticValue),
					.right = nullptr,
					.type = type
				});
		}else{
			return new ExprNode(ExprNode{
					.refCount = 0,
					.left = copyNode(obj->node),
					.right = nullptr,
					.type = type
				});
		}
	};

	// ノードコピー
	static ExprNode* copyNode(ExprNode* node){
		//null check
		if(node == nullptr)
			return nullptr;

		if(node->type != NodeType::NODE_VALUE){
			if(node->left)
				copyNode((ExprNode*)node->left);
			if(node->right)
				copyNode((ExprNode*)node->right);
		}
		
		//copy
		node->refCount++;
		return node;
	};

	//　ノード削除
	static void deleteNode(ExprNode* node) noexcept{
		//null check
		if(node == nullptr)
			return;

		//deleate
		if(node->type != NodeType::NODE_VALUE){
			//if node
			deleteNode((ExprNode*)node->left);
			deleteNode((ExprNode*)node->right);
		}else{
			//if JsValue
			delete (JsValue*)node->left;
		}

		//ref dec
		node->refCount--;
		if(!node->refCount)
			delete node;
	};

public:
	JsValue():node(nullptr){};
	JsValue(const JsValue& other);
	JsValue(JsValue&& other);
	JsValue(ExprNode* left,ExprNode* right,NodeType type);

	~JsValue();
};

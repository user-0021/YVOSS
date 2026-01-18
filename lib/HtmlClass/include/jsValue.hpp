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
	NODE_EQ,
	NODE_ADD,
	NODE_SUB,
	NODE_MUL,
	NODE_DIV,
	NODE_ARGV,
	NODE_FUN
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


class JsValue{
protected:
	//state	
	bool isStatic;

	//dor dynamic
	ExprNode* node; 

	//copy node
	ExprNode* setNode(ExprNode& node);
	ExprNode* setNode(ExprNode&& node);


public:
	JsValue():node(nullptr){};
	JsValue(const JsValue& other);
	JsValue(JsValue&& other);
	JsValue(ExprNode* left,ExprNode* right,NodeType type);

	~JsValue();
};

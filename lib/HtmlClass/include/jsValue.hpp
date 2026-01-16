#pragma once
#include <stdint.h>
#include <string>

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
	std::vector<JsValue> args;
	std::string jsCode;
};


class JsValue{
protected:
	//state	
	bool isStatic;
	JsValueType valueType; 
	
	//for static value
	void* staticValue;

	//dor dynamic
	ExprNode* node; 

	std::string asString() const;

	void* copyStaticResource() const noexcept; 
	void releaseResource() noexcept;

public:
	JsValue(const JsValue& other);
	JsValue(JsValue&& other);
	JsValue(const JsValue& left,const JsValue& right,const NodeType& nodeType);
	JsValue(const std::string& s);
	JsValue(const int& i);
	JsValue(const double& d);

	~JsValue();

	std::string encord() const;

	JsValue& operator=(const JsValue& right) noexcept;
	JsValue& operator=(JsValue&& right) noexcept;
	JsValue operator+(const JsValue& right) const;
	JsValue operator-(const JsValue& right) const;
	JsValue operator*(const JsValue& right) const;
	JsValue operator/(const JsValue& right) const;
};

// int class
class JsInt: JsValue{
	public:
};

// string class
class JsString: JsValue{
	public:
		static JsValue fromCharCode(std::vector<JsInt> args);
};


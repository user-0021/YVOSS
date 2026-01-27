#pragma once
#include <vector>
#include <string>
#include <memory>
#include <array>
#include <string.h>
#include <stdint.h>

#define HTML_TAG_FOREACH_BEGIN(...) [&]() -> std::vector<HtmlTag>{std::vector<HtmlTag> ____________dontuse_tags; for(__VA_ARGS__){____________dontuse_tags = ____________dontuse_tags+[&]() -> std::vector<HtmlTag>
#define HTML_TAG_FOREACH_END ();}return ____________dontuse_tags;}()

/**
 * @brief html class for modern website dev
 * 
 */
namespace html_class
{
	class HtmlTag;
	/**
	 * @brief html tag class
	 * 
	 */
	class HtmlTag
	{
	protected:
		/// @brief check tag or text
		bool  _isTag;
		/// @brief tag name
		std::string _tag;
		/// @brief option (use as text in text node)
		std::string _option;
		/// @brief (<_tag _option></_tag>).length()
		std::size_t _dataLen;

		/// @brief for tag tree
		std::vector<HtmlTag> _children;

		/// @brief look up table for replace escape text in html 
		inline static constexpr const std::array<const char*, 256> _htmlEscapeStr = [] {
        std::array<const char*, 256> table{};
        
        table[(unsigned char)'&']  = "&amp;";
        table[(unsigned char)'<']  = "&lt;";
        table[(unsigned char)'>']  = "&gt;";
        table[(unsigned char)'"']  = "&quot;";
        table[(unsigned char)'\''] = "&#39;";
        table[(unsigned char)'\n'] = "<br>";
        
        return table;
    }();
		/// @brief look up table for check text to need escape and calc length
		inline static constexpr const std::array<uint8_t, 256> _htmlEscapeFlag = [] {
        std::array<uint8_t, 256> flags{};
        
        flags[(unsigned char)'&']  = strlen("&amp;")  -1;
        flags[(unsigned char)'<']  = strlen("&lt;")   -1;
        flags[(unsigned char)'>']  = strlen("&gt;")   -1;
        flags[(unsigned char)'"']  = strlen("&quot;") -1;
        flags[(unsigned char)'\''] = strlen("&#39;")  -1;
        flags[(unsigned char)'\n'] = strlen("<br>")   -1;
        
        return flags;
    }();



		/// @brief for encord_raw_text
		/// @param [in] buff copy buffer
		/// @return endorded raw text 
		void chained_encord_raw_text(std::string& buff) const noexcept;
	public:
	
		/// @brief copy constractor
		/// @param [in] other other  
		HtmlTag(const HtmlTag& other);
		/// @brief move constractor
		/// @param [in] other other 
		HtmlTag(HtmlTag&& other) noexcept;
		/// @brief create html text
		/// @param [in] text text
		HtmlTag(std::string text);
		/// @brief create html tag without children
		/// @param [in] tag tag name 
		/// @param [in] option option value
		HtmlTag(std::string tag,std::string option);
		/// @brief create html tag
		/// @param [in] tag tag name 
		/// @param [in] option option value
		/// @param [in] children tag children
		HtmlTag(std::string tag,std::string option,std::vector<HtmlTag> children);
		/// @brief destractor
		~HtmlTag() noexcept;

		/// @brief check tag or text
		/// @return true is Tag
		/// @return false is text
		bool isTag() const noexcept {return this->_isTag;}
		/// @brief encord node to raw text
		/// @return endorded raw text 
		std::string encord_raw_text() const;
		

		/// @brief cast to std::vector<HtmlTag>
		operator std::vector<HtmlTag>() const{return std::vector<HtmlTag>{*this};}
		
		/// @brief copy set
		/// @param [in] other other 
		/// @return self
		HtmlTag& operator=(const HtmlTag& other);
		/// @brief move set
		/// @param [in] other other 
		/// @return self
		HtmlTag& operator=(HtmlTag&& other) noexcept;
	};	

	/// @brief add HtmlTag to HtmlTag
	/// @param [in] left left 
	/// @param [in] right right
	/// @return std::vector<HtmlTag>{left,right}
	inline std::vector<HtmlTag> operator+(const HtmlTag& left,const HtmlTag& right);
	/// @brief add HtmlTag to HtmlTag (left is move)
	/// @param [in] left left 
	/// @param [in] right right
	/// @return std::vector<HtmlTag>{left,right}
	inline std::vector<HtmlTag> operator+(      HtmlTag&&left,const HtmlTag& right);
	/// @brief add HtmlTag to HtmlTag (right is move)
	/// @param [in] left left 
	/// @param [in] right right
	/// @return std::vector<HtmlTag>{left,right}
	inline std::vector<HtmlTag> operator+(const HtmlTag& left,      HtmlTag&&right);
	/// @brief add HtmlTag to HtmlTag (left and right is move)
	/// @param [in] left left 
	/// @param [in] right right
	/// @return std::vector<HtmlTag>{left,right}
	inline std::vector<HtmlTag> operator+(      HtmlTag&&left,      HtmlTag&&right);
	/// @brief add HtmlTag to std::vector<HtmlTag>
	/// @param left left(vector)
	/// @param right right(HtmlTag)
	/// @return std::vector<HtmlTag>{left,right}
	inline std::vector<HtmlTag> operator+(const std::vector<HtmlTag>& left,const HtmlTag& right);
	/// @brief add HtmlTag to std::vector<HtmlTag> (left is move)
	/// @param left left(vector)
	/// @param right right(HtmlTag)
	/// @return std::vector<HtmlTag>{left,right}
	inline std::vector<HtmlTag> operator+(      std::vector<HtmlTag>&&left,const HtmlTag& right);
	/// @brief add HtmlTag to std::vector<HtmlTag> (right is move)
	/// @param left left(vector)
	/// @param right right(HtmlTag)
	/// @return std::vector<HtmlTag>{left,right}
	inline std::vector<HtmlTag> operator+(const std::vector<HtmlTag>& left,      HtmlTag&&right);
	/// @brief add HtmlTag to std::vector<HtmlTag> (left and right is move)
	/// @param left left(vector)
	/// @param right right(HtmlTag)
	/// @return std::vector<HtmlTag>{left,right}
	inline std::vector<HtmlTag> operator+(      std::vector<HtmlTag>&&left,      HtmlTag&&right);
	/// @brief add std::vector<HtmlTag> to std::vector<HtmlTag>
	/// @param left left
	/// @param right right
	/// @return std::vector<HtmlTag>{left,right}
	inline std::vector<HtmlTag> operator+(const std::vector<HtmlTag>& left,const std::vector<HtmlTag>& right);
	/// @brief add std::vector<HtmlTag> to std::vector<HtmlTag> (left is move)
	/// @param left left
	/// @param right right
	/// @return std::vector<HtmlTag>{left,right}
	inline std::vector<HtmlTag> operator+(      std::vector<HtmlTag>&&left,const std::vector<HtmlTag>& right);
	/// @brief add std::vector<HtmlTag> to std::vector<HtmlTag> (right is move)
	/// @param left left
	/// @param right right
	/// @return std::vector<HtmlTag>{left,right}
	inline std::vector<HtmlTag> operator+(const std::vector<HtmlTag>& left,      std::vector<HtmlTag>&&right);
	/// @brief add std::vector<HtmlTag> to std::vector<HtmlTag> (left and right is move)
	/// @param left left
	/// @param right right
	/// @return std::vector<HtmlTag>{left,right}
	inline std::vector<HtmlTag> operator+(      std::vector<HtmlTag>&&left,      std::vector<HtmlTag>&&right);
	/// @brief add equal HtmlTag to std::vector<HtmlTag>
	/// @param left left(vector)
	/// @param right right(HtmlTag)
	/// @return std::vector<HtmlTag>{left,right}
	inline std::vector<HtmlTag>& operator+=(      std::vector<HtmlTag>&left,const HtmlTag& right);
	/// @brief add equal HtmlTag to std::vector<HtmlTag> (right is move)
	/// @param left left(vector)
	/// @param right right(HtmlTag)
	/// @return std::vector<HtmlTag>{left,right}
	inline std::vector<HtmlTag>& operator+=(      std::vector<HtmlTag>&left,      HtmlTag&&right);
	/// @brief add equal std::vector<HtmlTag> to std::vector<HtmlTag>
	/// @param left left
	/// @param right right
	/// @return std::vector<HtmlTag>{left,right}
	inline std::vector<HtmlTag>& operator+=(      std::vector<HtmlTag>& left,const std::vector<HtmlTag>&right);
	/// @brief add equal std::vector<HtmlTag> to std::vector<HtmlTag> (right is move)
	/// @param left left
	/// @param right right
	/// @return std::vector<HtmlTag>{left,right}
	inline std::vector<HtmlTag>& operator+=(      std::vector<HtmlTag>& left,      std::vector<HtmlTag>&&right);










	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//                                  Constractor and Destoractor
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	HtmlTag::HtmlTag(const HtmlTag& other):
	_isTag(   other._isTag),
	_tag(     other._tag),
	_option(  other._option),
	_dataLen( other._dataLen),
	_children(other._children){
		
	}

	HtmlTag::HtmlTag(HtmlTag&& other) noexcept:
	_isTag   (std::move(other._isTag)),
	_tag     (std::move(other._tag)),
	_option  (std::move(other._option)),
	_dataLen (std::move(other._dataLen)),
	_children(std::move(other._children)){
	}

	HtmlTag::HtmlTag(std::string text):
	_isTag   (false),
	_tag     (),
	_dataLen (),
	_children(){

		//count char to need escape
		std::size_t copiedLen = 0;
		for (char c : text){
			if(HtmlTag::_htmlEscapeFlag[(unsigned char) c]) [[unlikely]] {
				copiedLen += this->_htmlEscapeFlag[(unsigned char) c];
			}
		}

		if (!copiedLen) [[likely]]{
			// if don't escape
			this->_option = std::move(text);
		} else {
			//reserve new text size
			this->_option.reserve(text.size() + copiedLen);
			
			std::size_t lastPos = 0;
			std::size_t escapePos = 0;
			for (char c : text){
				if(const char* replaceText = HtmlTag::_htmlEscapeStr[(unsigned char) c]) [[unlikely]] {
					//if need escape
					this->_option.append(text, lastPos, escapePos - lastPos);
					this->_option.append(replaceText);
					lastPos = escapePos + 1;
				}
				escapePos++;
			}
			this->_option.append(text, lastPos, std::string::npos);
		}
		
		//update len
		this->_dataLen = _option.length();
}

	HtmlTag::HtmlTag(std::string tag,std::string option):
	_isTag   (true),
	_tag     (std::move(tag)),
	_option  (std::move(option)),
	_children(){
		if(!this->_option.empty())
			this->_option.insert(this->_option.begin(),' ');
		this->_dataLen = _tag.length() + _option.length() + 5;
	}

	HtmlTag::HtmlTag(std::string tag,std::string option,std::vector<HtmlTag> children):
	_isTag   (true),
	_tag     (std::move(tag)),
	_option  (std::move(option)),
	_children(std::move(children)){
		if(!this->_option.empty())
			this->_option.insert(this->_option.begin(),' ');
		this->_dataLen = _tag.length() + _option.length() + 5;
	}

	HtmlTag::~HtmlTag() noexcept{
		
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//                                  Members functions
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	void HtmlTag::chained_encord_raw_text(std::string& buff) const noexcept{
		if(this->_isTag){
			buff += '<'; 
			buff += this->_tag;
			buff += this->_option;
			buff += '>';

			for(const auto& elem: this->_children){
				elem.chained_encord_raw_text(buff);
			}

			buff += "</";
			buff += this->_tag;
			buff += '>';
		}else{
			buff += this->_option;
		}
	}

	std::string HtmlTag::encord_raw_text() const{
		std::string rawText;
		rawText.reserve(this->_dataLen);

		if(this->_isTag){
			rawText += '<'; 
			rawText += this->_tag;
			rawText += this->_option;
			rawText += '>';

			for(const auto& elem: this->_children){
				elem.chained_encord_raw_text(rawText);
			}

			rawText += "</";
			rawText += this->_tag;
			rawText += '>';
		}else{
			rawText += this->_option;
		}

		
		return rawText;
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//                                  Members operands
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	HtmlTag& HtmlTag::operator=(const HtmlTag& other){
		_isTag    = other._isTag;
		_tag      = other._tag;
		_option   = other._option;
		_dataLen  = other._dataLen;
		_children = other._children;

		return * this;
	}

	HtmlTag& HtmlTag::operator=(HtmlTag&& other) noexcept{
		_isTag    = std::move(other._isTag);
		_tag      = std::move(other._tag);
		_option   = std::move(other._option);
		_dataLen  = std::move(other._dataLen);
		_children = std::move(other._children);

		return * this;
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//                                  operands
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	inline std::vector<HtmlTag> operator+(const HtmlTag& left,const HtmlTag& right){
		std::vector<HtmlTag> ret;
		ret.reserve(2);
		ret.push_back(left);
		ret.push_back(right);
		return ret;
	}
	
	inline std::vector<HtmlTag> operator+(      HtmlTag&&left,const HtmlTag& right){
		std::vector<HtmlTag> ret;
		ret.reserve(2);
		ret.push_back(std::move(left));
		ret.push_back(right);
		return ret;
	}
	
	inline std::vector<HtmlTag> operator+(const HtmlTag& left,      HtmlTag&&right){
		std::vector<HtmlTag> ret;
		ret.reserve(2);
		ret.push_back(left);
		ret.push_back(std::move(right));
		return ret;
	}
	
	inline std::vector<HtmlTag> operator+(      HtmlTag&&left,      HtmlTag&&right){
		std::vector<HtmlTag> ret;
		ret.reserve(2);
		ret.push_back(std::move(left));
		ret.push_back(std::move(right));
		return ret;
	}
	
	inline std::vector<HtmlTag> operator+(const std::vector<HtmlTag>& left,const HtmlTag& right){
		std::vector<HtmlTag> ret;
		ret.reserve(left.size() + 1);
		ret = left;
		ret.push_back(right);
		return ret;
	}
	
	inline std::vector<HtmlTag> operator+(      std::vector<HtmlTag>&&left,const HtmlTag& right){
		return std::move(left+=right);
	}
	
	inline std::vector<HtmlTag> operator+(const std::vector<HtmlTag>& left,      HtmlTag&&right){
		std::vector<HtmlTag> ret;
		ret.reserve(left.size() + 1);
		ret = left;
		ret.push_back(std::move(right));
		return ret;
	}
	
	inline std::vector<HtmlTag> operator+(      std::vector<HtmlTag>&&left,      HtmlTag&&right){
		return std::move(left+=right);
	}
	
	inline std::vector<HtmlTag> operator+(const std::vector<HtmlTag>& left,const std::vector<HtmlTag>& right){
		std::vector<HtmlTag> ret;
		ret.reserve(left.size() + right.size());
		ret = left;
		ret.insert(ret.end(),right.begin(),right.end());
		return ret;
	}
	
	inline std::vector<HtmlTag> operator+(      std::vector<HtmlTag>&&left,const std::vector<HtmlTag>& right){
		return std::move(left+=right);
	}
	
	inline std::vector<HtmlTag> operator+(const std::vector<HtmlTag>& left,      std::vector<HtmlTag>&&right){
		std::vector<HtmlTag> ret;
		ret.reserve(left.size() + right.size());
		ret = left;
		ret.insert(ret.end(),std::make_move_iterator(right.begin()),std::make_move_iterator(right.end()));
		return ret;
	}
	
	inline std::vector<HtmlTag> operator+(      std::vector<HtmlTag>&&left,      std::vector<HtmlTag>&&right){
		return std::move(left+=right);
	}
	
	inline std::vector<HtmlTag>& operator+=(      std::vector<HtmlTag>&left,const HtmlTag& right){
		left.push_back(right);
		return left;
	}
	
	inline std::vector<HtmlTag>& operator+=(      std::vector<HtmlTag>&left,      HtmlTag&&right){
		left.push_back(std::move(right));
		return left;
	}
	
	inline std::vector<HtmlTag>& operator+=(      std::vector<HtmlTag>& left,const std::vector<HtmlTag>&right){
		left.reserve(left.size() + right.size());
		left.insert(left.end(),right.begin(),right.end());
		return left;
	}
	
	inline std::vector<HtmlTag>& operator+=(      std::vector<HtmlTag>& left,      std::vector<HtmlTag>&&right){
		left.reserve(left.size() + right.size());
		left.insert(left.end(),std::make_move_iterator(right.begin()),std::make_move_iterator(right.end()));
		return left;
	}
}
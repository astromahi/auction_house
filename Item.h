

#ifndef ITEM_H
#define ITEM_H
#include <string>
#include <sstream>

class Item
{
private:

	int lotno;
	int resprice;
	std::string str;
	std::string type;
	std::string description;
	std::string itemstate;

public:

	Item() { }
	~Item() { }
	void setLotno(std::istream&, std::ostream&);
	int getLotno(void) const;
	void setType(std::istream&, std::ostream&);
	std::string getType(void) const ;
	void setDescription(std::istream&, std::ostream&);
	std::string getDescription(void) const;
	void setItemstate(std::istream&, std::ostream&);
	std::string getItemstate(void) const ;
	void setResprice(std::istream&, std::ostream&);
	int getResprice(void) const ;

};
#endif

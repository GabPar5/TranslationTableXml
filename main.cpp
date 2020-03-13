#include <iostream>
#include <string>
#include <fstream>
#include <strstream>

#include "team.hxx"
#include "translationTable.hxx"

// Call and print every element
void DisplayAllXml(std::auto_ptr<translationTable> &table) {
	translationTable::entry_iterator it;
	for (it = table->entry().begin(); it != table->entry().end(); it++) {
		std::cout << it->stringName() << " " << it->result() << "\n";
	}
}

void AddEntry(std::auto_ptr<translationTable> &table) {
	std::string name, result;
	std::cout << "\nName: " << std::flush;
	std::getline(std::cin, name);
	std::cout << "\nResult: " << std::flush;
	std::getline(std::cin, result);
	entry _entry = entry(result, name);
	table->entry().push_back(_entry);
}

// Save to xml file
void ToXml(std::auto_ptr<translationTable> &table, std::string path) {
	xml_schema::namespace_infomap map;
	map["gt"].name = "translationTable_english_new.xml";
	map["gt"].schema = "translationTable.xsd";
	std::ofstream ofs(path.c_str());
	translationTable_(ofs, *table, map);
}

// main function
int main()
{
	try {
		std::auto_ptr<translationTable> table(translationTable_("data//translationTable_english.xml"));
		DisplayAllXml(table);
		AddEntry(table);
		ToXml(table, "data//translationTable_english_new.xml");
		DisplayAllXml(table);
	}
	catch (const xml_schema::exception & e) {
		std::cout << e << std::endl;
		return 1;
	}
	return 0;
}

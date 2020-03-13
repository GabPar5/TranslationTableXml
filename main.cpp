#include <iostream>
#include <string>
#include <fstream>
#include <strstream>

#include "team.hxx"

// Call and print every element
void DisplayAllXml(std::auto_ptr<ProjectTeam> &proj) {
	std::cout << "Team name: " << proj->TeamName() << std::endl;

	ProjectTeam::Member_const_iterator it;
	for (it = proj->Member().begin(); it != proj->Member().end(); it++) {
		std::cout << "Name: " << it->Name() << "\nBrainPower: " << it->BrainPower() << std::endl;
	}
}

// Add a new element to a sequence
void AddMember(std::auto_ptr<ProjectTeam> &proj) {
	std::cout << "\n\nAdding a new member: ";
	std::string name;
	std::cout << "\nName: " << std::flush;
	std::getline(std::cin, name);
	std::string strPower;
	std::cout << "Brain Power: " << std::flush;
	std::getline(std::cin, strPower);
	int power = std::stoi(strPower);
	Member member = Member(name, power);
	proj->Member().push_back(member);
}

// Save to xml file
void ToXml(std::auto_ptr<ProjectTeam> &proj, std::string path) {
	xml_schema::namespace_infomap map;
	map["gt"].name = "team_new.xml";
	map["gt"].schema = "library.xsd";
	std::ofstream ofs(path.c_str());
	ProjectTeam_(ofs, *proj, map);
}

// main function
int main()
{
	try {
		std::auto_ptr<ProjectTeam> proj(ProjectTeam_("team.xml"));
		DisplayAllXml(proj);
		AddMember(proj);
		ToXml(proj, "team_new.xml");
		DisplayAllXml(proj);
	}
	catch (const xml_schema::exception & e) {
		std::cout << e << std::endl;
		return 1;
	}
	return 0;
}

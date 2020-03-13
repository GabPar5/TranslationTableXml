#include<iostream>
#include<string>
#include<fstream>
#include<strstream>
#include"library.hxx"

using std::cout;
using std::endl;
using std::string;
using std::cin;
using std::getline;
using std::stringstream;
using gSOAP::test::Library;
using gSOAP::test::Library_;
using gSOAP::test::Book;

void DisplayAllBooks(const  std::auto_ptr < library > & pLibrary) {
  cout << "\n\nDisplaying all books in the library:" << endl;
  Library::Books_type::Book_const_iterator it = pLibrary - > Books().Book().begin();
  for (; it != pLibrary - > Books().Book().end(); it++) {
    cout << "\nBook:\n" << "\tTitle:" << ( * it).title() << "\n\tAuthor:" << ( * it).author() << "\n\tISBN: " << ( * it).isbn() << "\n\tCopies available: " << static_cast < int > (( * it).CopiesAvailable()) << endl;
  }
}

void AddBook(std::auto_ptr < Library > & pLibrary) { 
  cout << "\n\nAdding a new book:" << endl;
  string strTitle;
  cout << "\tTitle: " << std::flush;
  getline(cin, strTitle);
  string strAuthor;
  cout << "\tAuthor: " << std::flush;
  getline(cin, strAuthor);
  string strISBN;
  cout << "\tISBN:" << std::flush;
  getline(cin, strISBN);
  cout << "\tCopies available: " << std::flush;
  string strCopiesAvailable;
  unsigned int unCopiesAvailable = 0;
  getline(cin, strCopiesAvailable);
  stringstream ss(strCopiesAvailable);
  ss >> unCopiesAvailable;
  Book book(unCopiesAvailable, strTitle, strAuthor, strISBN);
  pLibrary - > Books().Book().push_back(book);
}

void ExportToXML(const  std::auto_ptr < library > & pLibrary,  const    string & strXMLPath) {
  xml_schema::namespace_infomap map;
  map["gt"].name = "http://www.bk.com/gSOAP/test";
  map["gt"].schema = "library.xsd";
  std::ofstream ofs(strXMLPath.c_str());
  Library_(ofs, * pLibrary, map);
}

int main() {  
  try {
    string strXMLPath("library.xml");
    std::auto_ptr < library > pLibrary(Library_((strXMLPath.c_str())));
    DisplayAllBooks(pLibrary);
    AddBook(pLibrary);
    DisplayAllBooks(pLibrary);
    ExportToXML(pLibrary, strXMLPath);
  } 
  catch (const xml_schema::exception & e) {
    cout << e << endl;
    return     1;
  }
  return
  0;
}
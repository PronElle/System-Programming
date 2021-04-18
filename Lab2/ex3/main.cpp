#include <iostream>
#include "Directory.h"

using namespace std;

int main() {
    std::shared_ptr<Directory> root = Directory::getRoot();
    root->addDirectory("Pippo");
    root->addDirectory("Pluto");
    cout << "after Pippo and Pluto: \n";
    root->ls(0);

    auto under_root = root -> addDirectory( "Padre" );
    root -> addDirectory( "Figlio" )->addFile( "Figlio1" , 10 );
    root -> getDir( "Figlio" ) -> addFile( "Figlio2" , 25 );
    root -> getDir("Figlio") ->addDirectory("new_dir")->addFile("foo", 10);

    cout << "\nadded dirs and files: \n";
    under_root -> getDir( ".." ) -> ls(0);

    root -> remove( "Figlio" );
    cout << "\nafter removing Figlio: \n";
    root -> ls(0);
    return 0;
}
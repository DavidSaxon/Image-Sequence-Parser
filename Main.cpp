/**************************************************************************\
| This a simple script that takes a folder name that contains a sequence   |
| of images and renames the image names so that any preceding zeros before |
| numbers are removed.                                                     |
|                                                                          |
| @author David Saxon                                                      |
\**************************************************************************/
#include <iostream>
#include <map>
#include <sstream>
#include <stdio.h>
#include <vector>

#include "Utilities/ArgumentsUtil.hpp"
#include "Utilities/FileSystemUtil.hpp"

//TYPEDEFS
typedef std::map<std::string, bool*> FlagMap;
typedef std::vector<std::string> ArgumentList;
typedef std::vector<std::string> PathNameList;

//PROTOTYPES
/*!Displays the help to the terminal*/
void displayHelp();

//MAIN FUNCTION
int main(int argc, char* argv[]) {

    //flag variables
    //is true if the help should be displayed
    bool help =  false;

    //create the mapping from flags to booleans
    FlagMap flagMap;
    flagMap.insert(std::make_pair("h", &help));

    //vector containing the arguments
    ArgumentList argumentList;

    //parse the command line arguments
    argumentList = util::arg::parseCmdLineArguments(argc, argv, flagMap);

    //display the help info and exit
    if (help) {

        displayHelp();
        return 0;
    }

    //check that some arguments have been provided
    if (argumentList.empty()) {

        //print error and exit
        std::cout << "Error: no directories given" << std::endl;
        return -1;
    }

    //for each file name passed rename any images contained within
    ArgumentList::const_iterator
        it = argumentList.begin(),
        ite = argumentList.end();

    //first check that all the arguments are directories
    for (; it != ite; ++it) {

        if (!util::file::dirExists(*it)) {

            //print error message and exit
            std::cout << "Error: " << *it << " is not a valid directory name" <<
                std::endl;
            return -2;
        }
    }


    //create the output directory
    util::file::createDirectory("output");

    //process each directory
    it = argumentList.begin();
    for (; it != ite; ++it) {

        //create a vector to store all the path names in this dirctory
        PathNameList pathNameList;

        //get the paths in the directory
        util::file::getPathsInDir(*it, pathNameList);

        unsigned i = 0;

        //for each path rename it
        PathNameList::const_iterator
            pIt = pathNameList.begin(),
            pIte = pathNameList.end();
        for (; pIt != pIte; ++pIt) {

            //check if it is a png
            if (util::file::extensionEquals(*pIt, "png")) {

                //the current name of the image
                std::string currentName = *pIt;

                //convert the counter to a string
                std::stringstream newName;
                newName << "output/" << i << ".png";

                //rename the image
                rename(currentName.c_str(), newName.str().c_str());

                ++i;
            }
        }
    }

    std::cout << "done" << std::endl;

    return 0;
}

void displayHelp() {

    std::cout << "\nUSE:\n" << std::endl;
    std::cout << "\tPass the the directory of images which names to be passed " <<
        "as a command line argument" << std::endl;
    std::cout << std::endl;
    std::cout << "FLAGS:\n" << std::endl;
    std::cout << "\t--h\t:\tdisplay this help message" << std::endl;
    std::cout << std::endl;
}
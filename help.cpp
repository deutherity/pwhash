#include <iostream>


void printhelp()
{
    std::cout 
    << "Usage: \n"
    << "\tpwhash ACTION [OPTIONS]\n"
    << "\tpwhash {-h | --help}\n\n"
    << "ACTION\n"
    << "\tn[ew]\tgenerates new password. Fill in the options\n"
    << "\th[elp]\tprints this manual\n"
    << "\tu[se]\tprints your password using xclip. Usage: pwhash use {id}\n" 
    << "\tl[ist]\tprints info about your passwords\n" << std::endl;
}
#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <vector>

std::string trim(std::string const& s);
std::vector<std::vector<std::string>> readCSV(std::string const& csvFile);

#endif /* UTILS_H */

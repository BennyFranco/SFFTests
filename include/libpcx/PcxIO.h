#pragma once

#include <string>

#include "PCXImage.h"

PCXImage ReadPCX(char * fileName);
void WritePCX(char * fileName, PCXImage image);
std::string TestMethod();

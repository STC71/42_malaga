/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-01-13 10:02:33 by sternero          #+#    #+#             */
/*   Updated: 2025-01-13 10:02:33 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <fstream>
#include <string>

// Function to print an error message and exit 
int printErrorAndExit(const std::string& errorMessage) {
    std::cerr << "sed encountered an error: " << errorMessage << '\n';
    return 1;
}

int main(int argc, char** argv) {
	// Check the number of arguments
    if (argc != 4) {
        return printErrorAndExit(
            "Incorrect number of arguments provided.\n"
            "Usage: ./sed <inputFileName> <searchString> <replaceString>"
        );
    }

    std::string inputFileName(argv[1]);
    std::string searchString(argv[2]);
    std::string replaceString(argv[3]);

	// Check if the search string is empty
    if (searchString.empty()) {
        return printErrorAndExit(
            "The search string cannot be empty. Please provide a valid string."
        );
    }

	// Open the input file
    std::ifstream inputFile(inputFileName.c_str());
    if (!inputFile.is_open()) {
        return printErrorAndExit(
            "Unable to open the specified file. \n"
			"Please check if the file exists and has read permissions."
        );
    }

	// Create the output file
    std::string outputFileName = inputFileName + ".replaced";
    std::ofstream outputFile(outputFileName.c_str());
    if (!outputFile.is_open()) {
        return printErrorAndExit(
            "Unable to create the output file. Please check your write permissions."
        );
    }

	// Process line by line
    std::string currentLine;
    while (std::getline(inputFile, currentLine)) {
        size_t foundPos = 0;
        while ((foundPos = currentLine.find(searchString, foundPos)) != std::string::npos) {
            currentLine.erase(foundPos, searchString.length());
            currentLine.insert(foundPos, replaceString);
            foundPos += replaceString.length();
        }
        outputFile << currentLine << '\n';
    }

	// Success message
    std::cout << "File processed successfully! The new file is: " << outputFileName << std::endl;

    return 0;
}

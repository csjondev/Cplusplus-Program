#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <unordered_map>

// Structure to represent a Course
struct Course {
    std::string courseCode;
    std::string courseName;
    std::vector<std::string> prerequisites;
};

// Function to load course data from file
void loadCourseData(const std::string& filename, std::unordered_map<std::string, Course>& courseMap) {
    std::ifstream file(filename);
    std::string line;

    if (file.is_open()) {
        // Read data line by line from the file
        while (std::getline(file, line)) {
            std::istringstream iss(line);
            std::string code, name, prereqList;

            // Extract course code, name, and prerequisites from each line
            if (std::getline(iss, code, ',')) {
                if (std::getline(iss, name, ',')) {
                    Course course;
                    course.courseCode = code;
                    course.courseName = name;

                    // Extract and store prerequisites for the course
                    if (std::getline(iss, prereqList)) {
                        std::istringstream prereqStream(prereqList);
                        std::string prereq;
                        while (std::getline(prereqStream, prereq, ',')) {
                            course.prerequisites.push_back(prereq);
                        }
                    }

                    // Store the course in the map using course code as the key
                    courseMap[course.courseCode] = course;
                }
            }
        }
        file.close();
        std::cout << "Course data loaded successfully." << std::endl;
    }
    else {
        std::cout << "Error: Unable to open the file." << std::endl;
    }
}

// Function to display the list of courses
void displayCourses(const std::unordered_map<std::string, Course>& courseMap) {
    // Retrieve course codes and sort them
    std::vector<std::string> courseCodes;
    for (const auto& pair : courseMap) {
        courseCodes.push_back(pair.first);
    }
    std::sort(courseCodes.begin(), courseCodes.end());

    // Display the list of courses (code and name)
    std::cout << "Course List:" << std::endl;
    for (const auto& code : courseCodes) {
        std::cout << courseMap.at(code).courseCode << ": " << courseMap.at(code).courseName << std::endl;
    }
}

// Function to display information for a specific course
void displayCourseInformation(const std::unordered_map<std::string, Course>& courseMap, const std::string& courseCode) {
    // Check if the course code exists in the map
    if (courseMap.find(courseCode) != courseMap.end()) {
        const Course& course = courseMap.at(courseCode);
        // Display course title
        std::cout << "Course Title: " << course.courseName << std::endl;
        // Display prerequisites, if any
        if (!course.prerequisites.empty()) {
            std::cout << "Prerequisites: ";
            for (const auto& prereq : course.prerequisites) {
                std::cout << prereq << ", ";
            }
            std::cout << std::endl;
        }
        else {
            std::cout << "No prerequisites for this course." << std::endl;
        }
    }
    else {
        std::cout << "Course not found." << std::endl;
    }
}

int main() {
    std::unordered_map<std::string, Course> courseMap;

    std::string filename = "course_list.txt"; // Course input list
    loadCourseData(filename, courseMap);

    // Menu-driven loop for user interaction
    while (true) {
        std::cout << "\nMenu:\n";
        std::cout << "1. Show Course List\n";
        std::cout << "2. Show Course Information\n";
        std::cout << "3. Exit\n";
        std::cout << "Enter your choice: ";

        int choice;
        std::cin >> choice;

        switch (choice) {
        case 1:
            displayCourses(courseMap);
            break;
        case 2: {
            std::string courseCode;
            std::cout << "Enter the course code: ";
            std::cin >> courseCode;
            displayCourseInformation(courseMap, courseCode);
            break;
        }
        case 3:
            std::cout << "Exiting the program.\n";
            return 0;
        default:
            std::cout << "Invalid choice. Please enter a valid option.\n";
            break;
        }
    }

    return 0;
}

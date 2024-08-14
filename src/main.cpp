#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unistd.h>

void createProject(const std::string& projectName, const std::vector<std::string>& dependencies) {
    // Create project folder
    char buffer[FILENAME_MAX];
    std::string projectPath;
    // Get the current working directory
    if (getcwd(buffer, sizeof(buffer)) != nullptr) {
        projectPath = std::string(buffer) + "/" + projectName;
        std::cout << "buffer: " << buffer << std::endl;
        std::cout << "Position Choice worked: " << projectPath << std::endl;

    } else {
        projectPath = "/mnt/c/Users/fierz/Documents/LF/arbeiten/programming/" + projectName;
        std::cout << "Default location chosen for the project." << std::endl << "Default is: " << projectPath << std::endl;
    }
    std::string srcPath = projectPath + "/src";
    std::string buildPath = projectPath + "/build";
    std::string includePath = projectPath + "/include";
    std::string configPath = projectPath + "/config";
    std::string mainFilePath = srcPath + "/main.cpp";
    std::string cmakeFilePath = projectPath + "/CMakeLists.txt";

    std::cout << "Creating project folder: " << projectPath << std::endl;
    std::system(("mkdir -p " + srcPath).c_str());
    std::system(("mkdir -p " + buildPath).c_str());
    std::system(("mkdir -p " + includePath).c_str());
    std::system(("mkdir -p " + configPath).c_str());
    std::system(("mkdir -p " + configPath).c_str());

    // Create main.cpp file
    std::ofstream mainFile(mainFilePath);
    mainFile << "#include <iostream>\n\n";
    mainFile << "int main() {\n";
    mainFile << "    std::cout << \"Hello, " << projectName << "!\" << std::endl;\n";
    mainFile << "    return 0;\n";
    mainFile << "}\n";
    mainFile.close();

    // Create CMakeLists.txt file
    std::ofstream cmakeFile(cmakeFilePath);
    cmakeFile << "cmake_minimum_required(VERSION 3.10)\n\n";
    cmakeFile << "project(" << projectName << ")\n\n";
    cmakeFile << "include_directories(" << " include)\n\n";
    cmakeFile << "add_executable(" << projectName << " src/main.cpp)\n\n";
    for (const std::string& dependency : dependencies) {
        cmakeFile << "find_package(" << dependency << " REQUIRED)\n";
        cmakeFile << "target_link_libraries(" << projectName << " " << dependency << ")\n\n";
    }
    cmakeFile.close();

    std::cout << "Project created successfully!" << std::endl;
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <project_name> [<dependency1> <dependency2> ...]" << std::endl;
        return 1;
    }

    std::string projectName = argv[1];
    std::vector<std::string> dependencies;
    for (int i = 2; i < argc; ++i) {
        dependencies.push_back(argv[i]);
    }

    createProject(projectName, dependencies);

    return 0;
}

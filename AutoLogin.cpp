#include "API/API.hpp"
#include "Utils/Utils.hpp"
#include "Utils/json/json.hpp"
#include <fstream>
#include <iostream>

using json = nlohmann::json;

void AUTH::SaveInfo(std::string username, std::string password) {

	std::string preset = ("{ 'username': '" + username + "', 'password': '" +  Utils::AESEncrypt(password, "12345678909876541234567890987654", "0123456789098765") + "'}");

	std::ofstream file("C:\\Windows\\RE.bin", std::ios::binary);



	file << preset << std::endl;

	file.close();

	std::ifstream MyFile;

	MyFile.open("C:\\Windows\\RE.bin");
	if (!MyFile) {
		MessageBoxA(NULL, "Erro ao salvar", "Erro", NULL);
		return;
	}
	
}

void AUTH::AutoLogin() {
	std::ifstream file;

	std::string credentials;

	file.open("C:\\Windows\\RE.bin", std::ios::binary);

	if (file.is_open()) {
		while (std::getline(file, credentials)) {
			std::cout << credentials << std::endl;
		}
	}

	//if (!file) return;

	std::string result = credentials;
    MessageBoxA(NULL, result.c_str(), "Titulo", NULL);
	json j;

	j = json::parse(result);
	std::string username = j["username"];
	std::string password = j["parssword"];

	

}


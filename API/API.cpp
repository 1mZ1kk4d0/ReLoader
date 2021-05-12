#include <iostream>
#include <fstream>
#include <Windows.h>
#include "API.hpp"
#include "../Utils/curl/curl.h"
#include "../Utils/json/json.hpp"
#include "../Utils/Utils.hpp"
#include "../Utils/encrypts/xor.hpp"
#pragma comment(lib, "Normaliz.lib")
#pragma comment(lib, "Ws2_32.lib")
#pragma comment(lib, "Wldap32.lib")
#pragma comment(lib, "Crypt32.lib")
#pragma comment(lib, "advapi32.lib")



using json = nlohmann::json;

std::string token = "";

static size_t my_write(void* buffer, size_t size, size_t nmemb, void* param) {
	std::string& text = *static_cast<std::string*>(param);
	size_t totalsize = size * nmemb;
	text.append(static_cast<char*>(buffer), totalsize);
	return totalsize;
}


char* AUTH::getImageUser() {
	try {
		CURL* curl;
		CURLcode res;
		std::string resultado;

		curl = curl_easy_init();

		if (curl) {

			curl_easy_setopt(curl, CURLOPT_URL, "http://localhost/api/v1/auth/image");
			curl_easy_setopt(curl, CURLOPT_PROXY, NULL);
			curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, my_write);
			curl_easy_setopt(curl, CURLOPT_POST, true);
			curl_easy_setopt(curl, CURLOPT_POSTFIELDS, "hwid=" + Utils::getHWID());
			curl_easy_setopt(curl, CURLOPT_WRITEDATA, &resultado);
			res = curl_easy_perform(curl);

			curl_easy_cleanup(curl);

			json j;
			j = json::parse(resultado);

			std::string us = j["USER"]["username"];
			std::string ex = j["USER"]["expire"];


			int STATUS = j["STATUS"]["status"];
			std::string Token = Utils::AESDecrypt(j["STATUS"]["token"], "12345678909876543212345678909876", "1234567890987654");

		}
	}
	catch (const std::string e) {

		MessageBoxA(NULL, "Something went wrong, Contact an Administrator!", "Flux Cheats", NULL);
		return false;
	}
	return false;
}

/*BYTE AUTH::getProfile() {
	try
	{
		CURL* curl;
		CURLcode res;
		BYTE logo[] = "";


		curl_easy_setopt(curl, CURLOPT_URL, "http://localhost/api/v1/auth/user");
		curl_easy_setopt(curl, CURLOPT_PROXY, NULL);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, my_write);
		curl_easy_setopt(curl, CURLOPT_POST, true);
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, "&hwid=" + Utils::AESEncrypt(Utils::getHWID(), "12345678909876543212345678909876", "1234567890987654"));
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &logo);

		curl = curl_easy_init();

		if (curl) {

		}
	}
	catch (const std::exception&)
	{

	}
}*/


//Codigo da Authenticação Do Usuario!
bool AUTH::AuthUser(const std::string username, const std::string password) {
	try {
		CURL* curl;
		CURLcode res;
		std::string resultado;

		curl = curl_easy_init();

		if (curl) {
			curl_easy_setopt(curl, CURLOPT_URL, "http://localhost/api/v1/auth");
			curl_easy_setopt(curl, CURLOPT_PROXY, NULL);
			curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, my_write);
			curl_easy_setopt(curl, CURLOPT_POST, true);
			curl_easy_setopt(curl, CURLOPT_POSTFIELDS, "username=" + username + "&password=" + Utils::AESEncrypt(password, "12345678909876543212345678909876", "1234567890987654").c_str() + "&hwid=" + Utils::AESEncrypt(Utils::getHWID(), "12345678909876543212345678909876", "1234567890987654").c_str());
			curl_easy_setopt(curl, CURLOPT_WRITEDATA, &resultado);
			res = curl_easy_perform(curl);

			curl_easy_cleanup(curl);

			json j;
			j = json::parse(resultado);

			std::string us = j["USER"]["username"];
			std::string ex = j["USER"]["expire"];


			int STATUS = j["STATUS"]["status"];
			std::string Token = Utils::AESDecrypt(j["STATUS"]["token"], "12345678909876543212345678909876", "1234567890987654");


			switch ((AUTH::RequestType)STATUS)
			{

			case AUTH::OK: {
				user = us;
				expiration = ex;
				MessageBoxA(NULL, ("Welcome " + us).c_str(), "Flux  Cheats", MB_SETFOREGROUND);
				return true;
			}
			break;

			case AUTH::INVALID_USER: {
				MessageBoxA(NULL, "Invalid User, Plase try Again", "Flux Cheats", MB_SETFOREGROUND);
				return false;
			}
			break;

			case AUTH::INVALID_PASSWORD: {
				MessageBoxA(NULL, "Wrong Password", "Flux Cheats", MB_SETFOREGROUND);
				return false;
			}
			break;

			case AUTH::INVALID_HWID: {
				MessageBoxA(NULL, "Wrong HWID!", "Flux Cheats", MB_SETFOREGROUND);
				exit(0);
			}
			break;

			case AUTH::BANNED: {
				MessageBoxA(NULL, "You're banned!", "Flux Cheats", MB_SETFOREGROUND);
				return false;
			}
			break;

			default:
				return false;
				break;
			}
		}
	}
	catch (const std::string e) {

		MessageBoxA(NULL, "Something went wrong, Contact an Administrator!", "Revolution Cheats", NULL);
		return false;
	}
	return false;
}

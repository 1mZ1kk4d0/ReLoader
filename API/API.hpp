#pragma once
#include <iostream>
#include <cstring>
#include <future>
#include "../Utils/mmp/injector/inject.h"
#include "../Utils/json/json.hpp"
namespace AUTH {
	bool AuthUser(const std::string username, const std::string password);
	char* getImageUser();
	void SaveInfo(std::string username, std::string password);
	void AutoLogin();

	enum RequestType {
		OK,
		INVALID_USER,
		INVALID_PASSWORD,
		INVALID_HWID,
		BANNED
	};
}

static std::string user = "";
static std::string expiration = "";
static std::string titles = "Flux Cheats";

static char image_profile[] = { NULL };
static char cheat[] = { NULL };





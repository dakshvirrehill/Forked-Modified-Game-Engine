///-------------------------------------------------------------------------------------------------
// file: FileSystem.h
//
// author: William Barry
// date: 10/28/2019
//
// summary:	The File System
///-------------------------------------------------------------------------------------------------
#ifndef _FILESYSTEM_H_
#define _FILESYSTEM_H_
#pragma once

#include "ISystem.h"

class FileSystem final : public ISystem
{
private:
	std::map<STRCODE, json::JSON> fileData;
	std::list<STRCODE> protectedFiles;
	std::list<STRCODE> removedFiles;
	STRCODE currentLevel;

protected:
    void initialize() override;
    void update(float deltaTime) override;

	void load(std::string fileName, bool protectedFile);
	void unload(std::string fileName);
	STRCODE getCurrentLevel();

    friend class GameEngine;

public:
	DECLARE_SINGLETON(FileSystem)
};
#endif
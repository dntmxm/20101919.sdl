#include "StateParser.h"
#include "TextureManager.h"
#include "Game.h"
#include "GameObjectFactory.h"
#include <string>
#include <vector>

GameObjectFactory* GameObjectFactory::s_pInstance = 0;

bool StateParser::parseState(const char *stateFile,
	std::string stateID, std::vector<GameObject*> *pObjects,
	std::vector<std::string> *pTextureIDs)
{
	XMLDocument xmlDoc;
	if (tinyxml2::XMLError::XML_SUCCESS != xmlDoc.LoadFile(stateFile))
	{
		std::cerr << xmlDoc.ErrorName() << "\n";
		return false; 
	}

	XMLNode* pStateRoot = 0;
	XMLNode* node = xmlDoc.FirstChild();

	std::string str;
	for (XMLNode* child = node->FirstChild(); child != 0; child = child->NextSibling())
	{
		str = child->Value();
		if (str.compare(stateID) == 0)
		{
			pStateRoot = child;
		}
	}
	XMLElement* pTextureRoot = 0;
	for (XMLElement* e = pStateRoot->FirstChildElement(); e != NULL;
		e = e->NextSiblingElement()) {
		if (e->Value() == std::string("TEXTURES")) {
			pTextureRoot = e;
		}
	}
	parseTextures(pTextureRoot, pTextureIDs);

	XMLElement* pObjectRoot = 0;

	for (XMLElement* e = pStateRoot->FirstChildElement(); e != NULL;
		e = e->NextSiblingElement()) {
		if (e->Value() == std::string("OBJECTS")) {
			pObjectRoot = e;
		}
	}
	parseObjects(pObjectRoot, pObjects);

	return true;
}

void StateParser::parseTextures(XMLElement* pStateRoot,
	std::vector<std::string> *pTextureIDs)
{
	for (XMLElement* e = pStateRoot->FirstChildElement(); e != NULL;
		e = e->NextSiblingElement())
	{
		std::string filenameAttribute = e->Attribute("filename");
		std::string idAttribute = e->Attribute("ID");
		pTextureIDs->push_back(idAttribute);
		TheTextureManager::Instance()->load(filenameAttribute,
			idAttribute, TheGame::Instance()->getRenderer());
	}
}

void StateParser::parseObjects(XMLElement* pStateRoot,
	std::vector<GameObject*> *pObjects)
{
	for (XMLElement* e = pStateRoot->FirstChildElement(); e != NULL;
		e = e->NextSiblingElement())
	{
		int x, y, width, height, numFrames, callbackID, animSpeed;
		std::string textureID;
		x = e->IntAttribute("x");
		y = e->IntAttribute("y");
		width = e->IntAttribute("width");
		height = e->IntAttribute("height");
		numFrames = e->IntAttribute("numFrames");
		callbackID = e->IntAttribute("callbackID");
		animSpeed = e->IntAttribute("animSpeed");

		textureID = e->Attribute("textureID");
		GameObject* pGameObject = TheGameObjectFactory::Instance()
			->create(e->Attribute("type"));
		pGameObject->load(new LoaderParams
			(x, y, width, height, textureID, numFrames, callbackID, animSpeed));
		pObjects->push_back(pGameObject);
	}
}
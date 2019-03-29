#include "GameLoader.h"

GameLoader::GameLoader(){};
GameLoader::~GameLoader(){};
void GameLoader::parseJSONData(std::string const & jsonData, shared_ptr<GameData> &data)
{
	// Retrieve the main root object
	JSONValue * value = JSON::Parse(jsonData.c_str());
	JSONObject root = value->AsObject();

	// Load the global settings object
	JSONObject globalSettings = root[L"global_settings"]->AsObject();
	JSONArray tempTokens = globalSettings[L"tokens"]->AsArray();
	for (int i = 0; i < 10; i++)
	{
		JSONObject temp = tempTokens[i]->AsObject();
		data->tokens[i] = temp[L"token"]->AsNumber();
	}
	JSONArray tempCredits = globalSettings[L"credits"]->AsArray();
	for (int i = 0; i < 10; i++)
	{
		JSONObject tempO = tempCredits[i]->AsObject();
		data->credits[i] = tempO[L"credit"]->AsNumber();
	}

	//Portal
	JSONObject tempPortalPos = globalSettings[L"portal_position"]->AsObject();
	data->portalPositionX = tempPortalPos[L"x"]->AsNumber();
	data->portalPositionY = tempPortalPos[L"y"]->AsNumber();
	data->portalImage = m_json.wStringToString(globalSettings[L"portal_image"]->AsString());

	//Base tower
	JSONObject tempBasePos = globalSettings[L"base_position"]->AsObject();
	data->basePositionX = tempBasePos[L"x"]->AsNumber();
	data->basePositionY = tempBasePos[L"y"]->AsNumber();
	data->baseImage = m_json.wStringToString(globalSettings[L"base_image"]->AsString());

	//Enemies per wave
	JSONArray tempWaveCount = globalSettings[L"waves"]->AsArray();
	for (int i = 0; i < 10; i++)
	{
		JSONObject temp = tempWaveCount[i]->AsObject();
		data->walkingNum[i] = temp[L"walking"]->AsNumber();
		data->flyingNum[i] = temp[L"flying"]->AsNumber();
		data->mountedNum[i] = temp[L"mounted"]->AsNumber();
	}

	//Overlays
	data->menuImage = m_json.wStringToString(globalSettings[L"menu_image_file"]->AsString());
	data->splashImage = m_json.wStringToString(globalSettings[L"splash_image_file"]->AsString());
	data->creditsImageOne = m_json.wStringToString(globalSettings[L"overlay_credits_1"]->AsString());
	data->creditsImageTwo = m_json.wStringToString(globalSettings[L"overlay_credits_2"]->AsString());
	data->creditsImageThree = m_json.wStringToString(globalSettings[L"overlay_credits_3"]->AsString());

	//Game
	JSONObject tempScreen = globalSettings[L"screen"]->AsObject();
	data->screenWidth = tempScreen[L"screen_width"]->AsNumber();
	data->screenHeight = tempScreen[L"screen_height"]->AsNumber();

	//Headings
	data->menuHeading = m_json.wStringToString(globalSettings[L"menu_heading"]->AsString());
	data->extrasHeading = m_json.wStringToString(globalSettings[L"extras_heading"]->AsString());
	data->modeHeading = m_json.wStringToString(globalSettings[L"mode_menu_heading"]->AsString());
	data->optionsHeading = m_json.wStringToString(globalSettings[L"options_heading"]->AsString());
	data->pauseHeading = m_json.wStringToString(globalSettings[L"pause_heading"]->AsString());

	//Font
	data->font = m_json.wStringToString(globalSettings[L"font"]->AsString());

	//Buttons
	data->menuButtonImage = m_json.wStringToString(globalSettings[L"menu_button_image"]->AsString());
	data->towerButtonImage = m_json.wStringToString(globalSettings[L"tower_buttons_image"]->AsString());
	data->buttonSounds = m_json.wStringToString(globalSettings[L"button_sound"]->AsString());
	data->pauseButtonImage = m_json.wStringToString(globalSettings[L"pause_button_Image"]->AsString());

	//Music
	data->gameMusic = m_json.wStringToString(globalSettings[L"music"]->AsString());
}

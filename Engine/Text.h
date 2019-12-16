///-------------------------------------------------------------------------------------------------
// file: Text.h
//
// author: Justin Hole
// date: 11/29/2019
//
// summary:	A component that renders text onto the screen
///-------------------------------------------------------------------------------------------------

#pragma once

#include "Component.h"
#include "IRenderable.h"

class Text : public Component, IRenderable
{
	DECLARE_DYNAMIC_DERIVED_CLASS(Text, Component)
	sf::Vector2f offset;
	sf::Text text;
	std::string fontAssetGUID = "";
	STRCODE fontAssetID = -1;
	std::string string = "";
	int characterSize = 24;
	sf::Color fillColor;
	sf::Text::Style style = sf::Text::Style::Regular;
	bool isTextStrikeThrough = false;
	bool isTextUnderlined = false;
protected:
	void update(float deltaTime) override;
	void initialize() override;
	virtual void render(sf::RenderWindow* _window) override;
public:
	void updatePosition();
	void load(json::JSON& node) override;
	Text() = default;
	~Text();
	void setText(std::string inString);
	void setText(sf::Font& inFont, std::string inString, int inCharacterSize, sf::Color inFillColor, sf::Text::Style inStyle);
	void setIsStrikeThrough(bool inIsTextStrikeThrough) { isTextStrikeThrough = inIsTextStrikeThrough; }
	void setIsUnderlined(bool inIsTextUnderlined) { isTextUnderlined = inIsTextUnderlined; }
	void setTextString(std::string& inString) { string = inString; }
};


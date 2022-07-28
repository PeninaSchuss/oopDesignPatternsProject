#pragma once
//---------------------------------------------------------------------------------------
#include<vector>
#include "Utilities.h"
//------------------------------
class Graphics {
public:
	static Graphics& getGraphics();
	~Graphics() = default;
	sf::Font& getFont() { return m_font; }//Cant be const
	sf::Texture& getTexture(int i) { return m_tex[i]; }//Cant be const
	sf::SoundBuffer& getSound(int index) { return (m_soundBufferVec[index]); }//Cant be const
	std::vector<std::unique_ptr<sf::Sound>>& getSoundVec() { return m_soundVec; }//Cant be const
	sf::RenderWindow& getWindow(){ return m_window; }//Cant be const
	void createWindow();
private:
	Graphics();
	Graphics(const Graphics&) = default;
	std::vector<sf::Texture> m_tex;
	std::vector<sf::Text> m_text;
	std::vector<sf::SoundBuffer> m_soundBufferVec;
	std::vector<std::unique_ptr<sf::Sound>> m_soundVec;
	sf::Font m_font;
	sf::RenderWindow m_window;
};


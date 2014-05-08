#ifndef PRINT_H
#define PRINT_H

#include <SFML/Graphics.hpp>
#include <Map.h>

class print
{
    public:
        print(sf::RenderWindow &vapp);
        void affiche(Map* gamemap);
        int registerSprite(string name, int id = 0);
        const sf::Texture& getTexture(int id);
        const sf::Texture& getTexture(string name);
        virtual ~print();
    protected:
        sf::RenderWindow *app;
        std::map<int, const sf::Texture> TextureMap;
        std::map<string, int> NameMap;
        int max_id;
        sf::Sprite sprite;
    private:
};

#endif // PRINT_H

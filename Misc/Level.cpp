//
// Created by kgbcomrade on 4/29/20.
//

#include <tinyxml/tinyxml.h>
#include <iostream>
#include "Level.h"

bool Level::loadFromFile(const std::string& filename) {
    TiXmlDocument levelFile(filename.c_str());//��������� ���� � TiXmlDocument

    // ��������� XML-�����
    if (!levelFile.LoadFile())//���� �� ������� ��������� �����
    {
        std::cout << "Loading level \"" << filename << "\" failed." << std::endl;//������ ������
        return false;
    }

    // �������� � ����������� map
    TiXmlElement map = *levelFile.FirstChildElement("map");

    // ������ �����: <map version="1.0" orientation="orthogonal"
    // width="10" height="10" tilewidth="34" tileheight="34">
    size.x = (int) strtol(map.Attribute("width"), nullptr, 10);//��������� �� ����� ����� �� ��������
    size.y = (int) strtol(map.Attribute("height"), nullptr, 10);//�� ��������, ������� �������� ��� ������ �
    tileSize.x = (int) strtol(map.Attribute("tilewidth"), nullptr, 10);//������� ���������
    tileSize.y = (int) strtol(map.Attribute("tileheight"), nullptr, 10);

    // ����� �������� �������� � ������������� ������� �����
    TiXmlElement tileSetElement = *map.FirstChildElement("tileset");
    firstTileID = (int) strtol(tileSetElement.Attribute("firstgid"), nullptr, 10);

    // source - ���� �� �������� � ���������� image
    TiXmlElement image = *tileSetElement.FirstChildElement("image");
    std::string imagePath = image.Attribute("source");

    // �������� ��������� �������
    sf::Image img;

    if (!img.loadFromFile(imagePath))
    {
        std::cout << "Failed to load tile sheet." << std::endl;//���� �� ������� ��������� �������-������� ������ � �������
        return false;
    }


    img.createMaskFromColor(sf::Color(255, 255, 255));//��� ����� �����.������ ��� �����
    tileSetImage = new sf::Texture();
    tileSetImage->loadFromImage(img);
    tileSetImage->setSmooth(false);//�����������

    // �������� ���������� �������� � ����� ��������
    size_t columns = tileSetImage->getSize().x / tileSize.x;
    size_t rows = tileSetImage->getSize().y / tileSize.y;

    // ������ �� ��������������� ����������� (TextureRect)
    std::vector<sf::Rect<int>> subRects;

    for (size_t y = 0; y < rows; y++)
        for (size_t x = 0; x < columns; x++)
        {
            sf::Rect<int> rect;

            rect.top = y * tileSize.y;
            rect.height = tileSize.y;
            rect.left = x * tileSize.x;
            rect.width = tileSize.x;

            subRects.push_back(rect);
        }

    TiXmlElement* layerElement = map.FirstChildElement("layer");
    while (layerElement)
    {
        auto *layer = new Layer;

        if (layerElement->Attribute("opacity") != nullptr)
        {
            layer->opacity = (int)(strtod(layerElement->Attribute("opacity"), nullptr) * 255);
        }
        else
        {
            layer->opacity = 255;
        }

        TiXmlElement* layerDataElement;
        layerDataElement = layerElement->FirstChildElement("data");

        if (layerDataElement == nullptr)
        {
            std::cout << "Bad map. No layer information found." << std::endl;
            return false;
        }

        TiXmlElement* tileElement;
        tileElement = layerDataElement->FirstChildElement("tile");

        if (tileElement == nullptr)
        {
            std::cout << "Bad map. No tile information found." << std::endl;
            return false;
        }

        int x = 0;
        int y = 0;

        while (tileElement)
        {
            if(tileElement->Attribute("gid") == nullptr) {
                tileElement = tileElement->NextSiblingElement("tile");
                continue;
            }
            int tileGID = (int) strtol(tileElement->Attribute("gid"), nullptr, 10);
            int subRectToUse = tileGID - firstTileID;

            // ������������� TextureRect ������� �����
            if (subRectToUse >= 0)
            {
                auto *sprite = new sf::Sprite(*tileSetImage);
                sprite->setTextureRect(subRects[subRectToUse]);
                sprite->setPosition((float) x * tileSize.x, (float) y * tileSize.y);
                sprite->setColor(sf::Color(255, 255, 255, layer->opacity));

                layer->tiles.push_back(sprite);//���������� � ���� �strtod(layerElement->Attribute("opacity"), nullptr)������ ������
            }

            tileElement = tileElement->NextSiblingElement("tile");

            x++;
            if (x >= size.x)
            {
                x = 0;
                y++;
                if (y >= size.y)
                    y = 0;
            }
        }

        layers.push_back(layer);

        layerElement = layerElement->NextSiblingElement("layer");
    }

    // ������ � ���������
    TiXmlElement* objectGroupElement;

    // ���� ���� ���� ��������
    if (map.FirstChildElement("objectgroup") != nullptr)
    {
        objectGroupElement = map.FirstChildElement("objectgroup");
        while (objectGroupElement)
        {
            //  ��������� <object>
            TiXmlElement* objectElement;
            objectElement = objectGroupElement->FirstChildElement("object");

            while (objectElement)
            {

                // �������� ��� ������ - ���, ���, �������, � ��
                std::string objectType;
                if (objectElement->Attribute("type") != nullptr)
                {
                    objectType = objectElement->Attribute("type");
                }
                std::string objectName;
                if (objectElement->Attribute("name") != nullptr)
                {
                    objectName = objectElement->Attribute("name");
                }
                int x = (int) strtol(objectElement->Attribute("x"), nullptr, 10);
                int y = (int) strtol(objectElement->Attribute("y"), nullptr, 10);

                int width, height;

                sf::Sprite sprite;
                sprite.setTexture(*tileSetImage);
                sprite.setTextureRect(sf::Rect<int>(0, 0, 0, 0));
                sprite.setPosition((float)x, (float)y);

                if (objectElement->Attribute("width") != nullptr)
                {
                    width = (int) strtol(objectElement->Attribute("width"), nullptr, 10);
                    height = (int) strtol(objectElement->Attribute("height"), nullptr, 10);
                }
                else
                {
                    width = subRects[(int) strtol(objectElement->Attribute("gid"), nullptr, 10) - firstTileID].width;
                    height = subRects[(int) strtol(objectElement->Attribute("gid"), nullptr, 10) - firstTileID].height;
                    sprite.setTextureRect(subRects[(int) strtol(objectElement->Attribute("gid"), nullptr, 10) - firstTileID]);
                }

                auto *object = new Object;
                object->name = objectName;
                object->type = objectType;
                object->sprite = sprite;

                sf::Rect <float> objectRect;
                objectRect.top = y;
                objectRect.left = x;
                objectRect.height = height;
                objectRect.width = width;
                object->rect = objectRect;

                TiXmlElement* properties;
                properties = objectElement->FirstChildElement("properties");
                if (properties != nullptr)
                {
                    TiXmlElement* prop;
                    prop = properties->FirstChildElement("property");
                    if (prop != nullptr)
                    {
                        while (prop)
                        {
                            std::string propertyName = prop->Attribute("name");
                            std::string propertyValue = prop->Attribute("value");

                            object->properties[propertyName] = propertyValue;

                            prop = prop->NextSiblingElement("property");
                        }
                    }
                }


                objects.push_back(object);

                objectElement = objectElement->NextSiblingElement("object");
            }
            objectGroupElement = objectGroupElement->NextSiblingElement("objectgroup");
        }
    }
    else
    {
        std::cout << "No object layers found..." << std::endl;
    }

    return true;
}

Object* Level::getObject(const std::string& name) {
    for(auto &i : objects) {
        if(i->name == name)
            return i;
    }
    return new Object();
}

std::vector<Object*> Level::getObjects(const std::string& name) {
    std::vector<Object*> res;
    for(auto &i : objects) {
        if(i->name == name)
            res.push_back(i);
    }
    return res;
}

std::vector<Object*> Level::getAllObjects() {
    return objects;
}

void Level::draw(sf::RenderWindow &window) {
    for(auto & layer : layers)
        for(const auto &tile : layer->tiles)
            window.draw(*tile);
}

sf::Vector2i Level::getTileSize() {
    return tileSize;
}

Level::~Level() {
    delete tileSetImage;
    for(auto *i : objects)
        delete i;
    for(auto *i : layers)
        delete i;


}



#include "Level.h"

Level::Level(Texture* tileset, Vector2i tileSize, int levelNumber) : tileset(tileset), tileSize(tileSize), levelNumber(levelNumber), filename("")
{
	filename = "data/levels/" + to_string(levelNumber) + ".csv";

	FileInputStream stream;

	stream.open(filename);

	char newchar = 'a';
	int newcharInt;

	int newnumchar;
	string newnumString = "";

	unsigned int widthcounter = 0;
	unsigned int prevWidth = 0;
	unsigned int heightcounter = 0;

	for (int i = 0; i < stream.getSize(); i++)
	{
		stream.read(&newchar, 1);
		newcharInt = (int)newchar;
		newnumchar = newcharInt - 48;

		if (newnumchar <= 9 && newnumchar >= 0) //if the new character is a number then add the new number digit to the end of newnumstring
		{
			newnumString += to_string(newnumchar);
		}

		if (newcharInt == 59)
		{
			tileType.push_back(stoi(newnumString));
			newnumString = "";

			widthcounter++;
		}

		if (newcharInt == 10)
		{
			if (newnumString == "")
				cout << "Warning! Please remove semi-colon from the end of row " + to_string(heightcounter) + " to avoid unexcpected behavior.\n";
			tileType.push_back(stoi(newnumString));
			newnumString = "";

			if (heightcounter > 0 && prevWidth != widthcounter)
				cout << "Warning! Row lengths are different in level(" << prevWidth << ", " << widthcounter << "). This may cause unexpected behavior.";

			prevWidth = widthcounter;
			widthcounter = 0;
			heightcounter++;
		}
	}
	if (heightcounter == 18 && prevWidth <= 256 && prevWidth >= 32)
	{
		levelSize = Vector2u(prevWidth + 1, heightcounter);
	}
	else
	{
		cout << "Error: Level height must be 18 tiles and level width must be between 32 and 256 tiles.\n";
		levelSize = Vector2u(0, 0);
	}
	Load();
}

Level::Level() : tileset(nullptr)
{
}

Level::~Level()
{
}

void Level::Load()
{
	for (int i = 0; i < levelSize.y; i++)
	{
		for (int j = 0; j < levelSize.x; j++)
		{
			unsigned int tileNumber = i * levelSize.x + j;

			if (tileNumber < tileType.size())
			{
				Vector2u tilesetSize = Vector2u(tileset->getSize().x / tileSize.x, tileset->getSize().y / tileSize.y);
				Vector2u tilePosition;
				if (tileType.at(tileNumber) == 0)
				{
					tilePosition = Vector2u(0, 0);
				}
				else
				{
					tilePosition = Vector2u(fmod(tileType.at(tileNumber), tilesetSize.x), floor(tileType.at(tileNumber) / tilesetSize.x));
				}

				Vector2i position = Vector2i(j, i);

				tile.push_back(Tile(tileset, tileSize, tilePosition, position));
			}
		}
	}
}

void Level::Unload()
{
	
}

void Level::Draw(RenderWindow& window)
{
	for (Tile& tile : tile)
	{
		bool a = (tile.getX() < window.getView().getCenter().x + window.getView().getSize().x / 2 + tileSize.x);
		bool b = (tile.getX() > window.getView().getCenter().x - window.getView().getSize().x / 2 - tileSize.x);
		bool c = (tile.getY() < window.getView().getCenter().y + window.getView().getSize().y / 2 + tileSize.y);
		bool d = (tile.getY() > window.getView().getCenter().y - window.getView().getSize().y / 2 - tileSize.y);
		if (a && b && c && d)
			tile.Draw(window);
	}
}

void Level::Collide(Character& character, float ledgeTreshold)
{
	Vector2f direction;

	for (int i = 0; i < tile.size(); i++)
	{
		if (tileType.at(i) != 0 && tileType.at(i) != 39 && tileType.at(i) != 49 && tileType.at(i) != 59)
		{
			bool a = (tile[i].getX() < character.GetPosition().x + character.GetSize().x + tileSize.x);
			bool b = (tile[i].getX() > character.GetPosition().x - character.GetSize().x - tileSize.x);
			bool c = (tile[i].getY() < character.GetPosition().y + character.GetSize().y / 2);
			bool d = (tile[i].getY() > character.GetPosition().y - character.GetSize().y);

			bool e = (tile[i].getX() < character.GetPosition().x + tileSize.x * ledgeTreshold);
			bool f = (tile[i].getX() > character.GetPosition().x - tileSize.x * ledgeTreshold);
			bool g = (tile[i].getY() < character.GetPosition().y + character.GetSize().y + tileSize.y);
			bool h = (tile[i].getY() > character.GetPosition().y - character.GetSize().y - tileSize.y);
			if ((a && b && c && d) || (e && f && g && h))
			{
				direction = tile[i].GetCollider().CheckCollision(character.GetCollider(), 1);
				if (direction != Vector2f(0, 0))
				{
					if (direction.y > 0)
						character.groundedClock.restart();
					character.OnCollision(direction);
				}
			}
		}
	}
}

FloatRect Level::GetBounds()
{
	return FloatRect(0, 0, tileSize.x * levelSize.x, tileSize.y * levelSize.y);
}

#pragma once
// All of the variables used here are defined in main - `lab_09.cpp`

std::pair<sf::Sprite, sf::RectangleShape> createPlatform(int pID, float x, float y) {
    std::pair<sf::Sprite, sf::RectangleShape> result;
    sf::Sprite platform;
    platform.setTexture(tilesTexture);
    platform.setTextureRect(tiles[pID]);
    platform.setScale(scale, scale);
    platform.setPosition(x, y);
    result.first = platform;
    sf::RectangleShape hitbox;
    hitbox.setPosition(x + hitboxes[pID].left * scale, y + hitboxes[pID].top * scale);
    hitbox.setSize(sf::Vector2f(hitboxes[pID].width * scale, hitboxes[pID].height * scale));
    hitbox.setFillColor(sf::Color::Red);
    result.second = hitbox;
    return result;
}

sf::RectangleShape joinHitboxes(std::vector<sf::RectangleShape> hitboxes) {
    // SHOULD BE MADE MORE UNIVERSAL, BUT THE DEMO DOESN'T NEED IT
    sf::RectangleShape hitbox;
    float min_x = std::min_element(hitboxes.begin(), hitboxes.end(),
                                   [](const auto& a, const auto& b) { return a.getGlobalBounds().left < b.getGlobalBounds().left; })->getGlobalBounds().left;
    sf::FloatRect rect = std::max_element(hitboxes.begin(), hitboxes.end(),
                                   [](const auto& a, const auto& b) { return a.getGlobalBounds().left+ a.getGlobalBounds().width < b.getGlobalBounds().left+ b.getGlobalBounds().width; })->getGlobalBounds();
    float max_x = rect.left + rect.width;
    float min_y = std::min_element(hitboxes.begin(), hitboxes.end(),
                                   [](const auto& a, const auto& b) { return a.getGlobalBounds().top < b.getGlobalBounds().top; })->getGlobalBounds().top;
    rect = std::max_element(hitboxes.begin(), hitboxes.end(),
                                   [](const auto& a, const auto& b) { return a.getGlobalBounds().top + a.getGlobalBounds().height < b.getGlobalBounds().top + b.getGlobalBounds().height; })->getGlobalBounds();
    float max_y = rect.top + rect.height;
    hitbox.setPosition(min_x, min_y);
    hitbox.setSize(sf::Vector2f(max_x - min_x, max_y - min_y));
    hitbox.setFillColor(sf::Color::Red);
    return hitbox;
}

void setupTiles() {
    if (!tilesTexture.loadFromFile("resources/map/tileset.png")) { throw "[TILES] TEXTURE FAILED TO LOAD"; }

    // TILE_PLATFORM_MEDIUM
    tiles.push_back(sf::IntRect(32, 16, 112, 96));
    hitboxes.push_back(sf::IntRect(16, 16, 80, 16));

    // TILE_PLATFORM_SMALL
    tiles.push_back(sf::IntRect(48, 112, 48, 48));
    hitboxes.push_back(sf::IntRect(0, 16, 48, 16));

    // TILE_LAND_LEFT
    tiles.push_back(sf::IntRect(32, 176, 48, 96));
    hitboxes.push_back(sf::IntRect(16, 16, 32, 16));

    // TILE_LAND_CENTER
    tiles.push_back(sf::IntRect(80, 176, 48, 96));
    hitboxes.push_back(sf::IntRect(0, 16, 48, 16));

    // TILE_LAND_RIGHT
    tiles.push_back(sf::IntRect(512, 176, 48, 96));
    hitboxes.push_back(sf::IntRect(0, 16, 32, 16));

    // TILE_TREE
    tiles.push_back(sf::IntRect(188, 32, 128, 128));

    // Tile IDs
    enum tileIDs {
        TILE_PLATFORM_MEDIUM,
        TILE_PLATFORM_SMALL,
        TILE_LAND_LEFT,
        TILE_LAND_CENTER,
        TILE_LAND_RIGHT,
        TILE_TREE
    };

    // Add tress
    sf::Sprite tree;
    tree.setTexture(tilesTexture);
    tree.setTextureRect(tiles[TILE_TREE]);
    tree.setScale(scale, scale);
    tree.setPosition(win_width - tiles[TILE_LAND_CENTER].width * scale - tiles[TILE_LAND_LEFT].width * scale,
                     win_height - tiles[TILE_LAND_CENTER].height * scale - tiles[TILE_TREE].height * scale + hitboxes[TILE_LAND_CENTER].height * scale);
    decorations.emplace_back(tree);
    tree.setScale(-scale, scale);
    tree.setPosition(tiles[TILE_LAND_CENTER].width* scale + tiles[TILE_LAND_LEFT].width * scale,
                     win_height - tiles[TILE_LAND_CENTER].height * scale - tiles[TILE_TREE].height * scale + hitboxes[TILE_LAND_CENTER].height * scale);
    decorations.emplace_back(tree);

    // Add platforms
    auto platform = createPlatform(TILE_LAND_CENTER, 0, win_height - tiles[TILE_LAND_CENTER].height * scale);
    decorations.emplace_back(platform.first);
    sf::RectangleShape obstacle = platform.second;
    sf::RectangleShape obstacleOverflow = platform.second;
    obstacleOverflow.setPosition(-obstacleOverflow.getSize().x, obstacleOverflow.getPosition().y);
    platform = createPlatform(TILE_LAND_RIGHT, tiles[TILE_LAND_CENTER].width * scale, win_height - tiles[TILE_LAND_CENTER].height * scale);
    decorations.emplace_back(platform.first);
    obstacles.emplace_back(joinHitboxes({obstacle, obstacleOverflow, platform.second}));

    platform = createPlatform(TILE_LAND_CENTER, win_width - tiles[TILE_LAND_CENTER].width * scale, win_height - tiles[TILE_LAND_CENTER].height * scale);
    decorations.emplace_back(platform.first);
    obstacle = platform.second;
    obstacleOverflow = platform.second;
    obstacleOverflow.setPosition(obstacleOverflow.getPosition().x + obstacleOverflow.getSize().x * 2, obstacleOverflow.getPosition().y);
    platform = createPlatform(TILE_LAND_LEFT, win_width - tiles[TILE_LAND_CENTER].width * scale - tiles[TILE_LAND_LEFT].width * scale, win_height - tiles[TILE_LAND_CENTER].height * scale);
    decorations.emplace_back(platform.first);
    obstacles.emplace_back(joinHitboxes({obstacle, obstacleOverflow, platform.second}));

    platform = createPlatform(TILE_PLATFORM_MEDIUM, win_width/3 - tiles[TILE_PLATFORM_MEDIUM].width*2/3 * scale,
                              win_height - tiles[TILE_LAND_CENTER].height * scale + tiles[TILE_PLATFORM_MEDIUM].height/3 * scale);
    decorations.emplace_back(platform.first);
    obstacles.emplace_back(platform.second);
    platform = createPlatform(TILE_PLATFORM_MEDIUM, win_width/2 - tiles[TILE_PLATFORM_MEDIUM].width/2 * scale,
                              win_height - tiles[TILE_LAND_CENTER].height * scale);
    decorations.emplace_back(platform.first);
    obstacles.emplace_back(platform.second);
    platform = createPlatform(TILE_PLATFORM_MEDIUM, win_width*2/3 - tiles[TILE_PLATFORM_MEDIUM].width/3 * scale,
                              win_height - tiles[TILE_LAND_CENTER].height * scale + tiles[TILE_PLATFORM_MEDIUM].height/3 * scale);
    decorations.emplace_back(platform.first);
    obstacles.emplace_back(platform.second);



    // platform = createPlatform(TILE_PLATFORM_MEDIUM, win_width / 2 - tiles[TILE_PLATFORM_MEDIUM].width / 2 * scale,
    //     win_height - 2 * tiles[TILE_LAND_CENTER].height * scale);
    // decorations.emplace_back(platform.first);
    // obstacles.emplace_back(platform.second);
}

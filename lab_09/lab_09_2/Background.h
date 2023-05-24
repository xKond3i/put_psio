#pragma once
// All of the variables used here are defined in main - `lab_09.cpp`

void setupBackground() {
    if (!skyTexture.loadFromFile("resources/map/sky.png")) { throw "[SKY] TEXTURE FAILED TO LOAD"; }
    float skyHeight = skyTexture.getSize().y;
    skyTexture.setRepeated(true);
    sky.setTexture(skyTexture);
    sky.setTextureRect(sf::IntRect(0, 0, win_width, skyHeight));
    sky.setOrigin(0, skyHeight);
    sky.setPosition(0, win_height);

    if (!cloudsTexture.loadFromFile("resources/map/clouds.png")) { throw "[CLOUDS] TEXTURE FAILED TO LOAD"; }
    float cloudsWidth = cloudsTexture.getSize().x;
    float cloudsHeight = cloudsTexture.getSize().y;
    cloudsTexture.setRepeated(true);
    clouds.setTexture(cloudsTexture);
    clouds.setTextureRect(sf::IntRect(-cloudsWidth, 0, win_width + cloudsWidth, cloudsHeight));
    clouds.setOrigin(0, cloudsHeight);
    clouds.setPosition(-cloudsWidth, win_height);

    if (!seaTexture.loadFromFile("resources/map/sea.png")) { throw "[SEA] TEXTURE FAILED TO LOAD"; }
    float seaWidth = seaTexture.getSize().x;
    float seaHeight = seaTexture.getSize().y;
    seaTexture.setRepeated(true);
    sea.setTexture(seaTexture);
    sea.setTextureRect(sf::IntRect(-seaWidth, 0, win_width + seaWidth, seaHeight));
    sea.setOrigin(0, seaHeight);
    sea.setPosition(-seaWidth, win_height);

    if (!farGroundsTexture.loadFromFile("resources/map/far-grounds.png")) { throw "[FAR-GROUNDS] TEXTURE FAILED TO LOAD"; }
    float farGroundsWidth = farGroundsTexture.getSize().x;
    float farGroundsHeight = farGroundsTexture.getSize().y;
    farGrounds.setTexture(farGroundsTexture);
    farGrounds.setOrigin(0, farGroundsHeight);
    farGrounds.setPosition(rand() % (int)(win_width - 2 * farGroundsWidth), win_height);
}

void animateBackground() {
    clouds.move(backgroundAnimationSpeed * 0.25, 0);
    sf::Vector2f cloudsPos = clouds.getPosition();
    int cloudsWidth = clouds.getTexture()->getSize().x;
    if (cloudsPos.x >= 0) clouds.setPosition(-cloudsWidth, cloudsPos.y);

    sea.move(backgroundAnimationSpeed * 0.5, 0);
    sf::Vector2f seaPos = sea.getPosition();
    int seaWidth = sea.getTexture()->getSize().x;
    if (seaPos.x >= 0) sea.setPosition(-seaWidth, seaPos.y);
}

void renderBackground(sf::RenderTarget& target) {
    target.draw(sky);
    target.draw(clouds);
    target.draw(sea);
    target.draw(farGrounds);
}

void updateView(sf::RenderWindow& window, sf::Sprite& player) {
    sf::Vector2f playerPos = player.getPosition();
    sf::Vector2f viewPos = player.getPosition();
    sf::Vector2f viewSize = view.getSize();
    if (playerPos.x - viewSize.x / 2 < 0) viewPos.x = viewSize.x / 2;
    if (playerPos.x + viewSize.x / 2 > win_width) viewPos.x = win_width - viewSize.x / 2;
    if (playerPos.y + viewSize.y / 2 > win_height) viewPos.y = win_height - viewSize.y / 2;
    view.setCenter(viewPos);
    window.setView(view);
}

#include "Common.h"

#include "MapLayer.h"
#include "PlayerTank.h"
#include "Block.h"
#include "Bullet.h"

#include <string>

USING_NS_CC;

static MapLayer* _mapLayer = nullptr;

bool MapLayer::init() {
	if (!cocos2d::LayerColor::init()) {
		return false;
	}

	// ���ñ�����ɫ
	this->initWithColor(Color4B(0, 0, 0, 255));

	__addSpriteFrameCache();

	return true;
}

MapLayer* MapLayer::getInstance() {
	if (!_mapLayer) {
		_mapLayer = MapLayer::create();
	}
	return _mapLayer;
}

void MapLayer::__addSpriteFrameCache() {
	auto spriteFrameCache = SpriteFrameCache::getInstance();

	// ��Ӫ
	auto* camp_0 = Sprite::create("images/block/camp0.png")->getSpriteFrame();
	auto* camp_1 = Sprite::create("images/block/camp1.png")->getSpriteFrame();

	spriteFrameCache->addSpriteFrame(camp_0, "camp_0");
	spriteFrameCache->addSpriteFrame(camp_1, "camp_1");

	// ����
	auto* wall = Sprite::create("images/block/wall.png")->getSpriteFrame();
	auto* stone = Sprite::create("images/block/stone.png")->getSpriteFrame();
	auto* forest = Sprite::create("images/block/forest.png")->getSpriteFrame();
	auto* ice = Sprite::create("images/block/ice.png")->getSpriteFrame();
	auto* river_0 = Sprite::create("images/block/river-0.png")->getSpriteFrame();
	auto* river_1 = Sprite::create("images/block/river-1.png")->getSpriteFrame();

	spriteFrameCache->addSpriteFrame(wall, "wall");
	spriteFrameCache->addSpriteFrame(stone, "stone");
	spriteFrameCache->addSpriteFrame(forest, "forest");
	spriteFrameCache->addSpriteFrame(ice, "ice");
	spriteFrameCache->addSpriteFrame(river_0, "river_0");
	spriteFrameCache->addSpriteFrame(river_1, "river_1");

	// �ӵ�
	auto* bullet_l = Sprite::create("images/bullet/bullet-0.png")->getSpriteFrame();
	auto* bullet_u = Sprite::create("images/bullet/bullet-1.png")->getSpriteFrame();
	auto* bullet_r = Sprite::create("images/bullet/bullet-2.png")->getSpriteFrame();
	auto* bullet_d = Sprite::create("images/bullet/bullet-3.png")->getSpriteFrame();

	spriteFrameCache->addSpriteFrame(bullet_l, "bullet_l");
	spriteFrameCache->addSpriteFrame(bullet_u, "bullet_u");
	spriteFrameCache->addSpriteFrame(bullet_r, "bullet_r");
	spriteFrameCache->addSpriteFrame(bullet_d, "bullet_d");

	// �ӵ���ը
	auto* bumb_0 = Sprite::create("images/bullet/bumb0.png")->getSpriteFrame();
	auto* bumb_1 = Sprite::create("images/bullet/bumb1.png")->getSpriteFrame();
	auto* bumb_2 = Sprite::create("images/bullet/bumb2.png")->getSpriteFrame();

	spriteFrameCache->addSpriteFrame(bumb_0, "bumb_0");
	spriteFrameCache->addSpriteFrame(bumb_1, "bumb_1");
	spriteFrameCache->addSpriteFrame(bumb_2, "bumb_2");

	// ̹�˱�ը
	auto* blast_0 = Sprite::create("images/blast/0.png")->getSpriteFrame();
	auto* blast_1 = Sprite::create("images/blast/1.png")->getSpriteFrame();
	auto* blast_2 = Sprite::create("images/blast/2.png")->getSpriteFrame();
	auto* blast_3 = Sprite::create("images/blast/3.png")->getSpriteFrame();
	auto* blast_4 = Sprite::create("images/blast/4.png")->getSpriteFrame();

	spriteFrameCache->addSpriteFrame(blast_0, "blast_0");
	spriteFrameCache->addSpriteFrame(blast_1, "blast_1");
	spriteFrameCache->addSpriteFrame(blast_2, "blast_2");
	spriteFrameCache->addSpriteFrame(blast_3, "blast_3");
	spriteFrameCache->addSpriteFrame(blast_4, "blast_4");
}

void MapLayer::addPlayer() {
	auto player = PlayerTank::create();
	this->addChild(player);
	player->setPosition(PLAYER1_START_X, PLAYER1_START_Y);

	auto bullets = player->getAllBullets();
	for (auto& bullet : bullets) {
		this->addChild(bullet, 100);
	}

	players.pushBack(player);
}

void MapLayer::addEnemies() {
	// TODO
}

void MapLayer::loadLevelData(int stage) {
	// �����Ӵ�Ӫ
	auto camp = BlockCamp::create();
	this->addChild(camp);
	camp->setPosition(CAMP_X, CAMP_Y);
	blocks.pushBack(camp);

	// Ȼ��������������
	std::string filename = "maps/" + std::to_string(stage) + ".txt";
	auto str = FileUtils::getInstance()->getStringFromFile("maps/4.txt");

	int index = 0;

	for (int i = 0; i < 26; i++) {
		for (int j = 0; j < 26; j++) {
			char c = str[index++];
			if (c == '\r') {
				j--;
				index++;
				continue;
			}
			// ���쾫��
			Block* block = nullptr;

			// ������ͬ���͵ķ���
			if (c == '3') {
				block = BlockWall::create();
			} else if (c == '5') {
				block = BlockStone::create();
			} else if (c == '1') {
				block = BlockForest::create();
			} else if (c == '4') {
				block = BlockRiver::create();
			}

			if (block) {
				// ���������ӵ�ͼ��
				this->addChild(block);

				// ���þ�����ͼ���ϵ�λ��
				block->setAnchorPoint(Vec2(0, 0));
				block->setPosition(Vec2(j * BLOCK_SIZE, (25 - i) * BLOCK_SIZE));

				// �洢vector
				blocks.pushBack(block);
			}

		}
	}
}

TankBase* MapLayer::getPlayer1() {
	return players.at(0);
}

Block* MapLayer::getCamp() {
	return blocks.at(0);
}

cocos2d::Vector<Block*>& MapLayer::getAllBlocks() {
	return blocks;
}
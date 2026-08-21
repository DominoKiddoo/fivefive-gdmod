#include <Geode/Geode.hpp>
#include <Geode/modify/MenuLayer.hpp>
#include <fryy_55.amber/include/amber.hpp>
using namespace geode::prelude;


$on_mod(Loaded) {
	auto mod = Mod::get();    
	listenForSettingChanges<bool>("vortrox", [](bool value) {
		if (value == true) {
            auto image = CCSprite::create("fortrocks.jpg"_spr);
            auto oM = OverlayManager::get();
            auto winSize = CCDirector::sharedDirector()->getWinSize();
            auto imgSize = image->getContentSize();
            image->setScaleX(winSize.width / imgSize.width);
            image->setScaleY(winSize.height / imgSize.height);
            image->setPosition(CCPoint(winSize.width / 2, winSize.height / 2));
            oM->addChild(image);
            
            auto engine = FMODAudioEngine::get();
            engine->playEffect("boom.mp3"_spr);
            image->runAction(CCSequence::create(
                CCDelayTime::create(0.6f),
                CCFadeOut::create(1.f),
                CCRemoveSelf::create(),
                nullptr
            ));
        }
	}, mod);
}



class $modify(MenuLayer) {
    bool init() {
        if (!MenuLayer::init()) return false;

        Loader::get()->queueInMainThread([this]() {
            if (!Mod::get()->getSavedValue<bool>("shown-update-1.2.0")) {
                fourTrucks();
                Mod::get()->setSavedValue<bool>("shown-update-1.2.0", true);
            }
            return true;
        });

        return true;
    }

    void fourTrucks() {
        amber::TextboxChain::create(
            amber::TextboxChain::Background::Brown,
            amber::TextboxObject::create(
                "Vortrox",
                "hi",
                CCSprite::create("fourtrucks.png"_spr)
            )->setSkippable(false),
            amber::TextboxObject::create(
                "Samme",
                "isn't this <cr>my mod</c>?",
                CCSprite::create("samme.png"_spr)
            )->setSkippable(false),
            amber::TextboxObject::create(
                "Vortrox",
                "shh<d010>.<d010>.<d010>. im just here to <cf>tell everyone</c> that there is now a <cg>Votrox Mode</c> in the <cb>Five-Five</c> mod!",
                CCSprite::create("fourtrucks.png"_spr)
            ),
            amber::TextboxObject::create(
                "Vortrox",
                "By enabling it, when you <cr>die</c> at <cy>92%</c>, well<d010>.<d010>.<d010>. uh<d010>.<d010>.<d010>. you'll have to <cb>find out</c>.",
                CCSprite::create("fourtrucks.png"_spr)
            )->setShowCallback([](amber::TextboxChain* chain) static {
                chain->setTextboxPosition(amber::TextboxChain::TextboxPosition::Center);
            })->setSkippable(false)
        )->show(amber::TextboxChain::StartAnimation::Random);
    }
};


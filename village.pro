QT = core

CONFIG += c++17 cmdline

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        main.cpp \
        src/dataManager/datamanager.cpp \
        src/dataManager/potiondatamanager.cpp \
        src/dataManager/spelldatamanager.cpp \
        src/entity/entity.cpp \
        src/entity/hero/hero.cpp \
        src/entity/hero/mage.cpp \
        src/entity/hero/paladin.cpp \
        src/entity/hero/warrior.cpp \
        src/entity/merchant.cpp \
        src/entity/monster.cpp \
        src/inventory/inventory.cpp \
        src/locations/buildings/building.cpp \
        src/locations/buildings/forge.cpp \
        src/locations/buildings/mine.cpp \
        src/locations/buildings/shop.cpp \
        src/locations/village.cpp \
        src/locations/buildings/hostel.cpp \
        src/pattern/merchantSellListener.cpp \
        src/potion/potion.cpp \
        src/starter/gameloader.cpp \
        src/starter/herocreator.cpp \
        src/weapon/shield.cpp \
        src/weapon/staff.cpp \
        src/weapon/sword.cpp \
        src/weapon/weapon.cpp \
        src/damage.cpp \
        src/Element.cpp \
        src/game.cpp \
        src/spell.cpp \
        src/Type.cpp \
        src/utils.cpp \


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    headers/main.h \
    headers/dataManager/datamanager.h \
    headers/dataManager/potiondatamanager.h \
    headers/dataManager/spelldatamanager.h \
    headers/entity/entity.h \
    headers/entity/merchant.h \
    headers/entity/monster.h \
    headers/entity/hero/hero.h \
    headers/entity/hero/mage.h \
    headers/entity/hero/paladin.h \
    headers/entity/hero/warrior.h \
    headers/inventory/inventory.h \
    headers/locations/buildings/building.h \
    headers/locations/buildings/forge.h \
    headers/locations/buildings/mine.h \
    headers/locations/buildings/shop.h \
    headers/locations/village.h \
    headers/locations/buildings/hostel.h \
    headers/pattern/merchantSellEmitter.h \
    headers/pattern/merchantSellListener.h \
    headers/potion/potion.h \
    headers/starter/gameloader.h \
    headers/starter/herocreator.h \
    headers/weapon/shield.h \
    headers/weapon/staff.h \
    headers/weapon/sword.h \
    headers/weapon/weapon.h \
    headers/coutTag.h \
    headers/damage.h \
    headers/Element.h \
    headers/game.h \
    headers/spell.h \
    headers/Type.h \
    headers/utils.h

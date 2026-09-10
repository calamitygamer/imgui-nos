#pragma once
#include "imgui.h"
#include "data.hpp"
#include <string>
#include <vector>
#include <array>

// ── Applied skin entry ────────────────────────────────────────────────────────

struct AppliedEntry {
    Weapon      weapon;
    Skin        skin;
    float       floatVal   = 12.0f;
    bool        stattrak   = false;
    std::array<int, 4> stickerSlots = { -1, -1, -1, -1 }; // index into sticker list
    const char* FloatLabel() const {
        if (floatVal < 7)  return "Factory New";
        if (floatVal < 15) return "Minimal Wear";
        if (floatVal < 38) return "Field-Tested";
        if (floatVal < 45) return "Well-Worn";
        return "Battle-Scarred";
    }
    const char* FloatShort() const {
        if (floatVal < 7)  return "FN";
        if (floatVal < 15) return "MW";
        if (floatVal < 38) return "FT";
        if (floatVal < 45) return "WW";
        return "BS";
    }
    ImVec4 FloatColor() const {
        if (floatVal < 15) return { 0.604f, 0.722f, 0.0f, 1.0f };
        if (floatVal < 38) return { 0.753f, 0.565f, 0.125f, 1.0f };
        return { 0.851f, 0.251f, 0.251f, 1.0f };
    }
};

// ── Config entry ──────────────────────────────────────────────────────────────

struct Config {
    std::string name;
    std::string description;
    std::string created;
    std::string modified;
    bool        active = false;
};

// ── Menu state ────────────────────────────────────────────────────────────────

struct MenuState {
    // ── Skins
    int                     skinCatFilter  = 0;   // 0=All,1=Rifle,2=Pistol,...
    int                     selectedWeapon = 0;
    char                    weaponSearch[64] = {};
    char                    skinSearch[64]   = {};
    // modal
    bool                    skinModalOpen  = false;
    int                     modalWeapon    = 0;
    int                     modalSkin      = 0;
    float                   modalFloat     = 12.0f;
    bool                    modalStattrak  = false;
    std::array<int,4>       modalSlots     = { -1,-1,-1,-1 };
    int                     modalSelSticker= -1;
    int                     modalSelCharm  = -1;
    int                     modalTab       = 0; // 0=stickers,1=charms
    int                     modalWear      = 0;
    float                   modalCharmPos  = 50.0f;
    char                    stickerSearch[64] = {};

    // ── Loadout
    std::vector<AppliedEntry> applied;
    int                     loadoutSel     = -1;

    // ── Visuals
    bool healthBar=false, playerName=false, playerFlags=false;
    bool weaponText=false, weaponIcon=false, ammo=false;
    bool distance=false, glow=false, hitMarker=false;
    bool hitMarkerSound=false, skeleton=false, fovArrow=false;
    ImVec4 glowColor = { 0.604f, 0.722f, 0.0f, 1.0f };
    int healthStyle=0, nameStyle=0, glowStyle=0, distStyle=0;

    bool radar=false, droppedWeapons=false, grenades=false;
    bool inaccuracy=false, recoilOverlay=false, crosshair=false;
    bool bomb=false, grenadeTrajectory=false, soundEsp=false;
    int soundEspMode=0, radarMode=0;

    bool removeFlash=false, removeSmoke=false, removeFog=false;
    bool removeSkybox=false, removeScopeOverlay=false;
    bool nightMode=false, fullBright=false;
    int skyboxMode=0;

    bool playerCham=false, playerWallCham=false;
    bool teammateCham=false, teammateWallCham=false;
    bool localCham=false, localArmsCham=false;
    ImVec4 playerChamColor      = { 0.294f, 0.412f, 1.0f, 1.0f };
    ImVec4 playerWallChamColor  = { 0.827f, 0.173f, 0.902f, 1.0f };

    // ── Misc
    bool bhop=false, autoStrafe=false;
    bool autoAccept=false, revealRanks=false;
    bool regionForcer=false;
    int  regionSel=0;
    bool menuGradient=false, spectatorList=false, clanTag=false;
    ImVec4 menuGradientColor = { 0.722f, 0.663f, 0.788f, 1.0f };
    ImVec4 menuColor         = { 0.722f, 0.663f, 0.788f, 1.0f };

    // ── Configs
    std::vector<Config> configs;
    int    configSel = 0;
    char   newCfgName[64] = {};
    char   newCfgDesc[128] = {};
    std::string flashMsg;
    float  flashTimer = 0.0f;
    bool   flashOk    = true;
};

// ── Theme / forward decls ─────────────────────────────────────────────────────

void ApplyNostalgiaTheme();

class Menu {
public:
    Menu();
    void Render();

private:
    void RenderSkinsTab();
    void RenderSkinModal();
    void RenderLoadoutTab();
    void RenderVisualsTab();
    void RenderMiscTab();
    void RenderConfigsTab();

    void ColorDot(bool on, float size = 8.0f);
    void ColorDotRarity(Rarity r, float size = 7.0f);
    bool GsCheckbox(const char* label, bool* v, ImVec4* colorPicker = nullptr);
    void GsSlider(const char* label, float* v, float mn, float mx, const char* fmt = "%.0f", float width = 110.0f);
    void GsSliderInt(const char* label, int* v, int mn, int mx, const char* fmt = "%d", float width = 110.0f);
    void SectionHeader(const char* title);
    bool RadioItem(const char* label, bool selected);

    std::vector<Weapon>  m_weapons;
    std::vector<Sticker> m_stickers;
    std::vector<Charm>   m_charms;
    MenuState            m_state;

    int  m_activeTab = 0;
    int  m_activeUsers = 247;
};

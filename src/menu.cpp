#include "menu.hpp"
#include "imgui_internal.h"
#include <algorithm>
#include <cstring>
#include <cstdio>

// ── Colour constants ──────────────────────────────────────────────────────────
static const ImVec4 COL_BG_WINDOW    = { 0.110f, 0.110f, 0.118f, 1.0f };
static const ImVec4 COL_BG_PANEL     = { 0.137f, 0.137f, 0.149f, 1.0f };
static const ImVec4 COL_BG_SECTION   = { 0.165f, 0.165f, 0.176f, 1.0f };
static const ImVec4 COL_BG_HOVER     = { 0.184f, 0.184f, 0.200f, 1.0f };
static const ImVec4 COL_BG_INPUT     = { 0.102f, 0.102f, 0.110f, 1.0f };
static const ImVec4 COL_BG_TITLEBAR  = { 0.094f, 0.094f, 0.098f, 1.0f };
static const ImVec4 COL_BORDER       = { 0.212f, 0.212f, 0.220f, 1.0f };
static const ImVec4 COL_BORDER_FAINT = { 0.173f, 0.173f, 0.180f, 1.0f };
static const ImVec4 COL_GREEN        = { 0.604f, 0.722f, 0.000f, 1.0f };
static const ImVec4 COL_GREEN_DIM    = { 0.416f, 0.498f, 0.000f, 1.0f };
static const ImVec4 COL_GREEN_GLOW   = { 0.604f, 0.722f, 0.000f, 0.18f };
static const ImVec4 COL_TEXT_BRIGHT  = { 0.910f, 0.910f, 0.910f, 1.0f };
static const ImVec4 COL_TEXT_NORMAL  = { 0.706f, 0.706f, 0.714f, 1.0f };
static const ImVec4 COL_TEXT_DIM     = { 0.431f, 0.431f, 0.447f, 1.0f };
static const ImVec4 COL_TEXT_MUTED   = { 0.290f, 0.290f, 0.306f, 1.0f };
static const ImVec4 COL_RED          = { 0.851f, 0.251f, 0.251f, 1.0f };
static const ImVec4 COL_PURPLE       = { 0.722f, 0.663f, 0.788f, 1.0f };

static ImU32 ToU32(ImVec4 c) { return ImGui::ColorConvertFloat4ToU32(c); }

// ── Theme ─────────────────────────────────────────────────────────────────────
void ApplyNostalgiaTheme() {
    ImGuiStyle& s = ImGui::GetStyle();
    s.WindowPadding     = { 0, 0 };
    s.FramePadding      = { 6, 3 };
    s.ItemSpacing       = { 6, 3 };
    s.ItemInnerSpacing  = { 4, 4 };
    s.ScrollbarSize     = 5.0f;
    s.ScrollbarRounding = 2.0f;
    s.GrabMinSize       = 8.0f;
    s.GrabRounding      = 0.0f;
    s.FrameRounding     = 0.0f;
    s.WindowRounding    = 0.0f;
    s.PopupRounding     = 0.0f;
    s.ChildRounding     = 0.0f;
    s.TabRounding       = 0.0f;
    s.WindowBorderSize  = 1.0f;
    s.ChildBorderSize   = 0.0f;
    s.PopupBorderSize   = 1.0f;
    s.FrameBorderSize   = 0.0f;

    ImVec4* c = s.Colors;
    c[ImGuiCol_WindowBg]            = COL_BG_WINDOW;
    c[ImGuiCol_ChildBg]             = COL_BG_PANEL;
    c[ImGuiCol_PopupBg]             = { 0.157f, 0.157f, 0.165f, 1.0f };
    c[ImGuiCol_Border]              = COL_BORDER;
    c[ImGuiCol_BorderShadow]        = { 0,0,0,0 };
    c[ImGuiCol_FrameBg]             = COL_BG_INPUT;
    c[ImGuiCol_FrameBgHovered]      = COL_BG_HOVER;
    c[ImGuiCol_FrameBgActive]       = COL_BG_SECTION;
    c[ImGuiCol_TitleBg]             = COL_BG_TITLEBAR;
    c[ImGuiCol_TitleBgActive]       = COL_BG_TITLEBAR;
    c[ImGuiCol_TitleBgCollapsed]    = COL_BG_TITLEBAR;
    c[ImGuiCol_MenuBarBg]           = COL_BG_TITLEBAR;
    c[ImGuiCol_ScrollbarBg]         = { 0,0,0,0 };
    c[ImGuiCol_ScrollbarGrab]       = { 0.227f, 0.227f, 0.235f, 1.0f };
    c[ImGuiCol_ScrollbarGrabHovered]= { 0.314f, 0.314f, 0.322f, 1.0f };
    c[ImGuiCol_ScrollbarGrabActive] = COL_GREEN_DIM;
    c[ImGuiCol_CheckMark]           = COL_GREEN;
    c[ImGuiCol_SliderGrab]          = COL_GREEN;
    c[ImGuiCol_SliderGrabActive]    = COL_GREEN_DIM;
    c[ImGuiCol_Button]              = COL_BG_SECTION;
    c[ImGuiCol_ButtonHovered]       = COL_BG_HOVER;
    c[ImGuiCol_ButtonActive]        = COL_BG_INPUT;
    c[ImGuiCol_Header]              = COL_BG_HOVER;
    c[ImGuiCol_HeaderHovered]       = COL_BG_HOVER;
    c[ImGuiCol_HeaderActive]        = COL_BG_SECTION;
    c[ImGuiCol_Separator]           = COL_BORDER_FAINT;
    c[ImGuiCol_SeparatorHovered]    = COL_BORDER;
    c[ImGuiCol_SeparatorActive]     = COL_GREEN_DIM;
    c[ImGuiCol_ResizeGrip]          = { 0,0,0,0 };
    c[ImGuiCol_Tab]                 = COL_BG_TITLEBAR;
    c[ImGuiCol_TabHovered]          = COL_BG_HOVER;
    c[ImGuiCol_TabActive]           = COL_BG_PANEL;
    c[ImGuiCol_TabUnfocused]        = COL_BG_TITLEBAR;
    c[ImGuiCol_TabUnfocusedActive]  = COL_BG_PANEL;
    c[ImGuiCol_Text]                = COL_TEXT_NORMAL;
    c[ImGuiCol_TextDisabled]        = COL_TEXT_MUTED;
    c[ImGuiCol_InputTextCursor]     = COL_GREEN;
}

// ── Constructor ───────────────────────────────────────────────────────────────
Menu::Menu() {
    m_weapons  = BuildWeaponList();
    m_stickers = BuildStickerList();
    m_charms   = BuildCharmList();

    m_state.configs = {
        { "default",      "Default configuration",  "2024-01-15", "2024-03-20", true  },
        { "tournament",   "Tournament preset",       "2024-02-01", "2024-03-18", false },
        { "warmup",       "Warmup server config",    "2024-02-14", "2024-03-10", false },
        { "hvh_preset",   "HvH configuration",       "2024-03-01", "2024-03-21", false },
        { "rankup_grind", "Rank up grind preset",    "2024-03-05", "2024-03-22", false },
    };
}

// ── Helpers ───────────────────────────────────────────────────────────────────
void Menu::ColorDot(bool on, float size) {
    ImDrawList* dl = ImGui::GetWindowDrawList();
    ImVec2 p = ImGui::GetCursorScreenPos();
    p.x += 1; p.y += (ImGui::GetTextLineHeight() - size) * 0.5f + 1;
    ImU32 col = on ? ToU32(COL_GREEN) : ToU32({ 0.180f, 0.180f, 0.188f, 1.0f });
    ImU32 bdr = on ? ToU32(COL_GREEN_DIM) : ToU32(COL_BORDER);
    dl->AddRectFilled(p, { p.x + size, p.y + size }, col);
    dl->AddRect(p, { p.x + size, p.y + size }, bdr);
    ImGui::Dummy({ size + 4, size });
}

void Menu::ColorDotRarity(Rarity r, float size) {
    ImDrawList* dl = ImGui::GetWindowDrawList();
    ImVec2 p = ImGui::GetCursorScreenPos();
    p.y += (ImGui::GetTextLineHeight() - size) * 0.5f + 1;
    ImVec4 cv = RarityColor(r);
    dl->AddRectFilled(p, { p.x + size, p.y + size }, ToU32(cv));
    ImGui::Dummy({ size + 4, size });
}

void Menu::SectionHeader(const char* title) {
    ImGui::PushStyleColor(ImGuiCol_ChildBg, COL_BG_PANEL);
    ImGui::SetCursorPosY(ImGui::GetCursorPosY());
    ImGui::PushStyleColor(ImGuiCol_Text, COL_TEXT_BRIGHT);
    ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 10);
    ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 6);
    ImGui::TextUnformatted(title);
    ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 2);
    ImGui::PopStyleColor(2);

    ImDrawList* dl = ImGui::GetWindowDrawList();
    ImVec2 p = ImGui::GetCursorScreenPos();
    ImVec2 sz = ImGui::GetContentRegionAvail();
    dl->AddLine(p, { p.x + sz.x, p.y }, ToU32(COL_BORDER_FAINT));
}

bool Menu::GsCheckbox(const char* label, bool* v, ImVec4* colorPicker) {
    ImGui::PushID(label);
    ImVec2 pos = ImGui::GetCursorPos();
    float  w   = ImGui::GetContentRegionAvail().x;
    float  h   = ImGui::GetTextLineHeight() + 6;

    bool hovered = ImGui::IsMouseHoveringRect(
        ImGui::GetCursorScreenPos(),
        { ImGui::GetCursorScreenPos().x + w, ImGui::GetCursorScreenPos().y + h });

    if (hovered)
        ImGui::GetWindowDrawList()->AddRectFilled(
            ImGui::GetCursorScreenPos(),
            { ImGui::GetCursorScreenPos().x + w, ImGui::GetCursorScreenPos().y + h },
            ToU32(COL_BG_HOVER));

    ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 3);
    ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 10);
    ImGui::SameLine();
    ColorDot(*v);
    ImGui::SameLine();
    ImGui::PushStyleColor(ImGuiCol_Text, *v ? COL_TEXT_BRIGHT : COL_TEXT_NORMAL);
    ImGui::TextUnformatted(label);
    ImGui::PopStyleColor();

    if (colorPicker) {
        ImGui::SameLine(w - 36);
        ImGui::SetCursorPosY(ImGui::GetCursorPosY() - 1);
        ImGui::ColorEdit4("##cp", (float*)colorPicker,
            ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel |
            ImGuiColorEditFlags_NoAlpha  | ImGuiColorEditFlags_NoBorder);
    }

    ImGui::SetCursorPosY(pos.y + 3);
    ImGui::InvisibleButton("##btn", { w, h });
    bool clicked = ImGui::IsItemClicked();
    if (clicked) *v = !*v;

    ImGui::PopID();

    ImDrawList* dl = ImGui::GetWindowDrawList();
    ImVec2 sp = { ImGui::GetCursorScreenPos().x, ImGui::GetCursorScreenPos().y };
    ImVec2 ep = { sp.x + ImGui::GetContentRegionAvail().x, sp.y };
    dl->AddLine(sp, ep, ToU32(COL_BORDER_FAINT));

    return clicked;
}

void Menu::GsSlider(const char* label, float* v, float mn, float mx, const char* fmt, float width) {
    ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 10);
    ImGui::PushStyleColor(ImGuiCol_Text, COL_TEXT_NORMAL);
    float avail = ImGui::GetContentRegionAvail().x - 10;
    ImGui::Text("%s", label);
    ImGui::SameLine(avail - width - 36);
    ImGui::PushStyleColor(ImGuiCol_FrameBg,       COL_BG_INPUT);
    ImGui::PushStyleColor(ImGuiCol_SliderGrab,     COL_GREEN);
    ImGui::PushStyleColor(ImGuiCol_SliderGrabActive, COL_GREEN_DIM);
    ImGui::SetNextItemWidth(width);
    char id[64]; snprintf(id, sizeof(id), "##sl_%s", label);
    ImGui::SliderFloat(id, v, mn, mx, "");
    ImGui::PopStyleColor(3);
    ImGui::SameLine();
    char val[32]; snprintf(val, sizeof(val), fmt, *v);
    ImGui::PushStyleColor(ImGuiCol_Text, COL_TEXT_BRIGHT);
    ImGui::SetNextItemWidth(32);
    ImGui::Text("%s", val);
    ImGui::PopStyleColor(2);

    ImDrawList* dl = ImGui::GetWindowDrawList();
    ImVec2 sp = ImGui::GetCursorScreenPos();
    dl->AddLine(sp, { sp.x + ImGui::GetContentRegionAvail().x + 10, sp.y }, ToU32(COL_BORDER_FAINT));
}

void Menu::GsSliderInt(const char* label, int* v, int mn, int mx, const char* fmt, float width) {
    float fv = (float)*v;
    GsSlider(label, &fv, (float)mn, (float)mx, fmt, width);
    *v = (int)fv;
}

bool Menu::RadioItem(const char* label, bool selected) {
    ImVec2 pos = ImGui::GetCursorPos();
    float w = ImGui::GetContentRegionAvail().x;
    float h = ImGui::GetTextLineHeight() + 6;

    bool hov = ImGui::IsMouseHoveringRect(
        ImGui::GetCursorScreenPos(),
        { ImGui::GetCursorScreenPos().x + w, ImGui::GetCursorScreenPos().y + h });

    if (selected || hov)
        ImGui::GetWindowDrawList()->AddRectFilled(
            ImGui::GetCursorScreenPos(),
            { ImGui::GetCursorScreenPos().x + w, ImGui::GetCursorScreenPos().y + h },
            selected ? ToU32({ 0.180f,0.180f,0.196f,1.0f }) : ToU32(COL_BG_HOVER));

    ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 3);
    ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 18);
    ColorDot(selected);
    ImGui::SameLine();
    ImGui::PushStyleColor(ImGuiCol_Text, selected ? COL_GREEN : COL_TEXT_NORMAL);
    ImGui::TextUnformatted(label);
    ImGui::PopStyleColor();

    ImGui::SetCursorPosY(pos.y + 3);
    ImGui::InvisibleButton(label, { w, h });
    bool clicked = ImGui::IsItemClicked();

    ImDrawList* dl = ImGui::GetWindowDrawList();
    ImVec2 sp = ImGui::GetCursorScreenPos();
    dl->AddLine(sp, { sp.x + ImGui::GetContentRegionAvail().x, sp.y }, ToU32(COL_BORDER_FAINT));
    return clicked;
}

// ── Main Render ───────────────────────────────────────────────────────────────
void Menu::Render() {
    ImGuiIO& io = ImGui::GetIO();
    ImVec2 center = { io.DisplaySize.x * 0.5f, io.DisplaySize.y * 0.5f };
    ImGui::SetNextWindowPos(center, ImGuiCond_Always, { 0.5f, 0.5f });
    ImGui::SetNextWindowSize({ 860, 570 }, ImGuiCond_Always);
    ImGui::SetNextWindowBgAlpha(1.0f);

    ImGuiWindowFlags flags =
        ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove |
        ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar |
        ImGuiWindowFlags_NoBringToFrontOnFocus;

    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, { 0.0f, 0.0f });
    ImGui::PushStyleColor(ImGuiCol_WindowBg, COL_BG_WINDOW);
    ImGui::PushStyleColor(ImGuiCol_Border, COL_BORDER);
    ImGui::Begin("##nos", nullptr, flags);
    ImGui::PopStyleVar();
    ImGui::PopStyleColor(2);

    ImDrawList* dl = ImGui::GetWindowDrawList();
    ImVec2 wpos   = ImGui::GetWindowPos();
    float  ww     = ImGui::GetWindowWidth();

    // ── Title bar ─────────────────────────────────────────────────────────────
    float tbH = 30.0f;
    dl->AddRectFilled(wpos, { wpos.x + ww, wpos.y + tbH }, ToU32(COL_BG_TITLEBAR));
    dl->AddLine({ wpos.x, wpos.y + tbH }, { wpos.x + ww, wpos.y + tbH }, ToU32(COL_BORDER));

    // separators
    dl->AddLine({ wpos.x + 10, wpos.y + 8 }, { wpos.x + 10, wpos.y + 22 }, ToU32(COL_BORDER));

    // "nostalgia" gradient text
    float tx = wpos.x + 18;
    float ty = wpos.y + 8;
    ImFont* font = ImGui::GetFont();
    // render gradient by drawing with two colors split
    const char* title = "nostalgia";
    ImVec2 tsz = ImGui::CalcTextSize(title);
    dl->AddText(font, 13.0f, { tx, ty }, ToU32(COL_TEXT_BRIGHT), "nostal");
    float off = ImGui::CalcTextSize("nostal").x;
    dl->AddText(font, 13.0f, { tx + off, ty }, ToU32(COL_PURPLE), "gia");

    float sep2x = tx + tsz.x + 10;
    dl->AddLine({ sep2x, wpos.y + 8 }, { sep2x, wpos.y + 22 }, ToU32(COL_BORDER));

    // active users (right side)
    char usrBuf[64];
    snprintf(usrBuf, sizeof(usrBuf), "active users: %d", m_activeUsers);
    ImVec2 usrSz = ImGui::CalcTextSize(usrBuf);
    float ux = wpos.x + ww - usrSz.x - 28;
    float uy = wpos.y + (tbH - usrSz.y) * 0.5f;
    // green dot
    dl->AddCircleFilled({ ux - 10, uy + usrSz.y * 0.5f }, 4.0f, ToU32(COL_GREEN));
    dl->AddText({ ux, uy }, ToU32(COL_TEXT_DIM), "active users: ");
    float labelOff = ImGui::CalcTextSize("active users: ").x;
    char numBuf[16]; snprintf(numBuf, sizeof(numBuf), "%d", m_activeUsers);
    dl->AddText({ ux + labelOff, uy }, ToU32(COL_GREEN), numBuf);

    // ── Tab bar ───────────────────────────────────────────────────────────────
    float tabBarY = tbH;
    float tabBarH = 30.0f;
    dl->AddRectFilled(
        { wpos.x, wpos.y + tabBarY },
        { wpos.x + ww, wpos.y + tabBarY + tabBarH },
        ToU32(COL_BG_TITLEBAR));
    dl->AddLine(
        { wpos.x, wpos.y + tabBarY + tabBarH },
        { wpos.x + ww, wpos.y + tabBarY + tabBarH },
        ToU32(COL_BORDER));

    const char* tabNames[] = { "Skins", "Loadout", "Visuals", "Misc", "Configs" };
    ImGui::SetCursorPos({ 8, tabBarY });

    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, { 0, 0 });
    for (int i = 0; i < 5; i++) {
        bool active = (m_activeTab == i);
        ImVec2 tpos = { wpos.x + ImGui::GetCursorPosX(), wpos.y + tabBarY };
        ImVec2 tsz2 = ImGui::CalcTextSize(tabNames[i]);
        float tw = tsz2.x + 28;

        bool hov = ImGui::IsMouseHoveringRect(tpos, { tpos.x + tw, tpos.y + tabBarH });
        ImU32 tCol = active ? ToU32(COL_GREEN) : (hov ? ToU32(COL_TEXT_NORMAL) : ToU32(COL_TEXT_DIM));
        dl->AddText(font, 11.0f,
            { tpos.x + 14, tpos.y + (tabBarH - 11.0f) * 0.5f },
            tCol, tabNames[i]);
        if (active)
            dl->AddLine(
                { tpos.x, tpos.y + tabBarH - 1 },
                { tpos.x + tw, tpos.y + tabBarH - 1 },
                ToU32(COL_GREEN), 2.0f);

        ImGui::InvisibleButton(tabNames[i], { tw, tabBarH });
        if (ImGui::IsItemClicked()) m_activeTab = i;
        ImGui::SameLine();
    }
    ImGui::PopStyleVar();

    // version label right side
    ImVec2 vSz = ImGui::CalcTextSize("v2.4.1");
    dl->AddText({ wpos.x + ww - vSz.x - 10, wpos.y + tabBarY + (tabBarH - vSz.y) * 0.5f },
        ToU32(COL_TEXT_MUTED), "v2.4.1");

    // ── Content area ──────────────────────────────────────────────────────────
    float contentTop = tabBarY + tabBarH;
    float statusH    = 22.0f;
    float contentH   = 570.0f - contentTop - statusH;

    ImGui::SetCursorPos({ 0, contentTop });
    ImGui::PushStyleColor(ImGuiCol_ChildBg, COL_BG_WINDOW);
    ImGui::BeginChild("##content", { ww, contentH }, false, ImGuiWindowFlags_NoScrollbar);

    switch (m_activeTab) {
        case 0: RenderSkinsTab();   break;
        case 1: RenderLoadoutTab(); break;
        case 2: RenderVisualsTab(); break;
        case 3: RenderMiscTab();    break;
        case 4: RenderConfigsTab(); break;
    }

    ImGui::EndChild();
    ImGui::PopStyleColor();

    // ── Status bar ────────────────────────────────────────────────────────────
    float sbY = 570.0f - statusH;
    dl->AddRectFilled(
        { wpos.x, wpos.y + sbY },
        { wpos.x + ww, wpos.y + 570.0f },
        ToU32(COL_BG_TITLEBAR));
    dl->AddLine(
        { wpos.x, wpos.y + sbY },
        { wpos.x + ww, wpos.y + sbY },
        ToU32(COL_BORDER));

    float sy = wpos.y + sbY + (statusH - ImGui::GetTextLineHeight()) * 0.5f;
    float sx = wpos.x + 10;
    auto DrawStatusText = [&](const char* txt, ImVec4 col) {
        ImVec2 tsz3 = ImGui::CalcTextSize(txt);
        dl->AddText({ sx, sy }, ToU32(col), txt);
        sx += tsz3.x + 10;
    };
    auto DrawSep = [&]() {
        dl->AddLine({ sx, sy + 1 }, { sx, sy + ImGui::GetTextLineHeight() - 1 }, ToU32(COL_BORDER));
        sx += 10;
    };

    DrawStatusText("build", COL_TEXT_MUTED);
    DrawStatusText("2024.03.22", COL_TEXT_DIM);
    DrawSep();
    DrawStatusText("cs2.exe", COL_TEXT_MUTED);
    DrawSep();
    DrawStatusText("x64", COL_TEXT_MUTED);

    ImGui::End();

    // Skin modal (rendered outside the child window)
    if (m_state.skinModalOpen) RenderSkinModal();
}

// ── Skins Tab ─────────────────────────────────────────────────────────────────
void Menu::RenderSkinsTab() {
    const char* cats[] = { "All","Rifle","Pistol","SMG","Shotgun","Sniper","Machine Gun","Knife","Gloves" };
    int nCats = 9;

    // Category filter bar
    ImGui::SetCursorPos({ 8, 5 });
    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, { 4, 0 });
    ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, { 8, 2 });
    for (int i = 0; i < nCats; i++) {
        bool sel = (m_state.skinCatFilter == i);
        if (sel) {
            ImGui::PushStyleColor(ImGuiCol_Button,        COL_GREEN_GLOW);
            ImGui::PushStyleColor(ImGuiCol_ButtonHovered, COL_GREEN_GLOW);
            ImGui::PushStyleColor(ImGuiCol_Text,          COL_GREEN);
            ImGui::PushStyleColor(ImGuiCol_Border,        COL_GREEN_DIM);
            ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 1.0f);
        } else {
            ImGui::PushStyleColor(ImGuiCol_Text, COL_TEXT_NORMAL);
            ImGui::PushStyleColor(ImGuiCol_Button, COL_BG_SECTION);
            ImGui::PushStyleColor(ImGuiCol_ButtonHovered, COL_BG_HOVER);
            ImGui::PushStyleColor(ImGuiCol_Border, COL_BORDER);
            ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 1.0f);
        }
        ImGui::PushFont(ImGui::GetIO().Fonts->Fonts[0]);
        if (ImGui::Button(cats[i])) m_state.skinCatFilter = i;
        ImGui::PopFont();
        ImGui::PopStyleColor(4);
        ImGui::PopStyleVar();
        ImGui::SameLine();
    }
    ImGui::PopStyleVar(2);
    ImGui::NewLine();

    // Separator
    ImDrawList* dl = ImGui::GetWindowDrawList();
    ImVec2 sp = ImGui::GetCursorScreenPos();
    dl->AddLine(sp, { sp.x + ImGui::GetContentRegionAvail().x, sp.y }, ToU32(COL_BORDER_FAINT));
    ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 1);

    // Content: weapon list | skin list
    float panelH = ImGui::GetContentRegionAvail().y;
    float weaponW = 185.0f;

    // Weapon panel
    ImGui::PushStyleColor(ImGuiCol_ChildBg, COL_BG_WINDOW);
    ImGui::BeginChild("##weapons", { weaponW, panelH }, false);

    // Header
    ImGui::PushStyleColor(ImGuiCol_Text, COL_TEXT_BRIGHT);
    ImGui::SetCursorPos({ 10, 7 });
    ImGui::TextUnformatted("Weapons");
    ImGui::PopStyleColor();
    ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 2);
    ImVec2 hsp = ImGui::GetCursorScreenPos();
    dl->AddLine(hsp, { hsp.x + weaponW, hsp.y }, ToU32(COL_BORDER_FAINT));

    // Search
    ImGui::SetCursorPos({ 8, ImGui::GetCursorPosY() + 4 });
    ImGui::SetNextItemWidth(weaponW - 16);
    ImGui::PushStyleColor(ImGuiCol_FrameBg, COL_BG_INPUT);
    ImGui::InputText("##wsearch", m_state.weaponSearch, sizeof(m_state.weaponSearch));
    ImGui::PopStyleColor();
    ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 3);

    // Filter
    std::string wFilter = m_state.weaponSearch;
    std::transform(wFilter.begin(), wFilter.end(), wFilter.begin(), ::tolower);
    const char* filterCat = (m_state.skinCatFilter == 0) ? nullptr : cats[m_state.skinCatFilter];

    int wi = 0;
    for (auto& w : m_weapons) {
        if (filterCat && w.category != filterCat) { wi++; continue; }
        std::string wn = w.name; std::transform(wn.begin(),wn.end(),wn.begin(),::tolower);
        if (!wFilter.empty() && wn.find(wFilter) == std::string::npos) { wi++; continue; }

        bool sel = (m_state.selectedWeapon == wi);
        ImVec2 cpos = ImGui::GetCursorScreenPos();
        float  rw   = weaponW;
        bool   hov  = ImGui::IsMouseHoveringRect(cpos, { cpos.x + rw, cpos.y + 22 });

        if (sel || hov)
            dl->AddRectFilled(cpos, { cpos.x + rw, cpos.y + 22 },
                sel ? ToU32({ 0.180f,0.180f,0.196f,1.0f }) : ToU32(COL_BG_HOVER));

        ImGui::SetCursorPosX(10);
        ColorDot(sel);
        ImGui::SameLine();
        ImGui::PushStyleColor(ImGuiCol_Text, sel ? COL_TEXT_BRIGHT : COL_TEXT_NORMAL);
        ImGui::TextUnformatted(w.name.c_str());
        ImGui::PopStyleColor();

        // category badge right side
        ImVec2 catSz = ImGui::CalcTextSize(w.category.c_str());
        dl->AddText({ cpos.x + rw - catSz.x - 8, cpos.y + (22 - catSz.y) * 0.5f },
            ToU32(COL_TEXT_MUTED), w.category.c_str());

        dl->AddLine({ cpos.x, cpos.y + 22 }, { cpos.x + rw, cpos.y + 22 }, ToU32(COL_BORDER_FAINT));

        // invisible hit area
        ImGui::SetCursorPosY(ImGui::GetCursorPosY() - ImGui::GetTextLineHeight() - 5);
        ImGui::InvisibleButton(("##w" + w.id).c_str(), { rw, 22 });
        if (ImGui::IsItemClicked()) {
            m_state.selectedWeapon = wi;
            memset(m_state.skinSearch, 0, sizeof(m_state.skinSearch));
        }
        wi++;
    }

    ImGui::EndChild();
    ImGui::PopStyleColor();

    // Vertical divider
    ImVec2 wcp = ImGui::GetWindowPos();
    float wcy  = ImGui::GetScrollY();
    dl->AddLine(
        { wcp.x + weaponW, wcp.y },
        { wcp.x + weaponW, wcp.y + panelH + 100 },
        ToU32(COL_BORDER_FAINT));

    ImGui::SameLine();

    // Skin panel
    float skinPanelW = ImGui::GetContentRegionAvail().x;
    ImGui::PushStyleColor(ImGuiCol_ChildBg, COL_BG_WINDOW);
    ImGui::BeginChild("##skins", { skinPanelW, panelH }, false);

    Weapon* selWeapon = (m_state.selectedWeapon < (int)m_weapons.size())
        ? &m_weapons[m_state.selectedWeapon] : nullptr;

    // count visible skins
    std::string sFilter = m_state.skinSearch;
    std::transform(sFilter.begin(), sFilter.end(), sFilter.begin(), ::tolower);

    int visCount = 0;
    if (selWeapon) {
        for (auto& sk : selWeapon->skins) {
            std::string sn = sk.name; std::transform(sn.begin(),sn.end(),sn.begin(),::tolower);
            if (sFilter.empty() || sn.find(sFilter) != std::string::npos) visCount++;
        }
    }

    // Header
    ImGui::SetCursorPos({ 10, 7 });
    ImGui::PushStyleColor(ImGuiCol_Text, COL_TEXT_BRIGHT);
    ImGui::TextUnformatted(selWeapon ? selWeapon->name.c_str() : "—");
    ImGui::PopStyleColor();

    char cntBuf[32]; snprintf(cntBuf, sizeof(cntBuf), "%d skins", visCount);
    ImVec2 cntSz = ImGui::CalcTextSize(cntBuf);
    ImVec2 hdrPos = ImGui::GetWindowPos();
    dl->AddText({ hdrPos.x + skinPanelW - cntSz.x - 10, hdrPos.y + 7 },
        ToU32(COL_TEXT_DIM), cntBuf);

    ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 2);
    ImVec2 shsp = ImGui::GetCursorScreenPos();
    dl->AddLine(shsp, { shsp.x + skinPanelW, shsp.y }, ToU32(COL_BORDER_FAINT));

    // Search
    ImGui::SetCursorPos({ 8, ImGui::GetCursorPosY() + 4 });
    ImGui::SetNextItemWidth(skinPanelW - 16);
    ImGui::PushStyleColor(ImGuiCol_FrameBg, COL_BG_INPUT);
    ImGui::InputText("##ssearch", m_state.skinSearch, sizeof(m_state.skinSearch));
    ImGui::PopStyleColor();
    ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 3);

    if (selWeapon) {
        int si = 0;
        for (auto& sk : selWeapon->skins) {
            std::string sn = sk.name;
            std::string snl = sn; std::transform(snl.begin(),snl.end(),snl.begin(),::tolower);
            if (!sFilter.empty() && snl.find(sFilter) == std::string::npos) { si++; continue; }

            ImVec2 cpos = ImGui::GetCursorScreenPos();
            float rw = skinPanelW;
            bool hov = ImGui::IsMouseHoveringRect(cpos, { cpos.x + rw, cpos.y + 22 });
            if (hov) dl->AddRectFilled(cpos, { cpos.x + rw, cpos.y + 22 }, ToU32(COL_BG_HOVER));

            ImGui::SetCursorPosX(10);
            ColorDotRarity(sk.rarity);
            ImGui::SameLine();
            ImGui::PushStyleColor(ImGuiCol_Text, COL_TEXT_NORMAL);
            ImGui::TextUnformatted(sk.name.c_str());
            ImGui::PopStyleColor();

            if (!sk.collection.empty()) {
                ImVec2 colSz = ImGui::CalcTextSize(sk.collection.c_str());
                dl->AddText({ cpos.x + rw - colSz.x - 80, cpos.y + (22 - colSz.y) * 0.5f },
                    ToU32(COL_TEXT_MUTED), sk.collection.c_str());
            }

            ImVec4 rc = RarityColor(sk.rarity);
            const char* rl = RarityLabel(sk.rarity);
            ImVec2 rlSz = ImGui::CalcTextSize(rl);
            dl->AddText({ cpos.x + rw - rlSz.x - 22, cpos.y + (22 - rlSz.y) * 0.5f },
                ToU32(rc), rl);

            // arrow
            dl->AddText({ cpos.x + rw - 14, cpos.y + (22 - ImGui::GetTextLineHeight()) * 0.5f },
                ToU32({ 0.604f, 0.722f, 0.0f, 0.7f }), ">");

            dl->AddLine({ cpos.x, cpos.y + 22 }, { cpos.x + rw, cpos.y + 22 }, ToU32(COL_BORDER_FAINT));

            ImGui::SetCursorPosY(ImGui::GetCursorPosY() - ImGui::GetTextLineHeight() - 5);
            char btnId[64]; snprintf(btnId, sizeof(btnId), "##sk%d", si);
            ImGui::InvisibleButton(btnId, { rw, 22 });
            if (ImGui::IsItemClicked()) {
                m_state.skinModalOpen  = true;
                m_state.modalWeapon    = m_state.selectedWeapon;
                m_state.modalSkin      = si;
                m_state.modalFloat     = 12.0f;
                m_state.modalStattrak  = false;
                m_state.modalSlots     = { -1,-1,-1,-1 };
                m_state.modalSelSticker= -1;
                m_state.modalTab       = 0;
                memset(m_state.stickerSearch, 0, sizeof(m_state.stickerSearch));
            }
            si++;
        }
    }

    ImGui::EndChild();
    ImGui::PopStyleColor();
}

// ── Skin Modal ────────────────────────────────────────────────────────────────
void Menu::RenderSkinModal() {
    if (m_state.modalWeapon >= (int)m_weapons.size()) { m_state.skinModalOpen = false; return; }
    Weapon& w  = m_weapons[m_state.modalWeapon];
    if (m_state.modalSkin >= (int)w.skins.size())     { m_state.skinModalOpen = false; return; }
    Skin&   sk = w.skins[m_state.modalSkin];

    ImGuiIO& io = ImGui::GetIO();
    ImGui::SetNextWindowPos({ io.DisplaySize.x * 0.5f, io.DisplaySize.y * 0.5f },
        ImGuiCond_Always, { 0.5f, 0.5f });
    ImGui::SetNextWindowSize({ 680, 400 }, ImGuiCond_Always);
    ImGui::SetNextWindowBgAlpha(1.0f);

    ImGui::PushStyleColor(ImGuiCol_WindowBg, COL_BG_PANEL);
    ImGui::PushStyleColor(ImGuiCol_Border,   COL_BORDER);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, { 0.0f, 0.0f });
    ImGui::Begin("##modal", nullptr,
        ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove |
        ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar);
    ImGui::PopStyleVar();
    ImGui::PopStyleColor(2);

    ImDrawList* dl  = ImGui::GetWindowDrawList();
    ImVec2 mpos     = ImGui::GetWindowPos();
    float  mw       = 680.0f, mh = 400.0f;

    // Header bar
    dl->AddRectFilled(mpos, { mpos.x + mw, mpos.y + 32 }, ToU32(COL_BG_TITLEBAR));
    dl->AddLine({ mpos.x, mpos.y + 32 }, { mpos.x + mw, mpos.y + 32 }, ToU32(COL_BORDER));

    // weapon | skin name
    dl->AddText({ mpos.x + 10, mpos.y + 6 }, ToU32(COL_TEXT_DIM), "Skin Preview");
    std::string fullName = w.name + " | ";
    ImVec2 wnSz = ImGui::CalcTextSize(fullName.c_str());
    dl->AddText({ mpos.x + 10, mpos.y + 16 }, ToU32(COL_TEXT_BRIGHT), fullName.c_str());
    dl->AddText({ mpos.x + 10 + wnSz.x, mpos.y + 16 },
        ToU32(RarityColor(sk.rarity)), sk.name.c_str());

    // Close button
    ImGui::SetCursorPos({ mw - 36, 6 });
    ImGui::PushStyleColor(ImGuiCol_Button, COL_BG_SECTION);
    ImGui::PushStyleColor(ImGuiCol_Text,   COL_TEXT_DIM);
    if (ImGui::Button("x##close", { 24, 20 })) m_state.skinModalOpen = false;
    ImGui::PopStyleColor(2);

    // Left column (preview + float + apply)
    float leftW = 430.0f;
    ImGui::SetCursorPos({ 0, 32 });
    ImGui::PushStyleColor(ImGuiCol_ChildBg, COL_BG_PANEL);
    ImGui::BeginChild("##mleft", { leftW, mh - 32 }, false);

    // Fake preview area (colored gradient placeholder)
    ImVec2 prevPos = ImGui::GetCursorScreenPos();
    float prevH = 190.0f;
    ImVec4 rc = RarityColor(sk.rarity);
    dl->AddRectFilledMultiColor(prevPos,
        { prevPos.x + leftW, prevPos.y + prevH },
        ToU32({ 0.06f,0.06f,0.07f,1.0f }),
        ToU32({ rc.x*0.3f, rc.y*0.3f, rc.z*0.3f, 1.0f }),
        ToU32({ rc.x*0.15f,rc.y*0.15f,rc.z*0.15f,1.0f }),
        ToU32({ 0.06f,0.06f,0.07f,1.0f }));
    // Diagonal pattern for visual interest
    for (int i = 0; i < 12; i++) {
        float x = prevPos.x + i * 40.0f;
        dl->AddLine({ x, prevPos.y }, { x + prevH, prevPos.y + prevH },
            ToU32({ 1,1,1, 0.02f }), 1.0f);
    }
    // Weapon name large text
    ImVec2 wnBigSz = ImGui::CalcTextSize(w.name.c_str());
    dl->AddText(ImGui::GetFont(), 18.0f,
        { prevPos.x + (leftW - wnBigSz.x * 1.4f) * 0.5f, prevPos.y + prevH * 0.35f },
        ToU32({ 1,1,1,0.08f }), w.name.c_str());

    // Rarity badge
    dl->AddRectFilled(prevPos, { prevPos.x + 8, prevPos.y + prevH }, ToU32(rc));
    const char* rl = RarityLabel(sk.rarity);
    ImVec2 rlSz = ImGui::CalcTextSize(rl);
    dl->AddText({ prevPos.x + 16, prevPos.y + prevH - 22 }, ToU32(rc), rl);

    // StatTrak badge
    if (m_state.modalStattrak) {
        dl->AddText({ prevPos.x + leftW - 90, prevPos.y + prevH - 22 },
            ToU32({ 0.894f,0.682f,0.224f,1.0f }), "StatTrak\xe2\x84\xa2");
    }

    ImGui::Dummy({ leftW, prevH });

    // Float slider
    ImDrawList* dl2 = ImGui::GetWindowDrawList();
    ImVec2 sep1 = ImGui::GetCursorScreenPos();
    dl2->AddLine(sep1, { sep1.x + leftW, sep1.y }, ToU32(COL_BORDER_FAINT));
    ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 4);
    GsSlider("Float Value", &m_state.modalFloat, 0, 100, "%.0f", 130);

    // Float bar
    ImGui::SetCursorPosX(10);
    ImVec2 fbPos = ImGui::GetCursorScreenPos();
    float fbW = leftW - 130;
    float fbPct = m_state.modalFloat / 100.0f;
    ImVec4 fbCol = (m_state.modalFloat < 15) ? COL_GREEN
                 : (m_state.modalFloat < 38) ? ImVec4{0.753f,0.565f,0.125f,1.0f}
                 : COL_RED;
    dl2->AddRectFilled(fbPos, { fbPos.x + fbW, fbPos.y + 3 }, ToU32(COL_BG_INPUT));
    dl2->AddRectFilled(fbPos, { fbPos.x + fbW * fbPct, fbPos.y + 3 }, ToU32(fbCol));
    ImGui::Dummy({ fbW, 7 });
    ImGui::SameLine();
    const char* floatLbl = (m_state.modalFloat < 7) ? "Factory New"
        : (m_state.modalFloat < 15) ? "Minimal Wear"
        : (m_state.modalFloat < 38) ? "Field-Tested"
        : (m_state.modalFloat < 45) ? "Well-Worn" : "Battle-Scarred";
    ImGui::PushStyleColor(ImGuiCol_Text, fbCol);
    ImGui::TextUnformatted(floatLbl);
    ImGui::PopStyleColor();

    ImVec2 sep2 = ImGui::GetCursorScreenPos();
    dl2->AddLine(sep2, { sep2.x + leftW, sep2.y }, ToU32(COL_BORDER_FAINT));
    ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 2);

    // StatTrak checkbox
    bool st = m_state.modalStattrak;
    GsCheckbox("StatTrak\xe2\x84\xa2", &m_state.modalStattrak);

    // Apply button
    ImGui::SetCursorPos({ 10, ImGui::GetContentRegionAvail().y - 28 + ImGui::GetCursorPosY() });
    ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 6);
    ImGui::PushStyleColor(ImGuiCol_Button, COL_GREEN_GLOW);
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, { 0.604f,0.722f,0.0f,0.25f });
    ImGui::PushStyleColor(ImGuiCol_Text,   COL_GREEN);
    ImGui::PushStyleColor(ImGuiCol_Border, COL_GREEN_DIM);
    ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 1.0f);
    if (ImGui::Button("Apply Skin", { leftW - 20, 26 })) {
        AppliedEntry entry;
        entry.weapon     = w;
        entry.skin       = sk;
        entry.floatVal   = m_state.modalFloat;
        entry.stattrak   = m_state.modalStattrak;
        entry.stickerSlots = m_state.modalSlots;

        // replace if exists
        bool found = false;
        for (auto& a : m_state.applied) {
            if (a.weapon.id == w.id) { a = entry; found = true; break; }
        }
        if (!found) m_state.applied.push_back(entry);
        m_state.loadoutSel = -1; // reset so loadout auto-selects
        m_state.skinModalOpen = false;
    }
    ImGui::PopStyleVar();
    ImGui::PopStyleColor(4);

    ImGui::EndChild();
    ImGui::PopStyleColor();

    // Right column (stickers / charms)
    ImGui::SetCursorPos({ leftW, 32 });
    float rightW = mw - leftW;
    ImGui::PushStyleColor(ImGuiCol_ChildBg, COL_BG_PANEL);
    ImGui::BeginChild("##mright", { rightW, mh - 32 }, false);

    // Sub-tabs
    ImDrawList* dlr = ImGui::GetWindowDrawList();
    ImVec2 rpos = ImGui::GetWindowPos();
    dlr->AddLine({ rpos.x, rpos.y }, { rpos.x, rpos.y + mh }, ToU32(COL_BORDER_FAINT));

    const char* mtabs[] = { "Stickers", "Charms" };
    ImGui::SetCursorPos({ 0, 0 });
    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, { 0, 0 });
    for (int i = 0; i < 2; i++) {
        bool sel = (m_state.modalTab == i);
        ImVec2 tp = ImGui::GetCursorScreenPos();
        float tw = rightW / 2.0f;
        bool hov = ImGui::IsMouseHoveringRect(tp, { tp.x + tw, tp.y + 26 });
        ImVec2 tsz = ImGui::CalcTextSize(mtabs[i]);
        dlr->AddText({ tp.x + (tw - tsz.x) * 0.5f, tp.y + (26 - tsz.y) * 0.5f },
            sel ? ToU32(COL_GREEN) : ToU32(COL_TEXT_DIM), mtabs[i]);
        if (sel)
            dlr->AddLine({ tp.x, tp.y + 25 }, { tp.x + tw, tp.y + 25 }, ToU32(COL_GREEN), 2.0f);
        ImGui::InvisibleButton(mtabs[i], { tw, 26 });
        if (ImGui::IsItemClicked()) m_state.modalTab = i;
        ImGui::SameLine();
    }
    ImGui::PopStyleVar();
    ImGui::NewLine();
    ImVec2 subSep = ImGui::GetCursorScreenPos();
    dlr->AddLine(subSep, { subSep.x + rightW, subSep.y }, ToU32(COL_BORDER_FAINT));

    if (m_state.modalTab == 0) {
        // Sticker slots
        ImGui::SetCursorPosX(8);
        ImGui::PushStyleColor(ImGuiCol_Text, COL_TEXT_DIM);
        ImGui::TextUnformatted("Sticker Slots");
        ImGui::PopStyleColor();

        ImGui::SetCursorPosX(8);
        float slotW = (rightW - 20) / 4.0f - 3;
        for (int i = 0; i < 4; i++) {
            int idx = m_state.modalSlots[i];
            ImVec2 sp2 = ImGui::GetCursorScreenPos();
            bool hov2 = ImGui::IsMouseHoveringRect(sp2, { sp2.x + slotW, sp2.y + 30 });
            ImU32 bg = (idx >= 0) ? ToU32(COL_GREEN_GLOW) : ToU32(COL_BG_INPUT);
            ImU32 br = (idx >= 0) ? ToU32(COL_GREEN_DIM) : ToU32(COL_BORDER);
            dlr->AddRectFilled(sp2, { sp2.x + slotW, sp2.y + 30 }, bg);
            dlr->AddRect(sp2, { sp2.x + slotW, sp2.y + 30 }, br);
            char slotLbl[32];
            if (idx >= 0 && idx < (int)m_stickers.size())
                snprintf(slotLbl, sizeof(slotLbl), "%.8s", m_stickers[idx].name.c_str());
            else
                snprintf(slotLbl, sizeof(slotLbl), "S%d", i+1);
            ImVec2 slSz = ImGui::CalcTextSize(slotLbl);
            dlr->AddText({ sp2.x + (slotW - slSz.x) * 0.5f, sp2.y + (30 - slSz.y) * 0.5f },
                idx >= 0 ? ToU32(COL_GREEN) : ToU32(COL_TEXT_MUTED), slotLbl);
            ImGui::Dummy({ slotW, 30 });
            if (ImGui::IsItemClicked() && idx >= 0) m_state.modalSlots[i] = -1;
            if (i < 3) ImGui::SameLine(0, 3);
        }

        // Apply / Clear buttons
        ImGui::SetCursorPosX(8);
        ImGui::PushStyleColor(ImGuiCol_Button, COL_GREEN_GLOW);
        ImGui::PushStyleColor(ImGuiCol_Text, COL_GREEN);
        float bw = (rightW - 20) / 2.0f;
        if (ImGui::Button("Apply##st", { bw, 20 }) && m_state.modalSelSticker >= 0) {
            for (int i = 0; i < 4; i++) {
                if (m_state.modalSlots[i] < 0) { m_state.modalSlots[i] = m_state.modalSelSticker; break; }
            }
        }
        ImGui::PopStyleColor(2);
        ImGui::SameLine(0, 4);
        ImGui::PushStyleColor(ImGuiCol_Button, { 0.180f*0.5f,0.06f,0.06f,1.0f });
        ImGui::PushStyleColor(ImGuiCol_Text, COL_RED);
        if (ImGui::Button("Clear##st", { bw, 20 })) m_state.modalSlots = { -1,-1,-1,-1 };
        ImGui::PopStyleColor(2);

        // Wear slider
        GsSliderInt("Wear", &m_state.modalWear, 0, 100, "%d%%", 80);

        // Sticker search
        ImGui::SetCursorPosX(6);
        ImGui::SetNextItemWidth(rightW - 12);
        ImGui::PushStyleColor(ImGuiCol_FrameBg, COL_BG_INPUT);
        ImGui::InputText("##stsearch", m_state.stickerSearch, sizeof(m_state.stickerSearch));
        ImGui::PopStyleColor();
        ImVec2 stSep = ImGui::GetCursorScreenPos();
        dlr->AddLine(stSep, { stSep.x + rightW, stSep.y }, ToU32(COL_BORDER_FAINT));

        // Sticker list
        std::string stFilter = m_state.stickerSearch;
        std::transform(stFilter.begin(), stFilter.end(), stFilter.begin(), ::tolower);

        int si = 0;
        for (auto& st : m_stickers) {
            std::string sn = st.name;
            std::string snl = sn; std::transform(snl.begin(),snl.end(),snl.begin(),::tolower);
            if (!stFilter.empty() && snl.find(stFilter) == std::string::npos) { si++; continue; }

            bool sel = (m_state.modalSelSticker == si);
            ImVec2 cp = ImGui::GetCursorScreenPos();
            float rw2 = rightW;
            bool hov2 = ImGui::IsMouseHoveringRect(cp, { cp.x + rw2, cp.y + 20 });
            if (sel || hov2)
                dlr->AddRectFilled(cp, { cp.x + rw2, cp.y + 20 },
                    sel ? ToU32({ 0.180f,0.180f,0.196f,1.0f }) : ToU32(COL_BG_HOVER));

            ImGui::SetCursorPosX(6);
            ColorDotRarity(st.rarity, 6);
            ImGui::SameLine();
            ImGui::PushStyleColor(ImGuiCol_Text, sel ? COL_TEXT_BRIGHT : COL_TEXT_NORMAL);
            ImGui::TextUnformatted(st.name.c_str());
            ImGui::PopStyleColor();

            dlr->AddLine({ cp.x, cp.y + 20 }, { cp.x + rw2, cp.y + 20 }, ToU32(COL_BORDER_FAINT));
            ImGui::SetCursorPosY(ImGui::GetCursorPosY() - ImGui::GetTextLineHeight() - 4);
            char bid[32]; snprintf(bid, sizeof(bid), "##sti%d", si);
            ImGui::InvisibleButton(bid, { rw2, 20 });
            if (ImGui::IsItemClicked()) m_state.modalSelSticker = si;
            si++;
        }
    } else {
        // Charm position slider
        GsSlider("Position", &m_state.modalCharmPos, 0, 100, "%.0f%%", 80);

        // Position visualiser
        ImGui::SetCursorPosX(8);
        ImVec2 pvPos = ImGui::GetCursorScreenPos();
        float pvW = rightW - 16;
        dlr->AddRectFilled(pvPos, { pvPos.x + pvW, pvPos.y + 18 }, ToU32(COL_BG_INPUT));
        dlr->AddRect(pvPos, { pvPos.x + pvW, pvPos.y + 18 }, ToU32(COL_BORDER));
        // track
        float tx1 = pvPos.x + pvW * 0.04f, tx2 = pvPos.x + pvW * 0.96f;
        float ty2 = pvPos.y + 9;
        dlr->AddLine({ tx1, ty2 }, { tx2, ty2 }, ToU32(COL_BG_SECTION), 2);
        // thumb
        float thumb = tx1 + (tx2 - tx1) * (m_state.modalCharmPos / 100.0f);
        dlr->AddCircleFilled({ thumb, ty2 }, 5.0f, ToU32(COL_GREEN));
        ImGui::Dummy({ pvW, 18 });

        ImVec2 cSep = ImGui::GetCursorScreenPos();
        dlr->AddLine(cSep, { cSep.x + rightW, cSep.y }, ToU32(COL_BORDER_FAINT));

        // Charm list
        int ci = 0;
        for (auto& ch : m_charms) {
            bool sel = (m_state.modalSelCharm == ci);
            ImVec2 cp = ImGui::GetCursorScreenPos();
            float rw3 = rightW;
            bool hov3 = ImGui::IsMouseHoveringRect(cp, { cp.x + rw3, cp.y + 20 });
            if (sel || hov3)
                dlr->AddRectFilled(cp, { cp.x + rw3, cp.y + 20 },
                    sel ? ToU32({ 0.180f,0.180f,0.196f,1.0f }) : ToU32(COL_BG_HOVER));

            ImGui::SetCursorPosX(6);
            ColorDot(sel);
            ImGui::SameLine();
            ImGui::PushStyleColor(ImGuiCol_Text, sel ? COL_TEXT_BRIGHT : COL_TEXT_NORMAL);
            ImGui::TextUnformatted(ch.name.c_str());
            ImGui::PopStyleColor();

            ImVec4 crc = RarityColor(ch.rarity);
            ImVec2 rSz = ImGui::CalcTextSize(ch.rarity == Rarity::Gold ? "gold" : RarityLabel(ch.rarity));
            dlr->AddText({ cp.x + rw3 - rSz.x - 8, cp.y + (20 - rSz.y) * 0.5f },
                ToU32(crc), RarityLabel(ch.rarity));
            dlr->AddLine({ cp.x, cp.y + 20 }, { cp.x + rw3, cp.y + 20 }, ToU32(COL_BORDER_FAINT));

            ImGui::SetCursorPosY(ImGui::GetCursorPosY() - ImGui::GetTextLineHeight() - 4);
            char bid[32]; snprintf(bid, sizeof(bid), "##chi%d", ci);
            ImGui::InvisibleButton(bid, { rw3, 20 });
            if (ImGui::IsItemClicked()) m_state.modalSelCharm = ci;
            ci++;
        }

        // Apply / Remove
        ImGui::SetCursorPosX(8);
        float bw2 = (rightW - 20) / 2.0f;
        ImGui::PushStyleColor(ImGuiCol_Button, COL_GREEN_GLOW);
        ImGui::PushStyleColor(ImGuiCol_Text, COL_GREEN);
        ImGui::Button("Apply##ch", { bw2, 22 });
        ImGui::PopStyleColor(2);
        ImGui::SameLine(0, 4);
        ImGui::PushStyleColor(ImGuiCol_Button, { 0.06f,0.03f,0.03f,1.0f });
        ImGui::PushStyleColor(ImGuiCol_Text, COL_RED);
        ImGui::Button("Remove##ch", { bw2, 22 });
        ImGui::PopStyleColor(2);
    }

    ImGui::EndChild();
    ImGui::PopStyleColor();

    // click outside to close
    if (ImGui::IsMouseClicked(0) && !ImGui::IsWindowHovered(ImGuiHoveredFlags_AnyWindow))
        m_state.skinModalOpen = false;

    ImGui::End();
}

// ── Loadout Tab ───────────────────────────────────────────────────────────────
void Menu::RenderLoadoutTab() {
    ImDrawList* dl = ImGui::GetWindowDrawList();
    float panelH   = ImGui::GetContentRegionAvail().y;
    float listW    = 230.0f;
    float previewW = ImGui::GetContentRegionAvail().x - listW;

    // ── Left: applied skin list ──────────────────────────────────────────────
    ImGui::PushStyleColor(ImGuiCol_ChildBg, COL_BG_WINDOW);
    ImGui::BeginChild("##llist", { listW, panelH }, false);
    ImVec2 llpos = ImGui::GetWindowPos();

    // Header
    dl->AddRectFilled(llpos, { llpos.x + listW, llpos.y + 28 }, ToU32(COL_BG_TITLEBAR));
    dl->AddLine({ llpos.x, llpos.y + 28 }, { llpos.x + listW, llpos.y + 28 }, ToU32(COL_BORDER));

    ImGui::SetCursorPos({ 10, 7 });
    ImGui::PushStyleColor(ImGuiCol_Text, COL_TEXT_BRIGHT);
    ImGui::TextUnformatted("Applied Skins");
    ImGui::PopStyleColor();
    char cntBuf[32]; snprintf(cntBuf, sizeof(cntBuf), "%d equipped", (int)m_state.applied.size());
    ImVec2 cntSz = ImGui::CalcTextSize(cntBuf);
    dl->AddText({ llpos.x + listW - cntSz.x - 8, llpos.y + 8 }, ToU32(COL_TEXT_MUTED), cntBuf);
    ImGui::SetCursorPosY(28);

    if (m_state.applied.empty()) {
        ImGui::SetCursorPosY(panelH * 0.4f);
        ImVec2 msg = ImGui::CalcTextSize("No skins applied yet.");
        ImGui::SetCursorPosX((listW - msg.x) * 0.5f);
        ImGui::PushStyleColor(ImGuiCol_Text, COL_TEXT_MUTED);
        ImGui::TextUnformatted("No skins applied yet.");
        ImGui::SetCursorPosX(0);
        ImVec2 msg2 = ImGui::CalcTextSize("Use the Skins tab.");
        ImGui::SetCursorPosX((listW - msg2.x) * 0.5f);
        ImGui::TextUnformatted("Use the Skins tab.");
        ImGui::PopStyleColor();
    }

    // Sort by category order
    static const char* CAT_ORDER[] = {
        "Rifle","Pistol","SMG","Shotgun","Sniper","Machine Gun","Knife","Gloves"
    };
    std::vector<const AppliedEntry*> sorted;
    for (auto& e : m_state.applied) sorted.push_back(&e);
    std::sort(sorted.begin(), sorted.end(), [](const AppliedEntry* a, const AppliedEntry* b) {
        int ai = 99, bi = 99;
        for (int i = 0; i < 8; i++) {
            if (a->weapon.category == CAT_ORDER[i]) ai = i;
            if (b->weapon.category == CAT_ORDER[i]) bi = i;
        }
        return ai < bi;
    });

    int ei = 0;
    for (auto* ep : sorted) {
        auto& e = *ep;
        bool sel = (m_state.loadoutSel == ei);
        ImVec2 cp = ImGui::GetCursorScreenPos();
        float rw = listW;
        float rh = 34.0f;
        bool hov = ImGui::IsMouseHoveringRect(cp, { cp.x + rw, cp.y + rh });

        if (sel)
            dl->AddRectFilled(cp, { cp.x + rw, cp.y + rh }, ToU32({ 0.165f,0.165f,0.196f,1.0f }));
        else if (hov)
            dl->AddRectFilled(cp, { cp.x + rw, cp.y + rh }, ToU32(COL_BG_HOVER));

        // rarity bar
        ImVec4 rc = RarityColor(e.skin.rarity);
        dl->AddRectFilled(cp, { cp.x + 3, cp.y + rh }, ToU32({ rc.x, rc.y, rc.z, 0.8f }));

        // weapon name
        ImGui::SetCursorPos({ 12, ImGui::GetCursorPosY() + 5 });
        ImGui::PushStyleColor(ImGuiCol_Text, sel ? COL_TEXT_BRIGHT : COL_TEXT_NORMAL);
        ImGui::TextUnformatted(e.weapon.name.c_str());
        ImGui::PopStyleColor();

        // skin name + stattrak
        ImGui::SetCursorPos({ 12, ImGui::GetCursorPosY() });
        std::string skinLine = (e.stattrak ? "ST\xe2\x84\xa2 " : "");
        ImGui::PushStyleColor(ImGuiCol_Text, RarityColor(e.skin.rarity));
        ImGui::TextUnformatted((skinLine + e.skin.name).c_str());
        ImGui::PopStyleColor();

        // float label right
        ImVec2 flSz = ImGui::CalcTextSize(e.FloatShort());
        dl->AddText({ cp.x + rw - flSz.x - 22, cp.y + (rh - flSz.y) * 0.5f },
            ToU32(COL_TEXT_MUTED), e.FloatShort());

        // remove button
        char xid[32]; snprintf(xid, sizeof(xid), "x##rm%d", ei);
        ImGui::SetCursorPos({ listW - 18, ImGui::GetCursorPosY() - ImGui::GetTextLineHeight() * 2 - 4 });
        ImGui::PushStyleColor(ImGuiCol_Button, { 0,0,0,0 });
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, { 0,0,0,0 });
        ImGui::PushStyleColor(ImGuiCol_Text, COL_TEXT_MUTED);
        if (ImGui::Button(xid, { 16, rh })) {
            std::string wid = e.weapon.id;
            m_state.applied.erase(std::remove_if(m_state.applied.begin(), m_state.applied.end(),
                [&](const AppliedEntry& a){ return a.weapon.id == wid; }), m_state.applied.end());
            if (m_state.loadoutSel == ei) m_state.loadoutSel = -1;
        }
        ImGui::PopStyleColor(3);

        // row hit area
        ImGui::SetCursorPosY(ImGui::GetCursorPosY());
        dl->AddLine({ cp.x, cp.y + rh }, { cp.x + rw, cp.y + rh }, ToU32(COL_BORDER_FAINT));

        // invisible select area
        ImGui::SetCursorPos({ 0, cp.y - llpos.y });
        ImGui::InvisibleButton(("##el" + e.weapon.id).c_str(), { listW - 18, rh });
        if (ImGui::IsItemClicked()) m_state.loadoutSel = ei;
        ei++;
    }

    ImGui::EndChild();
    ImGui::PopStyleColor();

    // Vertical divider
    ImVec2 divPos = ImGui::GetWindowPos();
    dl->AddLine({ divPos.x + listW, divPos.y },
                { divPos.x + listW, divPos.y + panelH }, ToU32(COL_BORDER_FAINT));
    ImGui::SameLine();

    // ── Right: preview panel ─────────────────────────────────────────────────
    const AppliedEntry* sel = nullptr;
    if (m_state.loadoutSel >= 0 && m_state.loadoutSel < (int)sorted.size())
        sel = sorted[m_state.loadoutSel];
    else if (!sorted.empty())
        sel = sorted[0];

    ImGui::PushStyleColor(ImGuiCol_ChildBg, COL_BG_WINDOW);
    ImGui::BeginChild("##lpreview", { previewW, panelH }, false);
    ImVec2 pvWpos = ImGui::GetWindowPos();

    if (!sel) {
        ImVec2 msg = ImGui::CalcTextSize("Select a skin to preview");
        ImGui::SetCursorPos({ (previewW - msg.x) * 0.5f, panelH * 0.45f });
        ImGui::PushStyleColor(ImGuiCol_Text, COL_TEXT_MUTED);
        ImGui::TextUnformatted("Select a skin to preview");
        ImGui::PopStyleColor();
    } else {
        // Hero image area
        float heroH = 180.0f;
        ImVec2 hp   = pvWpos;
        ImVec4 rc   = RarityColor(sel->skin.rarity);

        dl->AddRectFilledMultiColor(hp, { hp.x + previewW, hp.y + heroH },
            ToU32({ 0.05f,0.05f,0.06f,1.0f }),
            ToU32({ rc.x*0.35f,rc.y*0.35f,rc.z*0.35f,1.0f }),
            ToU32({ rc.x*0.18f,rc.y*0.18f,rc.z*0.18f,1.0f }),
            ToU32({ 0.05f,0.05f,0.06f,1.0f }));
        // Diagonal lines
        for (int i = 0; i < 10; i++) {
            float x = hp.x + i * 60.0f;
            dl->AddLine({ x, hp.y }, { x + heroH, hp.y + heroH }, ToU32({ 1,1,1,0.02f }));
        }
        // Gradient overlay
        dl->AddRectFilledMultiColor(hp, { hp.x + previewW, hp.y + heroH },
            ToU32({ 0,0,0,0 }), ToU32({ 0,0,0,0 }),
            ToU32({ 0.05f,0.05f,0.06f,0.92f }), ToU32({ 0.05f,0.05f,0.06f,0.92f }));

        // Rarity badge
        const char* rl = RarityLabel(sel->skin.rarity);
        dl->AddRectFilled(hp, { hp.x + 6, hp.y + heroH }, ToU32(rc));
        dl->AddCircleFilled({ hp.x + 18, hp.y + 14 }, 4.0f, ToU32(rc));
        dl->AddText({ hp.x + 26, hp.y + 8 }, ToU32(rc), rl);

        if (sel->stattrak)
            dl->AddText({ hp.x + previewW - 80, hp.y + 8 },
                ToU32({ 0.894f,0.682f,0.224f,1.0f }), "StatTrak\xe2\x84\xa2");

        // Title
        float tby = hp.y + heroH - 46;
        ImVec2 catSz = ImGui::CalcTextSize(sel->weapon.category.c_str());
        dl->AddText({ hp.x + 14, tby }, ToU32(COL_TEXT_DIM), sel->weapon.category.c_str());
        dl->AddText(ImGui::GetFont(), 16.0f,
            { hp.x + 14, tby + catSz.y + 2 }, ToU32(COL_TEXT_BRIGHT), sel->weapon.name.c_str());
        std::string skinTitle = "| " + sel->skin.name;
        ImVec2 wnSz = ImGui::CalcTextSize(sel->weapon.name.c_str());
        dl->AddText({ hp.x + 14, tby + catSz.y + 22 }, ToU32(rc), skinTitle.c_str());

        ImGui::Dummy({ previewW, heroH });

        // Float bar
        ImVec2 fbSep = ImGui::GetCursorScreenPos();
        dl->AddLine(fbSep, { fbSep.x + previewW, fbSep.y }, ToU32(COL_BORDER_FAINT));
        ImGui::SetCursorPos({ 14, ImGui::GetCursorPosY() + 8 });

        ImGui::PushStyleColor(ImGuiCol_Text, COL_TEXT_DIM);
        ImGui::Text("Float Value");
        ImGui::PopStyleColor();
        ImGui::SameLine(previewW - 100);
        ImGui::PushStyleColor(ImGuiCol_Text, sel->FloatColor());
        ImGui::TextUnformatted(sel->FloatLabel());
        ImGui::PopStyleColor();

        ImGui::SetCursorPosX(14);
        ImVec2 barp = ImGui::GetCursorScreenPos();
        float bw = previewW - 28;
        float pct = sel->floatVal / 100.0f;
        dl->AddRectFilled(barp, { barp.x + bw, barp.y + 4 }, ToU32(COL_BG_SECTION));
        dl->AddRectFilled(barp, { barp.x + bw * pct, barp.y + 4 }, ToU32(sel->FloatColor()));
        ImGui::Dummy({ bw, 8 });

        // FN / FT / BS labels
        ImGui::SetCursorPosX(14);
        ImGui::PushStyleColor(ImGuiCol_Text, COL_GREEN);       ImGui::Text("FN"); ImGui::PopStyleColor();
        ImGui::SameLine((previewW - 28) * 0.5f);
        ImGui::PushStyleColor(ImGuiCol_Text, { 0.753f,0.565f,0.125f,1.0f }); ImGui::Text("FT"); ImGui::PopStyleColor();
        ImGui::SameLine(previewW - 40);
        ImGui::PushStyleColor(ImGuiCol_Text, COL_RED);         ImGui::Text("BS"); ImGui::PopStyleColor();

        ImVec2 metaSep = ImGui::GetCursorScreenPos();
        dl->AddLine(metaSep, { metaSep.x + previewW, metaSep.y }, ToU32(COL_BORDER_FAINT));
        ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 6);

        // Sticker slots
        ImGui::SetCursorPosX(14);
        ImGui::PushStyleColor(ImGuiCol_Text, COL_TEXT_DIM); ImGui::Text("Sticker Slots"); ImGui::PopStyleColor();
        ImGui::SetCursorPosX(14);
        float slotW2 = (previewW - 28) / 4.0f - 3;
        for (int i = 0; i < 4; i++) {
            int idx = sel->stickerSlots[i];
            ImVec2 sp2 = ImGui::GetCursorScreenPos();
            ImU32 bg = (idx >= 0) ? ToU32(COL_GREEN_GLOW) : ToU32(COL_BG_INPUT);
            ImU32 br = (idx >= 0) ? ToU32(COL_GREEN_DIM) : ToU32(COL_BORDER);
            dl->AddRectFilled(sp2, { sp2.x + slotW2, sp2.y + 44 }, bg);
            dl->AddRect(sp2, { sp2.x + slotW2, sp2.y + 44 }, br);
            if (idx >= 0 && idx < (int)m_stickers.size()) {
                ImVec4 sc = RarityColor(m_stickers[idx].rarity);
                dl->AddRectFilled({ sp2.x + slotW2/2 - 3, sp2.y + 8 },
                    { sp2.x + slotW2/2 + 3, sp2.y + 14 }, ToU32(sc));
                ImVec2 nmSz = ImGui::CalcTextSize(m_stickers[idx].name.c_str());
                // truncated name
                std::string stn = m_stickers[idx].name;
                if (stn.size() > 8) stn = stn.substr(0,7) + ".";
                ImVec2 snSz = ImGui::CalcTextSize(stn.c_str());
                dl->AddText({ sp2.x + (slotW2 - snSz.x) * 0.5f, sp2.y + 18 },
                    ToU32(COL_TEXT_DIM), stn.c_str());
            } else {
                char slbl[8]; snprintf(slbl, sizeof(slbl), "S%d", i+1);
                ImVec2 slSz = ImGui::CalcTextSize(slbl);
                dl->AddText({ sp2.x + (slotW2 - slSz.x) * 0.5f, sp2.y + (44 - slSz.y) * 0.5f },
                    ToU32(COL_TEXT_MUTED), slbl);
            }
            ImGui::Dummy({ slotW2, 44 });
            if (i < 3) ImGui::SameLine(0, 3);
        }

        // Meta grid
        ImVec2 mgSep = ImGui::GetCursorScreenPos();
        dl->AddLine(mgSep, { mgSep.x + previewW, mgSep.y }, ToU32(COL_BORDER_FAINT));
        ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 8);

        auto MetaItem = [&](const char* lbl, const char* val, ImVec4 valCol = COL_TEXT_NORMAL) {
            ImGui::SetCursorPosX(14);
            ImGui::PushStyleColor(ImGuiCol_Text, COL_TEXT_MUTED); ImGui::Text("%s", lbl); ImGui::PopStyleColor();
            ImGui::SameLine();
            ImGui::PushStyleColor(ImGuiCol_Text, valCol); ImGui::Text("%s", val); ImGui::PopStyleColor();
        };

        char fbuf[32]; snprintf(fbuf, sizeof(fbuf), "%.0f / 100", sel->floatVal);
        MetaItem("Float:    ", fbuf, sel->FloatColor());
        MetaItem("Condition:", sel->FloatLabel());
        MetaItem("StatTrak: ", sel->stattrak ? "Enabled" : "Disabled",
            sel->stattrak ? ImVec4{0.894f,0.682f,0.224f,1.0f} : COL_TEXT_DIM);
        int stCnt = 0; for (auto s : sel->stickerSlots) if (s >= 0) stCnt++;
        char scBuf[16]; snprintf(scBuf, sizeof(scBuf), "%d / 4", stCnt);
        MetaItem("Stickers: ", scBuf);
        if (!sel->skin.collection.empty())
            MetaItem("Collection:", sel->skin.collection.c_str());
    }

    ImGui::EndChild();
    ImGui::PopStyleColor();
}

// ── Visuals Tab ───────────────────────────────────────────────────────────────
void Menu::RenderVisualsTab() {
    float colW = ImGui::GetContentRegionAvail().x / 2.0f;
    float panelH = ImGui::GetContentRegionAvail().y;

    // Left column
    ImGui::PushStyleColor(ImGuiCol_ChildBg, COL_BG_WINDOW);
    ImGui::BeginChild("##vl", { colW, panelH }, false);

    SectionHeader("Player ESP");
    GsCheckbox("Health bar",        &m_state.healthBar);
    GsCheckbox("Name",              &m_state.playerName);
    GsCheckbox("Flags",             &m_state.playerFlags);
    GsCheckbox("Weapon text",       &m_state.weaponText);
    GsCheckbox("Weapon icon",       &m_state.weaponIcon);
    GsCheckbox("Ammo",              &m_state.ammo);
    GsCheckbox("Distance",          &m_state.distance);
    GsCheckbox("Glow",              &m_state.glow, &m_state.glowColor);
    GsCheckbox("Hit marker",        &m_state.hitMarker);
    GsCheckbox("Hit marker sound",  &m_state.hitMarkerSound);
    GsCheckbox("Skeleton",          &m_state.skeleton);
    GsCheckbox("Out of FOV arrow",  &m_state.fovArrow);

    SectionHeader("Health Style");
    const char* hStyles[] = { "Bar","Text","Gradient bar","Cross" };
    for (int i = 0; i < 4; i++) if (RadioItem(hStyles[i], m_state.healthStyle == i)) m_state.healthStyle = i;

    SectionHeader("Name Style");
    const char* nStyles[] = { "Above box","Below box","On box","Fade" };
    for (int i = 0; i < 4; i++) if (RadioItem(nStyles[i], m_state.nameStyle == i)) m_state.nameStyle = i;

    SectionHeader("Effects");
    GsCheckbox("Remove flashbang effects", &m_state.removeFlash);
    GsCheckbox("Remove smoke grenades",    &m_state.removeSmoke);
    GsCheckbox("Remove fog",               &m_state.removeFog);
    GsCheckbox("Remove skybox",            &m_state.removeSkybox);
    GsCheckbox("Remove scope overlay",     &m_state.removeScopeOverlay);
    GsCheckbox("Night mode",               &m_state.nightMode);
    GsCheckbox("Full bright",              &m_state.fullBright);

    ImGui::EndChild();
    ImGui::PopStyleColor();

    // Divider
    ImDrawList* dl = ImGui::GetWindowDrawList();
    ImVec2 dp = ImGui::GetWindowPos();
    dl->AddLine({ dp.x + colW, dp.y }, { dp.x + colW, dp.y + panelH }, ToU32(COL_BORDER_FAINT));
    ImGui::SameLine();

    // Right column
    ImGui::PushStyleColor(ImGuiCol_ChildBg, COL_BG_WINDOW);
    ImGui::BeginChild("##vr", { colW, panelH }, false);

    SectionHeader("Other ESP");
    GsCheckbox("Radar",               &m_state.radar);
    GsCheckbox("Dropped weapons",     &m_state.droppedWeapons);
    GsCheckbox("Grenades",            &m_state.grenades);
    GsCheckbox("Inaccuracy overlay",  &m_state.inaccuracy);
    GsCheckbox("Recoil overlay",      &m_state.recoilOverlay);
    GsCheckbox("Crosshair",           &m_state.crosshair);
    GsCheckbox("Bomb",                &m_state.bomb);
    GsCheckbox("Grenade trajectory",  &m_state.grenadeTrajectory);
    GsCheckbox("Sound ESP",           &m_state.soundEsp);

    SectionHeader("Sound ESP Mode");
    const char* seModes[] = { "Rings","Bars","Arrows","Dots","Off" };
    for (int i = 0; i < 5; i++) if (RadioItem(seModes[i], m_state.soundEspMode == i)) m_state.soundEspMode = i;

    SectionHeader("Radar Style");
    const char* rModes[] = { "Classic","Minimal","Circle","Square","Off" };
    for (int i = 0; i < 5; i++) if (RadioItem(rModes[i], m_state.radarMode == i)) m_state.radarMode = i;

    SectionHeader("Chams");
    GsCheckbox("Player",               &m_state.playerCham,     &m_state.playerChamColor);
    GsCheckbox("Player behind wall",   &m_state.playerWallCham, &m_state.playerWallChamColor);
    GsCheckbox("Teammate",             &m_state.teammateCham);
    GsCheckbox("Teammate behind wall", &m_state.teammateWallCham);
    GsCheckbox("Local player",         &m_state.localCham);
    GsCheckbox("Local player arms",    &m_state.localArmsCham);

    ImGui::EndChild();
    ImGui::PopStyleColor();
}

// ── Misc Tab ──────────────────────────────────────────────────────────────────
void Menu::RenderMiscTab() {
    float colW   = ImGui::GetContentRegionAvail().x / 2.0f;
    float panelH = ImGui::GetContentRegionAvail().y;

    ImGui::PushStyleColor(ImGuiCol_ChildBg, COL_BG_WINDOW);
    ImGui::BeginChild("##ml", { colW, panelH }, false);

    SectionHeader("Movement");
    GsCheckbox("Bunny hop",   &m_state.bhop);
    GsCheckbox("Auto strafe", &m_state.autoStrafe);

    SectionHeader("Match");
    GsCheckbox("Auto accept",  &m_state.autoAccept);
    GsCheckbox("Reveal ranks", &m_state.revealRanks);

    SectionHeader("Region Forcer");
    GsCheckbox("Enable region forcer", &m_state.regionForcer);
    // Region dropdown
    const char* regions[] = {
        "Auto","US East","US West","EU West","EU North",
        "Asia","South America","Australia"
    };
    ImGui::SetCursorPosX(10);
    ImGui::PushStyleColor(ImGuiCol_FrameBg, COL_BG_INPUT);
    ImGui::SetNextItemWidth(colW - 20);
    ImGui::Combo("##region", &m_state.regionSel, regions, 8);
    ImGui::PopStyleColor();

    ImGui::EndChild();
    ImGui::PopStyleColor();

    ImDrawList* dl = ImGui::GetWindowDrawList();
    ImVec2 dp = ImGui::GetWindowPos();
    dl->AddLine({ dp.x + colW, dp.y }, { dp.x + colW, dp.y + panelH }, ToU32(COL_BORDER_FAINT));
    ImGui::SameLine();

    ImGui::PushStyleColor(ImGuiCol_ChildBg, COL_BG_WINDOW);
    ImGui::BeginChild("##mr", { colW, panelH }, false);

    SectionHeader("Appearance");
    GsCheckbox("Menu gradient",  &m_state.menuGradient, &m_state.menuGradientColor);
    bool menuColorOn = true;
    GsCheckbox("Menu color",     &menuColorOn, &m_state.menuColor);
    GsCheckbox("Spectator list", &m_state.spectatorList);
    GsCheckbox("Clan tag changer",&m_state.clanTag);

    ImGui::EndChild();
    ImGui::PopStyleColor();
}

// ── Configs Tab ───────────────────────────────────────────────────────────────
void Menu::RenderConfigsTab() {
    float listW  = 210.0f;
    float panelH = ImGui::GetContentRegionAvail().y;
    float detailW = ImGui::GetContentRegionAvail().x - listW;

    ImDrawList* dl = ImGui::GetWindowDrawList();

    // Config list
    ImGui::PushStyleColor(ImGuiCol_ChildBg, COL_BG_WINDOW);
    ImGui::BeginChild("##cfglist", { listW, panelH }, false);
    ImVec2 clpos = ImGui::GetWindowPos();

    dl->AddRectFilled(clpos, { clpos.x + listW, clpos.y + 28 }, ToU32(COL_BG_TITLEBAR));
    dl->AddLine({ clpos.x, clpos.y + 28 }, { clpos.x + listW, clpos.y + 28 }, ToU32(COL_BORDER));
    ImGui::SetCursorPos({ 10, 7 });
    ImGui::PushStyleColor(ImGuiCol_Text, COL_TEXT_BRIGHT); ImGui::TextUnformatted("Configs"); ImGui::PopStyleColor();
    char ctBuf[32]; snprintf(ctBuf, sizeof(ctBuf), "%d total", (int)m_state.configs.size());
    ImVec2 ctSz = ImGui::CalcTextSize(ctBuf);
    dl->AddText({ clpos.x + listW - ctSz.x - 8, clpos.y + 8 }, ToU32(COL_TEXT_DIM), ctBuf);
    ImGui::SetCursorPosY(28);

    for (int i = 0; i < (int)m_state.configs.size(); i++) {
        auto& cfg = m_state.configs[i];
        bool sel = (m_state.configSel == i);
        ImVec2 cp = ImGui::GetCursorScreenPos();
        float rh = 38.0f;
        bool hov = ImGui::IsMouseHoveringRect(cp, { cp.x + listW, cp.y + rh });

        if (sel) dl->AddRectFilled(cp, { cp.x + listW, cp.y + rh }, ToU32({ 0.173f,0.173f,0.196f,1.0f }));
        else if (hov) dl->AddRectFilled(cp, { cp.x + listW, cp.y + rh }, ToU32(COL_BG_HOVER));

        ImGui::SetCursorPosX(10);
        ColorDot(cfg.active);
        ImGui::SameLine();
        ImGui::PushStyleColor(ImGuiCol_Text, sel ? COL_TEXT_BRIGHT : COL_TEXT_NORMAL);
        ImGui::TextUnformatted(cfg.name.c_str());
        ImGui::PopStyleColor();
        ImGui::SetCursorPosX(22);
        ImGui::PushStyleColor(ImGuiCol_Text, COL_TEXT_MUTED);
        ImGui::TextUnformatted(cfg.modified.c_str());
        ImGui::PopStyleColor();

        if (cfg.active) {
            const char* act = "ACTIVE";
            ImVec2 aSz = ImGui::CalcTextSize(act);
            dl->AddRectFilled(
                { cp.x + listW - aSz.x - 14, cp.y + (rh - aSz.y - 4) * 0.5f },
                { cp.x + listW - 6, cp.y + (rh + aSz.y + 4) * 0.5f },
                ToU32({ 0.604f,0.722f,0.0f,0.08f }));
            dl->AddRect(
                { cp.x + listW - aSz.x - 14, cp.y + (rh - aSz.y - 4) * 0.5f },
                { cp.x + listW - 6, cp.y + (rh + aSz.y + 4) * 0.5f },
                ToU32({ 0.604f,0.722f,0.0f,0.3f }));
            dl->AddText(
                { cp.x + listW - aSz.x - 10, cp.y + (rh - aSz.y) * 0.5f },
                ToU32(COL_GREEN), act);
        }

        dl->AddLine({ cp.x, cp.y + rh }, { cp.x + listW, cp.y + rh }, ToU32(COL_BORDER_FAINT));
        ImGui::SetCursorPosY(cp.y - clpos.y);
        char bid[32]; snprintf(bid, sizeof(bid), "##cfg%d", i);
        ImGui::InvisibleButton(bid, { listW, rh });
        if (ImGui::IsItemClicked()) m_state.configSel = i;
    }

    ImGui::EndChild();
    ImGui::PopStyleColor();

    ImVec2 div = ImGui::GetWindowPos();
    dl->AddLine({ div.x + listW, div.y }, { div.x + listW, div.y + panelH }, ToU32(COL_BORDER_FAINT));
    ImGui::SameLine();

    // Detail panel
    ImGui::PushStyleColor(ImGuiCol_ChildBg, COL_BG_WINDOW);
    ImGui::BeginChild("##cfgdetail", { detailW, panelH }, false);
    ImVec2 cdpos = ImGui::GetWindowPos();

    // Header
    dl->AddLine(cdpos, { cdpos.x + detailW, cdpos.y }, ToU32(COL_BORDER_FAINT));
    ImGui::SetCursorPos({ 10, 7 });
    ImGui::PushStyleColor(ImGuiCol_Text, COL_TEXT_BRIGHT);
    ImGui::TextUnformatted("Config Manager");
    ImGui::PopStyleColor();

    // Flash message
    if (m_state.flashTimer > 0) {
        m_state.flashTimer -= ImGui::GetIO().DeltaTime;
        ImVec2 fSz = ImGui::CalcTextSize(m_state.flashMsg.c_str());
        dl->AddText({ cdpos.x + detailW - fSz.x - 10, cdpos.y + 7 },
            m_state.flashOk ? ToU32(COL_GREEN) : ToU32(COL_RED),
            m_state.flashMsg.c_str());
    }

    ImVec2 sep = ImGui::GetCursorScreenPos();
    dl->AddLine(sep, { sep.x + detailW, sep.y }, ToU32(COL_BORDER_FAINT));
    ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 6);

    auto Notify = [&](const char* msg, bool ok = true) {
        m_state.flashMsg   = msg;
        m_state.flashTimer = 2.2f;
        m_state.flashOk    = ok;
    };

    Config* active = (m_state.configSel < (int)m_state.configs.size())
        ? &m_state.configs[m_state.configSel] : nullptr;

    if (active) {
        // Selected config box
        ImGui::SetCursorPosX(10);
        ImVec2 boxPos = ImGui::GetCursorScreenPos();
        float  boxW   = detailW - 20;

        ImGui::PushStyleColor(ImGuiCol_Text, COL_TEXT_DIM);
        ImGui::TextUnformatted("Selected Config");
        ImGui::PopStyleColor();

        ImGui::SetCursorPosX(14);
        ColorDot(active->active);
        ImGui::SameLine();
        ImGui::PushStyleColor(ImGuiCol_Text, COL_TEXT_BRIGHT);
        ImGui::Text("%s", active->name.c_str());
        ImGui::PopStyleColor();

        ImGui::SetCursorPosX(14);
        ImGui::PushStyleColor(ImGuiCol_Text, COL_TEXT_DIM);
        ImGui::TextUnformatted(active->description.c_str());
        ImGui::PopStyleColor();

        ImGui::SetCursorPosX(14);
        ImGui::PushStyleColor(ImGuiCol_Text, COL_TEXT_MUTED);
        ImGui::Text("Created %s  Modified %s", active->created.c_str(), active->modified.c_str());
        ImGui::PopStyleColor();

        ImVec2 boxEnd = ImGui::GetCursorScreenPos();
        dl->AddRect(boxPos, { boxPos.x + boxW, boxEnd.y + 2 }, ToU32(COL_BORDER_FAINT));
        ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 8);
    }

    // Action buttons
    ImGui::SetCursorPosX(10);
    ImGui::PushStyleColor(ImGuiCol_Text, COL_TEXT_DIM);
    ImGui::TextUnformatted("Actions");
    ImGui::PopStyleColor();
    ImGui::SetCursorPosX(10);

    float bw = (detailW - 24) / 3.0f;

    ImGui::PushStyleColor(ImGuiCol_Button, COL_GREEN_GLOW);
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, { 0.604f,0.722f,0.0f,0.25f });
    ImGui::PushStyleColor(ImGuiCol_Text, COL_GREEN);
    if (ImGui::Button("Save##c", { bw, 24 }) && active) {
        active->modified = "2024-03-22";
        Notify(("Saved \"" + active->name + "\"").c_str());
    }
    ImGui::SameLine(0, 3);
    if (ImGui::Button("Load##c", { bw, 24 }) && active) {
        for (auto& c : m_state.configs) c.active = false;
        active->active = true;
        Notify(("Loaded \"" + active->name + "\"").c_str());
    }
    ImGui::PopStyleColor(3);
    ImGui::SameLine(0, 3);
    ImGui::PushStyleColor(ImGuiCol_Button, { 0.06f,0.03f,0.03f,1.0f });
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, { 0.10f,0.04f,0.04f,1.0f });
    ImGui::PushStyleColor(ImGuiCol_Text, COL_RED);
    if (ImGui::Button("Delete##c", { bw, 24 })) {
        if ((int)m_state.configs.size() > 1) {
            std::string nm = active ? active->name : "";
            m_state.configs.erase(m_state.configs.begin() + m_state.configSel);
            m_state.configSel = std::max(0, m_state.configSel - 1);
            Notify(("Deleted \"" + nm + "\"").c_str(), false);
        } else {
            Notify("Cannot delete last config", false);
        }
    }
    ImGui::PopStyleColor(3);

    ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 8);

    // Create new config
    ImVec2 newBoxPos = ImGui::GetCursorScreenPos();
    ImGui::SetCursorPosX(10);
    ImGui::PushStyleColor(ImGuiCol_Text, COL_TEXT_DIM);
    ImGui::TextUnformatted("Create New Config");
    ImGui::PopStyleColor();

    ImGui::SetCursorPosX(10);
    ImGui::SetNextItemWidth(detailW - 20);
    ImGui::PushStyleColor(ImGuiCol_FrameBg, COL_BG_INPUT);
    ImGui::InputTextWithHint("##newname", "Config name...", m_state.newCfgName, sizeof(m_state.newCfgName));
    ImGui::SetCursorPosX(10);
    ImGui::SetNextItemWidth(detailW - 20);
    ImGui::InputTextWithHint("##newdesc", "Description (optional)...", m_state.newCfgDesc, sizeof(m_state.newCfgDesc));
    ImGui::PopStyleColor();

    ImGui::SetCursorPosX(10);
    ImGui::PushStyleColor(ImGuiCol_Button, COL_GREEN_GLOW);
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, { 0.604f,0.722f,0.0f,0.25f });
    ImGui::PushStyleColor(ImGuiCol_Text, COL_GREEN);
    if (ImGui::Button("+ Create Config", { detailW - 20, 24 })) {
        if (m_state.newCfgName[0]) {
            std::string nm = m_state.newCfgName;
            std::string dc = m_state.newCfgDesc[0] ? m_state.newCfgDesc : "Custom config";
            m_state.configs.push_back({ nm, dc, "2024-03-22", "2024-03-22", false });
            m_state.configSel = (int)m_state.configs.size() - 1;
            memset(m_state.newCfgName, 0, sizeof(m_state.newCfgName));
            memset(m_state.newCfgDesc, 0, sizeof(m_state.newCfgDesc));
            Notify(("Created \"" + nm + "\"").c_str());
        } else {
            Notify("Name is required", false);
        }
    }
    ImGui::PopStyleColor(3);

    ImGui::EndChild();
    ImGui::PopStyleColor();
}

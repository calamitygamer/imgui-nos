#pragma once
#include <string>
#include <vector>

enum class Rarity { Consumer, Industrial, MilSpec, Restricted, Classified, Covert, Gold };

inline const char* RarityLabel(Rarity r) {
    switch (r) {
        case Rarity::Consumer:   return "Consumer";
        case Rarity::Industrial: return "Industrial";
        case Rarity::MilSpec:    return "Mil-Spec";
        case Rarity::Restricted: return "Restricted";
        case Rarity::Classified: return "Classified";
        case Rarity::Covert:     return "Covert";
        case Rarity::Gold:       return "Extraordinary";
    }
    return "";
}

inline ImVec4 RarityColor(Rarity r) {
    switch (r) {
        case Rarity::Consumer:   return { 0.690f, 0.765f, 0.851f, 1.0f };
        case Rarity::Industrial: return { 0.369f, 0.596f, 0.851f, 1.0f };
        case Rarity::MilSpec:    return { 0.294f, 0.412f, 1.000f, 1.0f };
        case Rarity::Restricted: return { 0.533f, 0.278f, 1.000f, 1.0f };
        case Rarity::Classified: return { 0.827f, 0.173f, 0.902f, 1.0f };
        case Rarity::Covert:     return { 0.922f, 0.294f, 0.294f, 1.0f };
        case Rarity::Gold:       return { 0.894f, 0.682f, 0.224f, 1.0f };
    }
    return { 1, 1, 1, 1 };
}

struct Skin {
    std::string name;
    Rarity      rarity;
    std::string collection;
};

struct Weapon {
    std::string         id;
    std::string         name;
    std::string         category;
    std::vector<Skin>   skins;
};

struct Sticker {
    std::string id;
    std::string name;
    Rarity      rarity;
};

struct Charm {
    std::string id;
    std::string name;
    Rarity      rarity;
};

// ── Weapon data ───────────────────────────────────────────────────────────────

inline std::vector<Weapon> BuildWeaponList() {
    return {
        { "ak47", "AK-47", "Rifle", {
            { "Howl",              Rarity::Covert,     "Huntsman"      },
            { "Fire Serpent",      Rarity::Covert,     "Bravo"         },
            { "Vulcan",            Rarity::Covert,     "Operation Bravo" },
            { "Gold Arabesque",    Rarity::Covert,     "Arabesque"     },
            { "Asiimov",           Rarity::Covert,     "Phoenix"       },
            { "Crane Flight",      Rarity::Classified, "Dead Hand"     },
            { "Wasteland Rebel",   Rarity::Classified, "Chroma 2"      },
            { "Neon Rider",        Rarity::Classified, "Spectrum"      },
            { "Case Hardened",     Rarity::Classified, "Bravo"         },
            { "Bloodsport",        Rarity::Classified, "Spectrum 2"    },
            { "Baroque Purple",    Rarity::Restricted, "Recoil"        },
            { "Emerald Pinstripe", Rarity::Restricted, "Recoil"        },
            { "Red Laminate",      Rarity::MilSpec,    "Bravo"         },
            { "Safari Mesh",       Rarity::Industrial, "Safehouse"     },
        }},
        { "m4a4", "M4A4", "Rifle", {
            { "Howl",          Rarity::Covert,     "Huntsman"   },
            { "Asiimov",       Rarity::Covert,     "Phoenix"    },
            { "Spider Lily",   Rarity::Covert,     "Anubis"     },
            { "The Emperor",   Rarity::Classified, "Ancient"    },
            { "Desolate Space",Rarity::Classified, "Horizon"    },
            { "Neo-Noir",      Rarity::Classified, "Riptide"    },
            { "Converter",     Rarity::Restricted, "Revolution" },
            { "In Living Color",Rarity::Restricted,"Spectrum 2" },
            { "X-Ray",         Rarity::MilSpec,    "Prisma"     },
            { "Tornado",       Rarity::Industrial, "Assault"    },
        }},
        { "m4a1s", "M4A1-S", "Rifle", {
            { "Hot Rod",         Rarity::Covert,     "Chroma"       },
            { "Printstream",     Rarity::Covert,     "Recoil"       },
            { "Hyper Beast",     Rarity::Covert,     "Falchion"     },
            { "Knight",          Rarity::Classified, "Chroma 3"     },
            { "Decimator",       Rarity::Classified, "Operation Hydra" },
            { "Leaded Glass",    Rarity::Classified, "Dreams & Nightmares" },
            { "Nightmare",       Rarity::Restricted, "Clutch"       },
            { "Cyrex",           Rarity::Restricted, "Chroma 2"     },
            { "Emphorosaur-S",   Rarity::MilSpec,    "Fracture"     },
        }},
        { "awp", "AWP", "Sniper", {
            { "Dragon Lore",     Rarity::Covert,     "Cobblestone"  },
            { "Medusa",          Rarity::Covert,     "Gods and Monsters" },
            { "Gungnir",         Rarity::Covert,     "Norse"        },
            { "Asiimov",         Rarity::Classified, "Phoenix"      },
            { "Hyper Beast",     Rarity::Classified, "Falchion"     },
            { "Man-o'-war",      Rarity::Classified, "The Armory"   },
            { "Wildfire",        Rarity::Classified, "Wildfire"     },
            { "Chromatic Aberration", Rarity::Restricted, "Chroma 2" },
            { "Electric Hive",   Rarity::Restricted, "Breakout"     },
            { "Fever Dream",     Rarity::MilSpec,    "Fever"        },
        }},
        { "ssg08", "SSG 08", "Sniper", {
            { "Blood in the Water", Rarity::Covert,  "Chroma"       },
            { "Dragonfire",       Rarity::Classified, "Gamma 2"     },
            { "Abyss",            Rarity::Restricted, "Chroma"      },
            { "Necropos",         Rarity::MilSpec,    "Anubis"      },
        }},
        { "deagle", "Desert Eagle", "Pistol", {
            { "Blaze",           Rarity::Classified, "Dust"         },
            { "Hand Cannon",     Rarity::Classified, "Bravo"        },
            { "Printstream",     Rarity::Classified, "Recoil"       },
            { "Hypnotic",        Rarity::Classified, "Cobblestone"  },
            { "Kumicho Dragon",  Rarity::Classified, "Dreams & Nightmares" },
            { "Fennec Fox",      Rarity::Restricted, "Fracture"     },
            { "Oxide Blaze",     Rarity::Restricted, "Chroma 2"     },
            { "Directive",       Rarity::MilSpec,    "Gamma"        },
            { "Urban Rubble",    Rarity::Industrial, "Dust 2"       },
        }},
        { "usps", "USP-S", "Pistol", {
            { "Kill Confirmed",  Rarity::Covert,     "Chroma 3"     },
            { "Neo-Noir",        Rarity::Covert,     "Riptide"      },
            { "Printstream",     Rarity::Classified, "Recoil"       },
            { "Orion",           Rarity::Classified, "Chroma"       },
            { "The Traitor",     Rarity::Restricted, "Recoil"       },
            { "Stainless",       Rarity::MilSpec,    "Chroma 2"     },
            { "Lead Conduit",    Rarity::Industrial, "Breakout"     },
        }},
        { "glock18", "Glock-18", "Pistol", {
            { "Fade",            Rarity::Classified, "Dust"         },
            { "Water Elemental", Rarity::Restricted, "Breakout"     },
            { "Bullet Queen",    Rarity::Restricted, "Operation Riptide" },
            { "Gamma Doppler",   Rarity::Restricted, "Gamma 2"      },
            { "Steel Disruption",Rarity::MilSpec,    "Revolution"   },
            { "Candy Apple",     Rarity::Industrial, "Italy"        },
        }},
        { "p250", "P250", "Pistol", {
            { "See Ya Later",    Rarity::Classified, "Fracture"     },
            { "Asiimov",         Rarity::Classified, "Gamma"        },
            { "Valence",         Rarity::Restricted, "Chroma 2"     },
            { "Facets",          Rarity::MilSpec,    "Revolution"   },
        }},
        { "mp5sd", "MP5-SD", "SMG", {
            { "Phosphor",        Rarity::Classified, "Dreams & Nightmares" },
            { "Liquidation",     Rarity::Classified, "Anubis"       },
            { "Oxide Oasis",     Rarity::Restricted, "Recoil"       },
            { "Nitro",           Rarity::Industrial, "Italy"        },
        }},
        { "mp9", "MP9", "SMG", {
            { "Wild Lily",       Rarity::Covert,     "Wildfire"     },
            { "Hydra",           Rarity::Classified, "Operation Hydra" },
            { "Rose Iron",       Rarity::Restricted, "Dreams & Nightmares" },
            { "Setting Sun",     Rarity::MilSpec,    "Inferno"      },
        }},
        { "mac10", "MAC-10", "SMG", {
            { "Neon Rider",      Rarity::Covert,     "Spectrum"     },
            { "Curse",           Rarity::Classified, "Clutch"       },
            { "Propaganda",      Rarity::Restricted, "Breakout"     },
            { "Oceanic",         Rarity::Industrial, "Horizon"      },
        }},
        { "nova", "Nova", "Shotgun", {
            { "Hyper Beast",     Rarity::Classified, "Falchion"     },
            { "Plume",           Rarity::Restricted, "Recoil"       },
            { "Clear Polymer",   Rarity::MilSpec,    "Spectrum"     },
            { "Forest Leaves",   Rarity::Industrial, "Safehouse"    },
        }},
        { "xm1014", "XM1014", "Shotgun", {
            { "Entombed",        Rarity::Classified, "Dreams & Nightmares" },
            { "Blue Steel",      Rarity::Restricted, "Arms Deal 3"  },
            { "Seasons",         Rarity::MilSpec,    "Chroma 2"     },
        }},
        { "negev", "Negev", "Machine Gun", {
            { "Power Loader",    Rarity::Classified, "Operation Hydra" },
            { "Lionfish",        Rarity::Restricted, "Gamma 2"      },
            { "Bratatat",        Rarity::Industrial, "Horizon"      },
        }},
        { "m249", "M249", "Machine Gun", {
            { "Spectre",         Rarity::Classified, "Fracture"     },
            { "Warbird",         Rarity::Restricted, "Huntsman"     },
            { "Aztec",           Rarity::Industrial, "Dust"         },
        }},
        { "karambit", "Karambit", "Knife", {
            { "Doppler",         Rarity::Gold,       ""             },
            { "Fade",            Rarity::Gold,       ""             },
            { "Tiger Tooth",     Rarity::Gold,       ""             },
            { "Marble Fade",     Rarity::Gold,       ""             },
            { "Crimson Web",     Rarity::Gold,       ""             },
            { "Case Hardened",   Rarity::Gold,       ""             },
            { "Night",           Rarity::Gold,       ""             },
            { "Lore",            Rarity::Gold,       ""             },
            { "Autotronic",      Rarity::Gold,       ""             },
            { "Black Laminate",  Rarity::Gold,       ""             },
            { "Rust Coat",       Rarity::Gold,       ""             },
        }},
        { "m9bayonet", "M9 Bayonet", "Knife", {
            { "Doppler",         Rarity::Gold,       ""             },
            { "Fade",            Rarity::Gold,       ""             },
            { "Tiger Tooth",     Rarity::Gold,       ""             },
            { "Marble Fade",     Rarity::Gold,       ""             },
            { "Crimson Web",     Rarity::Gold,       ""             },
            { "Night",           Rarity::Gold,       ""             },
            { "Lore",            Rarity::Gold,       ""             },
        }},
        { "butterfly", "Butterfly Knife", "Knife", {
            { "Doppler",         Rarity::Gold,       ""             },
            { "Fade",            Rarity::Gold,       ""             },
            { "Tiger Tooth",     Rarity::Gold,       ""             },
            { "Marble Fade",     Rarity::Gold,       ""             },
            { "Case Hardened",   Rarity::Gold,       ""             },
            { "Crimson Web",     Rarity::Gold,       ""             },
            { "Lore",            Rarity::Gold,       ""             },
        }},
        { "bayonet", "Bayonet", "Knife", {
            { "Doppler",         Rarity::Gold,       ""             },
            { "Fade",            Rarity::Gold,       ""             },
            { "Tiger Tooth",     Rarity::Gold,       ""             },
            { "Crimson Web",     Rarity::Gold,       ""             },
            { "Case Hardened",   Rarity::Gold,       ""             },
        }},
        { "gloves_sport", "Sport Gloves", "Gloves", {
            { "Pandora's Box",   Rarity::Gold,       "Gloves"       },
            { "Superconductor",  Rarity::Gold,       "Gloves"       },
            { "Hedge Maze",      Rarity::Gold,       "Gloves"       },
            { "Vice",            Rarity::Gold,       "Gloves"       },
            { "Amphibious",      Rarity::Gold,       "Gloves"       },
        }},
        { "gloves_driver", "Driver Gloves", "Gloves", {
            { "King Snake",      Rarity::Gold,       "Gloves"       },
            { "Lunar Weave",     Rarity::Gold,       "Gloves"       },
            { "Crimson Weave",   Rarity::Gold,       "Gloves"       },
            { "Black Tie",       Rarity::Gold,       "Gloves"       },
        }},
        { "gloves_specialist", "Specialist Gloves", "Gloves", {
            { "Crimson Kimono",  Rarity::Gold,       "Gloves"       },
            { "Marble Fade",     Rarity::Gold,       "Gloves"       },
            { "Tiger Strike",    Rarity::Gold,       "Gloves"       },
            { "Foundation",      Rarity::Gold,       "Gloves"       },
        }},
    };
}

// ── Sticker data ──────────────────────────────────────────────────────────────

inline std::vector<Sticker> BuildStickerList() {
    return {
        { "s_navi",        "Natus Vincere (Holo)",      Rarity::Classified },
        { "s_faze",        "FaZe Clan (Holo)",          Rarity::Classified },
        { "s_liquid",      "Team Liquid (Holo)",        Rarity::Classified },
        { "s_c9",          "Cloud9 (Gold)",             Rarity::Gold       },
        { "s_astralis",    "Astralis (Gold)",           Rarity::Gold       },
        { "s_vitality",    "Team Vitality (Holo)",      Rarity::Classified },
        { "s_g2",          "G2 Esports (Holo)",         Rarity::Classified },
        { "s_heroic",      "Heroic (Holo)",             Rarity::Classified },
        { "s_nlep",        "NAVI (Glitter)",            Rarity::Restricted },
        { "s_katowice14",  "Katowice 2014 Howling Dawn",Rarity::Gold       },
        { "s_crown_foil",  "Crown (Foil)",              Rarity::Classified },
        { "s_dragon_lore_holo","Dragon Lore (Holo)",    Rarity::Gold       },
        { "s_titan_holo",  "Titan (Holo) | Katowice 2014", Rarity::Gold   },
        { "s_ibp_holo",    "iBUYPOWER (Holo) | Katowice 2014", Rarity::Gold },
        { "s_skull",       "Skull",                     Rarity::MilSpec    },
        { "s_crosshairs",  "Crosshairs",                Rarity::MilSpec    },
        { "s_wanted",      "Wanted",                    Rarity::Restricted },
        { "s_notice_me",   "Notice Me",                 Rarity::Restricted },
        { "s_gg",          "GG",                        Rarity::Industrial },
        { "s_headshot",    "Headshot",                  Rarity::MilSpec    },
    };
}

// ── Charm data ────────────────────────────────────────────────────────────────

inline std::vector<Charm> BuildCharmList() {
    return {
        { "c_die",         "Die-cast AK",               Rarity::Gold       },
        { "c_ct",          "Die-cast CT",               Rarity::Gold       },
        { "c_t",           "Die-cast T",                Rarity::Gold       },
        { "c_bomb",        "Baby Karat CT",             Rarity::Classified },
        { "c_cherry",      "Cherry Blossom",            Rarity::Classified },
        { "c_four_leaf",   "Four-Leaf Clover",          Rarity::Restricted },
        { "c_hot_dog",     "Hot Dog",                   Rarity::Restricted },
        { "c_chicken",     "Baby Chicken",              Rarity::MilSpec    },
        { "c_storm",       "Storm Trooper",             Rarity::MilSpec    },
        { "c_octopus",     "Octopus",                   Rarity::MilSpec    },
        { "c_little_shell","Little Shell",              Rarity::Industrial },
        { "c_dice",        "Semi-Precious",             Rarity::Industrial },
    };
}
